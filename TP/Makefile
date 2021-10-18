PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
CC 	  = $(PREFIX)gcc
LD    = $(PREFIX)gcc## on utilise gcc
GDB   = gdb-multiarch

ASFLAGS = -g
LDFLAGS = -T ld_ram.lds -nostartfiles
CFLAGS = -g -O1 -c -ffreestanding#-ffreestanding pour ne pas utiliser biblioteque conventional
TARGET_ARCH = -mcpu=cortex-m4 -mthumb #on utilise mthumb pour avoir instructions par 2
TARGET_MACH = $(TARGET_ARCH)
LIBS= -lm

OBJS = main.o crt0.o init.o memfuncs.o led.o
EXE = main.elf##le quité el exe

all: $(EXE)


$(EXE):$(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@

%.o : %.s
	$(AS) $(ASFLAGS) $(TARGET_ARCH) $< -o $@


.PHONY: connect debug clean all ##sans fichiers


connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) $(EXE)

clean:
	rm -f $(EXE) $(OBJS)
