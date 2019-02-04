from entities.ShowEntity import ShowEntity
from errors.RepositoryError import RepositoryError

class ShowRepository():
    def __init__(self, filename):
        '''
        Initialize a repository for shows.

        Args:
            filename (str): The file to load/save to.
        '''
        self.__filename = filename

    def __load(self):
        '''
        Load the shows in the file.

        Returns:
            list: A list of the loaded shows.
        '''
        shows = []
        lines = []
        with open(self.__filename, 'r') as file:
            lines = file.readlines()

        for line in lines:
            try:
                show = ShowEntity.deserialize(line)
            except ValueError:
                continue
            shows.append(show)

        return shows

    def __save(self, shows):
        '''
        Save the shows to the file.

        Args:
            shows (list): The shows to save.
        '''
        lines = []
        for show in shows:
            line = show.serialize()
            lines.append(line)

        with open(self.__filename, 'w') as file:
            file.writelines(lines)

    def get_shows(self):
        '''
        Get all the shows saved in the file.

        Returns:
            list: A list containing all the shows saved in the file.
        '''
        shows = self.__load()
        return shows

    def find_show(self, name, type_):
        '''
        Find a show given a name and type.

        Args:
            name (str): The name to search for.
            type_ (str): The type to search for.

        Returns:
            ShowEntity: The matching show.

        Raises:
            RepositoryError: If the show does not exist.
        '''
        shows = self.__load()
        for show in shows:
            if show.matches(name, type_):
                return show

        raise RepositoryError('Show does not exist.')

    def delete_show(self, show):
        '''
        Delete the given show from the file.

        Args:
            show (ShowEntity): The show to delete.
        '''
        shows = self.__load()
        for other in shows:
            if show == other:
                shows.remove(other)
        self.__save(shows)

    def update_show(self, show, length, description):
        '''
        Update the given show with the given length and description.

        Args:
            show (ShowEntity): The show to update.
            length (int): The new length of the show.
            description (str): The new description of the show.

        Returns:
            ShowEntity: The updated show.
        '''
        shows = self.__load()
        updated = None

        show.set_length(length)
        show.set_description(description)

        for other in shows:
            if show == other:
                other.set_length(length)
                other.set_description(description)
                updated = other

        self.__save(shows)

        return updated
