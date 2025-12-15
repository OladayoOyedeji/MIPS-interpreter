        .text
        .globl main
        
passfail:       addiu   $sp, $sp, -4
        sw      $a0, 0($sp)
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
        lw      $a0, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra

#==========================================
# Prototype:
# size_t strnlen(const char * str1, size_t num)
# 
# Computes the length of a string
# Computes the length of string str1. The maximum length is num. The function look
# at characters of str1 from index position 0 up to at most num - 1.
#        
# Parameters
# str1          C string whose length is to be computed.
# num           Maximum number of characters the function will look at.
#
# Return Value
# The length of str1.
#==========================================
strnlen:
        addiu   $sp, $sp, -8
        sw      $a0, 4($sp)
        sw      $a1, 0($sp)
        
        addu    $a1, $a0, $a1
while:  
        lb      $t0, 0($a0)             # a[size]
        beq     $a0, $a1, end           # if size == max_size
        beq     $t0, $0, end            # if a[size] == '\0'

        addiu   $a0, $a0, 1
        j       while
end:
        move    $t0, $a0
        lw      $a0, 4($sp)
        subu    $v0, $t0, $a0

        lw      $a1, 0($sp)
        addiu   $sp, $sp, 8
        jr      $ra
        
        
main:
        #==============================================
        #FIRST RUN
        #==============================================
        la      $a0, test1              # gets ""
        li      $a1, 100                # size 100
        jal     strnlen
        move    $s0, $v0

        la      $a0, quote              # gets \"
        li      $v0, 4                  # prints ""
        syscall
        li      $v0, 4
        syscall

        la      $a0, space              # prints " "
        li      $v0, 4
        syscall

        move    $a0, $a1                # prints size
        li      $v0, 1
        syscall

        la      $a0, space              # prints " "
        li      $v0, 4
        syscall

        move    $a0, $s0                # prints result of strlen
        li      $v0, 1
        syscall

        la      $a0, space              # prints ' '
        li      $v0, 4
        syscall

        seq     $a0, $s0, $0            # a0 = (s0 == 0)
        jal     passfail

        la      $a0, newline            # print '\n'
        li      $v0, 4
        syscall

        la      $a0, quote              # print "\""
        li      $v0, 4
        syscall

        la      $a0, test2              # gets "hello world"
        li      $a1, 100                # size 100
        jal     strnlen
        move    $s0, $v0
        
        #==============================================
        #SECOND RUN
        #==============================================
        la      $a0, quote              # std::cout << "\""
        li      $v0, 4
        syscall
        
        la      $a0, test2              # std::cout << "hello world"
        li      $v0, 4
        syscall
        
        la      $a0, quote              # std::cout << "\""
        li      $v0, 4
        syscall
        
        la      $a0, space              # std::cout << " "
        li      $v0, 4
        syscall

        move    $a0, $a1                # std::cout << 100
        li      $v0, 1
        syscall

        la      $a0, space              # std::cout << " "
        li      $v0, 4
        syscall

        move    $a0, $s0                # std::cout << retval
        li      $v0, 1
        syscall

        la      $a0, space              # std::cout << " "
        li      $v0, 4
        syscall

        li      $t0, 11
        seq     $a0, $s0, $t0            # a0 = (s0 == 0)
        jal     passfail

        la      $a0, newline
        li      $v0, 4
        syscall
        
        #==============================================
        #THIRD RUN
        #==============================================
        la      $a0, quote              # print "\""
        li      $v0, 4
        syscall

        la      $a0, test2              # gets "hello world"
        li      $a1, 5                # size 100
        jal     strnlen
        move    $s0, $v0

        la      $a0, quote              # std::cout << "\""
        li      $v0, 4
        syscall
        
        la      $a0, test2              # std::cout << "hello world"
        li      $v0, 4
        syscall
        
        la      $a0, quote              # std::cout << "\""
        li      $v0, 4
        syscall
        
        la      $a0, space              # std::cout << " "
        li      $v0, 4
        syscall

        move    $a0, $a1                # std::cout << 100
        li      $v0, 1
        syscall

        la      $a0, space              # std::cout << " "
        li      $v0, 4
        syscall

        move    $a0, $s0                # std::cout << retval
        li      $v0, 1
        syscall

        la      $a0, space              # std::cout << " "
        li      $v0, 4
        syscall

        li      $t0, 5
        seq     $a0, $s0, $t0            # a0 = (s0 == 0)
        jal     passfail

        la      $a0, newline
        li      $v0, 4
        syscall
        
        li      $v0, 10                 
        syscall
        
        .data
pass:   .asciiz "pass"
fail:   .asciiz "FAIL"
space:  .asciiz " "
newline:        .asciiz "\n"
quote:  .byte   34 0
test1:  .asciiz ""
test2:  .asciiz "hello world"
