from Models.Student import Student

class StudentController():
    def __init__(self, students, validator):
        '''
        Initialize a students controller.

        Args:
            students (Collection): The students collection.
            validator (class): The validator used for validating the given data.
        '''
        self.__students = students
        self.__validator = validator

    def add_student(self, name):
        '''
        Create and add a student.

        Args:
            name (str): The name of the new student.

        Raises:
            ValueError: If the name of the student is invalid.

        Returns:
            Student: The new student.
        '''
        self.__validator.validate_name(name)

        student = Student(name)
        return self.__students.add(student)

    def get_students(self):
        '''
        Returns:
            list: A list containing all the students.
        '''
        return self.__students.get()

    def update_student(self, student, name=None):
        '''
        Update a student.

        Args:
            name (str, optional): The new name of the student.

        Raises:
            ValueError: If the name of the student is invalid.

        Returns:
            Student: The updated student.
        '''
        if name is not None:
            self.__validator.validate_name(name)
            student.set_name(name)

    def remove_student(self, student):
        '''
        Remove a student.

        Args:
            student (Student): The student to remove.

        Returns:
            Student: The removed student.
        '''
        return self.__students.remove(student)
