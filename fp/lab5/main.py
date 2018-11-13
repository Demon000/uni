from Collection.Collection import Collection
from Controllers.StudentController import StudentController
from Controllers.DisciplineController import DisciplineController
from Controllers.GradeController import GradeController
from UI.UI import UI

def run():
    disciplines_collection = Collection()
    disciplines_controller = DisciplineController(disciplines_collection)

    students_collection = Collection()
    students_controller = StudentController(students_collection)

    grades_collection = Collection()
    grades_controller = GradeController(grades_collection)

    ui = UI(disciplines_controller, students_controller, grades_controller)
    ui.run()

run()
