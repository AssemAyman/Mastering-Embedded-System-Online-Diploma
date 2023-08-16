/*
 * SPI_Section1.c
 *
 * Created: 8/15/2023 8:42:13 AM
 * Author : assem
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SS   4
#define MOSI 5
#define MISO 6
#define SCK  7

void SPI_Master_Init(){
	// Set MOSI, SCK and SS as Output Pins
	DDRB |= 1<<SS | 1<<MOSI | 1<<SCK;
	// Set MISO as an Input Pin
	DDRB &= ~(1<<MISO);
	//Master mode, Shift Clock = CLK /16
	SPCR |= 1<<MSTR | 1<<SPR0;
	// Enable SPI
	SPCR |= 1<<SPE;
}

unsigned char SPI_Master_Send(unsigned char data){
	// Start transmission
	SPDR = data;
	// Wait for transmission complete
	while(!(SPSR & 1<<SPIF));
	// return the received data from the slave
	return SPDR;
}

int main(void)
{
	//Make PORTA Output 
	DDRA = 0xff;
	
    SPI_Master_Init();
	
    for(char i = 0; i<255; i++){	
		//send and receive data and show received data at PORTA
		PORTA = SPI_Master_Send(i);
		_delay_ms(1000);
	}
}

