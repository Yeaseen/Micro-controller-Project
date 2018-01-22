/*
 * dc_motor_code.c
 *
 * Created: 1/14/2018 7:42:18 PM
 * Author : Asus
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL // 16MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF; //PORTB as Output
	while(1)
	{
		//Rotates Motor in Antilockwise
		PORTA = 0x01; //00000001
		_delay_ms(4000);

		
	}
}
