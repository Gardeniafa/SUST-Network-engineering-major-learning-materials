class GameStats:
    def __init__(self, alien_settings):
        self.level = None
        self.score = None
        self.alien_settings = alien_settings
        self.ships_left = 0
        self.reset_tags()
        self.game_active = not True
        self.highest = 0

    def reset_tags(self):
        self.ships_left = self.alien_settings.ship_num
        self.score = 0
        self.level = 1
