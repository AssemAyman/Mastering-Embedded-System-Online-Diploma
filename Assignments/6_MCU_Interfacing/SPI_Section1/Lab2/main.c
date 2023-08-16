/*
 * Lab2.c
 *
 * Created: 8/15/2023 10:52:30 PM
 * Author : assem
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#define SS   4
#define MOSI 5
#define SCK  7

void SPI_Master_Init(){
	// Enable SPI, Master mode, Shift Clock = CLK /16
	SPCR |= 1<<SPE | 1<<MSTR | 1<<SPR0;
	// Set MOSI, SCK and SS as Output Pins
	DDRB |= 1<<SS | 1<<MOSI | 1<<SCK;
}

void SPI_Master_Send(unsigned char CMD , unsigned char data){
	//initialize the packet by pulling SS low
	PORTB &= ~(1<<SS);
	//start CMD transmission
	SPDR = CMD;
	//wait CMD transfer to finish
	while(!(SPSR & 1<<SPIF));
	//start data transmission
	SPDR = data;
	//wait data transfer to finish
	while(!(SPSR & 1<<SPIF));
	///terminate the packet by pulling SS high
	PORTB |= 1<<SS;
}
int main(void)
{
	unsigned char counter = 0;
	
	SPI_Master_Init();
	
	SPI_Master_Send(0x9,0xff); //decode all displays
	SPI_Master_Send(0xa,0xf); //scan limit for all digits
	SPI_Master_Send(0xb,0x7); //max brightness intensity
	SPI_Master_Send(0xc,1);  //Turb On display
	
    while (1) 
    {
		for (char seg_index=1; seg_index<=8; seg_index++)
		{
			SPI_Master_Send(seg_index,counter++);
			_delay_ms(1000);
		}
    }
}

