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
# $s3 – i
# $s4 – t
#================================================================
#################################################################
# #
# text segment #
# #
#################################################################
        .text
        .globl main

main:   # get x
        li      $v0, 5          # read_input()
        syscall
        move    $s0, $v0

        # get y
        li      $v0, 5          # read_input()
        syscall
        move    $s1, $v0

        # get z
        li      $v0, 5          # read_input()
        syscall
        move    $s2, $v0

        # get i
        li      $v0, 5          # read_input()
        syscall
        move    $s3, $v0

        # get t
        li      $v0, 5          # read_input()
        syscall
        move    $s4, $v0

        add     $s2, $s2, $s3   # z + i

        div     $s1, $s2        # y / (z + i)
        mflo    $s1

        mul     $s2, $s4, $s4   # t * t
        mul     $s4, $s2, $s4

        mul     $s1, $s1, $s4   # y / (z + i) * t^3

        add     $s0, $s0, $s1   # x + y / (z + i) * t^3

        # print result
        move    $a0, $s0         # print_s0
        li      $v0, 1
        syscall

        la      $a0, NEWLINE      # prints space
        li      $v0, 4
        syscall

        li      $v0, 10         # exit
        syscall

        .data
NEWLINE:        .asciiz  "\n"
