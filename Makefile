# Need to add a check for current build mod, to check if we need to clean up obj

C=clang
LD=clang
CFLAGS= -W -Wall -I./$(INCLDIR) -std=c99 -D_POSIX_C_SOURCE=199309

LDFLAGS= #-L/usr/lib/x86_64-linux-gnu -lX11
EXEC=entropy
MOD=debug
EXECUTION=native
ANALYZE=no
OBJEXT=o
ifeq ($(MOD), debug)
    CFLAGS+= -g -O0
else ifeq ($(MOD), release)
	CFLAGS+= -O3
else
$(error Error : compilation mod not set correctly !)
endif
ifeq ($(EXECUTION), llvm)
ifneq ($(C), clang)
$(error Error : attempt to emit llvm IR, but not using clang)
endif
	CFLAGS += -emit-llvm
	LD = llvm-link
	EXEC := $(addprefix $(EXEC).,"bc")
	OBJEXT = bco
else
	LDFLAGS += -lm -lrt
endif
ifeq ($(ANALYZE), yes)
ifeq ($(C), clang)
	CFLAGS += --analyze
	OBJEXT = oscan
else
$(error Error : attempt to enable analysis, but not using clang)
endif
endif

	
	
LIBDIR=lib
OBJDIR=obj
SRCDIR=src
INCLDIR=include
SRC:= $(shell find $(SRCDIR) -name '*.c')

OBJ= $(notdir $(SRC:.c=.$(OBJEXT)))
ALLOBJ:= $(addprefix $(OBJDIR)/,$(OBJ))


all: pre-build $(EXEC) post-build

pre-build: build-info
	
post-build:
ifeq ($(MOD), release)
ifeq ($(EXECUTION), native)
	@echo "Stripping binary"
	@strip $(EXEC)
else
	@echo "Bytecode generated"
endif
endif
	@echo "End of compilation"

$(EXEC): $(ALLOBJ)
ifeq ($(ANALYZE), no)
	$(LD) -o $@ $^ $(LDFLAGS)
else
	@echo "No executable code output for analysis"
endif

%.$(OBJEXT): %.hxx

$(OBJDIR)/%.$(OBJEXT):  $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(C) -o $@ -c $< $(CFLAGS)

.PHONY: clean cleanall

clean: 
	rm -rf $(OBJDIR)/*

cleanall: clean 
	rm -rf $(EXEC)
	
build-info:
	@echo "--------------------------------------------------------------"
	@echo "               COMPILATION OF PROJECT : "$(EXEC)             
	@echo "Generation mod is "$(MOD)
	@echo ""
	@echo "sources directory search path is : "$(SRCDIR)" (SRCDIR)"
	@echo "includes directory search path is : "$(INCLDIR)" (INCLDIR)"
	@echo "libraries directory search path is : "$(LIBDIR)" (LIBDIR)"
	@echo "objects directory is : "$(OBJDIR)" (OBJDIR)"
	@echo "--------------------------------------------------------------"

