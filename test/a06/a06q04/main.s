        .text
        .globl main

print_space:    
        addiu   $sp, $sp, -4
        sw      $a0, 0($sp)
        la      $a0, space

        li      $v0, 4
        syscall

        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra
        
        
print_int:
        li      $v0, 1
        syscall

        jr       $ra

print_str:
        li      $v0, 4
        syscall

        jr       $ra

print_in_quotes:
        addiu   $sp, $sp, -4
        sw      $a0, 0($sp)

        la      $a0, quote
        li      $v0, 4
        syscall

        lw      $a0, 0($sp)
        li      $v0, 4
        syscall

        la      $a0, quote
        li      $v0, 4
        syscall

        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4

        jr      $ra

print_comma_space:
        addiu   $sp, $sp, -4
        sw      $a0, 0($sp)

        la      $a0, comma
        li      $v0, 4
        syscall

        la      $a0, space
        li      $v0, 4
        syscall

        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra

print_elipses:
        addiu   $sp, $sp, -4
        sw      $a0, 0($sp)

        la      $a0, elipses
        li      $v0, 4
        syscall
        
        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra

print_output_message:
        addiu   $sp, $sp, -4
        la      $a0, output_message

        li      $v0, 4
        syscall

        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra

print_newline:
        addiu   $sp, $sp, -4
        sw      $a0, 0($sp)
        la      $a0, newline
        li      $v0, 4
        syscall

        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra
        
passfail:
        bne     $a0, $0, else
        la      $a0, fail
        li      $t0, 0
        j       print
else:   la      $a0, pass
        li      $t0, 1
print:  li      $v0, 4
        syscall

        la      $a0, space
        li      $v0, 4
        syscall
        
        move    $v0, $t0
        jr      $ra

#===========================================================================
# Prototype:
# int strncmp(const char * str1, const char * str2, size_t num);
#                            a0                 a1          a2
# Compare characters of two strings
# Compares up to num characters of the C string str1 to those of the
# C-string str2.
# This function starts comparing the first character of each string. If they
# are equal to each other, it continues with the following pairs until
# the characters differ, until a terminating null-character is reached,
# or until num characters match in both strings, whichever happens first.
#
# Parameters
# str1          C string to be compared.
# str2          C string to be compared.
# num Maximum number of characters to compare.
#
# Return Value
# Returns an integral value indicating the relationship between the strings:
# A zero value indicates that the characters compared in both strings are all
# equal. A value greater than zero indicates that the first character that
# does not match has a greater value in str1 than in str2; and a value less
# than zero indicates the opposite. Your return value should be either -1,
# 0, or 1. (If your C++ compiler returns -5, then your MIPS function should
# return -1.)
#=============================================================================
strncmp:
        # save a0, a1, a2
        addiu   $sp, $sp, -12
        sw      $a0, 8($sp)
        sw      $a1, 4($sp)
        sw      $a2, 0($sp)
        
        li      $t0, 0
        li      $v0, 4

        lw      $a0, 8($sp)
        
strncmp_for:
        bge     $t0, $a2, strncmp_true

        lb      $t2, 0($a0)
        lb      $t3, 0($a1)

        bne     $t2, $t3, strncmp_false
        beq     $t2, $0, strncmp_true
        addiu   $a0, $a0, 1
        addiu   $a1, $a1, 1
        addi    $t0, $t0, 1
        j       strncmp_for

strncmp_true:
        li      $v0, 0
        j       return
        
strncmp_false:
        li      $v0, 1
        bge     $t2, $t3, return
        li      $v0, -1

        
return:         
        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
        lw      $a2, 0($sp)
        addiu   $sp, $sp, 12
        #====================
        jr      $ra
        #====================
        
test_strncmp:
        li      $s0, 0

        # save s0, ra 
        addiu   $sp, $sp, -4
        sw      $ra, 0($sp)
        
