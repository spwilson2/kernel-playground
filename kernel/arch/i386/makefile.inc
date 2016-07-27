sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

ARCH_INCLUDE := include

ARCH_SRCS := $(wildcard $(d)*.c)

#$(OBJDIR)$(d)%.d:$(d)%.c
#	$(CROSS_CC) $< -MM -MT $@ $(KERNEL_INCLUDE)
