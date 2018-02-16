#
# fs.mk
#

FS_SRC = fs-src
FS = fs

FS_BINS := $(addprefix $(FS)/bin/, init echo pwd ls cat)

$(FS): $(FS_BINS)
	@touch $@

$(FS)/bin:
	@mkdir -p $@

$(FS)/bin/init: $(FS_SRC)/sh.z80 $(FS_SRC)/string.z80
$(FS)/bin/echo: $(FS_SRC)/echo.z80 $(FS_SRC)/string.z80
$(FS)/bin/pwd: $(FS_SRC)/pwd.z80 $(FS_SRC)/string.z80
$(FS)/bin/ls: $(FS_SRC)/ls.z80 $(FS_SRC)/string.z80
$(FS)/bin/cat: $(FS_SRC)/cat.z80 $(FS_SRC)/string.z80

$(FS_BINS): | $(FS)/bin
	$(SPASM) $(SPASMOPTS) $< $@
	chmod +x $@

