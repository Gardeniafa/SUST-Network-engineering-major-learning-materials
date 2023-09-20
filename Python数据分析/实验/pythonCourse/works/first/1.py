from utils.timer import measure_time as mt
import numpy as np
import matplotlib.pyplot as plt


class DivisorCalculator:
    def __init__(self, num: int):
        self.num = num
        self.upper = int(num * 0.5) if num > 1 else 1

    def calculate_division_num(self) -> list:
        res = []
        for i in range(1, self.upper):
            if self.num % i == 0:
                if i > self.num ** 0.5:
                    break
                res.append(i)
                another = int(self.num / i)
                if another != i:
                    res.append(another)
        res.sort()
        return res

    def bomb_method(self):
        res = []
        for i in range(1, self.num+1):
            if self.num % i == 0:
                res.append(i)
        return res


def ana():
    # n = DivisorCalculator(int(input()))
    #
    # print(n.calculate_division_num())
    # print(n.bomb_method())
    time = {
        'sqrt': [],
        'bomb': []
    }
    ress = []
    for j in range(49):
        n = DivisorCalculator(2 ** j)
        u, v = mt(n.calculate_division_num)
        if j <= 26:
            x, y = mt(n.bomb_method)
        else:
            x, y = time['bomb'][-1], ress[-1]['bomb']
        ress.append({
            'j': j,
            'n': 2 ** j,
            'sqrt': v,
            'bomb': y
        })
        time['sqrt'].append(u)
        time['bomb'].append(x)
    plt.plot(time['sqrt'])
    plt.plot(time['bomb'])
    plt.legend(['sqrt', 'bomb'])
    plt.xlabel('j')
    plt.ylabel('time')
    plt.xticks(np.arange(0, 50, 1))
    plt.show()
    print(ress, time)


if __name__ == '__main__':
    print(' '.join(str(i) for i in DivisorCalculator(int(input('input a num:'))).calculate_division_num()))
