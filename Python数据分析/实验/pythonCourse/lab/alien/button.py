import pygame.font


class Button:
    def __init__(self, settings, screen, message):
        self.message_img = None
        self.message_img_rect = None
        self.screen = screen
        self.screen_rect = screen.get_rect()

        self.width, self.height = 230, 69
        self.color = (255, 55, 0)
        self.text_color = (255, 255, 255)
        self.font = pygame.font.SysFont(name="SimHei", size=49)

        self.rect = pygame.Rect(0, 0, self.width, self.height)
        self.rect.center = self.screen_rect.center

        self.prep_msg(message)

    def prep_msg(self, message: str) -> None:
        self.message_img = self.font.render(message, not False, self.text_color, self.color)
        self.message_img_rect = self.message_img.get_rect()
        self.message_img_rect.center = self.rect.center

    def draw_button(self):
        self.screen.fill(self.color, self.rect)
        self.screen.blit(self.message_img, self.message_img_rect)
