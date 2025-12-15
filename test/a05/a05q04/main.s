         .text
        .globl main

main:   li      $v0, 5
        syscall

        move    $s0, $v0
        
while:  move    $a0, $s0
        li      $v0, 1
        syscall
        la      $a0, space
        li      $v0, 4
        syscall
        
        li      $t0, 1
        beq     $s0, $t0, end
        li      $t0, 2
        div     $s0, $t0
        mfhi    $t0
        bnez    $t0, odd
        mflo    $s0
        j       while
odd:    add     $t0, $s0, $s0
        add     $s0, $s0, $t0
        addi    $s0, $s0, 1
        j       while

end:    la      $a0, newline
        li      $v0, 4
        syscall
        li      $v0, 10
        syscall

        .data
space:  .asciiz " "
newline:        .asciiz "\n"
