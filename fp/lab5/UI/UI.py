from Menu.Menu import Menu
from Menu.Entry import Entry
from Utils.Utils import validate_int, input_value, input_item

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
        discipline = input_item('Choose a discipline: ',
                self.__discipline_controller.get_disciplines())
        student = input_item('Choose a student: ',
                self.__student_controller.get_students())
        value = input_value('Grade: ', type_cast=int,
                validate_fn=self.__grade_controller.get_validator().validate_value)

        grade = self.__grade_controller.add_grade(discipline, student, value)
        print('Added grade: {}'.format(grade))

    def update_student(self):
        student = input_item('Choose a student: ',
                self.__student_controller.get_students())
        name = input_value('Student name: ',
                validate_fn=self.__student_controller.get_validator().validate_name,
                default=student.get_name())

        self.__student_controller.update_student(student, name)
        print('Updated student: {}', student)

    def update_discipline(self):
        discipline = input_item('Choose a discipline: ',
                self.__discipline_controller.get_disciplines())
        name = input_value('Discipline name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_name,
                default=discipline.get_name())
        professor = input_value('Professor name: ',
                validate_fn=self.__discipline_controller.get_validator().validate_professor,
                default=discipline.get_professor())

        self.__discipline_controller.update_discipline(discipline, name, professor)
        print('Updated discipline: {}', discipline)

    def remove_student(self):
        student = input_item('Choose a student: ',
                self.__student_controller.get_students())

        self.__student_controller.remove_student(student)
        self.__grade_controller.remove_matching_grades(student=student)
        print('Removed student: {}', student)

    def remove_discipline(self):
        discipline = input_item('Choose a discipline: ',
                self.__discipline_controller.get_disciplines())

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
            Entry(5, 'Back', self.noop),
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

        main_menu = Menu([
            Entry(1,  'Students', student_menu.run),
            Entry(2, 'Disciplines', discipline_menu.run),
            Entry(3, 'Grades', grade_menu.run),
            Entry('x', 'Exit', self.exit),
        ])

        while True:
            main_menu.run()
