#@Copyright : Abdelaziz
CC=
CFLAGS= --coverage -g -o0
INCS=-I .
LIBS=
SRC =$(wildcard *.c)
OBJ =$(SRC:.c=.o)
As =$(wildcard *.s)
AsOBJ =$(As:.s=.o)
Project_Name= High_Pressure_Detection


all: $(Project_Name).elf
	@echo "=============Build Done=============="

$(Project_Name).elf : 
	$(CC)gcc $(CFLAGS) $(SRC) -o $@	

gcov : *.gcno *.gcda
	gcov -a -b -c -d  *.c
	
gcovr : *.gcov
	gcovr -r . --html --html-details -o $(Project_Name)-details.html		
		
clean:
	rm *.elf *.html *.gcno *.gcda *.gcov


