#@Copyright : Abdelaziz
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2 
INCS=-I .
LIBS=
SRC =$(wildcard *.c)
OBJ =$(SRC:.c=.o)
As =$(wildcard *.s)
AsOBJ =$(As:.s=.o)
Project_Name=learn_in_depth_CortexM3_ToggleLED


all: $(Project_Name).bin
	@echo "=============Build Done=============="

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_Name).elf : $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=$(Project_Name).map	

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@		

clean:
	rm *.elf *.bin *.map	

clean_all:
	rm *.o *.elf *.bin *.map

