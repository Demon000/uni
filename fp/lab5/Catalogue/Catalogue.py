from Collection.Collection import Collection
from Models.Student import Student
from Models.Discipline import Discipline
from Models.Grade import Grade

class Catalogue():
    def __init__(self):
        self.__students = Collection(Student)
        self.__disciplines = Collection(Discipline)
        self.__grades = Collection(Grade)

    def get_students(self):
        return self.__students.get()

    def get_disciplines(self):
        return self.__disciplines.get()

    def add_student(self, name):
        return self.__students.create(name)

    def add_discipline(self, name, professor):
        return self.__disciplines.create(name, professor)

    def add_grade(self, discipline, student, value):
        return self.__grades.create(discipline.get_id(), student.get_id(), value)

    def update_student(self, student, name=None):
        if name is not None:
            student.set_name(name)

    def update_discipline(self, discipline, name=None, professor=None):
        if name is not None:
            discipline.set_name(name)

        if professor is not None:
            discipline.set_professor(professor)

    def delete_student(self, student):
        self.__students.remove(student)
        self.__grades.remove_matching(student_id=student.get_id())

    def delete_discipline(self, discipline):
        self.__disciplines.remove(discipline)
        self.__grades.remove_matching(discipline_id=discipline.get_id())

    def find_students(self, *args, **kwargs):
        return self.__students.find_matching(*args, **kwargs)

    def find_disciplines(self, *args, **kwargs):
        return self.__disciplines.find_matching(*args, **kwargs)
