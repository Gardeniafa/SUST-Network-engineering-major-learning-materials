import random
import numpy as n


def method_1():
    dis = [0]
    for i in range(1000):
        dis.append(dis[-1]+random.choice([-1, 1]))
    print(min(dis), max(dis))
    try:
        print(dis.index(30))
    except ValueError:
        print('no once time that walked fast than 30 steps.')


def method_2():
    steps = n.random.randint(0, 2, (1000, ))
    steps = n.where(steps == 0, -1, 1)
    distance = steps.cumsum(0)
    print(distance.min(), distance.max())
    print(n.where(n.abs(distance) >= 30, True, False).argmax())
    print((n.abs(distance) >= 30).argmax())


if __name__ == '__main__':
    # method_1()
    method_2()
