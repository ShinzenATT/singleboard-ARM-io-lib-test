/*
 * libMD407
 * keypad_driver.c
 * Keypad connected to PD8-PD15
 * Driver for KEYPAD
 */
#include "libMD407.h"

static int keypad_init( int initval );
static void keypad_deinit( int deinitval);
static int keypad_read(char *ptr, int len);

DEV_DRIVER_DESC KeyPad =
{
	{"Keypad"},
	keypad_init,
	keypad_deinit,
	0,
	0,
	0,
	0,
	0,
	0,
	keypad_read
};

/* KEYPAD types and constants definitions */
#define GPIO_D_BASE 0x40020C00
#define GPIO_D_MODER ((volatile unsigned long *) GPIO_D_BASE)
#define GPIO_D_OTYPER ((volatile unsigned short *) GPIO_D_BASE + 0x4)
#define GPIO_D_PUPDR ((volatile unsigned long *) GPIO_D_BASE + 0xC)
#define GPIO_D_IDR (GPIO_D_BASE + 0x10)
#define GPIO_D_ODR (GPIO_D_BASE + 0x14)

static unsigned char *GPOut = 0;
static volatile unsigned char *GPIn = 0;

/* Imported helper functions from lab 3.5 */

// Activates a row for input on the keypad, also updates the out-register. Index starts at 1
static void KeypadActivateRow(unsigned int rowIndex){
	if(rowIndex > 4 || rowIndex == 0){
		return;
	}
	
	unsigned char binaryIndex = 1 << (3 + rowIndex);
	*GPOut = binaryIndex;
	return;
}

// Returns column data of pressed keys in the active row
static unsigned char KeypadReadCol(){
	return *GPIn;
}

// Returns a keycode for the active key pressed (lowest value take priority)
static unsigned char getKeycode(){
		for(unsigned char i = 1; i <= 4; i++){
		KeypadActivateRow(i);
		unsigned char value = KeypadReadCol();
		
		if(value != 0){
			unsigned char mask = 1;
			for(unsigned char j = 1; j <= 4; j++){
				if((value & mask) != 0){
					return ((i-1) * 4) + j;
				}
				mask = mask << 1;
			}
		}
	}
	
	return 0xFF;
}

// Converts a keycode to the char equivalent of the key
static char convertKeycodeToChar(unsigned char keycode){
	switch(keycode){
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return 'A';
		case 5:
			return '4';
		case 6:
			return '5';
		case 7:
			return '6';
		case 8:
			return 'B';
		case 9:
			return '7';
		case 10:
			return '8';
		case 11:
			return '9';
		case 12:
			return 'C';
		case 13:
			return '*';
		case 14:
			return '0';
		case 15:
			return '#';
		case 16:
			return 'D';
		default:
			return '\0';
	}
}

/* Define functions here */

static int keypad_init( int initval ){ 
	unsigned long moderRCfg = 0x5500;
	unsigned long pupdRCfg = 0xAA00;
	unsigned short otyprRCfg = 0;
	
	// If initval isn't 0 then use pin 15 trough 8
	if(initval){
		*GPIO_D_MODER &= 0xFFFF;
		*GPIO_D_MODER |= moderRCfg << 16;
		
		*GPIO_D_OTYPER &= 0xFF;
		*GPIO_D_OTYPER |= otyprRCfg << 8;
		
		*GPIO_D_PUPDR &= 0xFFFF;
		*GPIO_D_PUPDR |= pupdRCfg << 16;
		
		GPOut = GPIO_D_ODR + 1;
		GPIn = GPIO_D_IDR + 1;
	}
	// Otherwise use pin 7 trough 0
	else{
		*GPIO_D_MODER &= 0xFFFF0000;
		*GPIO_D_MODER |= moderRCfg;
		
		*GPIO_D_OTYPER &= 0xFF00;
		*GPIO_D_OTYPER |= otyprRCfg;
		
		*GPIO_D_PUPDR &= 0xFFFF0000;
		*GPIO_D_PUPDR |= pupdRCfg;
		
		GPOut = GPIO_D_ODR;
		GPIn = GPIO_D_IDR;
	}
	return 0;
}

static void keypad_deinit( int deinitval){ 
	// If initval isn't 0 then disable pin 15 trough 8
	if(deinitval){
		*GPIO_D_MODER &= 0xFFFF;
		*GPIO_D_OTYPER &= 0xFF;
		*GPIO_D_PUPDR &= 0xFFFF;
	}
	// Otherwise disable pin 7 trough 0
	else{
		*GPIO_D_MODER &= 0xFFFF0000;
		*GPIO_D_OTYPER &= 0xFF00;
		*GPIO_D_PUPDR &= 0xFFFF0000;
	}
}

static int keypad_read(char *ptr, int len){ 
	unsigned char c = getKeycode();
	*ptr = convertKeycodeToChar(c);
	
	return 0;
}
