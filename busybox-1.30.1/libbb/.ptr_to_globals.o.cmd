cmd_libbb/ptr_to_globals.o := arm-linux-gnueabihf-gcc -Wp,-MD,libbb/.ptr_to_globals.o.d   -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.30.1)"  -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Os     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ptr_to_globals)"  -D"KBUILD_MODNAME=KBUILD_STR(ptr_to_globals)" -c -o libbb/ptr_to_globals.o libbb/ptr_to_globals.c

deps_libbb/ptr_to_globals.o := \
  libbb/ptr_to_globals.c \
  /usr/arm-linux-gnueabihf/include/stdc-predef.h \
  /usr/arm-linux-gnueabihf/include/errno.h \
  /usr/arm-linux-gnueabihf/include/features.h \
  /usr/arm-linux-gnueabihf/include/sys/cdefs.h \
  /usr/arm-linux-gnueabihf/include/bits/wordsize.h \
  /usr/arm-linux-gnueabihf/include/bits/long-double.h \
  /usr/arm-linux-gnueabihf/include/gnu/stubs.h \
  /usr/arm-linux-gnueabihf/include/gnu/stubs-hard.h \
  /usr/arm-linux-gnueabihf/include/bits/errno.h \
  /usr/arm-linux-gnueabihf/include/linux/errno.h \
  /usr/arm-linux-gnueabihf/include/asm/errno.h \
  /usr/arm-linux-gnueabihf/include/asm-generic/errno.h \
  /usr/arm-linux-gnueabihf/include/asm-generic/errno-base.h \
  /usr/arm-linux-gnueabihf/include/bits/types/error_t.h \

libbb/ptr_to_globals.o: $(deps_libbb/ptr_to_globals.o)

$(deps_libbb/ptr_to_globals.o):
