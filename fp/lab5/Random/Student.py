import string
import random

class RandomStudent():
    @staticmethod
    def get_name(length=None):
        chars = []

        if length is None:
            length = random.randrange(5, 15)

        first_char = random.choice(string.ascii_uppercase)
        chars.append(first_char)

        for i in range(length):
            char = random.choice(string.ascii_lowercase)
            chars.append(char)

        return ''.join(chars)
