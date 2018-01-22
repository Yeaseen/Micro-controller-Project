/*
 * Alc_Code.c
 *
 * Created: 1/6/2018 3:47:10 PM
 * Author : Asus
 */ 


#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <stdio.h>
//define the load resistance on the board, in kilo ohms
#define         RL_VALUE                     (10)     
// (Sensor resistance in clean air)/RO, which is derived from the chart in datasheet 
#define         RO_CLEAN_AIR_FACTOR          (9.83)  
// Gas identity no.
#define         LPG                      (0)         
#define         SMOKE                    (1)


float           Ro           =  10;                 //Ro is initialized to 10 kilo ohms

/*
 * sensor and load resistor forms a voltage divider. so using analog value and load value
 * we will find sensor resistor.
 */
float ResistanceCalculation(int raw_adc){   
	return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));     
}

/*
 * This function assumes that sensor is in clean air.
 */
float SensorCalibration(int a){
	int i;
	float val=0;
	
	
	for (i=0;i<50;i++) {                   //take multiple samples and calculate the average value
		
		val += ResistanceCalculation(a);
		_delay_ms(500);
	}
	val = val/50;
	val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro
														 //according to the chart in the datasheet
	return val;
}

int main(void){
    DDRD = 0xFF;
	DDRC = 0xFF;
	int i;
	Lcd8_Init();
	
	unsigned digital;
	unsigned temp;
	int ok;
	char buffer[9];
	
	ADMUX=0b01100000;
	ADCSRA=0b10000010;
	
	Lcd8_Clear();
	Lcd8_Set_Cursor(1,0);
	Lcd8_Write_String("Resistance: ");
	
		   
	
	while(1){
		
	
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	
	digital=ADCL;
	temp=ADCH;
	digital=(digital>>6) | (temp<<2);
	
	//Ro =ResistanceCalculation(digital);
	
	ok=(int) digital;
	
	
	
	//ok=91;
	//printf("echo1 %f \n", analog);
	sprintf(buffer,"%d",ok);
	//sprintf(buffer,"%f",Ro);
	Lcd8_Set_Cursor(2,0);
	Lcd8_Write_String(buffer);
	
	if(ok>500) PORTC=0x00;
	else PORTC = 0x01;	
	//_delay_ms(4000);		
	}

}



