import random


class GuessNumber:
    number = ''

    def generator(self):
        nums = [0 for _ in range(4)]
        nums[0] = random.randint(1, 10)
        for i in range(1, 4):
            while True:
                n = random.randint(0, 10)
                if n not in nums:
                    nums[i] = n
                    break
        self.number = ''.join(map(str, nums))

    def check(self, user_ans) -> bool:
        """
        check player answer
        :param user_ans: user answer, len(str) = 4
        :return: guess right or not
        """
        try:
            int(user_ans)
        except Exception:
            print('bad input, try again: ')
            return False
        if user_ans[0] == '0' or user_ans.count(user_ans[0]) != 1 or user_ans.count(user_ans[1]) != 1 or \
                user_ans.count(user_ans[2]) != 1 or user_ans.count(user_ans[3]) != 1:
            print('your guess obey the rules, please check repeat and if begin is 0, try again: ')
        else:
            cows = 0
            bulls = 0
            for i in range(4):
                if self.number[i] == user_ans[i]:
                    cows += 1
                bulls += self.number.count(user_ans[i])
            bulls += -1 * cows
            if cows == 4:
                print('Bingo! cows = 4, bulls = 0')
                return True
            else:
                print(f'cows = {cows}, bulls = {bulls}, try again: ')
        return False

    def begin(self):
        self.generator()
        print('input your guess:')
        while True:
            if self.check(input()):
                break


if __name__ == '__main__':
    GuessNumber().begin()
