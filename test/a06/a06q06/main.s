        .text
        .globl main

size_of_int:
        li      $v0, 0
size_int_while:
        beqz    $a0, size_int_end

        li      $t0, 10
        div     $a0, $t0
        mflo    $a0

        addi    $v0, $v0, 1
        j       size_int_while
size_int_end:
        jr      $ra

#=========================================
# int_pow()                              #
#=========================================        
int_pow:
        bnez    $a1, not_zero
        li      $v0, 1
        jr      $ra

not_zero:       
        move    $v0, $a0

        li      $s0, 1
        
int_pow_for:    bge     $s0, $a1, int_pow_end
        mul     $v0, $v0, $a0
        addi    $s0, $s0, 1
        
        j       int_pow_for
int_pow_end:    jr      $ra

        
        
#=========================================================================
# value = a0, string = a1, radix = a2
#=========================================================================
itoa:
        # base case for zero
zero_case:
        bne     $a0, $0, negative_case
        li      $t0, 48
        sb      $t0, 0($a1)

        addiu   $t1, $a1, 1
        j       return_string

        # if its negative
negative_case:
        addiu   $sp, $sp,-12
        sw      $a0, 8($sp)
        sw      $a1, 4($sp)
        sw      $ra, 0($sp)
        #=======================
        # store a1 in t1
        #=======================
        move    $t1, $a1
        bgtz    $a0, positive_case
        li      $t0, 45
        sb      $t0, 0($t1)

        addiu   $t1, $t1, 1
        li      $t0, -1
        mul     $a0, $a0, $t0
        sw      $a0, 8($sp)
        
positive_case:
        #=======================
        # 
        #=======================
        
        jal     size_of_int
        addi    $s0, $v0, -1
itoa_loop:
        bltz    $s0, itoa_loop_end
        li      $a0, 10
        move    $a1, $s0
        jal     int_pow

        lw      $a0, 8($sp)
        div     $a0, $v0
        mflo    $v0
        li      $t0, 10
        div     $v0, $t0
        mfhi    $v0
        li      $t0, 48
        
        add     $t0, $t0, $v0
        sb      $t0, 0($t1)
        addiu   $t1, $t1, 1

        addi    $s0, $s0, -1
        j       itoa_loop
        
itoa_loop_end:
        lw      $ra, 0($sp)
        lw      $v0, 4($sp)
        lw      $a0, 8($sp)
        addiu   $sp, $sp, 12

return_string:
        li      $t0, 0
        sb      $t0, 0($t1)
        jr      $ra
        
main:
        li      $a0, -54445
        la      $a1, str1
        li      $a2, 10
        
        jal     itoa

        move    $a0, $v0

        li      $v0, 4
        syscall

        li      $v0, 10
        syscall

        .data
str1:   .asciiz ""
        .space 100
