# Makefile for ATmegaBOOT
# E.Lins, 18.7.2005
# $Id$
#
# Gionata Boccalini, 01.11.2017
# This Makefile only includes target to burn the bootloaders.
# Changes from the Optiboot Makefile: 
# - removed unused platforms, and compile target
# - changed programmer to usbasp
#
# Instructions
#
# To burn bootloader .hex file:
# make attiny84_isp
# make attiny85_isp

PROGRAM    = empty

# The default behavior is to build using tools that are in the users
# current path variables.

# Enter the parameters for the avrdude isp tool
ISPTOOL	   = usbasp
ISPPORT	   = 
ISPSPEED   = 

MCU_TARGET = attiny84
LDSECTIONS = -Wl,--section-start=.text=0x3e00 -Wl,--section-start=.version=0x3ffe

# Build environments
# Start of some ugly makefile-isms to allow optiboot to be built
# in several different environments.  See the README.TXT file for
# details.

# default
fixpath = $(1)

GCCROOT = /usr/bin/
AVRDUDE_CONF = -C/etc/avrdude/avrdude.conf

# End of build environment code.


# The lock bits should be 0xff instead of 0x3f (to
# unlock the bootloader section) and 0xcf instead of 0x0f (to
# lock it), but since the high two bits of the lock byte are
# unused, avrdude would get confused.

ISPFUSES   = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
             -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
             -e -u -U lock:w:0xff:m -U lfuse:w:0x$(LFUSE):m \
             -U hfuse:w:0x$(HFUSE):m -U efuse:w:0x$(EFUSE):m  
ISPFLASH   = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
             -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
             -U flash:w:$(PROGRAM)_$(TARGET).hex -U lock:w:0x0f:m

OBJ        = $(PROGRAM).o
OPTIMIZE   = -Os -fno-inline-small-functions -fno-split-wide-types #-mshort-calls

DEFS       = 
LIBS       =

CC         = $(GCCROOT)avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS  = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS = $(LDSECTIONS) -Wl,--relax -Wl,--gc-sections -nostartfiles -nostdlib

OBJCOPY    = $(GCCROOT)avr-objcopy
OBJDUMP    = $(call fixpath,$(GCCROOT)avr-objdump)

SIZE       = $(GCCROOT)avr-size


#Tiny Bootloaders (8MHz only)
#
attiny84_8_isp: TARGET = attiny84_8Mhz
attiny84_8_isp: MCU_TARGET = attiny84
attiny84_8_isp: LFUSE = E2
attiny84_8_isp: HFUSE = DF
attiny84_8_isp: EFUSE = FF
attiny84_8_isp: isp
          
attiny85_8_isp: TARGET = attiny85_8Mhz
attiny85_8_isp: MCU_TARGET = attiny85
attiny85_8_isp: LFUSE = E2
attiny85_8_isp: HFUSE = DF
attiny85_8_isp: EFUSE = FF
attiny85_8_isp: isp

#Tiny Bootloaders (1MHz only)
#
attiny24_1_isp: TARGET = attiny24_1Mhz
attiny24_1_isp: MCU_TARGET = attiny24
attiny24_1_isp: LFUSE = 62
attiny24_1_isp: HFUSE = DF
attiny24_1_isp: EFUSE = FF
attiny24_1_isp: isp
       
attiny44_1_isp: TARGET = attiny44_1Mhz
attiny44_1_isp: MCU_TARGET = attiny44
attiny44_1_isp: LFUSE = 62
attiny44_1_isp: HFUSE = DF
attiny44_1_isp: EFUSE = FF
attiny44_1_isp: isp

attiny84_1_isp: TARGET = attiny84_1Mhz
attiny84_1_isp: MCU_TARGET = attiny84
attiny84_1_isp: LFUSE = 62
attiny84_1_isp: HFUSE = DF
attiny84_1_isp: EFUSE = FF
attiny84_1_isp: isp

attiny25_1_isp: TARGET = attiny25_1Mhz
attiny25_1_isp: MCU_TARGET = attiny25
attiny25_1_isp: LFUSE = 62
attiny25_1_isp: HFUSE = DF
attiny25_1_isp: EFUSE = FF
attiny25_1_isp: isp

attiny45_1_isp: TARGET = attiny45_1Mhz
attiny45_1_isp: MCU_TARGET = attiny45
attiny45_1_isp: LFUSE = 62
attiny45_1_isp: HFUSE = DF
attiny45_1_isp: EFUSE = FF
attiny45_1_isp: isp
         
attiny85_1_isp: TARGET = attiny85_1Mhz
attiny85_1_isp: MCU_TARGET = attiny85
attiny85_1_isp: LFUSE = 62
attiny85_1_isp: HFUSE = DF
attiny85_1_isp: EFUSE = FF
attiny85_1_isp: isp

#
# Generic build instructions
#
#
isp: $(TARGET)
	$(ISPFUSES)
	$(ISPFLASH)

%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(SIZE) $@

clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .bootloader.start -j .bootloader -j .data -j .version --set-section-flags .version=alloc,load -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .bootloader.start -j .bootloader -j .data -j .version --set-section-flags .version=alloc,load -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .bootloader.start -j .bootloader -j .data -j .version --set-section-flags .version=alloc,load -O binary $< $@
