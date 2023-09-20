import pygame


from pygame.sprite import Sprite
from settings import Settings


class Bullet(Sprite):
    def __init__(self, alien_setting: Settings, screen: pygame.Surface, ship):
        super().__init__()
        self.__screen = screen

        self.rect = pygame.Rect(0, 0, alien_setting.bullet['width'], alien_setting.bullet['height'])
        self.rect.centerx = ship.rect.centerx
        self.rect.top = ship.rect.top
        self.y = float(self.rect.y)
        self.color = alien_setting.bullet['rgb']
        self.speed_factor = alien_setting.bullet['speed']

    def update(self):
        self.y -= self.speed_factor
        self.rect.y = self.y

    def draw_bullet(self):
        pygame.draw.rect(self.__screen, self.color, self.rect)