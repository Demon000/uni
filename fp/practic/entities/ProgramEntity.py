class ProgramEntity():
    def __init__(self, hour, show, replay):
        '''
        Initialize a program entity.

        Args:
            hour (int): The hour at which the show should run.
            show (ShowEntity): The show running.
            replay (bool): Whether the show is running a second time.
        '''
        self.__hour = hour
        self.__show = show
        self.__replay = replay

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        asterisk = '*' if self.__replay else ''
        return '{}\t{}\t{}\t{}{}'.format(self.__hour, self.__show.get_name(),
                self.__show.get_type(), self.__show.get_description(), asterisk)
