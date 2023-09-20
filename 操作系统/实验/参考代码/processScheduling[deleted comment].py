class PCB:
    def __init__(self, program_name: str, time_require: int, priority: int, pointer=None):
        
        self.program_name = program_name
        self.time_require = time_require
        self.priority = priority
        
        self.state = 'R'
        self.next = pointer

    @property
    def get_priority(self):
        return self.priority

    
    def __str__(self):
        return f"{self.program_name}: time_require={self.time_require} priority={self.priority} state={self.state}"


class PCBList:
    def __init__(self):
        
        self.ready_list_header = PCB("header", -1, -1)
        
        self.programs_num = 0
        self.running_counter = 0
        self.finished = None

    
    def add_program(self, program: PCB):
        
        ptr = self.ready_list_header
        
        cur: PCB = ptr.next
        
        insert_in_middle = False
        
        while cur is not None:
            
            if cur.get_priority < program.get_priority:
                program.next = cur
                ptr.next = program
                
                insert_in_middle = True
                break
            else:
                ptr = cur
                cur = ptr.next
        
        if not insert_in_middle:
            ptr.next = program
        
        self.programs_num += 1

    
    def get_ready_list(self) -> str:
        
        string: str = ""
        
        ptr: PCB = self.ready_list_header.next
        
        if ptr is None:
            return "All program finished!"
        
        while ptr is not None:
            
            string += f"{{{str(ptr)}}}, "
            ptr = ptr.next
        
        return string[:-2]

    
    def get_finished_list(self) -> str:
        
        string: str = ""
        ptr: PCB = self.finished
        if ptr is None:
            return "None program finished!"
        while ptr is not None:
            string += f"{{{str(ptr)}}}, "
            ptr = ptr.next
        return string[:-2]

    
    def run(self):
        
        self.running_counter += 1
        
        ptr: PCB = self.ready_list_header
        
        cur: PCB = ptr.next
        
        print(f"Run {self.running_counter} --> \033[1;35m{cur.program_name}\033[0m is running...")
        
        ptr.next = cur.next
        
        cur.time_require += -1
        cur.priority += -1
        
        if cur.time_require == 0:
            
            cur.state = "E"
            
            cur.next = self.finished
            self.finished = cur
            
            print(f"\033[1;33m    | A new program finished: {{{str(cur)}}}\033[0m")
        else:
            
            cur.next = None
            
            self.add_program(cur)
        
        print("    | running state: ", self.get_ready_list())



def process_scheduling():
    
    process_list = PCBList()
    
    while True:
        try:
            
            
            s = input(" | input a new line string with program_name, time_require and priority, split with space, "
                      "\n |__other format to break:")
            sl = s.split(" ")
            process_list.add_program(PCB(sl[0], int(sl[1]), int(sl[2])))
        except Exception:
            break
    
    print("Init state: ", process_list.get_ready_list())
    
    while process_list.ready_list_header.next is not None:
        process_list.run()



if __name__ == '__main__':
    process_scheduling()
