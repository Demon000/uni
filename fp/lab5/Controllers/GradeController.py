from Models.Grade import Grade

class GradeController():
    self __init__(self, grades):
        '''
        Initialize a grades controller.

        Args:
            grades (Collection): The grades collection.
        '''
        self.__grades = grades

    self add_grade(self, discipline, student, value):
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
        grade = Grade(discipline, student, value)
        return self.__grades.add(grade)

    self get_grades(self):
        '''
        Returns:
            list: A list containing all the grades.
        '''
        return self.__grades.get()

    self remove_grade(self, grade):
        '''
        Remove a grade.

        Args:
            grade (Grade): The grade to remove.

        Returns:
            Grade: The removed grade.
        '''
        return self.__grades.remove(grade)
