import random


if __name__ == '__main__':
    while True:
        num = random.randint(1, 10)
        count = 0
        print('input your guess(between 1 and 9): ')
        while True:
            count += 1
            try:
                s = input()
                if s.lower() == 'exit':
                    exit(0)
                val = int(s)
                if val not in range(1, 10):
                    raise ValueError
            except Exception:
                count -= 1
                print('input error, please try again:')
            else:
                if val < num:
                    print('Too small, try again please:')
                elif val > num:
                    print('Too big, try again please:')
                else:
                    break
        print(f'Bingo, you have tried {count} times! Would u like to play again(`y` for next and other to end):')
        if input() not in ('y', 'Y'):
            break
