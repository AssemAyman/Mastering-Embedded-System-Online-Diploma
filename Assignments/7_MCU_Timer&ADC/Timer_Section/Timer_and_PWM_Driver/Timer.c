/*
 * Timer.c
 *
 * Created: 9/3/2023 11:20:20 AM
 *  Author: assem
 */ 

/* =========== INCLIDES =========*/
#include "Timer.h"
/*===============================*/

/*============ Global Variables========*/
TIMER0_Config_t g_TIMER0_Config;
/*=====================================*/

/* ================================================================
 * @Fn 				- MCAL_TIMER0_Init
 * @brief 			- Initializes TIMER0 according to the specified parameters in Timer_Cfg
 * @param [in] 		- TIMER0_Config : a pointer to TIMER_CONFIG_t structure that contains the configuration information for the specified TIMER Module
 * @retval 			- None
 * Note 			- Supported for TIMER0 ONLY
 *
 */
void MCAL_TIMER0_Init(TIMER0_Config_t* TIMER0_Config){
	
	g_TIMER0_Config = *TIMER0_Config;
	
	/* 1.Set Mode of the timer (normal, CTC, Fast PWM, Phase correct PWM) */ 
	TCCR0 |= TIMER0_Config->Mode;  
	
	if(TIMER0_Config->Mode != TIMER0_MODE_NORMAL)
	{
		/* Configure OC0 (PINB3) as Output */
		DDRB |= (1<<PINB3);
	}
	
	/* 2.Select Pre-Scaler for internal CLK or Select External CLK on T0 pin */
	TCCR0 |= TIMER0_Config->CLK;
	if(TIMER0_Config->CLK == TIMER0_CLOCK_SOURCE_EXTERNAL_FALLING_EDGE || TIMER0_Config->CLK == TIMER0_CLOCK_SOURCE_EXTERNAL_RISING_EDGE)
	{
		/* Configure T0 (PINB0) as Input */
		DDRB &= ~(1<<0);
	}
	
	/* 3.Enable or Disable Interrupts */
	TIMSK |= TIMER0_Config->IRQ_Enable;
	if (TIMER0_Config->IRQ_Enable != TIMER0_IRQ_ENABLE_NONE)
	{
		/* Enable Global Interrupt */
		sei();
	}
}
/* ================================================================
 * @Fn 				- MCAL_TIMER0_DeInit
 * @brief 			- DeInitialze Timer0 Operation By Disable Timer Clock
 * @retval 			- None
 * Note 			- Supported for TIMER0 ONLY
 */
void MCAL_TIMER0_Stop(){
	
	TCCR0 &= ~0b111;
	
}
/* ================================================================
 * @Fn 				- MCAL_TIMER0_GetCounterValue
 * @brief 			- Get Timer counter value
 * @retval 			- TicksNumber : value of counter value from counter register (TCNT0)
 * Note 			- None
 *
 */
uint8_t MCAL_TIMER0_GetCounterValue(){
	
	return TCNT0;
	
}
/* ================================================================
 * @Fn 				- MCAL_TIMER0_SetCompareValue
 * @brief 			- Set OCR Register compare Value in Compare Match Mode(CTC)
 * @param [in] 		- TicksNumber : Value to Set in OCR(compare value must not exceed 255)
 * @retval 			- None
 * Note 			- Supported for Compare Match Mode(CTC) only & compare value must not exceed 255
 */
void MCAL_SetCompareValue(uint8_t TicksNumber){
	
	OCR0 = TicksNumber;
	
}

/* ================================================================
 * @Fn 				- MCAL_PWM_DutyCycle
 * @brief 			- Set PWM duty cycle in Fast PWM Mode and phase correct mode
 * @param [in] 		- Duty_Cycle : Value of PWM duty cycle (from 0 to 255)
 * @retval 			- None
 * Note 			- None
 */
void MCAL_PWM_DutyCycle(uint8_t Duty_Cycle){
	
	if (g_TIMER0_Config.Mode == TIMER0_MODE_PWM_Phase_Correct_non_inverting_mode || g_TIMER0_Config.Mode == TIMER0_MODE_Fast_PWM_non_inverting_mode)
	{
		OCR0 = Duty_Cycle;
	} 
	else if(g_TIMER0_Config.Mode == TIMER0_MODE_PWM_Phase_Correct_inverting_mode || g_TIMER0_Config.Mode == TIMER0_MODE_Fast_PWM_inverting_mode)
	{
		OCR0 = 255 - Duty_Cycle;
	}
	
}

/* ================ ISR Functions Definations ===================== */

/* OVERFLOW ISR */
ISR(TIMER0_OVF_vect){
	
	g_TIMER0_Config.P_TIMER_CALLBACK();
	
}

/* COMPARE MATCH ISR */
ISR(TIMER0_COMP_vect){
	
	g_TIMER0_Config.P_TIMER_CALLBACK();
	
}