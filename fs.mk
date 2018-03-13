#
# fs.mk
#

FS_SRC = fs-src
FS = fs

FS_BINS := $(addprefix $(FS)/bin/, init echo pwd ls cat link unlink rmdir \
	rm mv basename dirname)

$(FS): $(FS_BINS)
	@touch $@

$(FS)/bin:
	@mkdir -p $@

$(FS)/bin/init: $(FS_SRC)/sh.z80 $(FS_SRC)/utils.z80
$(FS)/bin/echo: $(FS_SRC)/echo.z80 $(FS_SRC)/utils.z80
$(FS)/bin/pwd: $(FS_SRC)/pwd.z80 $(FS_SRC)/utils.z80
$(FS)/bin/ls: $(FS_SRC)/ls.z80 $(FS_SRC)/utils.z80
$(FS)/bin/cat: $(FS_SRC)/cat.z80 $(FS_SRC)/utils.z80
$(FS)/bin/link: $(FS_SRC)/link.z80 $(FS_SRC)/utils.z80
$(FS)/bin/unlink: $(FS_SRC)/unlink.z80 $(FS_SRC)/utils.z80
$(FS)/bin/rmdir: $(FS_SRC)/rmdir.z80 $(FS_SRC)/utils.z80
$(FS)/bin/mv: $(FS_SRC)/mv.z80 $(FS_SRC)/utils.z80
$(FS)/bin/rm: $(FS_SRC)/rm.z80 $(FS_SRC)/utils.z80
$(FS)/bin/dirname: $(FS_SRC)/dirname.z80 $(FS_SRC)/utils.z80
$(FS)/bin/basename: $(FS_SRC)/basename.z80 $(FS_SRC)/utils.z80

$(FS_BINS): | $(FS)/bin
	$(SPASM) $(SPASMOPTS) $< $@
	chmod +x $@

