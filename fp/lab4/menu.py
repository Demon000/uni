class Entry():
    def __init__(self, key, title, action):
        self.key = key
        self.title = title
        self.action = action

class Menu():
    def __init__(self, entries, *args, **kwargs):
        self.entries = entries
        self.args = args
        self.kwargs = kwargs

    def show(self):
        for entry in self.entries:
            print('{}. {}'.format(entry.key, entry.title))

    def find_entry_with_key(self, key):
        for entry in self.entries:
            if key == entry.key:
                return entry

        return None

    def ask(self):
        while True:
            try:
                key = int(input('Select an entry: '))
                entry = self.find_entry_with_key(key)
                if not entry:
                    raise ValueError()
            except ValueError:
                print('Entry is invalid.')
                continue

            entry.action(*self.args, **self.kwargs)
            break

    def run(self, *args, **kwargs):
        self.show()
        self.ask()
