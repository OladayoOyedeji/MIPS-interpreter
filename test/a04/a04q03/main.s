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
# $s2 – z
#================================================================
#################################################################
# #
# text segment #
# #
#################################################################

        .text
        .globl main

main:   # input
        li      $v0, 5          # read_int from user
        syscall
        move    $s0, $v0

        li      $v0, 5          # read_int from user
        syscall
        move    $s1, $v0

        li      $v0, 5          # read_int from user
        syscall
        move    $s2, $v0

        bltz    $s0, false
        bltz    $s1, false
        bltz    $s2, false
        
        mul     $s0, $s0, $s0
        mul     $s1, $s1, $s1
        mul     $s2, $s2, $s2

        add     $s0, $s0, $s1
        bne     $s0, $s2, false
true:   li      $a0, 1
        j       print
        
false:  li      $a0, 0
print:  li      $v0, 1
        syscall

        li      $v0, 10
        syscall
