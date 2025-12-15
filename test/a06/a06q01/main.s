        .text
        .globl main

print_int:      li      $v0, 1
        syscall

        jr       $ra

print_string:   li      $v0, 4
        syscall

        jr       $ra

read_int:       li      $v0, 5
        syscall

        jr       $ra

read_string:    li      $v0, 8
        syscall

        li      $v0, 4
        syscall
        
        jr      $ra
          
main:
        li      $a0, -5
        jal     print_int

        la      $a0, newline
        jal     print_string
        
        li      $a0, 42
        jal     print_int
        
        la      $a0, newline
        jal     print_string

        la      $a0, helloworld
        jal     print_string
        
        la      $a0, newline
        jal     print_string
        
        la      $a0, s_a_e
        jal     print_string

        jal     read_int

        move    $a0, $v0
        li      $v0, 1
        syscall

        li      $a1, 100
        jal     read_string

        li      $v0, 10
        syscall

        .data
helloworld:     .asciiz "hello world"
newline:        .asciiz "\n"
s_a_e:  .asciiz "spam and eggs\n"

        
