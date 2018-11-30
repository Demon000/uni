from Repository.Repository import Repository

from Services.DisciplineService import DisciplineService
from Services.StudentService import StudentService
from Services.GradeService import GradeService

from Validators.Discipline import DisciplineValidator
from Validators.Student import StudentValidator
from Validators.Grade import GradeValidator

from UI.UI import UI

from Tests.Tests import Tests

def run():
    disciplines_repository = Repository()
    discipline_validator = DisciplineValidator()
    discipline_service = DisciplineService(disciplines_repository, discipline_validator)

    students_repository = Repository()
    student_validator = StudentValidator()
    student_service = StudentService(students_repository, student_validator)

    grades_repository = Repository()
    grade_validator = GradeValidator()
    grade_service = GradeService(disciplines_repository, students_repository,
            grades_repository, grade_validator)

    ui = UI(discipline_service, student_service, grade_service)
    ui.run()

def run_tests():
    tests = Tests()
    tests.run()

run_tests()
run()
