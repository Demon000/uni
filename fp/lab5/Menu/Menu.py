from Menu.Entry import Entry

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
