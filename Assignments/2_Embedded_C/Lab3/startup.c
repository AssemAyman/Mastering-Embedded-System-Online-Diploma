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

static uint32_t Stack_top[256];

void (* const p_fn_Vectors[])()__attribute__((section(".vectors")))={
	
(void(*)()) (Stack_top + sizeof(Stack_top)),
            &Reset_Handler,
			&NMI_Handler,
			&H_fault_Handler
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
