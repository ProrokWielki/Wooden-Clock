import subprocess
import threading

class OpenOCD_Wraper:
    def __init__(self, interface_config_file, transport, target_config_file, binary_to_flash):
        self.openocd_output = []
        self.close = False
        
        self.openocd = subprocess.Popen(["openocd",  "-f", f"{interface_config_file}", "-c" f"transport select {transport}", "-f", f"{target_config_file}","-c", f"program {binary_to_flash}  verify reset"],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        
        self.output_collector_thread = threading.Thread(target=self.collect_outout)
        self.output_collector_thread.start()
        
    def collect_outout(self):
        while not self.close:
            line = self.openocd.stderr.readline()
            if not line:
                break
            self.openocd_output.append(line.decode("utf-8"))
        
    def is_flashed(self):
        for line in self.openocd_output:
            if "** Verified OK **" in line:
                return True
        return False
        
    
    def terminate(self):
        print("calling destructor")
        self.close = True
        self.openocd.kill()
        self.output_collector_thread.join()
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_value, traceback):
        self.terminate()
 
