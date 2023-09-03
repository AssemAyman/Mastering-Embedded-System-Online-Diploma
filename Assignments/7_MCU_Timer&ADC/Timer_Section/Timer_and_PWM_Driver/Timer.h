/*
 * Timer.h
 *
 * Created: 9/3/2023 11:20:33 AM
 *  Author: assem
 */ 


#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned char uint8_t;

/* =========== INCLIDES =========*/
#include <avr/io.h>
#include <avr/interrupt.h>
/*==============================*/

/*=============== Configuration Stucture ==========*/

typedef struct{
	
	uint8_t Mode;						// specifies Timer Mode (Normal mode or CTC)
										// This parameter must be set based on @ref TIMER0_MODE_DEFINE
	
	uint8_t CLK;						// specifies Timer Clock Source (External / Internal) and PreScaler with internal clock only
										// This parameter must be set based on @ref TIMER0_CLOCK_SOURCE_DEFINE
	
	uint8_t IRQ_Enable;					// Enable or Disable IRQ
										// This parameter must be set based on @ref TIMER0_IRQ_ENABLE_DEFINE
	
	void(*P_TIMER_CALLBACK)();			//set the C Function which will be called once IRQ Happens
	
}TIMER0_Config_t;


/*=============== Configuration Reference Macros ==========*/
//@ref TIMER0_MODE_DEFINE
#define TIMER0_MODE_NORMAL										0
#define TIMER0_MODE_PWM_Phase_Correct_non_inverting_mode		(1<<WGM00 | 1<<COM01)
#define TIMER0_MODE_PWM_Phase_Correct_inverting_mode			(1<<WGM00 | 1<<COM01 | 1<<COM00)
#define TIMER0_MODE_CTC_Toggle									(1<<WGM01 | 1<<COM00)	
#define TIMER0_MODE_CTC_Clear									(1<<WGM01 | 1<<COM01)
#define TIMER0_MODE_CTC_Set										(1<<WGM01 | 1<<COM01 | 1<<COM00)
#define TIMER0_MODE_Fast_PWM_non_inverting_mode					(1<<WGM00 | 1<<WGM01 | 1<<COM01)
#define TIMER0_MODE_Fast_PWM_inverting_mode						(1<<WGM00 | 1<<WGM01 | 1<<COM01 | 1<<COM00)

//@ref TIMER0_CLOCK_SOURCE_DEFINE
#define TIMER0_CLOCK_SOURCE_INTERNAL_NO_PRESCALER			0x01
#define TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_8			0x02
#define TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_64			0x03
#define TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_256			0x04
#define TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_1024			0x05
#define TIMER0_CLOCK_SOURCE_EXTERNAL_FALLING_EDGE			0x06
#define TIMER0_CLOCK_SOURCE_EXTERNAL_RISING_EDGE			0x07

//@ref TIMER0_IRQ_ENABLE_DEFINE
#define TIMER0_IRQ_ENABLE_NONE								0
#define TIMER0_IRQ_ENABLE_TOIE0								1<<0
#define TIMER0_IRQ_ENABLE_OCIE0								1<<1

/* =========== APIs Supported by "MCAL TIMER0 DRIVER" ============= */

extern void	MCAL_TIMER0_Init(TIMER0_Config_t* );
extern void	MCAL_TIMER0_Stop();

extern uint8_t MCAL_TIMER0_GetCounterValue();
extern void	MCAL_SetCompareValue(uint8_t TicksNumber);

extern void	MCAL_PWM_DutyCycle(uint8_t Duty_Cycle);

#endif /* TIMER_H_ */