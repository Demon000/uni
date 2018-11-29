from Menu.Menu import Menu
from Menu.Entry import Entry
from Utils.Utils import validate_int

import math

class UI():
    def __init__(self, discipline_service, student_service, grade_service):
        self.__discipline_service = discipline_service
        self.__student_service = student_service
        self.__grade_service = grade_service

    def __input_value(self, message, type_cast=None, validate_fn=None, default=None):
        while True:
            try:
                raw_value = input(message)
                if type_cast is not None:
                    value = type_cast(raw_value)
                else:
                    value = raw_value

                if validate_fn is not None:
                    validate_fn(value)
            except ValueError as ve:
                print(ve)
                if default is not None:
                    print('Using default value.')
                    value = default
                else:
                    continue

            return value

    def __input_int(self, message, min_value=None, max_value=None):
        def validate(value):
            validate_int(value, min_value=min_value, max_value=max_value)

        return self.__input_value(message, type_cast=int, validate_fn=validate)

    def __input_item(self, message, items):
        for index, item in enumerate(items):
            print('{}. {}'.format(index , item))

        index = self.__input_int(message, min_value=0, max_value=len(items) - 1)
        return items[index]

    def __input_student(self):
        students = self.__student_service.get_students()
        return self.__input_item('Choose a student: ', students)

    def __input_discipline(self):
        disciplines = self.__discipline_service.get_disciplines()
        return self.__input_item('Choose a discipline: ', disciplines)

    def __add_student(self):
        name = self.__input_value('Student name: ',
                validate_fn=self.__student_service.get_validator().validate_name)

        student = self.__student_service.add_student(name)
        print('Added student: {}'.format(student))

    def __add_discipline(self):
        name = self.__input_value('Discipline name: ',
                validate_fn=self.__discipline_service.get_validator().validate_name)
        professor = self.__input_value('Professor name: ',
                validate_fn=self.__discipline_service.get_validator().validate_professor)

        discipline = self.__discipline_service.add_discipline(name, professor)
        print('Added discipline: {}'.format(discipline))

    def __add_grade(self):
        discipline = self.__input_discipline()
        student = self.__input_student()

        value = self.__input_value('Grade: ', type_cast=int,
                validate_fn=self.__grade_service.get_validator().validate_value)

        grade = self.__grade_service.add_grade(discipline, student, value)
        print('Added grade: {}'.format(grade))

    def __update_student(self):
        student = self.__input_student()
        default_name = student.get_name()

        name = self.__input_value('Student name: ',
                validate_fn=self.__student_service.get_validator().validate_name,
                default=default_name)

        self.__student_service.update_student(student, name)
        print('Updated student: {}', student)

    def __update_discipline(self):
        discipline = self.__input_discipline()
        default_name = discipline.get_name()
        default_professor = discipline.get_professor()

        name = self.__input_value('Discipline name: ',
                validate_fn=self.__discipline_service.get_validator().validate_name,
                default=default_name)
        professor = self.__input_value('Professor name: ',
                validate_fn=self.__discipline_service.get_validator().validate_professor,
                default=default_professor)

        self.__discipline_service.update_discipline(discipline, name, professor)
        print('Updated discipline: {}', discipline)

    def __remove_student(self):
        student = self.__input_student()

        self.__grade_service.remove_student(student)
        print('Removed student: {}', student)

    def __remove_discipline(self):
        discipline = self.__input_discipline()

        self.__grade_service.remove_discipline(discipline)
        print('Removed discipline: {}', discipline)

    def __show_students(self):
        students = self.__student_service.get_students()
        print('Students:')
        for student in students:
            print(student)

    def __show_disciplines(self):
        disciplines = self.__discipline_service.get_disciplines()
        print('Disciplines:')
        for discipline in disciplines:
            print(discipline)

    def __show_grades(self):
        grades = self.__grade_service.get_grades()
        print('Grades:')
        for grade in grades:
            print(grade)

    def __search_students(self):
        partial_name = self.__input_value('Partial name: ')

        students = self.__student_service.get_most_similar_students(partial_name)
        print('Similar students:')
        for student in students:
            print(student)

    def __search_disciplines(self):
        partial_name = self.__input_value('Partial name: ')

        disciplines = self.__discipline_service.get_most_similar_disciplines(partial_name)
        print('Similar disciplines:')
        for discipline in disciplines:
            print(discipline)

    def __add_random_students(self):
        no_students = self.__input_value('Number of students: ', int)
        students = self.__student_service.add_random_students(no_students)

        print('Added students:')
        for student in students:
            print(student)

    def __report_grades_sorted_by_name(self):
        discipline = self.__input_discipline()
        grades = self.__grade_service.get_matching_grades_sorted(
                discipline=discipline, by_name=True)

        print('Grades sorted by student name:')
        for grade in grades:
            print(grade)

    def __report_grades_sorted_by_value(self):
        discipline = self.__input_discipline()
        grades = self.__grade_service.get_matching_grades_sorted(
                discipline=discipline, by_value=True)

        print('Grades sorted by value:')
        for grade in grades:
            print(grade)

    def __report_students_sorted_by_average(self):
        averages = self.__grade_service.get_averages()

        no_averages_to_print = math.ceil(len(averages) / 5)
        averages_to_print = averages[:no_averages_to_print]
        print('Students average:')
        for average in averages_to_print:
            print(average)

    def __report_student_with_most_grades_over(self):
        value = self.__input_value('Grade: ', type_cast=int,
                validate_fn=self.__grade_service.get_validator().validate_value)

        most_grades = self.__grade_service.get_student_with_most_grades(value)
        print(most_grades)

    def __noop(self):
        pass

    def __exit(self):
        print('Goodbye.')
        exit()

    def run(self):
        student_menu = Menu([
            Entry(1, 'Add student', self.__add_student),
            Entry(2, 'Update student', self.__update_student),
            Entry(3, 'Remove student', self.__remove_student),
            Entry(4, 'Show students', self.__show_students),
            Entry(5, 'Search students', self.__search_students),
            Entry(6, 'Add random students', self.__add_random_students),
            Entry(7, 'Back', self.__noop),
        ])

        discipline_menu = Menu([
            Entry(1, 'Add discipline', self.__add_discipline),
            Entry(2, 'Update discipline', self.__update_discipline),
            Entry(3, 'Remove discipline', self.__remove_discipline),
            Entry(4, 'Show disciplines', self.__show_disciplines),
            Entry(5, 'Search disciplines', self.__search_disciplines),
            Entry(6, 'Back', self.__noop),
        ])

        grade_menu = Menu([
            Entry(1, 'Add grade', self.__add_grade),
            Entry(2, 'Show grades', self.__show_grades),
            Entry(3, 'Back', self.__noop),
        ])

        report_menu = Menu([
            Entry(1, 'Grades for discipline sorted by name', self.__report_grades_sorted_by_name),
            Entry(2, 'Grades for discipline sorted by value', self.__report_grades_sorted_by_value),
            Entry(3, 'Students sorted by average grade', self.__report_students_sorted_by_average),
            Entry(4, 'Student with most grades over a given value', self.__report_student_with_most_grades_over),
        ])

        main_menu = Menu([
            Entry(1,  'Students', student_menu.run),
            Entry(2, 'Disciplines', discipline_menu.run),
            Entry(3, 'Grades', grade_menu.run),
            Entry(4, 'Report', report_menu.run),
            Entry('x', 'Exit', self.__exit),
        ])

        while True:
            main_menu.run()
