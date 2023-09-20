import pygame
from pygame.sprite import Sprite


class Star(Sprite):
    def __init__(self, screen: pygame.Surface, x: int, y: int):
        super(Star, self).__init__()
        self.screen = screen
        self.image = pygame.transform.scale(pygame.image.load('imgs/star.png'), (50, 50))
        self.rect: pygame.rect.Rect = self.image.get_rect()
        self.rect.left = x
        self.rect.top = y
        self.rect.width = 10
        self.rect.height = 11

    def blit_star(self):
        self.screen.blit(self.image, self.rect)
