import pygame
import settings
import game_functions
import numpy as np

from ship import Ship
from pygame.sprite import Group
from game_stats import GameStats
from button import Button
from scoreboard import Scoreboard


def run_game():
    pygame.init()
    pygame.font.SysFont("SimHei", 20)
    alien_settings = settings.Settings()
    stats = GameStats(alien_settings)
    screen = pygame.display.set_mode((alien_settings.screen_width, alien_settings.screen_height))
    coords = np.stack((np.random.uniform(0, screen.get_rect().right, alien_settings.star_num),
                       np.random.uniform(0, screen.get_rect().bottom, alien_settings.star_num)), axis=1)
    pygame.display.set_caption("外星人入侵")
    ship = Ship(screen, alien_settings)
    aliens = Group()
    game_functions.create_fleet(alien_settings, screen, ship, aliens)
    bullets = Group()
    play_button = Button(alien_settings, screen, '开始游戏')
    scoreboard = Scoreboard(alien_settings, screen, stats)
    while True:
        game_functions.check_events(ship, alien_settings, screen, stats, scoreboard, play_button, aliens, bullets)
        if stats.game_active:
            ship.update()
            game_functions.update_bullets(alien_settings, screen, stats, scoreboard, ship, aliens, bullets)
            game_functions.update_aliens(alien_settings, stats, scoreboard, screen, ship, aliens, bullets)
        game_functions.update_screen(alien_settings, screen, stats, scoreboard, ship, aliens, bullets, play_button, coords)


if __name__ == '__main__':
    run_game()
