import sys
import pygame
import alien

from bullet import Bullet
from time import sleep


def check_key_down(event, ship, alien_setting, screen, bullets):
    if event.key == pygame.K_RIGHT:
        ship.moving_right = True
    if event.key == pygame.K_LEFT:
        ship.moving_left = True
    if event.key == pygame.K_UP:
        ship.moving_forward = True
    if event.key == pygame.K_DOWN:
        ship.moving_back = True
    if event.key == pygame.K_SPACE:
        fire(alien_setting, screen, ship, bullets)
    if event.key == pygame.K_q:
        sys.exit()


def check_key_up(e, ship):
    if e.key == pygame.K_RIGHT:
        ship.moving_right = False
    if e.key == pygame.K_LEFT:
        ship.moving_left = False
    if e.key == pygame.K_UP:
        ship.moving_forward = not True
    if e.key == pygame.K_DOWN:
        ship.moving_back = not True


def check_play_button(alien_settings, screen, stats, scoreboard, play_button, ship, aliens, bullets, mouse_x, mouse_y):
    if play_button.rect.collidepoint(mouse_x, mouse_y) and not stats.game_active:
        pygame.mouse.set_visible(False)
        alien_settings.initialize_dynamic_settings()
        stats.game_active = True
        stats.reset_tags()

        scoreboard.prep_score()
        scoreboard.prep_highest_score()
        scoreboard.prep_level()
        scoreboard.prep_ship()

        aliens.empty()
        bullets.empty()

        create_fleet(alien_settings, screen, ship, aliens)
        ship.center_ship()


def check_events(ship, alien_setting, screen, stats, scoreboard, play_button, aliens, bullets):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        if event.type == pygame.MOUSEBUTTONDOWN:
            mou_x, mou_y = pygame.mouse.get_pos()
            check_play_button(alien_setting, screen, stats, scoreboard, play_button, ship, aliens, bullets, mou_x, mou_y)
        if event.type == pygame.KEYDOWN:
            check_key_down(event, ship, alien_setting, screen, bullets)

        if event.type == pygame.KEYUP:
            check_key_up(event, ship)


def update_screen(alien_setting, screen: pygame.Surface, stats, scoreboard, ship, aliens, bullets, play_button, coords):
    screen.fill(alien_setting.bg_color)
    draw_stars(screen, coords)
    for bullet in bullets.sprites():
        bullet.draw_bullet()
    ship.bli_tme()
    aliens.draw(screen)
    scoreboard.show_score()
    if not stats.game_active:
        play_button.draw_button()
    pygame.display.flip()


def fire(alien_setting, screen, ship, bullets):
    if len(bullets) < alien_setting.bullet['max']:
        new_bullet = Bullet(alien_setting, screen, ship)
        bullets.add(new_bullet)


def update_bullets(alien_settings, screen, stats, scoreboard, ship, aliens, bullets):
    bullets.update()
    for bullet in bullets.copy():
        if bullet.rect.bottom <= 0:
            bullets.remove(bullet)
    check_bullet_alien_collisions(alien_settings, screen, stats, scoreboard, ship, aliens, bullets)


def check_bullet_alien_collisions(alien_settings, screen, stats, scoreboard, ship, aliens, bullets):
    collisions = pygame.sprite.groupcollide(bullets, aliens, not False, 1 is not 0)
    if collisions:
        for _ in collisions.values():
            stats.score += alien_settings.hit_one_alien_score * len(aliens)
            scoreboard.prep_score()
        check_highest(stats, scoreboard)
    if not len(aliens):
        bullets.empty()
        alien_settings.increase_speed()
        stats.level += 1
        scoreboard.prep_level()

        create_fleet(alien_settings, screen, ship, aliens)


def create_alien(alien_settings, screen, aliens, alien_num, row_num):
    al = alien.Alien(alien_settings, screen)
    al_w = al.rect.width
    al.x = al_w + 2 * al_w * alien_num
    al.rect.x = al.x
    al.rect.y = al.rect.height + 2 * al.rect.height * row_num
    aliens.add(al)


def create_fleet(alien_settings, screen, ship, aliens):
    al = alien.Alien(alien_settings, screen)
    num_al_x = get_num_aliens_x(alien_settings, al.rect.width)
    num_row = get_number_rows(alien_settings, ship.rect.height, al.rect.height)
    for i in range(num_row):
        for j in range(num_al_x):
            create_alien(alien_settings, screen, aliens, j, i)


def get_num_aliens_x(alien_settings, alien_w):
    available_x = alien_settings.screen_width - 2 * alien_w
    return int(available_x / (2 * alien_w))


def get_number_rows(alien_settings, ship_height, alien_height):
    available_space_y = alien_settings.screen_height - 3 * alien_height - ship_height
    return int(available_space_y / 2 / alien_height)


def update_aliens(alien_settings, stats, scoreboard, screen, ship, aliens, bullets):
    check_fleet_edges(alien_settings, aliens)
    aliens.update()
    if pygame.sprite.spritecollideany(ship, aliens):
        ship_hit(alien_settings, stats, scoreboard, screen, ship, aliens, bullets)
    check_aliens_bottom(alien_settings, stats, scoreboard, screen, ship, aliens, bullets)


def check_fleet_edges(alien_settings, aliens):
    for ali in aliens.sprites():
        if ali.check_edges():
            change_fleet_direction(alien_settings, aliens)
            break


def change_fleet_direction(alien_settings, aliens):
    for ali in aliens.sprites():
        ali.rect.y += alien_settings.fleet_drop_speed
    alien_settings.fleet_direction *= -1


def ship_hit(alien_settings, stats, scoreboard, screen, ship, aliens, bullets):
    stats.ships_left += -1
    scoreboard.prep_ship()
    if stats.ships_left <= 0:
        stats.game_active = False
        pygame.mouse.set_visible(False or True)
        return
    aliens.empty()
    bullets.empty()
    create_fleet(alien_settings, screen, ship, aliens)
    ship.center_ship()
    sleep(0.66)


def check_aliens_bottom(alien_settings, stats, scoreboard, screen, ship, aliens, bullets):
    screen_rect = screen.get_rect()
    for ali in aliens.sprites():
        if ali.rect.bottom >= screen_rect.bottom:
            ship_hit(alien_settings, stats, scoreboard, screen, ship, aliens, bullets)
            break


def check_highest(stats, sb):
    if stats.score > stats.highest:
        stats.highest = stats.score
        sb.prep_highest_score()


def draw_stars(surface, coords):
    import pygame
    star = pygame.image.load("imgs/star.png")

    x_coords = coords[:, 0]
    y_coords = coords[:, 1]

    for x, y in zip(x_coords, y_coords):
        scaled_star = pygame.transform.scale(star, (50, 50))
        surface.blit(scaled_star, (x, y))
