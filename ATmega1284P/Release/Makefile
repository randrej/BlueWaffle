###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = ATmega1284p
COMPILER = "WinAVR"
TARGET = Release
SHELL = C:\Windows\system32\cmd.exe

## Tools general options
CCFLAGS=-Wall -gdwarf-2 -fsigned-char -MD -MP -DF_CPU=16000000 -Os -mmcu=atmega1284p -std=c99
LDFLAGS=-mmcu=atmega1284p

## Processing Tools
CC=avr-gcc.exe
ASM=avr-gcc.exe
LD=avr-gcc.exe
#  D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/Release/Release.hex: TOOL=LD
#  Post: $(OBJ) avr-objcopy -O ihex -R .eeprom "./Release.elf" "./Release.hex"
#  Post: $(OBJ) avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex "./Release.elf" "./Release.eep" || exit 0 
#     D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/Release/main.o: TOOL=CC
#        D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/main.c
#     D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/Release/spiAdc.o: TOOL=CC
#        D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/spiAdc.c
#     D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/Release/AvrAdc.o: TOOL=CC
#        D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/AvrAdc.c
#     D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/Release/LedsAndDisplay.o: TOOL=CC
#        D:/Users/Andrej/Desktop/pedale i switcheri/embedded projekti/BlueWaffle/ATmega1284P/LedsAndDisplay.c

# Build tree:
all:	Release

Release:	Release.hex
	cp "Release.hex" "../../ATmega1284P.hex"

Release.hex:	main.o spiAdc.o AvrAdc.o LedsAndDisplay.o 
	$(LD) $(LDFLAGS)  -o "./Release.elf" "main.o" "spiAdc.o" "AvrAdc.o" "LedsAndDisplay.o"
	$(OBJ) avr-objcopy -O ihex -R .eeprom "./Release.elf" "./Release.hex"
	$(OBJ) avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex "./Release.elf" "./Release.eep" || exit 0 

main.o:	../main.c 
	$(CC) $(CCFLAGS)  -o "main.o" -c "../main.c"

spiAdc.o:	../spiAdc.c 
	$(CC) $(CCFLAGS)  -o "spiAdc.o" -c "../spiAdc.c"

AvrAdc.o:	../AvrAdc.c 
	$(CC) $(CCFLAGS)  -o "AvrAdc.o" -c "../AvrAdc.c"

LedsAndDisplay.o:	../LedsAndDisplay.c 
	$(CC) $(CCFLAGS)  -o "LedsAndDisplay.o" -c "../LedsAndDisplay.c"

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf ./main.d
	rm -rf ./spiAdc.d
	rm -rf ./AvrAdc.d
	rm -rf ./LedsAndDisplay.d

# cleanup - delete all generated files
clean:	tidy
	rm -rf Release.hex
	rm -rf main.o
	rm -rf spiAdc.o
	rm -rf AvrAdc.o
	rm -rf LedsAndDisplay.o

