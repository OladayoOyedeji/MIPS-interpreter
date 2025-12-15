        .text
        .globl main

#========================================================
# a0:n, a1:k
#========================================================
j1:
        li      $t0, 1
j_base_case:    bne     $a0, $t0, j_recursive_case
        move    $v0, $t0
        jr      $ra
j_recursive_case:
        addiu   $sp, $sp, -8
        sw      $a0, 4($sp)
        sw      $ra, 0($sp)

        addi    $a0, $a0, -1
        jal     j1

        add     $v0, $v0, $a1
        addi    $v0, $v0, -1
        lw      $a0, 4($sp)
        div     $v0, $a0
        mflo    $v0
        addi    $v0, $v0, 1
        
        lw      $a0, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 8
        
        jr      $ra
        
main:   li      $v0, 5
        syscall
        
        move    $a0, $v0
        
        li      $v0, 5
        syscall

        move    $a1, $v0

        jal     j1

        move    $a0, $v0
        li      $v0, 1
        syscall
        
        la      $a0, newline
        li      $v0, 4
        syscall
        
        li      $v0, 10
        syscall

        .data
newline:        .asciiz "\n"
