/*
 * libMD407
 * asciidisplay_driver.c
 * Display connected to PE
 * Driver for ASCIIDISPLAY
 */
#include "libMD407.h"
#include <stdbool.h>

static int asciidisplay_init( int initval );
static void asciidisplay_deinit( int deinitval);
static int asciidisplay_write(char *ptr, int len);

DEV_DRIVER_DESC AsciiDisplay =
{
	{"AsciiDisplay"},
	asciidisplay_init,
	asciidisplay_deinit,
	0,
	0,
	0,
	0,
	0,
	asciidisplay_write,
	0
};

/* ASCIIDISPLAY types and constants definitions */
#define PORT_E 0x40021000
#define portModeR ((unsigned long *) PORT_E)
#define portOTypeR ((unsigned short *) (PORT_E + 0x4))
#define portSpeedR ((unsigned long *) (PORT_E + 0x8))
#define portPupdR ((unsigned long *) (PORT_E + 0xC))
#define portIdrLow ((volatile unsigned char *) (PORT_E + 0x10))
#define portIdrHigh ((volatile unsigned char *) (PORT_E + 0x11))
#define portOdrLow ((unsigned char *) (PORT_E + 0x14))
#define portOdrHigh ((unsigned char *) (PORT_E + 0x15))

#define SYS_TICK 0xE000E010
#define STK_CTRL ((volatile unsigned long *) (SYS_TICK))
#define STK_LOAD ((unsigned long *) (SYS_TICK + 0x4))
#define STK_VAL ((volatile unsigned long *) (SYS_TICK + 0x8))

#define B_E 0x40
#define B_SELECT 0x4
#define B_RW 0x2
#define B_RS 0x1

static bool useDoubleRows = false;
static bool secondRow = false;

/* Helper functions imported from Lab 2.3 */

// Causes a delay for n amount of cpu cycles
static void SleepNPulses(unsigned long cycles){
	*STK_CTRL = 0;
	*STK_LOAD = cycles;
	*STK_VAL = cycles;
	unsigned long mask = 0x10000;
	unsigned long temp = 0;
	*STK_CTRL = 0x5;
	
	do{
		temp = *STK_CTRL & mask;
	}while(!temp);
	
	*STK_CTRL = 0;
	return;
}

// Causes a delay for n amount of microseconds
static void SleepMicroSeconds(unsigned long microseconds){
	for(unsigned long i = 0; i < microseconds; i++){
		SleepNPulses(168);
	}
	return;
}

// Sets the selected bits to one in the control register
static void AsciiCtrlBitSet(unsigned char target){
	*portOdrLow |= target + B_SELECT;
}

// Sets the selected bits to zero in the control register
static void AsciiCrtlBitClear(unsigned char target){
	AsciiCtrlBitSet(B_SELECT);
	target = target * -1 - 1 ;
	*portOdrLow &= target;
}

// Writes any value to the data reigsters
static void AsciiWriteController(unsigned char value){
	SleepNPulses(7); // 40ns
	AsciiCtrlBitSet(B_E);
	*portOdrHigh = value;
	
	SleepNPulses(40); // 230ns
	AsciiCrtlBitClear(B_E);
	SleepNPulses(2); // 10ns
}

// Sends a command to the controller
static void AsciiWriteCmd(unsigned char command){
	AsciiCrtlBitClear(B_RS + B_RW);
	AsciiWriteController(command);
}

// Sends ASCII data to the controller
static void AsciiWriteData(unsigned char data){
	AsciiCrtlBitClear(B_RW);
	AsciiCtrlBitSet(B_RS);
	AsciiWriteController(data);
}

// Reads the data-registers and returns their value
static unsigned char AsciiReadController(){
	AsciiCtrlBitSet(B_E);
	SleepNPulses(61); // 360ns
	
	unsigned char value = *portIdrHigh;
	AsciiCrtlBitClear(B_E);
	
	return value;
}

// Reads the status from the registers and returns it
static unsigned char AsciiReadStatus(){
	*portModeR &= 0xFFFF;
	
	AsciiCrtlBitClear(B_RS);
	AsciiCtrlBitSet(B_RW);
	unsigned char value = AsciiReadController();
	
	*portModeR |= 0x55550000;
	return value;
}

