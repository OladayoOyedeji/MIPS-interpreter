        .text
        .globl main


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

        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
        lw      $a2, 0($sp)
        move    $v0, $a0
        addiu   $sp, $sp, 12
        jr      $ra

main:   la      $a0, str1
        la      $a1, str2
        li      $a2, 5

        jal     strcmpy

        li      $v0, 4
        syscall

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

str1:   .asciiz ""
        .space  100

str2:   .asciiz "hello world"
        .space  100

str3:   .asciiz "spam and eggs"
        
test1:  .word   str1 str1
        .word   100

test2:  .word   str1 str2
        .word   100

test3:  .word   str1 str3
        .word   100
        
        
test_cases:     .word   test1, test2, test3
