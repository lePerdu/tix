#
# Makefile
#
# Copyright (c) 2017 Zach Peltzer
# Subject to the MIT License
#

NAME = TIX

SRC = src
INC = inc
BUILD = build
BIN = bin

## Programs used for building

SPASM = spasm
SPASMOPTS += -A -N -I$(INC) -I$(SRC)

UNIX2DOS = unix2dos

MULTIHEX = multihex

PACKXXU = packxxu
PACKXXUOPTS = -t 83p -v 2.01 -h 255 -q 0A

# The signing key to use. This should be key 0A.
# If left blank, rabbitsign will search in the current directory and amoung the
# keys built into the binary.
KEY0A =
RABBITSIGN = rabbitsign
RABBITSIGNOPTS = -t 8xu -K 0A -g -p -r $(if $(KEY0A),-k $(KEY0A))

ROMPATCH = rompatch
ROMPATCHOPTS = -4

TIXFSGEN = tixfsgen
# Make everything owned by root
TIXFSGENOPTS = -u$(USER):0 -g$(USER):0

EMULATOR = tilem2
EMULATOROPTS =
EMULATOR_ROMOPT = -r
EMULATOR_UPGRADEOPT =
EMULATOR_DEBUGOPT = -d

SOURCES := $(wildcard $(SRC)/*)

HEADERS := $(wildcard $(INC)/*)

PAGES := $(filter $(SRC)/page%.z80, $(SOURCES))
PAGEHEXS := $(patsubst $(SRC)/%.z80,$(BUILD)/%.hex,$(PAGES))

# TODO Change this based on the model.
PRIV_PAGE = 6C

FS = fs
FS_HEX = $(BUILD)/$(FS).hex

OSHEX = $(BUILD)/$(NAME).hex
OSUPGRADE = $(BIN)/$(NAME).8xu
OSROM = $(BIN)/$(NAME).rom

# Set to a rom file to patch, if desired. The file is copied before it is
# modified.
ROMFILE = TI84pSE.rom

rom: $(OSROM)

upgrade: $(OSUPGRADE)

# Make the upgrade file by default so that a ROM does not have to be supplied.
all: rom upgrade

$(OSROM): $(OSHEX) $(ROMFILE) $(BIN)
	@cp $(ROMFILE) $@
	$(ROMPATCH) $@ $(ROMPATCHOPTS) $<

$(OSUPGRADE): $(OSHEX) $(BIN)
	$(PACKXXU) $(PACKXXUOPTS) -o $@ $<
	$(RABBITSIGN) $(RABBITSIGNOPTS) -o $@ $@

# If there is more than 1 page, combine them with multihex.
$(OSHEX): $(PAGEHEXS) $(FS_HEX)
	$(MULTIHEX) $(foreach page,$(filter-out %_priv.hex,$(PAGEHEXS)),$(page:$(BUILD)/page%.hex=%) $(page)) $(PRIV_PAGE) $(filter %_priv.hex,$(PAGEHEXS)) - $(FS_HEX) > $@
	$(UNIX2DOS) $@

include fs.mk
$(FS_HEX): $(FS)
	$(TIXFSGEN) $(TIXFSGENOPTS) $@ $<

# TODO Change this to not rebuild all pages when any file changes
$(BUILD)/%.hex: $(SRC)/%.z80 $(SOURCES) $(HEADERS) | $(BUILD)
	$(SPASM) $(SPASMOPTS) -T -L $< $@

$(BUILD) $(BIN):
	@mkdir -p $@

run: $(OSROM)
	$(EMULATOR) $(EMULATOROPTS) $(EMULATOR_ROMOPT) $<

debug: $(OSROM)
	$(EMULATOR) $(EMULATOR_DEBUGOPT) $(EMULATOR_ROMOPT) $<

run-upgrade: $(OSUPGRADE)
	$(EMULATOR) $(EMULATOROPTS) $(EMULATOR_UPGRADEOPT) $<

debug-upgrade: $(OSUPGRADE)
	$(EMULATOR) $(EMULATOR_DEBUGOPT) $(EMULATOR_UPGRADEOPT) $<

clean:
	@rm -rf $(BUILD) $(BIN) $(FS_BINS)

.PHONY: all rom upgrade run debug run-upgrade debug-upgrade clean

