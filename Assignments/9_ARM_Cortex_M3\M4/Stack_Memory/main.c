#include "Platform_Types.h"
#include "GPIO.h"
#include "EXTI.h"

#define OS_Stack_Size       512
#define TaskA_Stack_Size    100
#define TaskB_Stack_Size    100

#define Switch_to_Privileged()      __asm volatile("mrs r3,CONTROL \n\t lsr r3,r3,#0x1 \n\t lsl r3,r3,#0x1 \n\t msr CONTROL,r3")
#define Switch_to_UnPrivileged()    __asm volatile("mrs r3,CONTROL \n\t orr r3,r3,#0x1 \n\t msr CONTROL,r3")

#define OS_GENERATE_EXC()           __asm volatile("SVC #0x3")

#define Select_PSP()                __asm volatile("mrs r0,CONTROL \n\t orr r0,r0,#0x2 \n\t msr CONTROL,r0")
#define Set_PSP(add)                __asm volatile("msr PSP,%0" : : "r" (add))

#define Select_MSP()                __asm volatile("mrs r0,CONTROL \n\t and r0,r0,#0x5 \n\t msr CONTROL,r0")

extern int _estack;    // External definition for the stack pointer

vuint8_t IRQ_Flag, TaskA_Flag, TaskB_Flag;

// Interrupt Service Routine (ISR) for SVC (Supervisor Call) exception
void SVC_Handler(void) {
    Switch_to_Privileged();
}

// Callback function for IRQ9 interrupt
void IRQ9_CallBack() {

    if (IRQ_Flag == 1) {

        IRQ_Flag = 0;
        TaskA_Flag = 1;

    } else if (IRQ_Flag == 0) {

        IRQ_Flag = 1;
        TaskB_Flag = 1;
    }
}

int TaskA(int a, int b, int c) {
    return a + b + c;
}

int TaskB(int a, int b, int c, int d) {
    return a + b + c + d;
}

// Main operating system function
void main_os() {

    vuint32_t S_OS = (vuint32_t)&_estack;   // Start of OS stack
    vuint32_t E_OS = S_OS - OS_Stack_Size;  // End of OS stack

    vuint32_t S_TaskA = E_OS - 8;   // Start of TaskA stack
    vuint32_t E_TaskA = S_TaskA - TaskA_Stack_Size;   // End of TaskA stack

    vuint32_t S_TaskB = E_TaskA - 8;   // Start of TaskB stack
    vuint32_t E_TaskB = S_TaskB - TaskB_Stack_Size;   // End of TaskB stack

    while (1) {   // Infinite loop for task execution
        if (TaskA_Flag == 1) {    // Check if TaskA_Flag is set

            Set_PSP(S_TaskA);     // Set PSP to TaskA stack
            Select_PSP();         // Select PSP mode
            Switch_to_UnPrivileged();   // Switch to unprivileged mode

            TaskA_Flag = TaskA(1, 2, 3);    // Execute TaskA and store the result in TaskA_Flag

            OS_GENERATE_EXC();    // Generate an exception to return to the main OS loop
            Select_MSP();         // Select MSP mode

        } else if (TaskB_Flag == 1) {   // Check if TaskB_Flag is set

            Set_PSP(S_TaskB);     // Set PSP to TaskB stack
            Select_PSP();         // Select PSP mode
            Switch_to_UnPrivileged();   // Switch to unprivileged mode

            TaskB_Flag = TaskB(1, 2, 3, 4);    // Execute TaskB and store the result in TaskB_Flag

            OS_GENERATE_EXC();    // Generate an exception to return to the main OS loop
            Select_MSP();         // Select MSP mode
        }
    }
}

int main(void) {

    GPIOx_CLK_EN('B');

    EXTI_PinConfig_t pincfg;
    pincfg.EXTI_PIN = EXTI9PB9;
    pincfg.Trigger_Case = EXTI_Trigger_RISING;
    pincfg.IRQ_EN = EXTI_IRQ_Enable;
    pincfg.P_IRQ_CallBack = IRQ9_CallBack;

    MCAL_EXTI_GPIO_Init(&pincfg);

    main_os();    // Start the main operating system loop
}
