import pygame
import numpy as np

# 加载星星图片
star = pygame.image.load("imgs/star.png")


# 定义一个函数，传入一个surface对象和一个数字n
def draw_stars(surface, n):
    # 获取surface的宽度和高度
    width = surface.get_width()
    height = surface.get_height()

    # 使用numpy随机生成n个坐标，范围在0到width或height之间
    x_coords = np.random.randint(0, width, n)
    y_coords = np.random.randint(0, height, n)

    # 遍历每个坐标
    for x, y in zip(x_coords, y_coords):
        # 将星星缩放到合适的大小，这里假设缩放到50*50px
        scaled_star = pygame.transform.scale(star, (50, 50))

        # 将星星绘制到surface对象上，坐标为(x, y)
        surface.blit(scaled_star, (x, y))


import pygame

# 初始化pygame
pygame.init()

# 创建一个窗口，大小为800*600px
screen = pygame.display.set_mode((800, 600))

# 设置窗口标题
pygame.display.set_caption("Star Test")

# 创建一个循环，直到用户关闭窗口
count = 0
running = True
while running:
    # 处理事件
    for event in pygame.event.get():
        # 如果用户点击了关闭按钮，退出循环
        if event.type == pygame.QUIT:
            running = False

    # 填充背景色为黑色
    screen.fill((0, 0, 0))
    if count == 0:
    # 调用之前定义的函数，传入screen对象和一个数字10，表示绘制10个星星
        draw_stars(screen, 100)
        count += 1

    # 更新窗口显示
    pygame.display.flip()
    # running = False

# 退出pygame
# pygame.quit()
