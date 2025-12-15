#====================================================
# File: main.s
# Author: Oladayo Oyedeji
# INPUT:
#       a, b, c, d
# REGISTER ASSOCIATION:
#       $s0 = a
#       $s1 = b
#       $s2 = c
#       $s3 = d
#====================================================

        .text
        .globl main

main:   li      $v0, 5          # v0 = read_int()
        syscall
        move    $s0, $v0        # s0 = v0

        li      $v0, 5          # v0 = read_int()
        syscall
        move    $s1, $v0        # s1 = v0

        li      $v0, 5          # v0 = read_int()
        syscall
        move    $s2, $v0        # s2 = v0
        
        li      $v0, 5          # v0 = read_int()
        syscall
        move    $s3, $v0        # s3 = v0

        mul     $t0, $s0, $s1   # t0 = s0 * s1

        sub     $t1, $s1, $s2   # t1 = s1 - s2

        div     $t1, $s0        # t1 /= s0
        mflo    $t1

        div     $t1, $s3        # t1 %= s3
        mfhi    $t1

        add     $a0, $t0, $t1   # print(t0 + t1)
        li      $v0, 1
        syscall

        li      $v0, 5          # print_new_line()
        syscall

        li      $v0, 10         # exit
        syscall
