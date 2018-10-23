from utils import is_valid_unsigned

class Expense():
    types = {
        1: 'Food',
        2: 'Maintenance',
        3: 'Clothing',
        4: 'Phone bill',
        5: 'Miscellaneous',
    }

    def __init__(self, day, type_, sum_):
        self.day = day
        self.type = type_
        self.sum = sum_

    def matches(self, day=None, type_=None, sum_=None, test_fn=None):
        if day is not None and self.day != day:
            return False

        if type_ is not None and self.type != type_:
            return False

        if sum_ is not None and self.sum != sum_:
            return False

        if test_fn is not None and not test_fn(self):
            return False

        return True

    @staticmethod
    def is_valid_day(value):
        return is_valid_unsigned(value, 1, 31)

    @staticmethod
    def is_valid_sum(value):
        return is_valid_unsigned(value, 1)

    @staticmethod
    def is_valid_type(value):
        if value not in Expense.types.keys():
            return False

        return True

class ExpensesCollection():
    def __init__(self):
        self.collection = []

    def get(self):
        return self.collection

    def find(self, *args, **kwargs):
        matching_expenses = []
        for expense in self.collection:
            if expense.matches(*args, **kwargs):
                matching_expenses.append(expense)

        return matching_expenses

    def find_one(self, *args, **kwargs):
        matching_expenses = self.find(*args, **kwargs)
        if not len(matching_expenses):
            return None

        return matching_expenses[0]

    def add_one(self, day, type_, sum_):
        existing_expense = self.find_one(day, type_)
        if existing_expense:
            raise ValueError('An expense on this day and with '
                    'this type already exists.')

        expense = Expense(day, type_, sum_)
        self.collection.append(expense)
        return expense

    def update_one(self, day, type_, sum_):
        expense = self.find_one(day, type_)
        if not expense:
            raise ValueError('An expense on this day and with '
                    'this type does not exist.')

        expense.sum = sum_
        return expense

    def delete(self, *args, **kwargs):
        new_collection = []
        deleted_expenses = []
        for expense in self.collection:
            if expense.matches(*args, **kwargs):
                deleted_expenses.append(expense)
            else:
                new_collection.append(expense)

        self.collection = new_collection
        return deleted_expenses
