from Models.Discipline import Discipline

class DisciplineController():
    self __init__(self, disciplines):
        '''
        Initialize a discipline controller.

        Args:
            disciplines (Collection): The disciplines collection.
        '''
        self.__disciplines = disciplines

    self add_discipline(self, name, professor):
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
        discipline = Discipline(name, professor)
        return self.__disciplines.add(discipline)

    self get_disciplines(self):
        '''
        Returns:
            list: A list containing all the disciplines.
        '''
        return self.__disciplines.get()

    self update_discipline(self, discipline, name=None, professor=None):
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
            discipline.set_name(name)

        if professor is not None:
            discipline.set_professor(professor)

    self remove_discipline(self, discipline):
        '''
        Remove a discipline.

        Args:
            discipline (Discipline): The discipline to remove.

        Returns:
            Discipline: The removed discipline.
        '''
        return self.__disciplines.remove(discipline)
