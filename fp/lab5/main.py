from Collection.Collection import Collection
from Controllers.StudentController import StudentController
from Controllers.DisciplineController import DisciplineController
from Controllers.GradeController import GradeController
from UI.UI import UI

def run():
    disciplines_collection = Collection()
    discipline_controller = DisciplineController(disciplines_collection)

    students_collection = Collection()
    student_controller = StudentController(students_collection)

    grades_collection = Collection()
    grade_controller = GradeController(grades_collection)

    ui = UI(discipline_controller, student_controller, grade_controller)
    ui.run()

run()
