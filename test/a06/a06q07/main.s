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

size_str:
        li      $v0, 0
size_str_for:   lb      $t0, 0($a0)
        beqz    $t0, size_str_end
        addi    $v0, $v0, 1
        addiu   $a0, $a0, 1
        j       size_str_for
size_str_end:
        jr      $ra

#======================================
# str1:a0, str2:a1, size:a2
#======================================
strcmpy:
        #==============================
        # store a0, a1, a2
        #==============================
        li      $t0, 0
        addiu   $sp, $sp, -12
        sw      $a0, 8($sp)
        sw      $a1, 4($sp)
        sw      $a2, 0($sp)
strcmpy_for:
        bge     $t0, $a2, strcmpy_end
        lb      $t1, 0($a1)

        sb      $t1, 0($a0)
        beq     $t1, $0, strcmpy_end

        addiu   $a0, $a0, 1
        addiu   $a1, $a1, 1
        addi    $t0, $t0, 1
        j       strcmpy_for
strcmpy_end:
        move    $v0, $a0
        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
        lw      $a2, 0($sp)
        addiu   $sp, $sp, 12
        jr      $ra
        
#========================================================
# buffer:a0, count:a1, format:a2, argumet:a3
#========================================================        
snprintf:
        #================================================
        # store a0, a1, a2, a3, ra
        #================================================
        addiu   $sp, $sp, -20
        sw      $a0, 16($sp)
        sw      $a1, 12($sp)
        sw      $a2, 8($sp)
        sw      $a3, 4($sp)
        sw      $ra, 0($sp)
        
        #================================================
        # counting the size of buffer and also counting
        #------------------------------------------------
        # the amount of '%' which will be stored in s0
        #------------------------------------------------
        # and then doing s1 -= 2 * s0
        #------------------------------------------------
        # s0:percent_count, s1:size
        #================================================
        li      $s0, 0
        li      $s1, 0
size_for:       lb      $t0, 0($a2)
        beqz    $t0, size_for_end
        li      $t1, 37
        bne     $t0, $t1, size_for_continue
        addi    $s0, $s0, 1

        lw      $a0, 0($a3)
        
#       "d" = 64, "c" = 63, "s"=115
#--------------------------------------------------------
        lb      $t0, 1($a2)
        li      $t1, 100
        beq     $t0, $t1, size_for_int
        
        li      $t1, 99
        beq     $t0, $t1, size_for_char
        
        li      $t1, 115
        beq     $t0, $t1, size_for_string
size_for_int:   lw      $a0, 0($a0)
        jal     size_of_int
        j       size_for_add
size_for_string:
        jal     size_str
size_for_add:
        add     $s1, $s1, $v0
        addi    $s1, $s1, -1
size_for_char:  addiu   $a2, $a2, 1
        addiu   $a3, $a3, 4
size_for_continue:
        addi    $s1, $s1, 1
        addiu   $a2, $a2, 1
        j       size_for
size_for_end:
        
        #================================================
        # calculate the size of all the strings and store
        #------------------------------------------------
        # them in s3
        #================================================
        

        bge     $s1, $a1, snprintf_return
        move    $a0, $s1
        lw      $a2, 8($sp)
        lw      $a0, 16($sp)
        lw      $a3, 4($sp)
        #================================================
        # for loop through if you see a '%' th a0 you use
        #------------------------------------------------
        # insert the corresponding string, then increase
        #------------------------------------------------
        # a3 by 4, a2 by 1, a3 by whatever it needs to be
        #------------------------------------------------
        # dawg 
        #------------------------------------------------
        # them in s3
        #================================================
str_replace_for:
        lb      $t0, 0($a2)
        
        beqz    $t0, snprintf_return
        #sb      $t0, 0($a0)
        li      $t1, 37
        bne     $t0, $t1, str_replace_else
        #================================================
        # if it encounters a '%' it copies the argument[i]
        # (0(a3)) into the buffer pointer(a0) and increases
        # format by 1
        #================================================
        lb      $t1, 1($a2)
        lw      $t0, 0($a3)

        move    $a1, $t0
        
        li      $t2, 100
        beq     $t1, $t2, str_replace_ioa
        li      $t2, 99
        beq     $t1, $t2, str_replace_cha
        li      $t2, 115
        beq     $t1, $t2, str_replace_str
        # if t1 is d change argument from int to string
str_replace_ioa:
        addiu   $sp, $sp, -4
        sw      $a0, 0($sp)
        lw      $a0, 0($t0)
        la      $a1, temp_string
        
        jal     itoa
        move    $a1, $v0
        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4
        j       str_replace_str
        
        # if t1 is c store the address in a1
str_replace_cha:
        la      $a1, temp_string
        lw      $t0, 0($t0)
        sw      $t0, 0($a1)
        sw      $0, 4($t1)
str_replace_str:
        
        jal     strcmpy
        addiu   $a0, $v0, -1
        addiu   $a2, $a2, 1
        addiu   $a3, $a3, 4
        j       str_replace_continue
str_replace_else:   sb      $t0, 0($a0)
        
        #================================================
        # increase buffer(a0), increase(format)
        #================================================
str_replace_continue:
        addiu   $a0, $a0, 1
        addiu   $a2, $a2, 1
        j       str_replace_for
snprintf_return:
        lw      $a0, 16($sp)
        lw      $a1, 12($sp)
        lw      $a2, 8($sp)
        lw      $a3, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 20
        
        jr      $ra
        
main:
        la      $a0, str1
        li      $a1, 100
        la      $a2, format1
        la      $a3, arguments1

        jal     snprintf

        la      $a0, space
        li      $v0, 4
        syscall

        la      $a0, str1
        li      $v0, 4
        syscall

        li      $v0, 10
        syscall

        .data
str1:   .byte   0
        .space 100
arg1:   .word 1
arg2:   .word 2
arg3:   .asciiz "It was a dark"
        .space 100
arg4:   .asciiz " and stormy night"
        .space 100
arg5:   .byte   0
arg6:   .word   42
format1:        .asciiz "... %s%s ... %d is the answer."
        .space 100
arguments1:      .word  arg3 arg4 arg6
temp_string:    .byte   0
        .space  100
space:  .asciiz " "
newline:      .asciiz   "\n"  
