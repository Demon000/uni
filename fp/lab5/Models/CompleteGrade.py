class CompleteGrade():
    def __init__(self, grade, discipline, student):
        self.__grade = grade
        self.__discipline = discipline
        self.__student = student

    def __str__(self):
        return 'Student: {}, Discipline: {}, Grade: {}' \
                .format(self.__student.get_name(), self.__discipline.get_name(), self.get_value())

    def get_grade(self):
        return self.__grade

    def get_value(self):
        return self.__grade.get_value()

    def get_discipline(self):
        return self.__discipline

    def get_student(self):
        return self.__student
