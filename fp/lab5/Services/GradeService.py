from Models.Grade import Grade
from Models.CompleteGrade import CompleteGrade
from Models.AverageGrade import AverageGrade
from Models.MostGrades import MostGrades

from Sort.Sort import gnomesort

class GradeService():
    def __init__(self, disciplines, students, grades, validator):
        '''
        Initialize a grades service.

        Args:
            disciplines (Repository): The disciplines repository.
            students (Repository): The students repository.
            grades (Repository): The grades repository.
            validator (object): The validator used for validating the given data.
        '''
        self.__disciplines = disciplines
        self.__students = students
        self.__grades = grades
        self.__validator = validator

    def __complete_grade(self, grade):
        '''
        Returns:
            CompleteGrade: A complete grade built from the given grade.
        '''
        discipline_id = grade.get_discipline_id()
        discipline = self.__disciplines.get_one_matching(id_=discipline_id)

        student_id = grade.get_student_id()
        student = self.__students.get_one_matching(id_=student_id)

        complete_grade = CompleteGrade(grade, discipline, student)
        return complete_grade

    def __complete_grades(self, grades):
        '''
        Returns:
            list: A list of complete grades built from the given grades.
        '''
        complete_grades = []

        for grade in grades:
            complete_grade = self.__complete_grade(grade)
            complete_grades.append(complete_grade)

        return complete_grades

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
            CompleteGrade: The new grade.
        '''
        self.__validator.validate_value(value)

        id_ = self.__grades.get_available_id()
        discipline_id = discipline.get_id()
        student_id = student.get_id()

        grade = Grade(id_, discipline_id, student_id, value)
        self.__grades.add(grade)

        complete_grade = CompleteGrade(grade, discipline, student)
        return complete_grade

    def get_grades(self):
        '''
        Returns:
            list: A list containing all the complete grades.
        '''
        grades = self.__grades.get()
        complete_grades = self.__complete_grades(grades)
        return complete_grades

    def get_matching_grades(self, *args, **kwargs):
        '''
        Get all the complete grades that match the passed arguments.

        Args:
            Same arguments as Grade.matches().

        Returns:
            list: A list of the complete matching grades.
        '''
        matching_grades = self.__grades.get_matching(*args, **kwargs)
        complete_matching_grades = self.__complete_grades(matching_grades)
        return complete_matching_grades

    def get_matching_grades_sorted(self, by_value=False, by_name=False, *args, **kwargs):
        '''
        Get all the complete grades that match the passed arguments, sorted by the
        selected criteria.

        Args:
            Same arguments as Grade.matches().
            by_value (bool, optional): To sort the grades by value.
            by_name (bool, optional): To sort the grades by the student's name.

        Returns:
            list: A list of the sorted complete matching grades.
        '''
        matching_grades = self.get_matching_grades(*args, **kwargs)
        if by_value:
            matching_grades = gnomesort(matching_grades, key=lambda grade: grade.get_value(), reverse=True)
        elif by_name:
            matching_grades = gnomesort(matching_grades, key=lambda grade: grade.get_student().get_name())

        return matching_grades

    def remove_matching_grades(self, *args, **kwargs):
        '''
        Remove all the grades that match the passed arguments.

        Args:
            Same arguments as Grade.matches().

        Returns:
            list: A list of the complete removed grades.
        '''
        removed_grades = self.__grades.remove_matching(*args, **kwargs)
        complete_removed_grades = self.__complete_grades(removed_grades)
        return complete_removed_grades

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

        if not len(grades):
            return 0

        return sum_ / len(grades)

    def get_sorted_averages(self):
        '''
        Get average grades for each student, sorted by value, from higher to lower.

        Returns:
            list: List containing an AverageGrade for each student.
        '''
        students = self.__students.get()
        average_grades = []

        for student in students:
            value = self.get_student_average(student)
            average_grade = AverageGrade(student, value)
            average_grades.append(average_grade)

        average_grades = gnomesort(average_grades,
                key=lambda average_grade: average_grade.get_value(), reverse=True)

        return average_grades

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

        sorted_most_grades = gnomesort(students_most_grades,
                key=lambda most_grades: most_grades.get_no_grades(), reverse=True)

        return students_most_grades[0]
