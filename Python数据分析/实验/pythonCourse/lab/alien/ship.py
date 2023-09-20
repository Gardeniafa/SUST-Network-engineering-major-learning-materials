import pygame
from pygame.sprite import Sprite


class Ship(Sprite):
    def __init__(self, screen: pygame.Surface, alien_settings):
        super(Ship, self).__init__()
        self.__screen = screen

        self.__img = pygame.image.load("./imgs/ship-removebg-preview.png")
        self.image = self.__img
        self.rect = self.__img.get_rect()
        self.__screen__rect = self.__screen.get_rect()

        self.rect.centerx = self.__screen__rect.centerx
        self.rect.bottom = self.__screen__rect.bottom
        self.__alien_settings = alien_settings
        self.center = float(self.rect.centerx)
        self.moving_right = False
        self.moving_left = False

        self.moving_forward, self.moving_back = False, not True

    def bli_tme(self):
        self.__screen.blit(self.__img, self.rect)

    def update(self):
        if self.moving_right:
            if self.rect.right >= self.__screen__rect.right:
                return
            self.center += self.__alien_settings.ship_speed
        if self.moving_left:
            if self.rect.left <= 0:
                return
            self.center -= self.__alien_settings.ship_speed
        if self.moving_forward:
            if self.rect.top <= 0:
                return
            self.rect.centery -= self.__alien_settings.ship_speed
        if self.moving_back:
            if self.rect.bottom >= self.__screen__rect.bottom:
                return
            self.rect.centery += self.__alien_settings.ship_speed
        self.rect.centerx = self.center

    def center_ship(self):
        self.center = self.__screen__rect.centerx
