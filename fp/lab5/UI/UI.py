from Menu.Menu import Menu
from Menu.Entry import Entry
from Utils.Utils import input_value, input_item

class UI():
    def __init__(self, discipline_controller, student_controller, grade_controller):
        self.__discipline_controller = discipline_controller
        self.__student_controller = student_controller
        self.__grade_controller = grade_controller

    def add_student(self):
        name = input_value('Student name: ',
                validate_fn=self.__student_controller.get_validator().validate_name)

        student = self.__student_controller.add_student(name)
        print('Added student: {}'.format(student))

    def add_discipline(self):
        name = input_value('Discipline name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_name)
        professor = input_value('Professor name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_professor)

        discipline = self.__discipline_controller.add_discipline(name, professor)
        print('Added discipline: {}'.format(discipline))

    def add_grade(self):
        disciplines = self.__discipline_controller.get_disciplines()
        discipline = input_item('Choose a discipline: ', disciplines)

        students = self.__student_controller.get_students()
        student = input_item('Choose a student: ', students)

        value = input_value('Grade: ', type_cast=int,
                validate_fn=self.__grade_controller.get_validator().validate_value)

        grade = self.__grade_controller.add_grade(discipline, student, value)
        print('Added grade: {}'.format(grade))

    def update_student(self):
        students = self.__student_controller.get_students()
        student = input_item('Choose a student: ', students)

        default_name = student.get_name()

        name = input_value('Student name: ',
                validate_fn=self.__student_controller.get_validator().validate_name,
                default=default_name)

        self.__student_controller.update_student(student, name)
        print('Updated student: {}', student)

    def update_discipline(self):
        disciplines = self.__discipline_controller.get_disciplines()
        discipline = input_item('Choose a discipline: ', disciplines)

        default_name = discipline.get_name()
        default_professor = discipline.get_professor()

        name = input_value('Discipline name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_name,
                default=default_name)
        professor = input_value('Professor name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_professor,
                default=default_professor)

        self.__discipline_controller.update_discipline(discipline, name, professor)
        print('Updated discipline: {}', discipline)

    def remove_student(self):
        students = self.__student_controller.get_students()
        student = input_item('Choose a student: ', students)

        self.__student_controller.remove_student(student)
        self.__grade_controller.remove_matching_grades(student=student)
        print('Removed student: {}', student)

    def remove_discipline(self):
        disciplines = self.__discipline_controller.get_disciplines()
        discipline = input_item('Choose a discipline: ', disciplines)

        self.__discipline_controller.remove_discipline(discipline)
        self.__grade_controller.remove_matching_grades(discipline=discipline)
        print('Removed discipline: {}', discipline)

    def show_students(self):
        students = self.__student_controller.get_students()
        for student in students:
            print(student)

    def show_disciplines(self):
        disciplines = self.__discipline_controller.get_disciplines()
        for discipline in disciplines:
            print(discipline)

    def show_grades(self):
        grades = self.__grade_controller.get_grades()
        for grade in grades:
            print(grade)

    def search_students(self):
        partial_name = input_value('Partial name: ')

        students = self.__student_controller.get_students_sorted_by_similarity(partial_name)
        no_students_to_print = len(students) // 5 or 1
        students_to_print = students[:no_students_to_print]
        for student in students_to_print:
            print(student)

    def get_grades_for_discipline(self):
        disciplines = self.__discipline_controller.get_disciplines()
        discipline = input_item('Choose a discipline: ', disciplines)

        grades = self.__grade_controller.get_matching_grades(discipline=discipline)

        return grades

    def report_grades_sorted_by_name(self):
        grades = self.get_grades_for_discipline()

        grades.sort(key=lambda grade: grade.get_student().get_name())

        for grade in grades:
            print(grade)

    def report_grades_sorted_by_value(self):
        grades = self.get_grades_for_discipline()

        grades.sort(key=lambda grade: grade.get_value(), reverse=True)

        for grade in grades:
            print(grade)

    def report_students_sorted_by_average(self):
        students = self.__student_controller.get_students()
        students_average = []

        for student in students:
            average = self.__grade_controller.get_student_average(student)
            students_average.append((student, average))

        students_average.sort(key=lambda student_average: student_average[1], reverse=True)

        no_averages_to_print = len(students) // 5 or 1
        students_average_to_print = students_average[:no_averages_to_print]
        for student, average in students_average_to_print
            print('{}, Average grade: {}'.format(student, average))

    def noop(self):
        pass

    def exit(self):
        print('Goodbye.')
        exit()

    def run(self):
        student_menu = Menu([
            Entry(1, 'Add student', self.add_student),
            Entry(2, 'Update student', self.update_student),
            Entry(3, 'Remove student', self.remove_student),
            Entry(4, 'Show students', self.show_students),
            Entry(5, 'Search students', self.search_students),
            Entry(6, 'Back', self.noop),
        ])

        discipline_menu = Menu([
            Entry(1, 'Add discipline', self.add_discipline),
            Entry(2, 'Update discipline', self.update_discipline),
            Entry(3, 'Remove discipline', self.remove_discipline),
            Entry(4, 'Show disciplines', self.show_disciplines),
            Entry(5, 'Back', self.noop),
        ])

        grade_menu = Menu([
            Entry(1, 'Add grade', self.add_grade),
            Entry(2, 'Show grades', self.show_grades),
            Entry(3, 'Back', self.noop),
        ])

        report_menu = Menu([
            Entry(1, 'Grades for discipline sorted by name', self.report_grades_sorted_by_name),
            Entry(2, 'Grades for discipline sorted by value', self.report_grades_sorted_by_value),
            Entry(3, 'Students sorted by average grade', self.report_students_sorted_by_average),
        ])

        main_menu = Menu([
            Entry(1,  'Students', student_menu.run),
            Entry(2, 'Disciplines', discipline_menu.run),
            Entry(3, 'Grades', grade_menu.run),
            Entry(4, 'Report', report_menu.run),
            Entry('x', 'Exit', self.exit),
        ])

        while True:
            main_menu.run()
