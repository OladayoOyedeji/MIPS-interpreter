        .text
        .globl main

#===============================================================
# a0:start, a1:end
#===============================================================
is_palindrome:
is_palindrome_base_case:
        addiu   $t0, $a1, -1
        blt     $a0, $t0, is_palindrome_recursive
        li      $v0, 1
        jr      $ra
is_palindrome_recursive:
        addiu   $sp, $sp, -12
        sw      $a0, 8($sp)
        sw      $a1, 4($sp)
        sw      $ra, 0($sp)
        addiu   $a1, $a1, -1
        lb      $t0, 0($a0)
        lb      $t1, 0($a1)

        addi    $a0, $a0, 1
        
        beq     $t0, $t1, is_palindrome_recurse
        li      $v0, 0
        j       is_palindrome_continue
       
is_palindrome_recurse: 
        jal     is_palindrome
        
is_palindrome_continue: 
        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 12
        
        jr      $ra
        
main:   la      $a0, palindrome
        li      $v0, 8
        syscall

        li      $v0, 5
        syscall
        
        addu   $a1, $a0, $v0

        jal     is_palindrome

        move    $a0, $v0
        li      $v0, 1
        syscall

        la      $a0, newline
        li      $v0, 4
        syscall
        
        li      $v0, 10
        syscall

        .data
palindrome:     .asciiz   "madam"
        .space  100
newline:        .asciiz   "\n"
