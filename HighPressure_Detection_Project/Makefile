#@copyright : Assem Ayman

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)
Project_Name=HighPressure_Detection

all: $(Project_Name).bin
	@echo "============Build is done============"
	
%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c  $< -o $@
	
%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	
$(Project_Name).elf: $(OBJ) $(AsOBJ) 
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	
$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:
	rm *.o *.elf *.bin
	@echo "============All Clean============"

clean:
	rm *.elf *.bin