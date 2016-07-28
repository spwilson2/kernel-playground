sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)/
$(info $(d))

ALL_DIRS += $(ARCH_OBJ_DIR)$(d)

ARCH_INCLUDE += include
KERNEL_INCLUDE += -I$(d)include

ARCH_SRCS += $(wildcard $(d)*.c)
ARCH_OBJS += $(patsubst %.c,$(ARCH_OBJ_DIR)%.o,$(ARCH_SRCS))

KERNEL_SRCS += $(filter-out %main-arch.c, $(ARCH_SRCS))

arch: $(ARCH_OBJS)

#$(info $(ARCH_SRCS))
#$(info $(ARCH_OBJS))

$(ARCH_OBJ_DIR)%.o:%.c
	@echo $@
	$(CROSS_CC) $< -MM -MT $(patsubst %.d,%.o,$@) $(KERNEL_INCLUDE) >$@
	$(CROSS_CC) $< -c -o $@ $(KERNEL_INCLUDE)
