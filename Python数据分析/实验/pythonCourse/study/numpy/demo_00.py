import numpy as np
import matplotlib.pyplot as plt


# walk times
times = 1
# once walk steps
steps = 1000
# random forward or back
rand_steps = np.random.randint(0, 2, (times, steps))
rand_steps = np.where(rand_steps > 0, rand_steps, -1)
# calc steps on the first axis
dis_det = rand_steps.cumsum(axis=1)
# print the min max as max steps in left or right on the first axis
print(dis_det.min(axis=1), dis_det.max(axis=1))
# calc every step's distance if greater than 30
dis_30 = np.abs(dis_det) >= 30
# find the place greater than 30 on the first axis
print(dis_30.argmax(axis=1))
# calc the num of walk that max steps greater than 30
print(dis_30.any(axis=1).sum())
# calc the avg index steps bigger than 30
print(dis_30.argmax(axis=1).mean())


plt.scatter(dis_det[0], dis_det[0])
plt.show()
