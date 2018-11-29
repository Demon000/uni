class Average():
    def __init__(self, student, grade):
        self.__student = student
        self.__grade = grade

    def __str__(self):
        return 'Name: {}, Grade: {}'.format(self.__student.get_name(), self.get_grade())

    def get_student(self):
        return self.__student

    def get_grade(self):
        return self.__grade
