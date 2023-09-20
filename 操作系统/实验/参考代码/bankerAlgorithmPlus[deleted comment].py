import threading
import time
import typing
import random
import copy


class Computer:
    
    def __init__(self, resources: list, available: list, maximum: typing.List[list], allocated: typing.List[list]):
        try:
            
            self.resource_total_num: int = resources.__len__()
            self.resources = resources
            
            if available.__len__() != self.resource_total_num:
                raise Exception("Available array does not match resources array!")
            else:
                self.available = available
            
            self.progress_total_num = maximum.__len__()
            
            self.finished: typing.List[bool] = [False for _ in range(self.progress_total_num)]
            self.waiting: typing.List[bool] = [False for _ in range(self.progress_total_num)]
            
            self.solve_queue: typing.List[int] = []
            
            self.deadlock: bool = False
            
            self.allow_check_sys_safe: bool = False

            
            if maximum[0].__len__() != self.resource_total_num:
                raise Exception("Maximum array does not match resources array!")
            else:
                self.maximum = maximum
            
            if allocated.__len__() != self.progress_total_num:
                raise Exception("Allocated array does not match progress num!")
            else:
                
                if allocated[0].__len__() != self.resource_total_num:
                    raise Exception("Allocated array does not match resources num!")
                else:
                    self.allocated = allocated
            
            self.need: typing.List[typing.List[int]] = [[0 for __ in range(self.resource_total_num)] for _ in
                                                        range(self.progress_total_num)]
            for i in range(self.progress_total_num):
                for j in range(self.resource_total_num):
                    self.need[i][j] = self.maximum[i][j] - self.allocated[i][j]
            
            self.bk = {
                'need': copy.deepcopy(self.need),
                'available': copy.deepcopy(self.available),
                'allocate': copy.deepcopy(self.allocated)
            }
        
        except IndexError as e:
            raise IndexError("Must be maximum or allocated array out of range", e)
        except Exception as e:
            print(e)

    
    def progress(self, progress_index: int, lock: threading.Lock):
        
        while True:
            
            time.sleep(random.randint(10, 1000)/100000)
            
            lock.acquire()
            
            
            if self.deadlock:
                lock.release()
                return
            
            self.waiting[progress_index] = False
            
            lack_resources = []
            
            for i in range(self.resource_total_num):
                if self.need[progress_index][i] > self.available[i]:
                    
                    lack_resources.append([self.resources[i], f"need = {self.need[progress_index][i]}",
                                           f"available = {self.available[i]}"])
            
            
            if lack_resources:
                print(f"Progress {progress_index} is waiting for {'&'.join(str(i) for i in lack_resources)} now")
                self.waiting[progress_index] = True
                
                self.allow_check_sys_safe = True
            
            if self.waiting[progress_index]:
                lock.release()
                continue
            
            
            print(f"Progress {progress_index} is running now")
            
            self.solve_queue.append(progress_index)
            
            self.waiting[progress_index] = False
            self.finished[progress_index] = True
            
            for i in range(self.resource_total_num):
                self.available[i] += self.allocated[progress_index][i]
            print(f"Progress {progress_index} finished, available={self.available}")
            
            self.allow_check_sys_safe = False
            
            lock.release()
            break

    
    def check_died_lock(self) -> bool:
        
        for i in range(self.progress_total_num):
            if self.finished[i]:
                continue
            flag = True
            for j in range(self.resource_total_num):
                if self.need[i][j] > self.available[j]:
                    flag = False
            if flag:
                return flag
        return False

    
    def check_progress_finish(self) -> bool:
        
        return self.finished.count(False) == 0

    
    def check_system_is_not_safety(self) -> bool:
        
        lock = threading.Lock()
        
        for i in range(self.progress_total_num):
            
            process = threading.Thread(target=self.progress, args=(i, lock, ))
            process.start()
        
        while True:
            
            time.sleep(random.randint(130, 160)/10000)
            
            lock.acquire()
            
            if self.check_progress_finish():
                print(f"solve order: {' --> '.join(str(_) for _ in self.solve_queue)}")
                lock.release()
                return False
            
            if self.allow_check_sys_safe:
                if not self.check_died_lock():
                    self.deadlock = True
                    lock.release()
                    return True
            lock.release()

    
    def reset_bk_inf(self):
        
        self.available = copy.deepcopy(self.bk['available'])
        self.need = copy.deepcopy(self.bk['need'])
        self.allocated = copy.deepcopy(self.bk['allocate'])
        self.waiting = [False for _ in range(self.progress_total_num)]
        self.finished = [False for _ in range(self.progress_total_num)]
        self.solve_queue = []
        self.allow_check_sys_safe = False
        self.deadlock = False

    
    def apply_resource(self, progress_index, apply_array):
        
        bak_available = copy.deepcopy(self.available)
        bak_allocated = copy.deepcopy(self.allocated)
        bak_need = copy.deepcopy(self.need)
        
        flag = True
        for i in range(self.resource_total_num):
            
            if self.need[progress_index][i] < apply_array[i]:
                flag = False
                break
        if not flag:
            print(f"Allocate resource to progress {progress_index} failed, apply more than need!")
            return
        
        for i in range(self.resource_total_num):
            self.allocated[progress_index][i] += apply_array[i]
            self.need[progress_index][i] -= apply_array[i]
            self.available[i] -= apply_array[i]
        print("-----try to allocate and check died lock-----")
        print("after prepare allocate, the system situation: ")
        print(f"available array={self.available}\nallocated table={self.allocated}\nneed table={self.need}")
        
        if self.check_system_is_not_safety():
            
            print("Allocate failed: died lock will occur")
            print("return to last state")
            self.available = bak_available
            self.need = bak_need
            self.allocated = bak_allocated
        else:
            
            print("Allocate success")
            print(f"formal allocate resource{apply_array} to progress No.{progress_index}")
            self.available = bak_available
            self.allocated = bak_allocated
            self.need = bak_need
            for i in range(self.resource_total_num):
                self.available[i] -= apply_array[i]
                self.allocated[progress_index][i] += apply_array[i]
                self.need[progress_index][i] -= apply_array[i]
        
        
        time.sleep(0.3)
        
        self.waiting = [False for _ in range(self.progress_total_num)]
        self.finished = [False for _ in range(self.progress_total_num)]
        self.solve_queue = []
        self.deadlock = False
        self.allow_check_sys_safe = False
        print(f"available array={self.available}\nallocated table={self.allocated}\nneed table={self.need}")



