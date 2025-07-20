class Test_Results_Parser:
    def __init__(self, gdb_output):
        self.results = {}
        self.all_tests_passed = False
        
        test_case = ""
        expectations = []
        
        for line in gdb_output:
            print(f"debug: {line}")
            if self.__is_test_case_line(line):
               test_case = self.__parse_test_case(line)
            elif self.__is_expectation_line(line):
                expectations.append(self.__parse_expectation(line))
            elif self.__is_end_line(line):
                self.__store_result(test_case, expectations)
                expectations = []
            elif self.__is_beginning_line(line):
                self.all_tests_passed = self.__parse_all_tests_passed(line)
    
    def get_test_cases(self):
        return self.results.keys()
    
    def get_testcases_and_expectations(self):
        return self.results
    
    def did_all_tests_pass(self):
        return self.all_tests_passed
    
    def __is_test_case_line(self,line):
        if "#####" in line:
            return True
        return False
    
    def __is_beginning_line(self, line):
        if "****" in line:
            return True
        return False
    
    def __is_expectation_line(self, line):
        if "-----" in line:
            return True
        return False
    
    def __is_end_line(self, line):
        if "!!!!!!" in line:
            return True
        return False
    
    def __parse_expectation(self, line):
        expectation_line = line.split(" ")[1]
        expectation = (line.split(" ")[2], line.split(" ")[3])
        
        return (expectation_line, expectation)
    
    def __parse_all_tests_passed(self, line):
        line.split(" ")[1]
        passed = int(line.split(" ")[1])
        
        return passed == 1        
    
    def __parse_test_case(self, line):
        return line.split(" ")[1]
    
    def __store_result(self, test_case, expectations):
        self.results[test_case] = expectations
        
    

        