import pygame.font
from pygame.sprite import Group
from ship import Ship


class Scoreboard:
    def __init__(self, alien_settings, screen, stats):
        self.garage_rect = None
        self.garage_img = None
        self.ships = None
        self.level_rect = None
        self.level_img = None
        self.highest_rect = None
        self.highest_img = None
        import game_stats
        self.score_rect = None
        self.score_imgs = None
        self.screen = screen
        self.screen_rect = screen.get_rect()
        self.alien_settings = alien_settings
        self.stats: game_stats.GameStats = stats

        self.fore_ground_color = alien_settings.font_color
        self.font = pygame.font.SysFont("SimHei", 20)

        self.prep_score()
        self.prep_highest_score()
        self.prep_level()
        self.prep_ship()

    def prep_score(self):
        score_str = f'当前得分：{round(self.stats.score, -1):,}'
        self.score_imgs = self.font.render(score_str, not False, self.fore_ground_color, self.alien_settings.bg_color)

        self.score_rect = self.score_imgs.get_rect()
        self.score_rect.right = self.screen_rect.right - 20
        self.score_rect.top = 20

    def prep_highest_score(self):
        highest = f'历史最高分：{round(self.stats.highest, -1):,}'
        self.highest_img = self.font.render(highest, True, self.fore_ground_color, self.alien_settings.bg_color)

        self.highest_rect = self.highest_img.get_rect()
        self.highest_rect.centerx = self.screen_rect.centerx
        self.highest_rect.top = self.score_rect.top

    def prep_level(self):
        level = f'等级：{self.stats.level:,}'
        self.level_img = self.font.render(level, True, self.fore_ground_color, self.alien_settings.bg_color)

        self.level_rect = self.level_img.get_rect()
        self.level_rect.right = self.score_rect.right
        self.level_rect.top = self.score_rect.bottom + 13

    def prep_ship(self):
        self.ships = Group()

        garage = '可用飞船：'
        self.garage_img = self.font.render(garage, True, self.fore_ground_color, self.alien_settings.bg_color)

        self.garage_rect = self.garage_img.get_rect()
        self.garage_rect.x = 10
        self.garage_rect.top = 10

        for sn in range(self.stats.ships_left):
            ship = Ship(self.screen, self.alien_settings)
            ship.rect.x = 10 + sn * ship.rect.width + self.garage_rect.width
            ship.rect.y = 10
            self.ships.add(ship)

    def show_score(self):
        self.screen.blit(self.score_imgs, self.score_rect)
        self.screen.blit(self.highest_img, self.highest_rect)
        self.screen.blit(self.level_img, self.level_rect)
        self.ships.draw(self.screen)
        self.screen.blit(self.garage_img, self.garage_rect)
        