def main():
    try:
        
        rs = list(input("Input all the resource and the available num, like R=1, split with space:").split(' '))
        rs_name = []
        rs_avail = []
        for i in rs:
            tmp = i.split('=')
            rs_name.append(tmp[0])
            rs_avail.append(int(tmp[-1]))
        
        mx_tb: typing.List[list] = []
        count = 1
        while True:
            try:
                s = input(f"Input the No.{count} progress maximum table, split with space, other to break:").split(' ')
                mx_tb.append(list(map(int, s)))
                count += 1
            except Exception:
                break
        
        allocated_tb: typing.List[list] = []
        count = 1
        while True:
            try:
                s = input(f"Input the No.{count} progress allocated table, "
                          f"split with space, other to break:").split(' ')
                allocated_tb.append(list(map(int, s)))
                count += 1
            except Exception:
                break
        
        cp = Computer(rs_name, rs_avail, mx_tb, allocated_tb)
        
        is_died_lock = cp.check_system_is_not_safety()
        print("check sys init died lock state:", is_died_lock)
        
        if is_died_lock:
            print("Sys occurs died lock, could not apply resource for progress...")
            print("exit...")
            return
        
        
        time.sleep(0.01)
        
        cp.reset_bk_inf()
        
        progress_num = int(input(f"Input an index(max: {cp.progress_total_num-1}) to apply resource and check by "
                                 f"banker algorithm:"))
        
        apply_arr = list(map(int, input(f"Input the resources {cp.resources} want to apply, split by space:").split(' ')))
        
        cp.apply_resource(progress_num, apply_arr)
    
    except Exception as e:
        print(e)


if __name__ == '__main__':
    main()
