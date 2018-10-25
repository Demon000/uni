class Command():
    def __init__(self, name, *args, **kwargs):
        self.name = name
        self.args = args
        self.kwargs = kwargs

    def run(self, instance):
        '''
        Calls the attribute with name on the passes instance.
        '''
        attr = getattr(instance, self.name)
        return attr(*self.args, **self.kwargs)

class History():
    def __init__(self, Type):
        self.Type = Type

        self.empty_instance()
        self.empty_stack()
        self.empty_undone_stack()

    def empty_instance(self):
        '''
        Empties the instance.
        '''
        self.instance = self.Type()

    def empty_stack(self):
        '''
        Empties the commands stack.
        '''
        self.command_stack = []

    def empty_undone_stack(self):
        '''
        Empties the undone command stack.
        '''
        self.undone_command_stack = []

    def rerun(self):
        '''
        Empties the instance and reruns the command stack.
        '''
        self.empty_instance()
        for command in self.command_stack:
            command.run(self.instance)

    def undo(self):
        '''
        Removes the last command from the command stack and adds
        it to the undone command stack.
        Empties the instance and reruns the remaining commands.
        Raises a ValueError if there are no commands on the
        command stack.
        '''
        try:
            last_command = self.command_stack.pop()
        except:
            raise ValueError('There is nothing to undo.')

        self.undone_command_stack.append(last_command)
        self.rerun()

    def redo(self):
        '''
        Removes the last command from the undone command stack and adds
        it to the command stack, then runs the command.
        Raises a ValueError if there are no commands on the undone
        command stack.
        '''
        try:
            last_undone_command = self.undone_command_stack.pop()
        except IndexError:
            raise ValueError('There is nothing to redo.')

        self.command_stack.append(last_undone_command)
        return last_undone_command.run(self.instance)

    def do(self, name, *args, **kwargs):
        '''
        Creates a new command using the passed arguments, runs it,
        and stores it in the command stack.
        Empties the undone command stack unless the keep parameter is False.
        '''
        keep = kwargs.pop('keep', True)

        command = Command(name, *args, **kwargs)
        result = command.run(self.instance)

        if keep:
            self.command_stack.append(command)
            self.empty_undone_stack()

        return result
