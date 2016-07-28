sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)/

ARCH_INCLUDE += include
KERNEL_INCLUDE += -I$(d)include

ARCH_SRCS := $(wildcard $(d)*.c)

KERNEL_SRCS += $(filter-out %main-arch.c, $(ARCH_SRCS))
$(info $(KERNEL_SRCS))
#arch: ARCH_SRCS+=arch-main.c
