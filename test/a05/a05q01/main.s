        .text
        .globl main

main:   li      $v0, 5
        syscall

        move    $s0, $v0

        li      $t0, 9
        div     $s0, $t0
        mfhi    $a0

        li      $v0, 1
        syscall

        la      $a0, space
        li      $v0, 4
        syscall

        li      $s1, 0

        li      $t1, 10
        
        li      $t0, 1000
        div     $s0, $t0
        mflo    $t0
        div     $t0, $t1
        mfhi    $t0
        add     $s1, $s1, $t0

        li      $t0, 100
        div     $s0, $t0
        mflo    $t0
        div     $t0, $t1
        mfhi    $t0
        add     $s1, $s1, $t0

        li      $t0, 10
        div     $s0, $t0
        mflo    $t0
        div     $t0, $t1
        mfhi    $t0
        add     $s1, $s1, $t0

        
        div     $s0, $t1
        mfhi    $t0
        add     $s1, $s1, $t0

        move    $a0, $s1
        
        li      $v0, 1
        syscall

        la      $a0, space
        li      $v0, 4
        syscall

        li      $t0, 9
        div     $s1, $t0
        mfhi    $a0

        li      $v0, 1
        syscall

        la      $a0, newline
        li      $v0, 4
        syscall

        li      $v0, 10
        syscall

        .data
space:  .asciiz " "
newline:        .asciiz "\n"
