import numpy as np
import matplotlib.pyplot as plt


def draw_points(n=200):
    dates = np.arange(n)
    opens = np.random.uniform(1000, 2000, size=n)
    highs = opens + np.random.uniform(0, 100, size=n)
    lows = opens - np.random.uniform(0, 100, size=n)
    closes = lows + np.random.uniform(0, 200, size=n)
    volumes = np.random.randint(1000000, 5000000, size=n)
    adj_closes = closes * np.random.uniform(0.9, 1.1, size=n)
    price_data = np.rec.fromarrays([dates, opens, highs, lows, closes, volumes, adj_closes, ],
                                   names=['date', 'open', 'high', 'low', 'close', 'volume', 'adj_close'])
    delta1 = np.diff(price_data.adj_close) / price_data.adj_close[:-1]
    volume = (15 * price_data.volume[:-2] / price_data.volume[0]) ** 2
    close = 0.003 * price_data.close[:-2] / 0.003*price_data.open[:-2]
    fig, ax = plt.subplots()
    ax.scatter(delta1[:-1], delta1[1:], c=close, s=volume, alpha=0.5)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_title('Random points')
    ax.grid(True)
    fig.tight_layout()
    plt.show()


if __name__ == '__main__':
    draw_points()
