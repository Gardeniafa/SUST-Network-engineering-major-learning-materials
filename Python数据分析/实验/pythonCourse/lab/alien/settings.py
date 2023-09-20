class Settings:
    def __init__(self):
        import numpy
        self.screen_width = 1200
        self.screen_height = 800
        self.bg_color = (6, 67, 168)
        self.font_color = tuple(255-numpy.array(self.bg_color))
        self.ship_speed = 6

        self.bullet = {
            'speed': 150,
            'width': 3,
            'height': 30,
            'rgb': (255, 60, 60),
            'max': 3
        }

        self.star_num = 100

        self.alien_speed = 10

        self.fleet_drop_speed = 10
        self.fleet_direction = 1

        self.ship_num = 3

        self.speedup_scale = 1.1

        self.hit_one_alien_score = 33

        self.initialize_dynamic_settings()

    def initialize_dynamic_settings(self):
        self.ship_speed = 1.5
        self.bullet['speed'] = 1
        self.alien_speed = 1

        self.fleet_direction = 1

    def increase_speed(self):
        self.ship_speed *= self.speedup_scale
        self.bullet['speed'] *= self.speedup_scale
        self.alien_speed *= self.speedup_scale
