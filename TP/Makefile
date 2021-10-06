PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
CC 	  = $(PREFIX)gcc
LD    = $(PREFIX)ld  ## es ld o gcc?
GDB   = gdb-multiarch

ASFLAGS = -g
LDFLAGS = -g -T ld_ram.lds ##sobre una -g
CFLAGS = -g -O1
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 #le mcpu
TARGET_MACH = $(TARGET_ARCH) ##entender mejor qué es target_arch
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
