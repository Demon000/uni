from Collection.Collection import Collection

from Validators.Discipline import DisciplineValidator
from Validators.Student import StudentValidator
from Validators.Grade import GradeValidator

from Controllers.DisciplineController import DisciplineController
from Controllers.StudentController import StudentController
from Controllers.GradeController import GradeController

from UI.UI import UI

from Tests.Tests import run_tests

def run():
    disciplines_collection = Collection()
    discipline_controller = DisciplineController(disciplines_collection, DisciplineValidator)

    students_collection = Collection()
    student_controller = StudentController(students_collection, StudentValidator)

    grades_collection = Collection()
    grade_controller = GradeController(grades_collection, GradeValidator)

    ui = UI(discipline_controller, student_controller, grade_controller)
    ui.run()

run_tests()
run()
