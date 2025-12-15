        .text
        .globl main
#==========================================
# n:a0
#==========================================
h:
h_base_case:    li      $t0, 5
        bgt     $a0, $t0, h_recursive_1
        li      $v0, 2
        jr      $ra
h_recursive_1:
        addiu   $sp, $sp, -12
        sw      $a0, 4($sp)
        sw      $ra, 0($sp)
        
        addi    $a0, $a0, -1
        jal     h
        sw      $v0, 8($sp)
        lw      $a0, 4($sp)
        
        addi    $a0, $a0, -2
        jal     h
        lw      $t0, 8($sp)
        
        lw      $a0, 4($sp)
        
        li      $t1, 10
        bgt     $a0, $t1, h_recursive_2
        add     $v0, $t0, $v0
        
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 12
        jr      $ra

h_recursive_2:
        addu    $v0, $v0, $v0
        sub     $t0, $t0, $v0

        sw      $t0, 8($sp)
        lw      $a0, 4($sp)
        addi    $a0, $a0, -3
        
        jal     h
        lw      $t0, 8($sp)

        add     $v0, $t0, $v0
        
        lw      $a0, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 12
        jr      $ra
main:   
        li      $v0, 5
        syscall

        move    $a0, $v0
        jal     h

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
