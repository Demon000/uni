from entities.ProgramEntity import ProgramEntity
from errors.ServiceError import ServiceError

from random import randint

class ShowService():
    def __init__(self, show_repo):
        '''
        Initialize a new show service.

        Args:
            show_repo (ShowRepository): The repository to retrieve shows from.
        '''
        self.__show_repo = show_repo
        self.__blocked_types = []

    def __is_blocked_show(self, show):
        '''
        Check if the show is in the blocked types list.

        Returns:
            bool: Whether thee show is in the blocked types list or not.
        '''
        return show.get_type() in self.__blocked_types

    def delete_show(self, name, type_):
        '''
        Delete the show matching the name and type.

        Args:
            name (str): The name of the show that needs to be deleted.
            type_ (str): The type of the show that needs to be deleted.

        Returns:
            ShowEntity: The deleted show.
        '''
        show = self.__show_repo.find_show(name, type_)
        if self.__is_blocked_show(show):
            raise ServiceError('The show is blocked.')

        self.__show_repo.delete_show(show)

        return show

    def update_show(self, name, type_, length, description):
        '''
        Update the show that matches the name and type with
        the given length and description.

        Args:
            name (str): The name of the show that needs to be updated.
            type_ (str): The type of the show that needs to be updated.
            length (int): The new length of the show.
            description (str): The new description of the show.

        Returns:
            ShowEntity: The updated show.
        '''
        show = self.__show_repo.find_show(name, type_)
        if self.__is_blocked_show(show):
            raise ServiceError('The show is blocked.')
        updated_show = self.__show_repo.update_show(show, length, description)
        return updated_show

    def generate_programs(self, start_hour, end_hour):
        '''
        Generate a list of shows that will play in the given interval.

        Args:
            start_hour (int): The hour at which to start playing.
            end_hour (int): The hour at which to finish playing.
        '''
        shows = self.__show_repo.get_shows()

        programs = []
        added_shows = []
        current_hour = start_hour
        no_more_shows = False
        while current_hour < end_hour:
            index = randint(0, len(shows) - 1)
            show = shows[index]

            if show in added_shows:
                if len(added_shows) == len(shows):
                    no_more_shows = True
                elif not no_more_shows:
                    continue

            if self.__is_blocked_show(show):
                continue

            program = ProgramEntity(current_hour, show, no_more_shows)
            programs.append(program)
            added_shows.append(show)

            current_hour = current_hour + show.get_length()

        return programs

    def block_type(self, type_):
        '''
        Add a type to the blocked list.

        Args:
            type_ (str): The name of the type to block.
        '''
        self.__blocked_types.append(type_)

    def unblock_type(self, type_):
        '''
        Remove a type from the blocked list.

        Args:
            type_ (str): The name of the type to unblock.
        '''
        try:
            self.__blocked_types.remove(type_)
        except ValueError:
            raise ServiceError('The type is not blocked.')

    def clear_blocked_types(self):
        '''
        Clear all the blocked types.
        '''
        self.__blocked_types = []
