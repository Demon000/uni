class Command():
    def __init__(self, name, *args, **kwargs):
        '''
        Initialize a command.

        Args:
            name (str): Name of the attribute to be used when calling
                on an instance.
        '''
        self.name = name
        self.args = args
        self.kwargs = kwargs

    def run(self, instance):
        '''
        Call an attribute on the passed instance.

        Args:
            name (str): Name of the attribute to be called.

        Returns:
            The value returned by calling the attribute.
        '''
        attr = getattr(instance, self.name)
        return attr(*self.args, **self.kwargs)

class History():
    def __init__(self, Type):
        '''
        Initialize a history.

        Args:
            type (class): Class type to be used when initializing an empty
                instance.
        '''
        self.Type = Type

        self.empty_instance()
        self.empty_stack()
        self.empty_undone_stack()

    def empty_instance(self):
        '''
        Empty the instance.
        '''
        self.instance = self.Type()

    def empty_stack(self):
        '''
        Empty the commands stack.
        '''
        self.command_stack = []

    def empty_undone_stack(self):
        '''
        Empty the undone command stack.
        '''
        self.undone_command_stack = []

    def rerun(self):
        '''
        Empty the instance and reruns the command stack.
        '''
        self.empty_instance()
        for command in self.command_stack:
            command.run(self.instance)

    def undo(self):
        '''
        Remove the last command from the command stack and add
        it to the undone command stack.
        Empty the instance and rerun the remaining commands.

        Raises:
            ValueError: If there are no commands on the
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
        Remove the last command from the undone command stack and add
        it to the command stack, then run the command.

        Raises:
            ValueError: If there are no commands on the undone
                command stack.

        Returns:
            The value returned by running the last undone command.
        '''
        try:
            last_undone_command = self.undone_command_stack.pop()
        except IndexError:
            raise ValueError('There is nothing to redo.')

        self.command_stack.append(last_undone_command)
        return last_undone_command.run(self.instance)

    def do(self, name, *args, **kwargs):
        '''
        Create a new command using the passed arguments, run it,
        and store it in the command stack.

        Args:
            keep (bool, optional): Whether to keep the new command in the
                command stack or not.
            Same arguments as Command.__init__()

        Returns:
            The value returned by running the last undone command.
        '''
        keep = kwargs.pop('keep', True)

        command = Command(name, *args, **kwargs)
        result = command.run(self.instance)

        if keep:
            self.command_stack.append(command)
            self.empty_undone_stack()

        return result
