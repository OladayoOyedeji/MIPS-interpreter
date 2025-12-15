#================================================================
# Filename: main.s
# Author: Oladayo Oyedeji
# Date: 09/16/2025
#
# Description
#
# Register usage:
# $s0 - x
# $s1 – y
# $s2 – x + y
#================================================================
#################################################################
# #
# text segment #
# #
#################################################################

        .text
        .globl main

main:   # input
        li      $v0, 5          # input
        syscall
        move    $s0, $v0        # s0 = v0

        li      $v0, 5          # input
        syscall
        move    $s1, $v0        # s1 = v0

        add     $s2, $s0, $s1   # s2 = s0 + s1

        la      $a0, W1         # print("  ")
        li      $v0, 4
        syscall

        li      $t0, 10         # print(s0 / 10)
        div     $s0, $t0
        mflo    $a0

        li      $v0, 1
        syscall
        
        la      $a0, W2         # print(" ")
        li      $v0, 4
        syscall

        li      $t0, 10         # print(s0 % 10)
        div     $s0, $t0
        mfhi    $a0

        li      $v0, 1
        syscall
        
        la      $a0, NEWLINE    # print('\n')
        li      $v0, 4
        syscall
        
        la      $a0, W3         # print("+ ")
        li      $v0, 4
        syscall

        li      $t0, 10
        div     $s1, $t0
        mflo    $a0

        li      $v0, 1
        syscall
        
        la      $a0, W2
        li      $v0, 4
        syscall

        li      $t0, 10
        div     $s1, $t0
        mfhi    $a0

        li      $v0, 1
        syscall
        
        la      $a0, NEWLINE
        li      $v0, 4
        syscall

        la      $a0, W4
        li      $v0, 4
        syscall

        la      $a0, NEWLINE
        li      $v0, 4
        syscall

        
        li      $t0, 99
        ble     $s2, $t0, L
        
        li      $t0, 100
        div     $s2, $t0
        mflo    $a0

        li      $v0, 1
        syscall

        j       c

L:      la      $a0, W2
        li      $v0, 4
        syscall

c:      la      $a0, W2
        li      $v0, 4
        syscall

        li      $t0, 10
        div     $s2, $t0
        mflo    $t0

        li      $t1, 10
        div     $t0, $t1
        mfhi    $a0
        li      $v0, 1
        syscall

        la      $a0, W2
        li      $v0, 4
        syscall

        li      $t0, 10
        div     $s2, $t0
        mfhi    $a0
        li      $v0, 1
        syscall

        la      $a0, NEWLINE
        li      $v0, 4
        syscall

        la      $a0, W4
        li      $v0, 4
        syscall
        
        li      $v0, 10
        syscall

        .data
W1:     .asciiz "  "
        
W2:     .asciiz " "

W3:     .asciiz "+ "

W4:     .asciiz "-----"

NEWLINE:        .asciiz "\n"
