import random
import string

from Models.Student import Student
from Utils.Utils import get_similarity

class StudentService():
    def __init__(self, students, validator):
        '''
        Initialize a students service.

        Args:
            students (Repository): The students repository.
            validator (object): The validator used for validating the given data.
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

        self.__students.update(student, name)

    def get_validator(self):
        '''
        Returns:
            object: The validator.
        '''
        return self.__validator

    def get_most_similar_students(self, partial_name):
        '''
        Get the students most similar with the given partial name.

        Args:
            partial_name (str): A partial name to find the similarity against.

        Returns:
            list: List of students most similar.
        '''
        students = self.get_students()
        groups = {}
        max_similarity = 0
        for student in students:
            similarity = get_similarity(student.get_name(), partial_name)
            if similarity > max_similarity:
                max_similarity = similarity

            if similarity not in groups:
                groups[similarity] = []

            groups[similarity].append(student)

        return groups[max_similarity]

    def get_random_name(self, length=None):
        '''
        Generate a random name.

        Args:
            length (int, optional): The length of the generated name.

        Returns:
            The randomly generated name.
        '''
        chars = []

        if length is None:
            length = random.randrange(5, 15)

        first_char = random.choice(string.ascii_uppercase)
        chars.append(first_char)

        for i in range(length):
            char = random.choice(string.ascii_lowercase)
            chars.append(char)

        return ''.join(chars)

    def add_random_students(self, no_students):
        '''
        Add a number of randomly generated students.

        Args:
            no_students (int): The number of random students to add.

        Returns:
            list: List of random students that were added.
        '''
        students = []

        for i in range(no_students):
            name = self.get_random_name()
            student = self.add_student(name)
            students.append(student)

        return students
