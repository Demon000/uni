from Collection.Collection import Collection
from Controllers.StudentController import StudentController
from Controllers.DisciplineController import DisciplineController
from Controllers.GradeController import GradeController

from Models.Discipline import Discipline
from Models.Student import Student
from Models.Grade import Grade

def test_add_discipline():
    disciplines_collection = Collection()
    discipline_controller = DisciplineController(disciplines_collection)

    discipline = discipline_controller.add_discipline('Sport', 'Moca')
    assert discipline.get_name() == 'Sport'
    assert discipline.get_professor() == 'Moca'

def test_get_disciplines():
    disciplines_collection = Collection()
    discipline_controller = DisciplineController(disciplines_collection)

    discipline = discipline_controller.add_discipline('Sport', 'Moca')
    disciplines = discipline_controller.get_disciplines()
    assert len(disciplines) == 1
    assert disciplines[0].get_name() == 'Sport'
    assert disciplines[0].get_professor() == 'Moca'

def test_update_discipline():
    disciplines_collection = Collection()
    discipline_controller = DisciplineController(disciplines_collection)

    discipline = discipline_controller.add_discipline('Sport', 'Moca')
    discipline_controller.update_discipline(discipline, 'Physical training', 'NotMoca')
    assert discipline.get_name() == 'Physical training'
    assert discipline.get_professor() == 'NotMoca'

def test_delete_discipline():
    disciplines_collection = Collection()
    discipline_controller = DisciplineController(disciplines_collection)

    discipline = discipline_controller.add_discipline('Sport', 'Moca')
    discipline_controller.remove_discipline(discipline)
    disciplines = discipline_controller.get_disciplines()
    assert len(disciplines) == 0

def test_add_student():
    students_collection = Collection()
    student_controller = StudentController(students_collection)

    student = student_controller.add_student('Gigel')
    assert student.get_name() == 'Gigel'

def test_get_students():
    students_collection = Collection()
    student_controller = StudentController(students_collection)

    student = student_controller.add_student('Gigel')
    students = student_controller.get_students()
    assert len(students) == 1
    assert students[0].get_name() == 'Gigel'

def test_update_student():
    students_collection = Collection()
    student_controller = StudentController(students_collection)

    student = student_controller.add_student('Gigel')
    student_controller.update_student(student, 'Gigi')
    assert student.get_name() == 'Gigi'

def test_delete_student():
    students_collection = Collection()
    student_controller = StudentController(students_collection)

    student = student_controller.add_student('Gigel')
    student_controller.remove_student(student)
    students = student_controller.get_students()

    assert len(students) == 0

def test_add_grade():
    disciplines_collection = Collection()
    discipline_controller = DisciplineController(disciplines_collection)

    students_collection = Collection()
    student_controller = StudentController(students_collection)

    grades_collection = Collection()
    grade_controller = GradeController(grades_collection)

    discipline = discipline_controller.add_discipline('Sport', 'Moca')
    student = student_controller.add_student('Gigel')
    grade = grade_controller.add_grade(discipline, student, 10)

    assert grade.get_value() == 10

def test_validate_username():
    pass

def run_tests():
    test_add_discipline()
    test_get_disciplines()
    test_update_discipline()
    test_delete_discipline()

    test_add_student()
    test_get_students()
    test_update_student()
    test_delete_student()

    test_add_grade()
