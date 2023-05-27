NAME    = demonic-cats
MCU     = attiny13
FREQ    = 600000
FUSEH   = fd
FUSEL   = 01
DUDEOPT	= -B 500

SCONS		= scons
AVRDUDE		= avrdude
PROG		= usbasp
PORT		= /dev/ttyUSB0

.PHONY: all
all: build

.PHONY: build
build:
	$(SCONS) -f avr.scons NAME=$(NAME) MCU=$(MCU) FREQ=$(FREQ) GAL=$(GALPATH) ADDCFLAGS="$(CFLAGS)" ADDCXXFLAGS="$(CXXFLAGS)" ADDLDFLAGS="$(LDFLAGS)"

.PHONY: poke
poke: build
	$(AVRDUDE) -V $(DUDEOPT) -p $(MCU) -c $(PROG) -P $(PORT) -e -U lfuse:w:0x$(FUSEL):m -U hfuse:w:0x$(FUSEH):m -U flash:w:build/$(NAME).hex

.PHONY: clean
clean:
	$(SCONS) -c -f avr.scons NAME=$(NAME) MCU=$(MCU) FREQ=$(FREQ) GAL=$(GALPATH) ADDCFLAGS="$(CFLAGS)" ADDCXXFLAGS="$(CXXFLAGS)" ADDLDFLAGS="$(LDFLAGS)"
