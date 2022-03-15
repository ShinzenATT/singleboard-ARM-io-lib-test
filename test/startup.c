#include <stdlib.h>
#include <stdio.h>
#include <libMD407.h>

/*
 * 	startup.c
 */
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=__stack_top\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL _crt_init\n");			/* init C-runtime library */
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(" BL _crt_deinit\n");			/* deinit C-runtime library */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

void main(void){
	_crt_init();
	char str[] = "test\n";
	_write(STDOUT, str, 5);
	_write(ASCIIDISPLAY, str, 5);
	char *input = malloc(sizeof(char) * 25);
	_read(STDIN, input, 25);
	_read(KEYPAD, input, 25);
	printf("I am in a lot of pain");
	free(input);
	
}

