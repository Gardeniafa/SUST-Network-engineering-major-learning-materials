# import the time module
import time


# define the decorator function
def timer(func):
    # define a wrapper function that takes arbitrary arguments
    def wrapper(*args, **kwargs):
        # record the start time
        start = time.time()
        # call the original function with the arguments
        result = func(*args, **kwargs)
        # record the end time
        end = time.time()
        # print the elapsed time
        print(f"{func.__name__} took {end - start} seconds to run.")
        # return the result of the original function
        return result

    # return the wrapper function
    return wrapper


def measure_time(func, *args, **kwargs):
    """
    calc time cost of a function
    :param func: the function
    :param args: any args, will fill to the function
    :param kwargs: any kwargs, will fill to the function
    :return: time cost -> float, function result -> any
    """
    start = time.time()
    result = func(*args, **kwargs)
    end = time.time()
    return end - start, result
