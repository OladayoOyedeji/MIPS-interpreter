test_strncmp:
        li      $s0, 0

        # save s0, ra 
        addiu   $sp, $sp, -8
        sw      $ra, 4($sp)
        sw      $s0, 0($sp)
test_strncmp_for:
        li      $t0, 9
        bge     $s0, $t0, test_strncmp_end

        la      $a0, test
        jal     print_str

        add     $a0, $s1, 1
        jal     print_int

        la      $a0, colon
        jal     print_str

        la      $a1, test_cases

        add     $t0, $s0, $s0
        add     $t0, $t0, $t0
        addu    $a1, $a1, $t0

        la      $a0, 0($a1)
        jal     print_in_quotes
        jal     print_comma_space

        la      $a0, 4($s0)
        jal     print_in_quotes
        jal     print_comma_space
        
        la      $a0, 8($s0)
        jal     print_int
        jal     print_space
        jal     print_elipses
        jal     print_space
        jal     print_output_message

        jal     strncmp
        move    $a0, $v0

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

        seq     $a0, $v0, $a1
        jal     passfail
        jal     print_newline

        j       test_strncmp_for

test_strcmp_end:
        # restore ra
        lw      $ra, 4($sp)
        addiu   $sp, $sp, 8
        jr      $ra

        
        
