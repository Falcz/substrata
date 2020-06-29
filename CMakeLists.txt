cmake_minimum_required(VERSION 3.16)
project(MinimalBoot C)

set(CMAKE_C_STANDARD 99)

add_library(MinimalBoot kernel/kernel.c kernel/util.c kernel/util.h cpu/idt.c cpu/idt.h cpu/isr.c cpu/isr.h cpu/timer.c cpu/timer.h cpu/types.h drivers/ports.c drivers/ports.h drivers/screen.c drivers/screen.h)