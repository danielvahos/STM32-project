PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
CC 	  = $(PREFIX)gcc
LD    = $(PREFIX)ld
GDB   = gdb-multiarch

ASFLAGS = -g
LDFLAGS = -g -Tld_ram.lds
CFLAGS = -g -O1
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 #le mcpu
TARGET_MACH = $(TARGET_ARCH)
##LINKER_SCRIPT= ld_ram.lds  # new


OBJS = main.o
EXE = main.exe

all: $(EXE)


$(EXE):$(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@


.PHONY: connect debug clean


connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x gdbcmd

clean:
	rm -f $(EXE) $(OBJS)
