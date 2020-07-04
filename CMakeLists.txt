cmake_minimum_required(VERSION 3.16)
project(substrata C)

set(CMAKE_C_STANDARD 99)

add_library(substrata kernel/kernel.c cpu/idt.c cpu/idt.h cpu/isr.c cpu/isr.h cpu/timer.c cpu/timer.h cpu/types.h drivers/ports.c drivers/ports.h drivers/screen.c drivers/screen.h drivers/keyboard.h drivers/keyboard.c libc/mem.c libc/mem.h libc/string.c libc/string.h kernel/kernel.h)
