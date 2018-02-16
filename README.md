# TIX

A UNIX-like operating system for TI84+-series calculators. The primary goal for
this project (other than me learning more about operating systems) is to be as
compliant as possible to POSIX base standards. This is not really meant to be a
useful OS that would replace TI's or anyone elses OS, especially since it is for
a calculator but not calculator-oriented.

## Building

To build a ROM file to be run in a emulator, run `make rom` (or just `make`). To
build an OS upgrade file to be sent to a calculator, run `make upgrade`. To
build both, run `make all`. Output files are placed in the `bin/` directory of
the project.

Required dependencies:
* make
* [spasm-ng](https://github.com/alberthdev/spasm-ng). Another assembler would
  work just fine, with maybe a couple tweaks to the code. I am currently working
  on an assembler to better fit the needs of TIX (in particular, userspace
  programs for it) at [tixasm](https://github.com/lePerdu/tixasm), but it is not
  in a working state right now.
* [tixfsgen](https://github.com/lePerdu/tixfsgen)
* unix2dos
* multihex, rompatch (for creating a ROM image), and packxxu (for creating an OS
  upgrade file) from [ostools](https://github.com/lePerdu/ostools), forked from
  [ostools](http://www.ticalc.org/archives/files/fileinfo/350/35057.html)
* [rabbitsign](http://www.ticalc.org/archives/files/fileinfo/383/38392.html)
* Signing key 0A (I am not 100% sure about the legality of publishing the key
  here, so you have to go find it yourself for now).

Optional dependencies:
* [TilEm2](http://lpg.ticalc.org/prj_tilem/index.html) (for `make run` and
  friends)

## Installing

Install by sending the OS upgrade (.8xu) file to a calculator using something
like TI Connect or TiLP. Note: doing so is not recommended as this is **very**
much in a development stage and could potentially brick your calculator. If for
some reason you test this on an actual calculator and it freezes or starts doing
weird stuff, popping out a battery and holding down the `DEL` key when
re-inserting it will hopefully bring you to the OS install screen from where you
can re-install TI's OS, KnightOS, OS2, etc. (or TIX if you didn't learn your
lesson).

## Testing

Instead of sending TIX to an actual calculator, the best way to test this out is
to use an emulator. `make run` and `make run-upgrade` will run the OS in TilEm2
using the ROM image and the OS upgrade file, respectively. `make debug` and
`make debug-upgrade` are the same, but start TilEm2 paused with the debugger
open. It shouldn't be too difficult to modify the makefile to support another
emulator.

## License

TIX is licensed under the MIT license. See `LICENSE` file form more information.

