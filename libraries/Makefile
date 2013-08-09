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
SRC_PATH=$(SRC_KERN) $(SRC_HW) $(C_PATH_PROJECT)

EXE=./$(NAME)-$(mcu).lib


## Macro to compile:
COMPILER=$(GCC) $(COMPILER_OPTION) $(COMPILER_DEFINES) $(INCLUDE) -c
ASM_GCC=$(ASM) $(ASM_OPTIONS)

# Archiver command:
AR_CMD=$(AR) -rv -o $(EXE)

# Object search path:
OBJ_FILES =$(patsubst %.c,$(BUILD_PATH)/%.o,$(SOURCE_FILES))

## compiler & linker & library macro :

build: $(OBJ_FILES)
	@$(ASM_GCC) $(ASM_HW) -o $(BUILD_PATH)/startup.o
	$(AR_CMD) $(OBJ_FILES) $(BUILD_PATH)/startup.o
	
vpath %.c $(SRC_PATH)

$(BUILD_PATH)/%.o : %.c
	@echo $<
	@$(COMPILER) -o $@ $<


clean:
	rm $(BUILD_PATH)/*

cleanbuild:
	rm $(BUILD_PATH)/*

