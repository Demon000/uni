from Models.Grade import Grade
from Models.Average import Average
from Models.MostGrades import MostGrades

class GradeService():
    def __init__(self, disciplines, students, grades, validator):
        '''
        Initialize a grades service.

        Args:
            grades (Collection): The grades collection.
            validator (object): The validator used for validating the given data.
        '''
        self.__disciplines = disciplines
        self.__students = students
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

    def get_matching_grades(self, *args, **kwargs):
        '''
        Get all the grades that match the passed arguments.

        Args:
            Same arguments as Grade.matches().

        Returns:
            list: A list of the matching grades.
        '''
        return self.__grades.get_matching(*args, **kwargs)

    def get_matching_grades_sorted(self, by_value=False, by_name=False, *args, **kwargs):
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
        matching_grades = self.get_matching_grades(*args, **kwargs)

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

    def remove_student(self, student):
        '''
        Remove a student.

        Args:
            student (Student): The student to remove.

        Returns:
            Student: The removed student.
        '''
        self.remove_matching_grades(student=student)
        return self.__students.remove(student)


    def remove_discipline(self, discipline):
        '''
        Remove a discipline.

        Args:
            discipline (Discipline): The discipline to remove.

        Returns:
            Discipline: The removed discipline.
        '''
        self.remove_matching_grades(discipline=discipline)
        return self.__disciplines.remove(discipline)

    def remove_matching_grades(self, *args, **kwargs):
        '''
        Remove all the grades that match the passed arguments.

        Args:
            Same arguments as Grade.matches().

        Returns:
            list: A list of the removed grades.
        '''
        return self.__grades.remove_matching(*args, **kwargs)

    def get_validator(self):
        '''
        Returns:
            object: The validator.
        '''
        return self.__validator

    def get_student_average(self, student):
        '''
        Find the average grade for a student.

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

    def get_averages(self):
        '''
        Get the average grade for each student.

        Returns:
            list: List containing one Average for each student.
        '''
        students = self.__students.get()
        averages = []

        for student in students:
            grade = self.get_student_average(student)
            average = Average(student, grade)
            averages.append(average)

        averages.sort(key=lambda average: average.get_grade(), reverse=True)

        return averages

    def get_student_with_most_grades(self, over_value):
        '''
        Get the students with the most grades over a given value.

        Returns:
            MostGrades: The student with the most grades.
        '''
        students = self.__students.get()
        students_most_grades = []

        def get_grades_over(grade):
            return grade.get_value() > over_value

        def get_no_grades(student):
            grades = self.get_matching_grades(student=student, test_fn=get_grades_over)
            return len(grades)

        for student in students:
            no_grades = get_no_grades(student)
            most_grades = MostGrades(student, no_grades, over_value)
            students_most_grades.append(most_grades)

        students_most_grades.sort(key=lambda most_grades: most_grades.get_no_grades(), reverse=True)

        return students_most_grades[0]
