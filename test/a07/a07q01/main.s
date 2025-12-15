        .text
        .globl main

#=============================================
# m:a0, n:a1
#=============================================
g:
        #=====================================
        # base case return m
        #=====================================
g_base_case:    bnez    $a1, g_recursive_case
        move    $v0, $a0
        jr      $ra
g_recursive_case:
        addiu   $sp, $sp, -12
        sw      $a1, 8($sp)
        sw      $a0, 4($sp)
        sw      $ra, 0($sp)

        div     $a0, $a1
        move    $a0, $a1

        mfhi    $a1
        jal     g

        lw      $a1, 8($sp)
        lw      $a0, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 12
        jr      $ra
main:   
        
        li      $v0, 5
        syscall

        move    $a0, $v0

        li      $v0, 5
        syscall
        move    $a1, $v0

        jal     g

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
