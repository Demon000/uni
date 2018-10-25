class Entry():
    def __init__(self, key, title, action):
        self.key = str(key)
        self.title = title
        self.action = action

class Menu():
    def __init__(self, entries, *args, **kwargs):
        self.entries = entries
        self.args = args
        self.kwargs = kwargs

    def show(self):
        '''
        Prints the available key and title entries.
        '''
        for entry in self.entries:
            print('{}. {}'.format(entry.key, entry.title))

    def find_entry_with_key(self, key):
        '''
        Finds the entry with key {key}.
        Returns None if there is no such entry.
        '''
        for entry in self.entries:
            if key == entry.key:
                return entry

        return None

    def ask(self):
        '''
        Asks the user for an entry until the user inputs
        a valid one.
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

            entry.action(*self.args, **self.kwargs)
            break

    def run(self, *args, **kwargs):
        '''
        Prints the available entries and asks the user
        to choose one.
        '''
        self.show()
        self.ask()
