#include "Platform_Types.h"
#include "core_cm3.h"

typedef enum {
	Add=1,Sub=2,Mul=3,PendSV=4
}Service_Type;

void PendSV_Handler(){

}

void OS_SVC(uint32_t* Stack_Frame){

	uint8_t  SVC_ID = ((char*) Stack_Frame[6])[-2];

	uint32_t Argument1 = Stack_Frame[0];
	uint32_t Argument2 = Stack_Frame[1];

	switch(SVC_ID){

	case 1:
		Stack_Frame[0] = Argument1 + Argument2;
		break;

	case 2:
		Stack_Frame[0] = Argument1 - Argument2;
		break;

	case 3:
		Stack_Frame[0] = Argument1 * Argument2;
		break;

	case 4:
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;
	}
}

// Interrupt Service Routine (ISR) for SVC (Supervisor Call) exception
__attribute ((naked)) void SVC_Handler(void) {

	__asm("TST LR,#4 \n\t"
			"ITE EQ \n\t"
			"MRSEQ r0,MSP \n\t"
			"MRSNE r0,PSP \n\t"
			"B OS_SVC");
}

int OS_SVC_Set(int a, int b, Service_Type  SVC_ID){

	uint32_t Result;

	switch(SVC_ID){

	case Add:

		__asm("SVC #1 \n\t");

		break;

	case Sub:

		__asm("SVC #2 \n\t");

		break;

	case Mul:

		__asm("SVC #3 \n\t");

		break;

	case PendSV:

		__asm("SVC #4 \n\t");

		break;
	}

	__asm("MOV %0,r0 \n\t" : "=r" (Result));
	return Result;
}

int main(void) {

	vuint32_t Val;

	Val = OS_SVC_Set(5,4,Add);
	Val = OS_SVC_Set(5,4,Sub);
	Val = OS_SVC_Set(5,4,Mul);

	OS_SVC_Set(0,0,PendSV);

	while(1);
}
