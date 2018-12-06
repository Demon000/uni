from Repository.Repository import Repository

from Services.DisciplineService import DisciplineService
from Services.StudentService import StudentService
from Services.GradeService import GradeService

from Validators.Discipline import DisciplineValidator
from Validators.Student import StudentValidator
from Validators.Grade import GradeValidator

from Models.Discipline import Discipline
from Models.Student import Student
from Models.Grade import Grade

import unittest

class DisciplineTest(unittest.TestCase):
    def test_create(self):
        discipline = Discipline(0, 'Sport', 'Moca')
        self.assertEqual(discipline.get_id(), 0)
        self.assertEqual(discipline.get_name(), 'Sport')
        self.assertEqual(discipline.get_professor(), 'Moca')

    def test_set(self):
        discipline = Discipline(0, 'Sport', 'Moca')
        discipline.set_name('Educatie')
        discipline.set_professor('Boca')
        self.assertEqual(discipline.get_name(), 'Educatie')
        self.assertEqual(discipline.get_professor(), 'Boca')

class StudentTest(unittest.TestCase):
    def test_create(self):
        student = Student(0, 'Gigel')
        self.assertEqual(student.get_id(), 0)
        self.assertEqual(student.get_name(), 'Gigel')

    def test_set(self):
        student = Student(0, 'Gigel')
        student.set_name('Gigi')
        self.assertEqual(student.get_name(), 'Gigi')

class Tests(unittest.TestCase):
    def init_empty(self):
        disciplines_repository = Repository()
        students_repository = Repository()
        grades_repository = Repository()

        discipline_validator = DisciplineValidator()
        student_validator = StudentValidator()
        grade_validator = GradeValidator()

        self.__discipline_service = DisciplineService(disciplines_repository, discipline_validator)
        self.__student_service = StudentService(students_repository, student_validator)
        self.__grade_service = GradeService(disciplines_repository, students_repository,
                grades_repository, grade_validator)

    def test_add_discipline(self):
        self.init_empty()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        self.assertEqual(discipline.get_name(), 'Sport')
        self.assertEqual(discipline.get_professor(), 'Moca')

    def test_get_disciplines(self):
        self.init_empty()

        self.__discipline_service.add_discipline('Sport', 'Moca')
        disciplines = self.__discipline_service.get_disciplines()
        self.assertEqual(len(disciplines), 1)
        self.assertEqual(disciplines[0].get_name(), 'Sport')
        self.assertEqual(disciplines[0].get_professor(), 'Moca')

    def test_update_discipline(self):
        self.init_empty()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        self.__discipline_service.update_discipline(discipline, 'Physical training', 'NotMoca')
        self.assertEqual(discipline.get_name(), 'Physical training')
        self.assertEqual(discipline.get_professor(), 'NotMoca')

    def test_delete_discipline(self):
        self.init_empty()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        self.__grade_service.remove_discipline(discipline)
        disciplines = self.__discipline_service.get_disciplines()
        self.assertEqual(len(disciplines), 0)

    def test_add_student(self):
        self.init_empty()

        student = self.__student_service.add_student('Gigel')
        self.assertEqual(student.get_name(), 'Gigel')

    def test_get_students(self):
        self.init_empty()

        self.__student_service.add_student('Gigel')
        students = self.__student_service.get_students()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_name(), 'Gigel')

    def test_update_student(self):
        self.init_empty()

        student = self.__student_service.add_student('Gigel')
        self.__student_service.update_student(student, 'Gigi')
        self.assertEqual(student.get_name(), 'Gigi')

    def test_delete_student(self):
        self.init_empty()

        student = self.__student_service.add_student('Gigel')
        self.__grade_service.remove_student(student)
        students = self.__student_service.get_students()

        self.assertEqual(len(students), 0)

    def test_add_grade(self):
        self.init_empty()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        student = self.__student_service.add_student('Gigel')
        grade = self.__grade_service.add_grade(discipline, student, 10)

        self.assertEqual(grade.get_value(), 10)

unittest.main()
