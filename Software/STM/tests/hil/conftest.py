import pytest
import os
import time

from helpers.gdb_parser.open_ocd_wrapper import OpenOCD_Wraper
from helpers.gdb_parser.gdb_wrapper import GDB_Wrapper
from helpers.gdb_parser.test_results_parser import Test_Results_Parser



def pytest_addoption(parser):
    parser.addoption("--name", action="store")

def pytest_generate_tests(metafunc):
    binary_to_flash = metafunc.config.option.name    
    
    print(f"starting {metafunc.config.option.name}\n")
    
    with OpenOCD_Wraper("/usr/share/openocd/scripts/interface/jlink.cfg", "swd","/usr/share/openocd/scripts/target/stm32l4x.cfg",binary_to_flash) as openocd_wrapper:
        print("flashing", end="")
        while not openocd_wrapper.is_flashed():
            print(".", end="")
            time.sleep(0.1)
        print("")
        
        gdb_wrapper = GDB_Wrapper(binary_to_flash, f"{os.path.dirname(__file__)}/helpers/gdb_script.gdb")
        print("waiting for test to finish", end="")
        while not gdb_wrapper.has_gdb_finished():
            print(".", end="")
            time.sleep(0.1)
        print("")

        test_result_parser = Test_Results_Parser(gdb_wrapper.get_output())

        test_cases = list(test_result_parser.get_testcases_and_expectations().keys()) 
        expectations = test_result_parser.get_testcases_and_expectations().values()


        if 'expectations' in metafunc.fixturenames:
            # Generate test cases based on the test_data list
            metafunc.parametrize('expectations', expectations, ids = test_cases)



    
