from Models.Grade import Grade

class GradeController():
    def __init__(self, grades, validator):
        '''
        Initialize a grades controller.

        Args:
            grades (Collection): The grades collection.
            validator (class): The validator used for validating the given data.
        '''
        self.__grades = grades
        self.__validator = validator

    def add_grade(self, discipline, student, value):
        '''
        Create and add a grade.

        Args:
            discipline (Discipline): The discipline that the grade has been given for.
            student (Student): The student that got the grade.
            value (int): The value of the grade.

        Raises:
            ValueError: If the value of the new grade is invalid.

        Returns:
            Grade: The new grade.
        '''
        self.__validator.validate_value(value)

        grade = Grade(discipline, student, value)
        return self.__grades.add(grade)

    def get_grades(self):
        '''
        Returns:
            list: A list containing all the grades.
        '''
        return self.__grades.get()

    def get_matching_grades(self, discipline=None, student=None, value=None):
        '''
        Get all the grades that match the passed arguments.

        Args:
            Same arguments as Grade.matches().

        Returns:
            list: A list of the matching grades.
        '''
        matching_grades = []

        for grade in self.get_grades():
            if grade.matches(discipline, student, value):
                matching_grades.append(grade)

        return matching_grades

    def remove_grade(self, grade):
        '''
        Remove a grade.

        Args:
            grade (Grade): The grade to remove.

        Returns:
            Grade: The removed grade.
        '''
        return self.__grades.remove(grade)

    def remove_matching_grades(self, discipline=None, student=None, value=None):
        '''
        Remove all the grades that match the passed arguments.

        Args:
            Same arguments as Grade.matches().

        Returns:
            list: A list of the removed grades.
        '''
        removed_grades = self.get_matching_grades(discipline, student, value)

        for grade in removed_grades:
            self.remove_grade(grade)

        return removed_grades

    def get_validator(self):
        '''
        Returns:
            class: The validator.
        '''
        return self.__validator
