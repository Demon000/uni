from expenses import ExpensesCollection, Expense
from history import History
from menu import Menu, Entry

def ui_input_day(message=None, error=None):
    if message is None:
        message = 'Enter a day: '

    if error is None:
        error = 'Entered day is invalid.'

    while True:
        try:
            day = int(input(message))
            if not Expense.is_valid_day(day):
                raise ValueError()
        except ValueError:
            print(error)
            continue

        return day

def ui_print_types():
    print('Valid expense types:')
    for index, type_ in Expense.get_types().items():
        print('{}. {}'.format(index, type_))

def ui_input_type(message=None, error=None):
    if message is None:
        message = 'Select a type: '

    if error is None:
        error = 'Selected type is invalid.'

    ui_print_types()

    while True:
        try:
            type_ = int(input(message))
            if not Expense.is_valid_type(type_):
                raise ValueError()
        except ValueError:
            print(error)
            continue

        return type_

def ui_input_sum(message=None, error=None):
    if message is None:
        message = 'Enter a sum: '

    if error is None:
        error = 'Entered sum is invalid.'

    while True:
        try:
            sum_ = int(input(message))
            if not Expense.is_valid_sum(sum_):
                raise ValueError()
        except ValueError:
            print(error)
            continue

        return sum_

def ui_print_expense(expense):
    day = expense.get_day()
    type_name = Expense.get_types()[expense.get_type()]
    sum_ = expense.get_sum()
    print('Day: {}, Type: {}, Sum: {}'.format(day, type_name, sum_))

def ui_print_expenses(collection):
    if not len(collection):
        print('There are no such expenses.')
        return

    for expense in collection:
        ui_print_expense(expense)

def ui_add_expense(expenses):
    day = ui_input_day()
    type_ = ui_input_type()
    sum_ = ui_input_sum()

    try:
        expense = expenses.do('add_one', day, type_, sum_)
    except ValueError as ve:
        print(ve)
        return

    print('Added expense:')
    ui_print_expense(expense)
    print()

def ui_update_expense(expenses):
    day = ui_input_day()
    type_ = ui_input_type()
    sum_ = ui_input_sum()

    try:
        expense = expenses.do('update_one', day, type_, sum_)
    except ValueError as ve:
        print(ve)
        return

    print('Updated expense:')
    ui_print_expense(expense)
    print()

def ui_delete_for_day(expenses):
    day = ui_input_day()
    deleted_expenses = expenses.do('delete', day=day)

    print('Deleted expenses:')
    ui_print_expenses(deleted_expenses)
    print()

def ui_delete_for_interval(expenses):
    start_day = ui_input_day('Enter the starting day: ')
    end_day = ui_input_day('Enter the ending day: ')

    def match(expense):
        return start_day <= expense.get_day() <= end_day

    deleted_expenses = expenses.do('delete', test_fn=match)

    print('Deleted expenses:')
    ui_print_expenses(deleted_expenses)
    print()

def ui_delete_for_type(expenses):
    type_ = ui_input_type()
    deleted_expenses = expenses.do('delete', type_=type_)

    print('Deleted expenses:')
    ui_print_expenses(deleted_expenses)
    print()

def ui_find_larger_than(expenses):
    min_sum = ui_input_sum()

    def match(expense):
        return min_sum < expense.get_sum()

    matching_expenses = expenses.do('find', test_fn=match, keep=False)

    print('The expenses larger than {} are:'.format(min_sum))
    ui_print_expenses(matching_expenses)
    print()

def ui_find_before_day_smaller_than(expenses):
    max_day = ui_input_day()
    max_sum = ui_input_sum()

    def match(expense):
        return max_day > expense.get_day() and max_sum > expense.get_sum()

    matching_expenses = expenses.do('find', test_fn=match, keep=False)

    print('The expenses made before {} and smaller than {} are:'.format(max_day, max_sum))
    ui_print_expenses(matching_expenses)
    print()

def ui_find_for_type(expenses):
    type_ = ui_input_type()

    matching_expenses = expenses.do('find', type_=type_, keep=False)

    type_name = Expense.get_types()[type_]
    print('The expenses of type {} are:'.format(type_name))
    ui_print_expenses(matching_expenses)
    print()

def ui_find_total_sum_for_type(expenses):
    type_ = ui_input_type()
    type_name = Expense.get_types()[type_]

    matching_expenses = expenses.do('find', type_=type_, keep=False)
    sum_ = 0
    for expense in matching_expenses:
        sum_ += expense.get_sum()

    print('The total sum for expenses of type {} is {}.'.format(type_name, sum_))
    print()

def ui_find_day_for_max_sum(expenses):
    max_expense = None

    for expense in expenses.do('get'):
        if max_expense is None or max_expense.get_sum() < expense.get_sum():
            max_expense = expense

    print('The day with the maximum sum is {}.'.format(max_expense.get_day()))
    print()

def ui_find_for_sum(expenses):
    sum_ = ui_input_sum()

    matching_expenses = expenses.do('find', sum_=sum_, keep=False)

    print('The expenses of sum {} are:'.format(sum_))
    ui_print_expenses(matching_expenses)
    print()

def ui_print_sorted_by_type(expenses):
    collection = expenses.do('find', keep=False)

    def sort_by_type(expense):
        return expense.get_type()

    collection.sort(key=sort_by_type)

    print('The sorted expenses are:')    
    ui_print_expenses(collection)
    print()

def ui_undo(expenses):
    try:
        expenses.undo()
    except ValueError as ve:
        print(ve)

def ui_redo(expenses):
    try:
        expenses.redo()
    except ValueError as ve:
        print(ve)

def ui_exit(expenses):
    print('Goodbye.')
    exit()

def ui_run():
    expenses = History(ExpensesCollection)

    add_menu = Menu([
        Entry(1, 'Add a new expense', ui_add_expense),
        Entry(2, 'Update an existing expense', ui_update_expense),
    ], expenses)

    delete_menu = Menu([
        Entry(1, 'Delete all expenses for any given day', ui_delete_for_day),
        Entry(2, 'Delete all expenses made between two days', ui_delete_for_interval),
        Entry(3, 'Delete all expenses of a given expense type', ui_delete_for_type),
    ], expenses)

    find_menu = Menu([
        Entry(1, 'Find all expenses larger than a given sum', ui_find_larger_than),
        Entry(2, 'Find all expenses done before a given day and smaller than a given sum', ui_find_before_day_smaller_than),
        Entry(3, 'Find all expenses of a given expense type', ui_find_for_type),
    ], expenses)

    report_menu = Menu([
        Entry(1, 'Find the total sum for a given expense type', ui_find_total_sum_for_type),
        Entry(2, 'Find the day with the maximum sum', ui_find_day_for_max_sum),
        Entry(3, 'Find all the expenses with a given sum', ui_find_for_sum),
        Entry(4, 'Show all the expenses sorted by type', ui_print_sorted_by_type),
    ], expenses)

    main_menu = Menu([
        Entry(1, 'Add', add_menu.run),
        Entry(2, 'Delete', delete_menu.run),
        Entry(3, 'Find', find_menu.run),
        Entry(4, 'Report', report_menu.run),
        Entry('u', 'Undo', ui_undo),
        Entry('r', 'Redo', ui_redo),
        Entry('e', 'Exit', ui_exit),
    ], expenses)

    while True:
        main_menu.run()

ui_run()
