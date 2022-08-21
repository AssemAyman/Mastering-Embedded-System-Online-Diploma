//startup.c
//Eng.Assem

#include <stdint.h>

extern int main(void);
void Reset_Handler(void);

void Default_Handler(void){

Reset_Handler();
	
}

void NMI_Handler(void)__attribute__((weak,alias("Default_Handler")));
void H_fault_Handler(void)__attribute__((weak,alias("Default_Handler")));
void MM_fault_Handler(void)__attribute__((weak,alias("Default_Handler")));
void Bus_fault(void)__attribute__((weak,alias("Default_Handler")));
void Usage_fault_Handler(void)__attribute__((weak,alias("Default_Handler")));

extern uint32_t _stack_top;
uint32_t vectors[] __attribute__((section(".vectors")))={

(uint32_t) &_stack_top,
(uint32_t) &Reset_Handler,
(uint32_t) &NMI_Handler,
(uint32_t) &H_fault_Handler,
(uint32_t) &MM_fault_Handler,
(uint32_t) &Bus_fault,
(uint32_t) &Usage_fault_Handler

};
extern uint32_t _E_text;
extern uint32_t _S_DATA;
extern uint32_t _E_DATA;
extern uint32_t _S_bss;
extern uint32_t _E_bss;

void Reset_Handler(void){

//copy data from flash to RAM
uint32_t Data_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
unsigned char* P_src = (unsigned char*)&_E_text;
unsigned char* P_dst = (unsigned char*)&_S_DATA;

for(int i = 0; i<Data_size; i++)
	*P_dst++ = *P_src++;

// init .bss with zero
uint32_t bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
P_dst = (unsigned char*)&_S_bss;
for(int i = 0; i<bss_size; i++)
	*P_dst++ = (unsigned char)0;

//jump to main function
main();

}
