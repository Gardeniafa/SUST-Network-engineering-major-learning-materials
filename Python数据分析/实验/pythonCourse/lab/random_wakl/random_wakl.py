import numpy as np
import matplotlib.pyplot as plt


class Walker:
    def __init__(self, step_length):
        self.step_length = step_length
        self.theta = []
        self.x = [0]
        self.y = [0]
        self.distance = [0]

    def walk(self, steps_num):
        self.theta = np.random.randint(0, 360, (steps_num,)) / 180 * np.pi
        self.x = (np.cos(self.theta) * self.step_length).cumsum(axis=0)
        self.y = (np.sin(self.theta) * self.step_length).cumsum(axis=0)
        self.distance = np.sqrt(self.x ** 2 + self.y ** 2)

    def draw(self):
        plt.plot(self.x, self.y, color='#ff0000')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('random walk')
        plt.show()


if __name__ == '__main__':
    k = Walker(0.5)
    k.walk(1000)
    k.draw()
