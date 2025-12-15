        .text
        .globl main

hanoi:
hanoi_base:
        li      $t0, 1
        bne     $a0, $t0, hanoi_recursive
        move    $a0, $a1
        li      $v0, 1
        syscall
        la      $a0, space
        li      $v0, 4
        syscall
        move    $a0, $a3
        li      $v0, 1
        syscall

        
        la      $a0, newline
        li      $v0, 4
        syscall

        jr      $ra

hanoi_recursive:
        addiu   $sp, $sp, -20
        sw      $a0, 16($sp)
        sw      $a1, 12($sp)
        sw      $a2, 8($sp)
        sw      $a3, 4($sp)
        sw      $ra, 0($sp)
        
        addi    $a0, $a0, -1
        lw      $a2, 4($sp)
        lw      $a3, 8($sp)
        
        jal     hanoi

        li      $a0, 1
        lw      $a1, 12($sp)
        lw      $a2, 8($sp)
        lw      $a3, 4($sp)

        jal     hanoi

        lw      $a0, 16($sp)
        addi    $a0, $a0, -1
        lw      $a1, 8($sp)
        lw      $a2, 12($sp)
        lw      $a3, 4($sp)

        jal     hanoi

        # restore from the stack
        lw      $a0, 16($sp)
        lw      $a1, 12($sp)
        lw      $a2, 8($sp)
        lw      $a3, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 20

        jr      $ra
main:   
        li      $v0, 5
        syscall

        move    $a0, $v0

        li      $a1, 0
        li      $a2, 1
        li      $a3, 2

        jal     hanoi

        li      $v0, 10
        syscall
        .data
space:  .asciiz " "
newline:        .asciiz "\n"
