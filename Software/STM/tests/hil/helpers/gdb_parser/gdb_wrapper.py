import os
import subprocess
import threading

class GDB_Wrapper:
    def __init__(self,flashed_binary, gdb_script):
        self.gdb = subprocess.Popen(["gdb-multiarch", f"{flashed_binary}", "--command", f"{gdb_script}"],stdout=subprocess.PIPE)
        
        self.gdb_finished = False
        
        self.gdb_communicate_thread = threading.Thread(target=self.wait_for_gdb_to_finish)
        self.gdb_communicate_thread.start()
       
    def wait_for_gdb_to_finish(self):
        self.gdb.wait()
        self.out, self.err = self.gdb.communicate()
        self.gdb_finished = True
        
    def has_gdb_finished(self):
        return self.gdb_finished
    
    def get_output(self):
        if not self.has_gdb_finished():
            raise RuntimeError("GDB has not finished yet")
        # raise RuntimeError(self.out.decode("utf-8"))
        
        return self.out.decode("utf-8").split("\n")
    
    def __del__(self):
        if not self.has_gdb_finished():
            self.gdb.kill()
            
        self.gdb_communicate_thread.join()    
        
        
        
    

