#================================================================
# Filename: main.s
# Author: Oladayo Oyedeji
# Date: 09/16/2025
#
# Description
#
# Register usage:
# $s0 - x
# $s1 – x[i]
# $s2 – max
# $s3 – second_max
# $s4 – i
#================================================================
#################################################################
# #
# text segment #
# #
#################################################################

        .text
        .globl main

main:   # initialization of the array
        la      $s0, arr                # 

        li      $v0, 5                  # input x[0]
        syscall
        sw      $v0, 0($s0)             # x[0] = input
        
        li      $v0, 5                  # input x[1]
        syscall
        sw      $v0, 4($s0)             # x[1] = input
        
        li      $v0, 5                  # input x[2]
        syscall
        sw      $v0, 8($s0)             # x[2] = input
        
        li      $v0, 5                  # input x[3]
        syscall
        sw      $v0, 12($s0)            # x[3] = input

        # max
        
LOOP:   lw      $s1, 0($s0)             # x[i]
        ble     $s1, $s2, elif          # if x[i] <= max goto elif
        move    $s3, $s2                # second_max = max
        move    $s2, $s1                # max = x[i]
        j       c                       # goto c
        
elif:   ble     $s1, $s3, c             # if x[i] <= second_max goto c
        move    $s3, $s1                # second = x[i]

c:      li      $t0, 4
        bge     $s4, $t0, END             # if i >= 4 goto END
        addi    $s0, $s0, 4               # x += 4
        addi    $s4, $s4, 1               # i++
        j       LOOP                    # goto LOOP
        
END:    move    $a0, $s3
        li      $v0, 1
        syscall
        # exit
        li      $v0, 10
        syscall

        .data
arr:    .word   0
