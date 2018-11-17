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
        name = UI.input_value('Student name: ',
                validate_fn=self.__student_controller.get_validator().validate_name)

        student = self.__student_controller.add_student(name)
        print('Added student: {}'.format(student))

    def add_discipline(self):
        name = UI.input_value('Discipline name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_name)
        professor = UI.input_value('Professor name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_professor)

        discipline = self.__discipline_controller.add_discipline(name, professor)
        print('Added discipline: {}'.format(discipline))

    def add_grade(self):
        discipline = UI.input_item('Choose a discipline: ',
                self.__discipline_controller.get_disciplines())
        student = UI.input_item('Choose a student: ',
                self.__student_controller.get_students())
        value = UI.input_value('Grade: ', type_cast=int,
                validate_fn=self.__grade_controller.get_validator().validate_value)

        grade = self.__grade_controller.add_grade(discipline, student, value)
        print('Added grade: {}'.format(grade))

    def update_student(self):
        student = UI.input_item('Choose a student: ',
                self.__student_controller.get_students())
        name = UI.input_value('Student name: ',
                validate_fn=self.__student_controller.get_validator().validate_name,
                default=student.get_name())

        self.__student_controller.update_student(student, name)

    def update_discipline(self):
        discipline = UI.input_item('Choose a discipline: ',
                self.__discipline_controller.get_disciplines())
        name = UI.input_value('Discipline name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_name,
                default=discipline.get_name())
        professor = UI.input_value('Professor name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_professor,
                default=discipline.get_professor())

        self.__discipline_controller.update_discipline(discipline, name, professor)

    def remove_student(self):
        student = UI.input_item('Choose a student: ',
                self.__student_controller.get_students())

        self.__student_controller.remove_student(student)
        self.__grade_controller.remove_matching_grades(student=student)

    def remove_discipline(self):
        discipline = UI.input_item('Choose a discipline: ',
                self.__discipline_controller.get_disciplines())

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

    def show_grades(self):
        grades = self.__grade_controller.get_grades()
        for grade in grades:
            print(grade)

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

        grade_menu = Menu([
            Entry(1, 'Add grade', self.add_grade),
            Entry(2, 'Show grades', self.show_grades),
        ])

        main_menu = Menu([
            Entry(1,  'Students', student_menu.run),
            Entry(2, 'Disciplines', discipline_menu.run),
            Entry(3, 'Grades', grade_menu.run),
            Entry('x', 'Exit', self.exit),
        ])

        while True:
            main_menu.run()
