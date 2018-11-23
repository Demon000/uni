from Models.Grade import Grade

class GradeService():
    def __init__(self, grades, validator):
        '''
        Initialize a grades service.

        Args:
            grades (Collection): The grades collection.
            validator (object): The validator used for validating the given data.
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
        return self.__grades.get_matching(discipline, student, value)

    def get_matching_grades_sorted(self, discipline=None, student=None,
            value=None, by_value=False, by_name=False):
        '''
        Get all the grades that match the passed arguments, sorted by the
        selected criteria.

        Args:
            Same arguments as Grade.matches().
            by_value (bool, optional): To sort the grades by value.
            by_name (bool, optional): To sort the grades by the student's name.

        Returns:
            list: A list of the sorted matching grades.
        '''
        matching_grades = self.get_matching_grades(discipline, student, value)

        if by_value is not None:
            matching_grades.sort(key=lambda grade: grade.get_value(), reverse=True)
        elif by_name is not None:
            matching_grades.sort(key=lambda grade: grade.get_student().get_name())

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
        return self.__grades.remove_matching(discipline, student, value)

    def get_validator(self):
        '''
        Returns:
            object: The validator.
        '''
        return self.__validator

    def get_student_average(self, student):
        '''
        Finds the average grade for a student.

        Args:
            student (Student): The student to find the average grade for.

        Returns:
            float: The average grade.
        '''
        grades = self.get_matching_grades(student=student)

        sum_ = 0
        for grade in grades:
            sum_ += grade.get_value()

        return sum_ / len(grades)
