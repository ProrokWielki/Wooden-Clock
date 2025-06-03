target extended-remote localhost:3333

set confirm off

define hook-stop
    set $current_test=0
    set $num_of_tests=tests.size()

    printf "************************** %d **************************\n", all_tests_executed
    
    while ($current_test < $num_of_tests)
        set $current_test_object=*(tests._M_impl._M_start + $current_test)
        set $current_test_num_of_expectations=(*(tests._M_impl._M_start + $current_test)).expectations.size()
        
        printf "########################## %s_%s ##########################\n", $current_test_object.test_name_.c_str(), $current_test_object.test_case_name_.c_str()
    
        set $current_expectation=0
        while ($current_expectation < $current_test_num_of_expectations)
            set $current_expectation_object = *(($current_test_object).expectations._M_impl._M_start + $current_expectation)
    
            printf "-------------------- %s %s %s ------------------------\n", (*(($current_test_object).expectations._M_impl._M_start + $current_expectation)).first.c_str(), (*(($current_test_object).expectations._M_impl._M_start + $current_expectation)).second.first.c_str(),  (*(($current_test_object).expectations._M_impl._M_start + $current_expectation)).second.second.c_str()
            
            set $current_expectation = $current_expectation + 1
        end
    
        echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n
    
        set $current_test = $current_test + 1 
    end
    quit
end

set breakpoint pending on
b testing_framework.cpp:28
run

quit


# p (*((*(tests._M_impl._M_start)).expectations._M_impl._M_start)).second