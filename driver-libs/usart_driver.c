/*
 * libMD407
 * usart_driver.c
 * USART driver
 * Drivers for STDIN, STDOUT and STDERR
 */
 
#include "libMD407.h"

/* Define functions here */
static int usart_init( int initval );
static void usart_deinit( int deinitval);
static int usart_write(char *ptr, int len);
static int usart_read(char *ptr, int len);

DEV_DRIVER_DESC StdIn =
{
	{"stdin"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	0,
	usart_read
};

DEV_DRIVER_DESC StdOut =
{
	{"stdout"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	usart_write,
	0
};

DEV_DRIVER_DESC StdErr =
{
	{"stderr"},
	usart_init,
	usart_deinit,
	0,
	_isatty,
	0,
	0,
	0,
	usart_write,
	0
};


/* USART types and constants definitions */
#define BIT_UE (1<<13)
#define BIT_TXE (1<<7)
#define BIT_RXNE (1<<5)
#define BIT_TE (1<<3)
#define BIT_RE (1<<2)

typedef struct{
	volatile unsigned short sr;
	volatile unsigned short unused0;
	volatile unsigned short dr;
	volatile unsigned short unused1;
	volatile unsigned short brr;
	volatile unsigned short unused2;
	volatile unsigned short cr1;
	volatile unsigned short unused3;
	volatile unsigned short cr2;
	volatile unsigned short unused4;
	volatile unsigned short cr3;
	volatile unsigned short unused5;
	volatile unsigned short gtpr;
} __USART;

#define USART1 ((__USART *) 0x40011000)

/* USART implementation */
static int usart_init( int initval ) { 
	USART1->brr = 0x2D9; // Baudrate 115200
	USART1->cr2 = 0;
	USART1->cr1 = BIT_UE | BIT_TE | BIT_RE;
}
static void usart_deinit( int deinitval){ 
	USART1->cr1 &= 0;
	USART1->cr2 &= 0;
	USART1->brr &= 0;
}
static int usart_write(char *ptr, int len){ 
	while((USART1->sr & BIT_TXE)== 0);
	USART1->dr = (unsigned short) *ptr;
	
	return 0;
}

static int usart_read(char *ptr, int len){ 
	while(!(USART1->sr) & !BIT_RXNE){}
	*ptr = (char) USART1->dr;
	
	return 0;
}