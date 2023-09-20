import numpy as np

if __name__ == '__main__':
    step = 0.5
    number_of_steps = 1000
    number_of_strolls = 5000

    theta = np.deg2rad(np.random.randint(0, 360, (number_of_strolls, number_of_steps)))
    x = (step * np.cos(theta)).cumsum(1)
    y = (step * np.sin(theta)).cumsum(1)
    dis = np.hypot(x, y)

    dis_greater_than_20 = np.where(dis >= 20, 1, 0)
    print(f'total {np.any(dis_greater_than_20 == 1, axis=1).sum()} times walk more than 20 meters.')
    print(f'average {np.mean(np.where(dis_greater_than_20.argmax(axis=1) > 0))} times can walk more than 20 meters.')
