import numpy as np
import matplotlib.pyplot as plt


class Drawer:
    def __init__(self):
        self.x = None
        self.y: np.ndarray or None = None
        self.legend = None
        self.x_label = None
        self.y_label = None
        self.colors = None

    def set_x(self, x: list):
        self.x = np.array(x)

    def add_y(self, y: list):
        if not self.y:
            self.y = np.array([y])
        else:
            if len(y) != len(self.y[0]):
                print('Invalid input: the datas should as same long. Please retry input: ')
            else:
                np.append(self.y, y)

    def set_labels(self, x: str = 'x', y: str = 'y'):
        self.x_label, self.y_label = x, y

    def set_legend(self, legend: list):
        if len(legend) != len(self.y):
            print(f'You have add {len(self.y)} groups data, but u just input {len(legend)} legend, please retry: ')
        else:
            self.legend = legend

