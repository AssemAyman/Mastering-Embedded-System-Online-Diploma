/*
 * slave.c
 *
 * Created: 8/15/2023 9:03:50 AM
 *  Author: assem
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SS   4
#define MOSI 5
#define MISO 6
#define SCK  7

void SPI_Slave_Init(){
	// Set MISO as an Output Pin
	DDRB |= 1<<MISO;
	// Enable SPI
	SPCR |= 1<<SPE;
}

unsigned char SPI_Slave_Receive(unsigned char data){
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
	
    SPI_Slave_Init();
	
    for(char i = 255; i>=0; i--){	
		//send and receive data and show received data at PORTA
		PORTA = SPI_Slave_Receive(i);
		_delay_ms(1000);
	}
}

