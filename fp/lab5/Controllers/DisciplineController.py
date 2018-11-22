from Models.Discipline import Discipline
from Utils.Utils import get_similarity

class DisciplineController():
    def __init__(self, disciplines, validator):
        '''
        Initialize a discipline service.

        Args:
            disciplines (Collection): The disciplines collection.
            validator (class): The validator used for validating the given data.
        '''
        self.__disciplines = disciplines
        self.__validator = validator

    def add_discipline(self, name, professor):
        '''
        Create and add a discipline.

        Args:
            name (str): The name of the new discipline.
            professor (str): The name of the professor teaching the new discipline.

        Raises:
            ValueError: If the name of the discipline or the name of the professor
                are invalid.

        Returns:
            Discipline: The new discipline.
        '''
        self.__validator.validate_name(name)
        self.__validator.validate_professor(professor)

        discipline = Discipline(name, professor)
        return self.__disciplines.add(discipline)

    def get_disciplines(self):
        '''
        Returns:
            list: A list containing all the disciplines.
        '''
        return self.__disciplines.get()

    def update_discipline(self, discipline, name=None, professor=None):
        '''
        Update a discipline.

        Args:
            discipline (Discipline): The discipline to update.
            name (str, optional): The new name of the discipline.
            professor (str, optional): The new name of the professor teaching the discipline.

        Raises:
            ValueError: If the name of the discipline or the name of the professor
                are invalid.

        Returns:
            Discipline: The updated discipline.
        '''
        if name is not None:
            self.__validator.validate_name(name)
            discipline.set_name(name)

        if professor is not None:
            self.__validator.validate_professor(professor)
            discipline.set_professor(professor)

    def remove_discipline(self, discipline):
        '''
        Remove a discipline.

        Args:
            discipline (Discipline): The discipline to remove.

        Returns:
            Discipline: The removed discipline.
        '''
        return self.__disciplines.remove(discipline)

    def get_validator(self):
        '''
        Returns:
            class: The validator.
        '''
        return self.__validator

    def get_disciplines_sorted_by_similarity(self, partial_name):
        '''
        Get all the disciplines sorted by similarity with the given partial name.

        Args:
            partial_name (str): A partial name to find the similarity against.

        Returns:
            list: List of disciplines sorted by similarity.
        '''
        disciplines = self.get_disciplines()

        disciplines.sort(key=lambda discipline: get_similarity(discipline.get_name(), partial_name), reverse=True)

        return disciplines
