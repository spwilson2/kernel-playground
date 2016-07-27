sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

KERNEL_SRCS := $(wildcard $(d)*.c)
KERNEL_OBJS := $(patsubst %.c,$(OBJDIR)%.o,$(KERNEL_SRCS))
KERNEL_INCLUDE := $(d)include

KERNEL_SUBSYSTEMS := $(filter-out %include %arch, $(shell find $(d) -mindepth 1 -maxdepth 1 -type d))
KERNEL_SUBSYSTEMS += $(ARCH_DIR)

ARCH_DIR := $(d)arch/$(ARCH)/

PHONY += arch kernel

kernel: $(OBJDIR)kernel.out

$(OBJDIR)kernel.out: arch $(KERNEL_OBJS)
	$(CROSS_CC) $(KERNEL_OBJS) -o $@

arch:
	$(eval dir := $(ARCH_DIR))
	$(eval include $(ARCH_DIR)makefile.inc)
	$(eval KERNEL_INCLUDE += $(addprefix -I$(ARCH_DIR),$(ARCH_INCLUDE)))

define INCLUDE_template
 dir= $(shell dir $1) 
 include $1 
endef

SUBSYSTEMS:=$(addsuffix /makefile.inc,$(KERNEL_SUBSYSTEMS))

$(foreach subsystem,$(SUBSYSTEMS),$(eval $(call INCLUDE_template, $(subsystem))))

$(OBJDIR)%.o:%.c
	$(CROSS_CC) $< -c -o $@ $(KERNEL_INCLUDE)

CLEAN += $(KERNEL_OBJS) $(OBJDIR)kernel.out


