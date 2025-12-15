#================================================================
# Filename: main.s
# Author: Oladayo Oyedeji
# Date: 09/16/2025
#
# Description
#
# Register usage:
# $s0 - x0
# $s1 – x1
# $s2 – x2
# $s2 – x3
#================================================================
#################################################################
# #
# text segment #
# #
#################################################################

        .text
        .globl main

main:   # input
        li      $v0, 5
        syscall
        move    $s0, $v0
        
        li      $v0, 5
        syscall
        move    $s1, $v0
        
        li      $v0, 5
        syscall
        move    $s2, $v0
        
        li      $v0, 5
        syscall
        move    $s3, $v0

        bgt     $s0, $s3, false
        bgt     $s2, $s1, false
        li      $a0, 1
        j       print

false:  li      $a0, 0
print:  li      $v0, 1
        syscall

        li      $v0, 10
        syscall
