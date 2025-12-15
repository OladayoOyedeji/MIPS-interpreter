        .text
        .globl main

passfail:       
        addiu   $sp, $sp, -4
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
        
main:   li      $a0, 5
        jal     passfail

        move    $a0, $v0
        li      $v0, 1
        syscall

        la      $a0, newline
        li      $v0, 4
        syscall
        
        li      $a0, -3
        jal     passfail

        move    $a0, $v0
        li      $v0, 1
        syscall
        
        la      $a0, newline
        li      $v0, 4
        syscall
        
        li      $a0, 42
        jal     passfail

        move    $a0, $v0
        li      $v0, 1
        syscall
        
        la      $a0, newline
        li      $v0, 4
        syscall
        
        li      $a0, 0
        jal     passfail

        move    $a0, $v0
        li      $v0, 1
        syscall

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
