sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

ARCH_DIR := $(d)arch/$(ARCH)/
ARCH_OBJ_DIR := $(OBJDIR)$(ARCH)/
ALL_DIRS += $(ARCH_OBJ_DIR)

KERNEL_SRCS := $(wildcard $(d)*.c)
KERNEL_INCLUDE := -I$(d)include

KERNEL_SUBSYSTEMS := $(filter-out %include %arch, $(shell find $(d) -mindepth 1 -maxdepth 1 -type d))
KERNEL_SUBSYSTEMS += $(ARCH_DIR)

PHONY += arch kernel


define INCLUDE_template
 dir= $(shell dirname $(1))
 include $(1)
endef

SUBSYSTEMS:=$(addsuffix /makefile.inc,$(KERNEL_SUBSYSTEMS))

$(foreach subsystem,$(SUBSYSTEMS),$(eval $(call INCLUDE_template, $(subsystem))))

KERNEL_OBJS := $(patsubst %.c,$(OBJDIR)%.o,$(KERNEL_SRCS))

CLEAN += $(KERNEL_OBJS) $(OBJDIR)kernel.out

kernel: $(OBJDIR)kernel.out arch

$(OBJDIR)kernel.out: $(KERNEL_OBJS)
	$(CROSS_CC) $(KERNEL_OBJS) -o $@

$(OBJDIR)%.o: %.c
	$(CROSS_CC) $< -MM -MT $(patsubst %.d,%.o,$@) $(KERNEL_INCLUDE) >$@
	$(CROSS_CC) $< -c -o $@ $(KERNEL_INCLUDE)

-include $(KERNEL_SRCS:%.c=$(OBJDIR)%.d)
