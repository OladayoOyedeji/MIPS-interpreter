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

main:   li      $v0, 5
        syscall
        move    $s0, $v0

        li      $v0, 5
        syscall
        move    $s1, $v0

        li      $v0, 5
        syscall
        move    $s2, $v0

        # printing
        move    $a0, $s0         # print_s0
        li      $v0, 1
        syscall
        
        la      $a0, SPACE      # prints space
        li      $v0, 4
        syscall
        
        move    $a0, $s1         # print_s0
        li      $v0, 1
        syscall
        
        la      $a0, SPACE      # prints space
        li      $v0, 4
        syscall

        move    $a0, $s2         # print_s0
        li      $v0, 1
        syscall

        la      $a0, SPACE      # prints space
        li      $v0, 4
        syscall

        # logic
        bgt     $s0, $s1, false
        bgt     $s1, $s2, false
        li      $a0, 1
        j       print
false:  li      $a0, 0
print:  li      $v0, 1
        syscall

        la      $a0, NEWLINE      # prints space
        li      $v0, 4
        syscall
        
        li      $v0, 10
        syscall

        .data
SPACE:  .asciiz  " "
NEWLINE:        .asciiz "\n"
        
