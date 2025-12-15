        .text
        .globl main
#======================================================
# a0:p, a1, q
#======================================================
swap:
        lw      $t0, 0($a0)
        lw      $t1, 0($a1)

        sw      $t1, 0($a0)
        sw      $t0, 0($a1)

        jr      $ra

#======================================================
# a0:start, a1:end
#======================================================
bubblesort_pass:
bubblesort_pass_base_case:
        addiu   $t0, $a1, -4
        blt     $a0, $t0, bubblesort_pass_recursive
        jr      $ra
bubblesort_pass_recursive:
        addiu   $sp, $sp, -12
        sw      $a0, 8($sp)
        sw      $a1, 4($sp)
        sw      $ra, 0($sp)

        lw      $t0, 4($a0)
        lw      $t1, 0($a0)     
        ble     $t1, $t0, bubblesort_pass_continue
        addiu   $a1, $a0, 4
        jal     swap
        
        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
bubblesort_pass_continue:  
        addiu   $a0, $a0, 4
        jal     bubblesort_pass
        
        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 12
        jr      $ra
      
#======================================================
# a0:start, a1:end
#======================================================  
bubblesort:
        blt     $a0, $a1, bubblesort_recursive
        jr      $ra
bubblesort_recursive:
        addiu   $sp, $sp, -12
        sw      $a0, 8($sp)
        sw      $a1, 4($sp)
        sw      $ra, 0($sp)
        
        jal     bubblesort_pass
        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
        addiu   $a1, $a1, -4

        jal     bubblesort
        lw      $a0, 8($sp)
        lw      $a1, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 12

        jr      $ra

#======================================================
# a0:start, a1:end
#======================================================  
println_int_array:
        blt     $a0, $a1, println_int_array_recursive
        move    $t0, $a0
        
        la      $a0, newline
        li      $v0, 4
        syscall

        move    $a0, $t0
        
        jr      $ra
println_int_array_recursive:
        addiu   $sp, $sp, -8
        sw      $a0, 4($sp)
        sw      $ra, 0($sp)

        lw      $a0, 0($a0)
        li      $v0, 1
        syscall

        la      $a0, space
        li      $v0, 4
        syscall

        lw      $a0, 4($sp)
        addiu   $a0, $a0, 4

        jal     println_int_array
        lw      $a0, 4($sp)
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 8
        jr      $ra
main:   
        li      $s0, 0
        la      $a0, x
        move    $a1, $a0
        
while:
        li      $v0, 5
        syscall

        li      $t0, -9999
        beq     $v0, $t0, end
        
        sw      $v0, 0($a1)
        
        addiu   $a1, $a1, 4
        j       while

end:
        jal     println_int_array
        jal     bubblesort
        jal     println_int_array

        li      $v0, 10
        syscall
        
        .data
x:      .word   4 2 5 1 8 9 6 7 3
        .space  100
space:  .asciiz " "
        .space 100
newline:        .asciiz "\n"
