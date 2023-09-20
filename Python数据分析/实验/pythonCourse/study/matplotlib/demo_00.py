import matplotlib.pyplot as mpl
import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['font.family'] = ['SimHei']


def main():
    fig = mpl.figure(facecolor='#ffffff', edgecolor='#666666', figsize=(16, 9))
    nums = np.arange(1, 11)
    mpl.subplot(221)
    mpl.plot(nums, nums)
    mpl.subplot(222)
    mpl.plot(nums, -1 * nums)
    mpl.subplot(212)
    mpl.plot(nums, pow(nums, 2))

    fig.add_subplot(339)
    mpl.plot(np.random.randn(100))

    mpl.show()


def demo_01():
    nums = np.arange(10, 0.1)

    fig = mpl.figure(figsize=(16, 9), dpi=300)
    _, pics = mpl.subplots(2, 2)

    pics[0, 1].plot(nums, nums * 3)
    pics[0, 1].plot(nums, nums / 2)

    mpl.subplots_adjust(wspace=0.2, hspace=0.2)

    mpl.title("demo plot fig")
    mpl.xlabel('横轴')
    mpl.ylabel('纵轴')
    mpl.xticks([0, 0.3, 10])
    mpl.yticks([0, 0.5, 30])

    mpl.show()


def demo_legend():
    plt.figure(dpi=300, figsize=(4, 3))
    nums = np.arange(0, 10, 0.1)
    plt.title('ren min wan sui!')
    plt.xlabel('x')
    # plt.ylabel('y', r)

    plt.xticks(np.arange(0, 10 + 0.1, 2))
    plt.yticks(np.arange(0, 100, 5))

    plt.plot(nums, nums)
    plt.plot(nums, nums / 2)
    plt.plot(nums, nums * 3)
    plt.plot(nums, nums ** 2)
    plt.plot(nums, np.log10(nums))
    plt.plot(nums, np.sin(nums * np.pi))

    plt.legend(['tan', 'div', 'mult', 'pow', 'log', 'sine'])

    plt.show()


def sub_config():
    fig = plt.figure()
    pic1 = fig.add_subplot(111)
    pic1.plot(np.where(np.random.randint(0, 2, 1000) == 1, 1, -1).cumsum(0))
    pic1.plot(np.where(np.random.randint(0, 2, 1000) == 1, 1, -1).cumsum(0))
    pic1.set_title('rand walker sum')
    pic1.set_xlabel('steps')
    pic1.set_ylabel('distance')
    pic1.set_ylim([-50, 50])
    pic1.set_xlim([0, 1000])
    pic1.set_xlabel(['0.1k', '0.2k', '0.3k'])
    pic1.legend(('walker A', 'walker B'))
    plt.show()


def bar_():
    labels = ('轻工', '材料', '环境', '食品', '机电', '经管')
    x = np.arange(len(labels))
    au = [3, 7, 0, 0, 4, 0]
    ag = [1, 7, 1, 3, 1, 3]
    cu = [1, 1, 1, 1, 5, 2]
    wid = 0.23
    p = plt.subplot(111)
    r1 = p.bar(x - wid, au, wid, label='金牌', color=['r'])
    r2 = p.bar(x, ag, wid, label='银牌', color=['g'])
    r3 = p.bar(x + wid, cu, wid, label='铜牌', color=['b'])
    p.set_ylabel('奖牌数量')
    p.set_title('校运会各学院奖牌榜（部分）')
    p.set_xticklabels(labels, )
    p.set_xticks(x)
    plt.xticks(rotation=70)
    p.legend()

    plt.show()



def liu():
    x = np.arange(1, 8, 2)
    N_0 = np.array([0.006, 0.00267, 0.051, 0.0786])
    N_1 = np.array([0.017, 0.0053, 0.085, 0.0767])
    N_3 = np.array([0.013, 0.0023, 0.027, 0.064])
    N_5 = np.array([0.01, 0.00767, 0.0362, 0.009])

    plt.plot(x, N_0, color='#ff0000', marker='v')
    plt.plot(x, N_1, color='#00ff00', marker='o')
    plt.plot(x, N_3, color='#0000ff', marker='s')
    plt.plot(x, N_5, color='#000000', marker='p')

    plt.xticks(x)
    plt.xlabel('X')
    plt.ylabel('Y')

    plt.legend(('N-0', 'N-1', 'N-3', 'N-5'))
    plt.show()


if __name__ == '__main__':
    liu()
