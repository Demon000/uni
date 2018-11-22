from Collection.Collection import Collection

from Services.DisciplineService import DisciplineService
from Services.StudentService import StudentService
from Services.GradeService import GradeService

from Validators.Discipline import DisciplineValidator
from Validators.Student import StudentValidator
from Validators.Grade import GradeValidator

class Tests():
    def init_disciplines(self):
        disciplines_collection = Collection()
        discipline_validator = DisciplineValidator()
        self.__discipline_service = DisciplineService(disciplines_collection, discipline_validator)

    def init_students(self):
        students_collection = Collection()
        student_validator = StudentValidator()
        self.__student_service = StudentService(students_collection, student_validator)

    def init_grades(self):
        grades_collection = Collection()
        grade_validator = GradeValidator()
        self.__grade_service = GradeService(grades_collection, grade_validator)

    def test_add_discipline(self):
        self.init_disciplines()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        assert discipline.get_name() == 'Sport'
        assert discipline.get_professor() == 'Moca'

    def test_get_disciplines(self):
        self.init_disciplines()

        self.__discipline_service.add_discipline('Sport', 'Moca')
        disciplines = self.__discipline_service.get_disciplines()
        assert len(disciplines) == 1
        assert disciplines[0].get_name() == 'Sport'
        assert disciplines[0].get_professor() == 'Moca'

    def test_update_discipline(self):
        self.init_disciplines()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        self.__discipline_service.update_discipline(discipline, 'Physical training', 'NotMoca')
        assert discipline.get_name() == 'Physical training'
        assert discipline.get_professor() == 'NotMoca'

    def test_delete_discipline(self):
        self.init_disciplines()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        self.__discipline_service.remove_discipline(discipline)
        disciplines = self.__discipline_service.get_disciplines()
        assert len(disciplines) == 0

    def test_add_student(self):
        self.init_students()

        student = self.__student_service.add_student('Gigel')
        assert student.get_name() == 'Gigel'

    def test_get_students(self):
        self.init_students()

        self.__student_service.add_student('Gigel')
        students = self.__student_service.get_students()
        assert len(students) == 1
        assert students[0].get_name() == 'Gigel'

    def test_update_student(self):
        self.init_students()

        student = self.__student_service.add_student('Gigel')
        self.__student_service.update_student(student, 'Gigi')
        assert student.get_name() == 'Gigi'

    def test_delete_student(self):
        self.init_students()

        student = self.__student_service.add_student('Gigel')
        self.__student_service.remove_student(student)
        students = self.__student_service.get_students()

        assert len(students) == 0

    def test_add_grade(self):
        self.init_disciplines()
        self.init_students()
        self.init_grades()

        discipline = self.__discipline_service.add_discipline('Sport', 'Moca')
        student = self.__student_service.add_student('Gigel')
        grade = self.__grade_service.add_grade(discipline, student, 10)

        assert grade.get_value() == 10

    def run(self):
        self.test_add_discipline()
        self.test_get_disciplines()
        self.test_update_discipline()
        self.test_delete_discipline()

        self.test_add_student()
        self.test_get_students()
        self.test_update_student()
        self.test_delete_student()

        self.test_add_grade()
