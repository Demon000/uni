from Models.Discipline import Discipline
from Models.Student import Student
from Models.Grade import Grade
from Menu.Menu import Menu
from Menu.Entry import Entry
from Utils.Utils import validate_int

class UI():
    def __init__(self, discipline_controller, student_controller, grade_controller):
        self.__discipline_controller = discipline_controller
        self.__student_controller = student_controller
        self.__grade_controller = grade_controller

    @staticmethod
    def input_value(message, type_cast=None, validate_fn=None, default=None):
        while True:
            try:
                raw_value = input(message)
                if type_cast is not None:
                    value = type_cast(raw_value)
                else:
                    value = raw_value

                validate_fn(value)
            except ValueError as ve:
                print(ve)
                if default is not None:
                    print('Using default value.')
                    value = default
                else:
                    continue

            return value

    @staticmethod
    def input_int(message, min_value=None, max_value=None):
        def validate(value):
            validate_int(value, min_value=min_value, max_value=max_value)

        return UI.input_value(message, type_cast=int, validate_fn=validate)

    @staticmethod
    def input_item(message, items):
        for index, item in enumerate(items):
            print('{}. {}'.format(index , item))

        index = UI.input_int(message, min_value=0, max_value=len(items) - 1)
        return items[index]

    def add_student(self):
        try:
            name = UI.input_value('Student name: ',
                    validate_fn=Student.validate_name)
        except ValueError as ve:
            print(ve)
            return

        student = self.__student_controller.add_student(name)
        print('Added student: {}'.format(student))

    def add_discipline(self):
        try:
            name = UI.input_value('Discipline name: ',
                    validate_fn=Discipline.validate_name)
            professor = UI.input_value('Professor name: ',
                    validate_fn=Discipline.validate_professor)
        except ValueError as ve:
            print(ve)
            return

        discipline = self.__discipline_controller.add_discipline(name, professor)
        print('Added discipline: {}'.format(discipline))

    def add_grade(self):
        try:
            discipline = UI.input_item('Choose a discipline: ',
                    self.__discipline_controller.get_disciplines())
            student = UI.input_item('Choose a student: ',
                    self.__student_controller.get_students())
            value = UI.input_value('Grade: ', type_cast=int,
                    validate_fn=Grade.validate_value)
        except ValueError as ve:
            print(ve)
            return

        grade = self.__grade_controller.add_grade(discipline, student, value)
        print('Added grade: {}'.format(grade))

    def update_student(self):
        try:
            student = UI.input_item('Choose a student: ',
                    self.__student_controller.get_students())
            name = UI.input_value('Student name: ',
                    validate_fn=Student.validate_name, default=student.get_name())
        except ValueError as ve:
            print(ve)
            return

        student.set_name(name)

    def update_discipline(self):
        try:
            discipline = UI.input_item('Choose a discipline: ',
                    self.__discipline_controller.get_disciplines())
            name = UI.input_value('Discipline name: ',
                    validate_fn=Discipline.validate_name, default=discipline.get_name())
            professor = UI.input_value('Professor name: ',
                    validate_fn=Discipline.validate_professor, default=discipline.get_professor())
        except ValueError as ve:
            print(ve)
            return

        discipline.set_name(name)
        discipline.set_professor(professor)

    def remove_student(self):
        try:
            student = UI.input_item('Choose a student: ',
                    self.__student_controller.get_students())
        except ValueError as ve:
            print(ve)
            return

        self.__student_controller.remove_student(student)
        self.__grade_controller.remove_matching_grades(student=student)

    def remove_discipline(self):
        try:
            discipline = UI.input_item('Choose a discipline: ',
                    self.__discipline_controller.get_disciplines())
        except ValueError as ve:
            print(ve)
            return

        self.__discipline_controller.remove_discipline(discipline)
        self.__grade_controller.remove_matching_grades(discipline=discipline)

    def show_students(self):
        students = self.__student_controller.get_students()
        for student in students:
            print(student)

    def show_disciplines(self):
        disciplines = self.__discipline_controller.get_disciplines()
        for discipline in disciplines:
            print(discipline)

    def exit(self):
        print('Goodbye.')
        exit()

    def run(self):
        student_menu = Menu([
            Entry(1, 'Add student', self.add_student),
            Entry(2, 'Update student', self.update_student),
            Entry(3, 'Remove student', self.remove_student),
            Entry(4, 'Show students', self.show_students),
        ])

        discipline_menu = Menu([
            Entry(1, 'Add discipline', self.add_discipline),
            Entry(2, 'Update discipline', self.update_discipline),
            Entry(3, 'Remove discipline', self.remove_discipline),
            Entry(4, 'Show disciplines', self.show_disciplines),
        ])

        main_menu = Menu([
            Entry(1,  'Students', student_menu.run),
            Entry(2, 'Disciplines', discipline_menu.run),
            Entry('x', 'Exit', self.exit)
        ])

        while True:
            main_menu.run()
