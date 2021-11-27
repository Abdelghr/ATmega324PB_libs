#*************************************
# - Variables
# Hardware
MCU   = atmega324pb
PROGRAMMER_TYPE = usbasp

# Fuse Bytes
LFUSE = 0xFF
HFUSE = 0x99
EFUSE = 0xF7
FUSE_WRITE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m
FUSE_READ_STRING  = -U lfuse:r:-:i -U hfuse:r:-:i -U efuse:r:-:i

# Compilation toolchain
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

# Source files
TARGET = main
SOURCES=$(wildcard *.c lib/*.c lib/*/*.c)
HEADERS=$(SOURCES:.c=.h)

# Compiled files
OBJECTS=$(SOURCES:.c=.o)
ELF = debug/$(TARGET).elf
MAP = debug/$(TARGET).map
HEX = debug/$(TARGET).hex

# Compilation flags
CFLAGS = -x c -Wall -g3 -O3 -ffunction-sections -fdata-sections
TARGET_ARCH = -mmcu=$(MCU)

# Linking flags
LDFLAGS = -Wl,-Map,$(MAP) -Wl,--gc-sections


#*************************************
# - Rules
# Default Goal: Make hexadecimal file
$(HEX): $(ELF) Makefile | size
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

# Make elf (executable linkable format) file resulting from linking all object files
$(ELF): $(OBJECTS) Makefile
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $(OBJECTS) -o $@

# Make all object files
%.o:%.c $(HEADERS) Makefile
	 $(CC) $(CFLAGS) $(TARGET_ARCH) -c -o debug/$@ $<

# %.eeprom: %.elf Makefile
# 	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 

# %.lst: %.elf Makefile
# 	$(OBJDUMP) -S $< > $@


#*************************************
# - Rules with phony targets (no file to be made)
.PHONY: all disassemble disasm eeprom size clean squeaky_clean flash fuses debug

# Flashing the program
flash: $(HEX) 
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER_TYPE) -U flash:w:$<:i

# Flashing to eeprom
flash_eeprom: $(TARGET).eeprom
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER_TYPE) -U eeprom:w:$<

avrdude_terminal:
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER_TYPE) -nt

# Writing fuses values
write_fuses_WARNING:
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER_TYPE) $(FUSE_WRITE_STRING)

# Reading fuses values
read_fuses:
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER_TYPE) $(FUSE_READ_STRING)

# Show information about the MCU and programmer type
debug:
	@echo
	@echo "Source files:"   $(SOURCES)
	@echo "MCU, Programmer:"  $(MCU), $(PROGRAMMER_TYPE)
	@echo

# Show size of the resulting program 
size:  $(ELF)
	@avr-objdump -Pmem-usage $(ELF)
#$(AVRSIZE) --format=avr --mcu=$(MCU) $(ELF)

clean:
ifneq (, $(wildcard debug/*))
	rm debug/*
endif
ifneq (, $(wildcard $(OBJECTS)))
	rm $(OBJECTS)
endif