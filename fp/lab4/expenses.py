from utils import is_valid_unsigned

class Expense():
    # Valid expense types
    types = {
        1: 'Food',
        2: 'Maintenance',
        3: 'Clothing',
        4: 'Phone bill',
        5: 'Miscellaneous',
    }

    def __init__(self, day, type_, sum_):
        '''
        Initialize an expense.

        Args:
            day (int): A day to be used for this new expense.
            type_ (int): A type to be used for this new expense.
            sum_ (int): A sum to be used for this new expense.
        '''
        self.day = day
        self.type = type_
        self.sum = sum_

    def matches(self, day=None, type_=None, sum_=None, test_fn=None):
        '''
        Check if the expense matches the passed arguments.

        Args:
            day (int, optional): A day that this expense is matched against.
            type_ (int, optional): A type that is expense is matched against.
            sum_ (int, optional): A sum that is expense is matched against.
            test_fn (function, optional): A function that is ran against the expense,
                that should return True if the expense matches.

        Returns:
            bool: Whether this expense matches all the arguments or not.
        '''
        if day is not None and self.get_day() != day:
            return False

        if type_ is not None and self.get_type() != type_:
            return False

        if sum_ is not None and self.get_sum() != sum_:
            return False

        if test_fn is not None and not test_fn(self):
            return False

        return True

    def get_day(self):
        '''
        Returns:
            int: The day of the current expense.
        '''
        return self.day

    def get_sum(self):
        '''
        Returns:
            int: The sum of the current expense.
        '''
        return self.sum

    def get_type(self):
        '''
        Returns:
            int: The type of the current expense.
        '''
        return self.type

    def set_sum(self, sum_):
        '''
        Set the sum of the current expense.

        Args:
            sum_ (int): Sets the current expense's sum to this value.
        '''
        self.sum = sum_

    @staticmethod
    def is_valid_day(day):
        '''
        Check if the passed value is a valid day.

        Args:
            day (int): The day to check validity for.
        '''
        return is_valid_unsigned(day, 1, 31)

    @staticmethod
    def is_valid_sum(sum_):
        '''
        Check if the passed value is a valid sum.

        Args:
            sum_ (int): The sum to check validity for.
        '''
        return is_valid_unsigned(sum_, 1)

    @staticmethod
    def is_valid_type(type_):
        '''
        Check if the passed value is a valid type.

        Args:
            type_ (int): The type to check validity for.
        '''
        if type_ not in Expense.types.keys():
            return False

        return True

class ExpensesCollection():
    def __init__(self):
        '''
        Initialize an expenses collection.
        '''
        self.collection = []

    def get(self):
        '''
        Returns:
            list: A list containing all the expenses.
        '''
        return self.collection

    def find(self, *args, **kwargs):
        '''
        Find the expenses that match the passed arguments.

        Args:
            Same arguments as Expense.matches()

        Returns:
            list: A list containing all matching the expenses.
        '''
        matching_expenses = []
        for expense in self.collection:
            if expense.matches(*args, **kwargs):
                matching_expenses.append(expense)

        return matching_expenses

    def find_one(self, *args, **kwargs):
        '''
        Find the expense that matches the passed arguments.

        Args:
            Same arguments as Expense.matches()

        Returns:
            Expense: The matching expense or None if there is no such expense.
        '''
        matching_expenses = self.find(*args, **kwargs)
        if not len(matching_expenses):
            return None

        return matching_expenses[0]

    def add_one(self, day, type_, sum_):
        '''
        Create an expense using the passed day, type and sum and
        add it to to the expenses list.

        Args:
            day (int): A day to use when creating the new expense.
            type_ (int): A type to use when creating the new expense.
            sum_ (int): A sum to use when creating the new expense.

        Returns:
            Expense: The newly added expense.

        Raises:
            ValueError: If an expense already exists with the
                day and type.
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
        Find an expense that matches the passed day and type and
        updates the sum.

        Args:
            day (int): A day to find the matching expense for.
            type_ (int): A type to find the matching expense for.
            sum_ (int): A sum to update the matching expense's sum with.

        Returns:
            Expense: The updated expense.

        Raises:
            ValueError: If no expense matches the day
                and type.
        '''
        expense = self.find_one(day, type_)
        if not expense:
            raise ValueError('An expense on this day and with '
                    'this type does not exist.')

        expense.set_sum(sum_)
        return expense

    def delete(self, *args, **kwargs):
        '''
        Find the expenses that match the passed arguments and
        removes them.

        Args:
            Same arguments as Expense.matches()

        Returns:
            list: A list containing the deleted expenses.
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
