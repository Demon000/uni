from Collection.Collection import Collection

from Services.DisciplineService import DisciplineService
from Services.StudentService import StudentService
from Services.GradeService import GradeService

from Validators.Discipline import DisciplineValidator
from Validators.Student import StudentValidator
from Validators.Grade import GradeValidator

from UI.UI import UI

from Tests.Tests import Tests

def run():
    disciplines_collection = Collection()
    discipline_service = DisciplineService(disciplines_collection, DisciplineValidator)

    students_collection = Collection()
    student_service = StudentService(students_collection, StudentValidator)

    grades_collection = Collection()
    grade_service = GradeService(grades_collection, GradeValidator)

    ui = UI(discipline_service, student_service, grade_service)
    ui.run()

def run_tests():
    tests = Tests()
    tests.run()

run_tests()
run()
