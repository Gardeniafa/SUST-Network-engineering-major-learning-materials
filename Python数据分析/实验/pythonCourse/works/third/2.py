import matplotlib.pyplot as plt
import numpy as np


plt.rcParams['font.family'] = ['SimHei']


def draw_rank():
    labels = ('轻工', '材料', '环境', '电智', '食品', '机电', '镐京', '经管')
    x = np.arange(len(labels))
    au = [3, 7, 0, 2, 0, 4, 14, 0]
    ag = [1, 7, 1, 1, 3, 1, 10, 3]
    cu = [1, 1, 1, 3, 1, 5, 9, 2]
    wid = 0.23
    p = plt.subplot(111)
    r1 = p.bar(x - wid, au, wid, label='金牌', color=['#FFD95A'])
    r2 = p.bar(x, ag, wid, label='银牌', color=['#DBDFEA'])
    r3 = p.bar(x + wid, cu, wid, label='铜牌', color=['#F7B183'])
    bars = [r1, r2, r3]
    for rs in bars:
        for bar in rs:
            height = bar.get_height()
            x_pos = bar.get_x() + wid/2
            plt.text(x_pos, height, height, ha="center", va="bottom")
    p.set_ylabel('奖牌数量')
    p.set_title('校运会各学院奖牌榜（部分）')
    p.set_xticklabels(labels, )
    p.set_xticks(x)
    plt.xticks(rotation=70)
    p.legend()

    plt.show()


if __name__ == '__main__':
    draw_rank()
