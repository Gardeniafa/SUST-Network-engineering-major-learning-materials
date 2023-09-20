import random as rd


class GuessTheBox:
    """
    define: 0 -> ✂   1 -> stone   2 -> cloth
    """
    sys_guess = -1

    def sys_re_guess(self):
        self.sys_guess = rd.choice(range(3))

    def judge(self, player_guess):
        sys, player, none = 'sys', 'player', 'no one'
        table = {
            0: {
                0: none, 1: player, 2: sys
            },
            1: {
                0: sys, 1: none, 2: player
            },
            2: {
                0: player, 1: sys, 2: none
            }
        }
        return table[self.sys_guess][player_guess]

    def begin(self):
        while True:
            self.sys_re_guess()
            while True:
                try:
                    player_guess = input('0 -> ✂   1 -> stone   2 -> cloth， please guess: ')
                    player_guess = int(player_guess)
                    if player_guess not in range(3):
                        raise ValueError()
                except Exception:
                    print('input error, guess again, notice: ', end='')
                else:
                    break
            print(f'{self.judge(player_guess)} win, guess again? `y` for next, other to exit:')
            if input() not in ('y', 'Y'):
                break


if __name__ == '__main__':
    GuessTheBox().begin()
