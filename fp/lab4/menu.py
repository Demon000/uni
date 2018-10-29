class Entry():
    def __init__(self, key, title, action):
        self.key = str(key)
        self.title = title
        self.action = action

class Menu():
    def __init__(self, entries):
        '''
        Initializes a menu.

        Args:
            entries (list): Array of entries to be used when asking the user
                for a valid one.
        '''
        self.entries = entries

    def show(self):
        '''
        Print the available key and title entries.
        '''
        for entry in self.entries:
            print('{}. {}'.format(entry.key, entry.title))

    def find_entry_with_key(self, key):
        '''
        Find a matching entry.

        Args:
            key (str): Key to find an entry for.

        Returns:
            The matching entry or None if there is no such entry.
        '''
        for entry in self.entries:
            if key == entry.key:
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

            entry.action()
            break

    def run(self):
        '''
        Print the available entries and ask the user
        to choose one.
        '''
        self.show()
        self.ask()
