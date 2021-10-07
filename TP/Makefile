PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
CC 	  = $(PREFIX)gcc
LD    = $(PREFIX)gcc## es ld o gcc?
GDB   = gdb-multiarch

ASFLAGS = -g -c#les agrego c
LDFLAGS = -T ld_ram.lds -nostartfiles##sobre una -g
CFLAGS = -g -O1 -c#agrego c
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
TARGET_MACH = $(TARGET_ARCH) ##entender mejor qué es target_arch
##LINKER_SCRIPT= ld_ram.lds  # new
LIBS= -lm

OBJS = main.o
EXE = main ##le quité el exe

all: $(EXE)


$(EXE):$(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@

%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@


.PHONY: connect debug clean


connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) $(EXE)

clean:
	rm -f $(EXE) $(OBJS)
