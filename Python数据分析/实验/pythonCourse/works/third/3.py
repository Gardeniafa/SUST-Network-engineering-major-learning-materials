import matplotlib.pyplot as plt
import numpy as n


def draw():
    x, y = n.random.rand(50), n.random.rand(50)
    colors = n.random.rand(50)
    area = (30 * n.random.rand(50)) ** 2

    plt.scatter(x, y, s=area, c=colors, alpha=0.6)
    plt.show()


if __name__ == '__main__':
    draw()