// Reads the data stored in the registers and returns it
static unsigned char AsciiReadData(){
	*portModeR &= 0xFFFF;
	
	AsciiCtrlBitSet(B_RW + B_RS);
	unsigned char value = AsciiReadController();
	
	*portModeR |= 0x55550000;
	return value;
}

// The basic template for excuting a command. A delay is expected afterwards
static void AsciiBaseCommand(unsigned char command){
	while((AsciiReadStatus() & 0x80) == 0x80){}
	
	SleepMicroSeconds(8);
	AsciiWriteCmd(command);
}

// Configures how the Ascii display renders text. 
// First boolean decides whether it's a single or double row.
// Second boolean decides wether the text size is 5x8pt or 5x11pt 
static void AsciiFunctionSet (bool doDoubleRows, bool doLargeFont){
	unsigned char N = doDoubleRows << 3;
	unsigned char F = doLargeFont << 2;
	unsigned char cmd = 0x30 | N | F;
	
	AsciiBaseCommand(cmd);
	SleepMicroSeconds(39);
}

// Turns the Ascii display on/off and configures the text cursor
static void AsciiDisplayControl(bool displayActive, bool textCursorActive, bool textCursorFlashing){
	unsigned char D = displayActive << 2;
	unsigned char C = textCursorActive << 1;
	
	unsigned char cmd = 0x8 | D | C | textCursorFlashing;
	
	AsciiBaseCommand(cmd);
	SleepMicroSeconds(39);
}

// Clears the contents of the Ascii display
static void AsciiClearDisplay(){
	AsciiBaseCommand(0x1);
	SleepMicroSeconds(1530); // 1,53ms
}

// Configures the movement of the text cursor and if the graphic memory shifts
static void AsciiEntryModeSet(bool cusorDecrementMode, bool memoryShift){
	unsigned char ID = cusorDecrementMode << 1;
	unsigned char cmd = 0x4 | ID | memoryShift;
	
	AsciiBaseCommand(cmd);
	SleepMicroSeconds(39);
}

// Sends a Ascii character to the data-registers
static void AsciiWriteChar(char letter){
	while((AsciiReadStatus() & 0x80) == 0x80){}
	SleepMicroSeconds(8);
	AsciiWriteData(letter);
	
	SleepMicroSeconds(43);
}

// Moves the text cursor to a specific position
static void AsciiGoToXY(unsigned char row, bool use2ndColumn){
	if(row > 20){
		row = 20;
	}
	unsigned char adress = row - 1;
	if(use2ndColumn){
		adress += 0x40;
	} 
	
	AsciiWriteCmd(0x80 | adress);
}

/* Define functions here */
static int asciidisplay_init( int initval ){
	bool largeLetters;
	switch(initval){
		// Uses two rows with small letters
		case 2:
			useDoubleRows = true;
		// Uses a single row with small letters
		case 1:
			largeLetters = false;
			break;
		// Uses a single row with small letters
		default:
			largeLetters = true;
			useDoubleRows = false;
	}
	
	*portModeR = 0x55555555;
	AsciiFunctionSet(useDoubleRows, largeLetters);
	AsciiDisplayControl(true, true, false);
	AsciiClearDisplay();
	AsciiEntryModeSet(false, false);
	
	secondRow = false;
	AsciiGoToXY(1, false);
	return 0;
}
static void asciidisplay_deinit( int deinitval){ 
	AsciiClearDisplay();
	AsciiDisplayControl(false, false, false);
	AsciiEntryModeSet(false, false);
	AsciiFunctionSet(false, false);
	*portModeR &= 0;
	
	useDoubleRows = false;
	secondRow = false;
}

static int asciidisplay_write(char *ptr, int len){
		if(*ptr == '\n' && useDoubleRows && !secondRow){
			secondRow = true;
			AsciiGoToXY(1, true);
		}
		else{
			AsciiWriteChar(*ptr);
		}
		
	return 0;
}