test_strncmp_for:
        #=====================================================================
        # the number of test cases are 9 so we run a for loop from address 1 -
        # 9
        #=====================================================================
        li      $t0, 9
        bge     $s0, $t0, test_strncmp_end

        #=====================================================================
        # print "Test "
        #=====================================================================
        la      $a0, test
        jal     print_str

        # print i + 1
        addi    $a0, $s0, 1
        jal     print_int

        # print ": "
        la      $a0, colon
        jal     print_str

        # print "a0->first", "a0->second", a0->third
        #=====================================================================
        la      $a1, test_cases

        add     $t0, $s0, $s0
        add     $t0, $t0, $t0
        addu    $a1, $a1, $t0

        lw      $a0, 0($a1)
        lw      $a0, 0($a0)
        jal     print_in_quotes
        jal     print_comma_space

        lw      $a0, 0($a1)
        lw      $a0, 4($a0)
        jal     print_in_quotes
        jal     print_comma_space
        
        lw      $a0, 0($a1)
        lw      $a0, 8($a0)
        jal     print_int
        jal     print_space
        #=====================================================================

        jal     print_output_message
        
        #=====================================================================
        # each a0 has the pointer to three places we need to put them in
        # a0 and a1 and a2
        #=====================================================================
        
        # put values (a0.first, a0.second, a0.third) in a0, a1 and a2 and call
        # strncmp
        #=====================================================================
        lw      $a0, 0($a1)
        lw      $a0, 0($a0)
        
        lw      $a2, 0($a1)
        lw      $a2, 8($a2)
        
        lw      $a1, 0($a1)
        lw      $a1, 4($a1)
        jal     strncmp
        #=====================================================================

        # time to call passfail, a1 has the correct values so we compare with
        # v0
        #=====================================================================
        move    $t2, $v0

        la      $a1, correct_answers
        
        add     $t0, $s0, $s0
        add     $t0, $t0, $t0
        addu    $a1, $a1, $t0
        
        lw      $a0, 0($a1)
        move    $a1, $a0
        jal     print_int
        jal     print_space
        jal     print_elipses
        jal     print_space

        seq     $a0, $t2, $a1
        jal     passfail
        jal     print_newline
        addi    $s0, $s0, 1
        j       test_strncmp_for

test_strncmp_end:
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra
        
main:   
        jal     test_strncmp

        li      $v0, 10
        syscall
        
        .data
pass:   .asciiz "pass"
fail:   .asciiz "FAIL"
space:  .asciiz " "
newline:        .asciiz "\n"
comma:        .asciiz ","
elipses:        .asciiz "..."
colon:  .asciiz ": "
output_message:        .asciiz "output(s): "
quote:  .byte   34 0

str11:  .asciiz ""
str21:  .asciiz ""
        
str12:    .asciiz "hello world"
str22:    .asciiz "hello world"
        
str13:    .asciiz "hello"
str23:    .asciiz "hellp"
        
str14:    .asciiz "hello"
str24:    .asciiz "hellq"
        
str15:    .asciiz "hellm"
str25:    .asciiz "hello"
        
str16:    .asciiz "hello"
str26:    .asciiz "hell"
        
str17:    .asciiz "hell"
str27:    .asciiz "hello"
        
str18:    .asciiz "hello"
str28:    .asciiz "hell"
        
str19:    .asciiz "hello"
str29:    .asciiz "hell"

test:   .asciiz "Test "
        
test1:  .word str11 str21
        .word   100
test2:  .word str12 str22
        .word   100
test3:  .word str13 str23
        .word   100
test4:  .word str14 str24
        .word   100
test5:  .word str15 str25
        .word   100
test6:  .word str16 str26
        .word   100
test7:  .word str17 str27
        .word   100
test8:  .word str18 str28
        .word   2
test9:  .word str19 str29
        .word   0

test_cases:     .word   test1 test2 test3 test4 test5 test6 test7 test8 test9
        
correct_answers:        .word 0 0 -1 -1 -1 1 -1 0 0
