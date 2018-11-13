class Entry():
    def __init__(self, key, title, action):
        '''
        Initialize an entry.

        Args:
            key (str): Key which will be used when asking the user
                to select a valid entry.
            title (str): Title which will be used when asking the user
                to select a valid entry.
            action (function): Function which will be called if the user
                selects this command.
        '''
        self.key = str(key)
        self.title = title
        self.action = action

    def show(self):
        '''
        Print this entry.
        '''
        print('{}. {}'.format(self.key, self.title))

    def run(self):
        '''
        Run this entry's action.
        '''
        self.action()

    def matches(self, key):
        '''
        Check if this entry matches.

        Args:
            key (str): The key to match this entry against.

        Returns:
            bool: Whether this entry matches the passed key.
        '''
        return key == self.key
