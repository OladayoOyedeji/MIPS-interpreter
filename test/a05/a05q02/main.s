        .text
        .globl main

main:   li      $v0, 5
        syscall

        move    $s0, $v0

        li      $s1, 0
FOR:    bgt     $s1, $s0, END
        move    $a0, $s1
        li      $v0, 1
        syscall

        la      $a0, TAB
        li      $v0, 4
        syscall

        mul     $t0, $s1, $s1
        mul     $a0, $t0, $s1

        li      $v0, 1
        syscall
        
        la      $a0, NEWLINE
        li      $v0, 4
        syscall

        addi    $s1, $s1, 1
        
        j       FOR
END:
        li      $v0, 10
        syscall

        .data
TAB:    .asciiz "\t"
NEWLINE:        .asciiz "\n"
