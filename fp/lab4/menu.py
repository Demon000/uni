class Entry():
    def __init__(self, key, title, action, *args, **kwargs):
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
        self.args = args
        self.kwargs = kwargs

    def show(self):
        '''
        Print this entry.
        '''
        print('{}. {}'.format(self.key, self.title))

    def run(self):
        '''
        Run this entry's action.
        '''
        self.action(*self.args, **self.kwargs)

    def matches(self, key):
        '''
        Check if this entry matches.

        Args:
            key (str): The key to match this entry against.

        Returns:
            bool: Whether this entry matches the passed key.
        '''
        return key == self.key

class Menu():
    def __init__(self, entries):
        '''
        Initialize a menu.

        Args:
            entries (list): Array of entries to be used when asking the user
                to select a valid entry.
        '''
        self.entries = entries

    def show(self):
        '''
        Print the available key and title entries.
        '''
        for entry in self.entries:
            entry.show()

    def find_entry_with_key(self, key):
        '''
        Find a matching entry.

        Args:
            key (str): Key to find an entry for.

        Returns:
            The matching entry or None if there is no such entry.
        '''
        for entry in self.entries:
            if entry.matches(key):
                return entry

        return None

    def ask(self):
        '''
        Ask the user for an entry key until the user inputs
        a valid one.
        Run the action of the found entry.
        '''
        while True:
            try:
                key = input('Select an entry: ')
                entry = self.find_entry_with_key(key)
                if not entry:
                    raise ValueError()
            except ValueError:
                print('Entry is invalid.')
                continue

            entry.run()
            break

    def run(self):
        '''
        Print the available entries and ask the user
        to choose one.
        '''
        self.show()
        self.ask()
