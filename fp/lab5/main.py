from Repository.Repository import Repository
from Repository.FileRepository import FileRepository

from Services.DisciplineService import DisciplineService
from Services.StudentService import StudentService
from Services.GradeService import GradeService

from Validators.Discipline import DisciplineValidator
from Validators.Student import StudentValidator
from Validators.Grade import GradeValidator

from Models.Discipline import Discipline
from Models.Student import Student
from Models.Grade import Grade

from Menu.Menu import Menu
from Menu.Entry import Entry

from UI.UI import UI

from Tests.Tests import Tests

class Coordinator():
    def __run_in_memory(self):
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

    def __run_persistent(self):
        disciplines_repository = FileRepository('disciplines.csv',
                Discipline.serialize, Discipline.deserialize)
        discipline_validator = DisciplineValidator()
        discipline_service = DisciplineService(disciplines_repository, discipline_validator)

        students_repository = FileRepository('students.csv',
                Student.serialize, Student.deserialize)
        student_validator = StudentValidator()
        student_service = StudentService(students_repository, student_validator)

        grades_repository = FileRepository('grades.csv',
                Grade.serialize, Grade.deserialize)
        grade_validator = GradeValidator()
        grade_service = GradeService(disciplines_repository, students_repository,
                grades_repository, grade_validator)

        ui = UI(discipline_service, student_service, grade_service)
        ui.run()

    def __exit(self):
        print('Goodbye.')
        exit()

    def run(self):
        menu = Menu([
            Entry(1, 'Run in memory', self.__run_in_memory),
            Entry(2,  'Run with persistency', self.__run_persistent),
            Entry('x', 'Exit', self.__exit),
        ])

        menu.run()

if __name__ == "__main__":
    coordinator = Coordinator()
    coordinator.run()

    tests = Tests()
    tests.run()
