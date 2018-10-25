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
    def is_valid_day(day):
        return is_valid_unsigned(day, 1, 31)

    @staticmethod
    def is_valid_sum(sum_):
        return is_valid_unsigned(sum_, 1)

    @staticmethod
    def is_valid_type(type_):
        if type_ not in Expense.types.keys():
            return False

        return True

class ExpensesCollection():
    def __init__(self):
        self.collection = []

    def get(self):
        return self.collection

    def find(self, *args, **kwargs):
        '''
        Finds the expenses that match the passed parameters.
        '''
        matching_expenses = []
        for expense in self.collection:
            if expense.matches(*args, **kwargs):
                matching_expenses.append(expense)

        return matching_expenses

    def find_one(self, *args, **kwargs):
        '''
        Finds the expense that matches the passed parameters.
        Returns None if there is no such expense.
        '''
        matching_expenses = self.find(*args, **kwargs)
        if not len(matching_expenses):
            return None

        return matching_expenses[0]

    def add_one(self, day, type_, sum_):
        '''
        Creates an expense using the passed day, type and sum and
        adds it to to the expenses list.
        Raises a ValueError if an expense already exists with the
        current day and type.
        '''
        existing_expense = self.find_one(day, type_)
        if existing_expense:
            raise ValueError('An expense on this day and with '
                    'this type already exists.')

        expense = Expense(day, type_, sum_)
        self.collection.append(expense)
        return expense

    def update_one(self, day, type_, sum_):
        '''
        Finds an expense that matches the passed day and type and
        updates the sum.
        Raises a ValueError if no expense matches the current day
        and type.
        '''
        expense = self.find_one(day, type_)
        if not expense:
            raise ValueError('An expense on this day and with '
                    'this type does not exist.')

        expense.sum = sum_
        return expense

    def delete(self, *args, **kwargs):
        '''
        Finds the expenses that match the passed parameters and
        removes them.
        '''
        new_collection = []
        deleted_expenses = []
        for expense in self.collection:
            if expense.matches(*args, **kwargs):
                deleted_expenses.append(expense)
            else:
                new_collection.append(expense)

        self.collection = new_collection
        return deleted_expenses
