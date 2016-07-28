ARCH:=i386
OBJDIR:=obj/

TARGET_TRIPLE:=

CROSS_CC:=$(TARGET_TRIPLE)gcc

ifneq ($(filter %clean ,$(MAKECMDGOALS)),)
NOMAKEDIR:=1
endif

PHONY := all build-dirs clean dist-clean
all: kernel

dir:=kernel/
include kernel/makefile.inc

ALL_SRCS += $(KERNEL_SRCS)
ALL_SRC_DIRS += $(dir $(ALL_SRCS))
ALL_DIRS += $(addprefix $(OBJDIR),$(ALL_SRC_DIRS))

clean:
	rm -rf $(CLEAN)

dist-clean:
	$(MAKE) clean
	rm -rf $(OBJDIR)

ifndef NOMAKEDIR
$(shell mkdir -p $(OBJDIR) $(ALL_DIRS))
endif

$(OBJDIR)%.o:%.c
	$(CROSS_CC) $< -c -o $@ $(KERNEL_INCLUDE)

.PHONY: $(PHONY)
