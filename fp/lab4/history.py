class Command():
    def __init__(self, name, *args, **kwargs):
        self.name = name
        self.args = args
        self.kwargs = kwargs

    def run(self, instance):
        attr = getattr(instance, self.name)
        return attr(*self.args, **self.kwargs)

class History():
    def __init__(self, Type):
        self.Type = Type

        self.empty_instance()
        self.empty_stack()
        self.empty_undone_stack()

    def empty_instance(self):
        self.instance = self.Type()

    def empty_stack(self):
        self.command_stack = []

    def empty_undone_stack(self):
        self.undone_command_stack = []

    def rerun(self):
        self.empty_instance()
        for command in self.command_stack:
            command.run(self.instance)

    def undo(self):
        try:
            last_command = self.command_stack.pop()
        except:
            raise ValueError('There is nothing to undo.')

        self.undone_command_stack.append(last_command)
        self.rerun()

    def redo(self):
        try:
            last_undone_command = self.undone_command_stack.pop()
        except IndexError:
            raise ValueError('There is nothing to redo.')

        self.command_stack.append(last_undone_command)
        return last_undone_command.run(self.instance)

    def do(self, name, *args, **kwargs):
        keep = kwargs.pop('keep', True)

        command = Command(name, *args, **kwargs)
        result = command.run(self.instance)

        if keep:
            self.command_stack.append(command)
            self.empty_undone_stack()

        return result
