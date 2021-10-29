PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
CC 	  = $(PREFIX)gcc
LD    = $(PREFIX)gcc## on utilise gcc
GDB   = gdb-multiarch

ASFLAGS = -g
LDFLAGS = -T ld_ram.lds -nostartfiles
CPPFLAGS = -I CMSIS/Device/ST/STM32L4xx/Include -I CMSIS/Include #ajoute le path où sont rechercés les headers
CFLAGS = -g -O1 -c -ffreestanding -mfloat-abi=hard -mfpu=fpv4-sp-d16# on doit ajouter pour les opérations flottantes
TARGET_ARCH = -mcpu=cortex-m4 -mthumb #on utilise mthumb pour avoir instructions par 2
TARGET_MACH = $(TARGET_ARCH)
LIBS= -lm

C_OBJS = main.o crt0.o init.o memfuncs.o led.o uart.o
OBJS = $(C_OBJS) clocks.o
EXE = main.elf##le quité el exe

all: $(EXE)


$(EXE):$(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

%.o : %.c#ajoute le CPPFLAGS
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@ $(CPPFLAGS)

%.o : %.s
	$(AS) $(ASFLAGS) $(TARGET_ARCH) $< -o $@


.PHONY: connect debug clean all ##sans fichiers


connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) $(EXE)

clean:
	rm -f $(EXE) $(C_OBJS)