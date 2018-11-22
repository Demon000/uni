from Collection.Collection import Collection

from Controllers.DisciplineController import DisciplineController
from Controllers.StudentController import StudentController
from Controllers.GradeController import GradeController

from Validators.Discipline import DisciplineValidator
from Validators.Student import StudentValidator
from Validators.Grade import GradeValidator

from UI.UI import UI

from Tests.Tests import Tests

def run():
    disciplines_collection = Collection()
    discipline_service = DisciplineController(disciplines_collection, DisciplineValidator)

    students_collection = Collection()
    student_service = StudentController(students_collection, StudentValidator)

    grades_collection = Collection()
    grade_service = GradeController(grades_collection, GradeValidator)

    ui = UI(discipline_service, student_service, grade_service)
    ui.run()

def run_tests():
    tests = Tests()
    tests.run()

run_tests()
run()
