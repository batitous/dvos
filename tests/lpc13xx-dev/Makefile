##########################################################################################
##                        main makefile to compile Dvos project                         ##
##########################################################################################
## Don't edit this file:                                                                ##
## -The toolchain configuration is located in Makefile.toolchainconfig                  ##
## -The project options (name, src filelist, Cflags…) is located in Makefile.options    ##
## -Dvos config is located in Dvos directory                                            ##
##########################################################################################


include Makefile.toolchainconfig
include Makefile.options
include $(DVOS_PATH)Makefile.dvos

BUILD_PATH=./build

SOURCE_FILES= $(DVOS_FILES) $(C_PROJECT)
SRC_PATH=$(SRC_KERN) $(SRC_HW) ./source

EXE=$(BUILD_PATH)/$(NAME).hex
EXE_MAIN=$(BUILD_PATH)/$(NAME).elf

# external library
LIB_USE=-lc $(BUILD_PATH)/startup.o

## Macro to compile and link:
COMPILER=$(GCC) $(COMPILER_OPTION) $(COMPILER_DEFINES) $(INCLUDE) -c
ASM_GCC=$(ASM) $(ASM_OPTIONS)
LINKER=$(GCC) $(LINKER_OPTION) -o $(EXE_MAIN)
HEX_OPTIONS= --output-target ihex $(EXE_MAIN) $(EXE)


# Object search path:
OBJ_FILES =$(patsubst %.c,$(BUILD_PATH)/%.o,$(SOURCE_FILES))

## compiler & linker & library macro :

build: $(OBJ_FILES)
	@$(ASM_GCC) $(ASM_HW) -o $(BUILD_PATH)/startup.o
	@$(LINKER) $(OBJ_FILES) $(LIB_USE)
	@$(HEX) $(HEX_OPTIONS)
	@$(SIZE) --target=ihex $(EXE)
	@$(SIZE) -A $(EXE_MAIN)

lib: $(OBJ_FILES)
	$(ARCHIVER_CMD) $(OBJ_FILES)
	
vpath %.c $(SRC_PATH)

$(BUILD_PATH)/%.o : %.c
	@echo $<
	@$(COMPILER) -o $@ $<

dump:
	$(DISASM) -d $(EXE_MAIN)

clean:
	rm $(BUILD_PATH)/*

cleanbuild:
	rm $(BUILD_PATH)/*


flash:
	$(FTDI) $(EXE) -wipe /dev/cu.usbserial-004013FD  115200 12000