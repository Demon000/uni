from expenses import ExpensesCollection, Expense
from history import History
from menu import Menu, Entry
from utils import bind_fn

def ui_input_validated(message, error, validate_fn):
    while True:
        try:
            value = int(input(message))
            if not validate_fn(value):
                raise ValueError()
        except ValueError:
            print(error)
            continue

        return value

def ui_input_day(message='Enter a day: ', error='Entered day is invalid.'):
    return ui_input_validated(message, error, Expense.is_valid_day)

def ui_print_types():
    print('Valid expense types:')
    for index, type_ in Expense.types.items():
        print('{}. {}'.format(index, type_))

def ui_input_type(message='Select a type: ', error='Selected type is invalid.'):
    ui_print_types()
    return ui_input_validated(message, error, Expense.is_valid_type)

def ui_input_sum(message='Enter a sum: ', error='Entered sum is invalid.'):
    return ui_input_validated(message, error, Expense.is_valid_sum)

def ui_print_expense(expense):
    day = expense.get_day()
    type_name = Expense.types[expense.get_type()]
    sum_ = expense.get_sum()
    print('Day: {}, Type: {}, Sum: {}'.format(day, type_name, sum_))

def ui_print_expenses(collection, title=None):
    if len(collection):
        if title is not None:
            print(title)
    else:
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

    ui_print_expenses(deleted_expenses, 'Deleted expenses:')
    print()

def ui_delete_for_interval(expenses):
    start_day = ui_input_day('Enter the starting day: ')
    end_day = ui_input_day('Enter the ending day: ')

    deleted_expenses = expenses.do('delete', min_day=start_day, max_day=end_day)

    ui_print_expenses(deleted_expenses, 'Deleted expenses:')
    print()

def ui_delete_for_type(expenses):
    type_ = ui_input_type()
    deleted_expenses = expenses.do('delete', type_=type_)

    ui_print_expenses(deleted_expenses, 'Deleted expenses:')
    print()

def ui_find_larger_than(expenses):
    min_sum = ui_input_sum()

    matching_expenses = expenses.do('find', min_sum=min_sum, keep=False)

    ui_print_expenses(matching_expenses,
            'The expenses larger than {} are:'.format(min_sum))
    print()

def ui_find_before_day_smaller_than(expenses):
    max_day = ui_input_day()
    max_sum = ui_input_sum()

    matching_expenses = expenses.do('find', max_day=max_day, max_sum=max_sum, keep=False)

    ui_print_expenses(matching_expenses,
            'The expenses before {} and smaller than {} are:'.format(max_day, max_sum))
    print()

def ui_find_for_type(expenses):
    type_ = ui_input_type()
    type_name = Expense.types[type_]

    matching_expenses = expenses.do('find', type_=type_, keep=False)

    ui_print_expenses(matching_expenses,
            'The expenses of type {} are:'.format(type_name))
    print()

def ui_find_total_sum_for_type(expenses):
    type_ = ui_input_type()
    type_name = Expense.types[type_]

    matching_expenses = expenses.do('find', type_=type_, keep=False)
    sum_ = 0
    for expense in matching_expenses:
        sum_ += expense.get_sum()

    print('The total sum for expenses of type {} is {}.'.format(type_name, sum_))
    print()

def ui_find_day_for_max_sum(expenses):
    max_expense = None

    for expense in expenses.do('get', keep=False):
        if max_expense is None or max_expense.get_sum() < expense.get_sum():
            max_expense = expense

    print('The day with the maximum sum is {}.'.format(max_expense.get_day()))
    print()

def ui_find_for_sum(expenses):
    sum_ = ui_input_sum()

    matching_expenses = expenses.do('find', sum_=sum_, keep=False)

    ui_print_expenses(matching_expenses, 'The expenses of sum {} are:'.format(sum_))
    print()

def ui_print_sorted_by_type(expenses):
    collection = expenses.do('find', keep=False)

    def sort_by_type(expense):
        return expense.get_type()

    collection.sort(key=sort_by_type)

    ui_print_expenses(collection, 'The expenses sorted by type are:')
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

def ui_exit():
    print('Goodbye.')
    exit()

def ui_run():
    expenses = History(ExpensesCollection)

    add_menu = Menu([
        Entry(1, 'Add a new expense',
                bind_fn(ui_add_expense, expenses)),
        Entry(2, 'Update an existing expense',
                bind_fn(ui_update_expense, expenses)),
    ])

    delete_menu = Menu([
        Entry(1, 'Delete all expenses for any given day',
                bind_fn(ui_delete_for_day, expenses)),
        Entry(2, 'Delete all expenses made between two days',
                bind_fn(ui_delete_for_interval, expenses)),
        Entry(3, 'Delete all expenses of a given expense type',
                bind_fn(ui_delete_for_type, expenses)),
    ])

    find_menu = Menu([
        Entry(1, 'Find all expenses larger than a given sum',
                bind_fn(ui_find_larger_than, expenses)),
        Entry(2, 'Find all expenses done before a given day and smaller than a given sum',
                bind_fn(ui_find_before_day_smaller_than, expenses)),
        Entry(3, 'Find all expenses of a given expense type',
                bind_fn(ui_find_for_type, expenses)),
    ])

    report_menu = Menu([
        Entry(1, 'Find the total sum for a given expense type',
                bind_fn(ui_find_total_sum_for_type, expenses)),
        Entry(2, 'Find the day with the maximum sum',
                bind_fn(ui_find_day_for_max_sum, expenses)),
        Entry(3, 'Find all the expenses with a given sum',
                bind_fn(ui_find_for_sum, expenses)),
        Entry(4, 'Show all the expenses sorted by type',
                bind_fn(ui_print_sorted_by_type, expenses)),
    ])

    main_menu = Menu([
        Entry(1, 'Add', add_menu.run),
        Entry(2, 'Delete', delete_menu.run),
        Entry(3, 'Find', find_menu.run),
        Entry(4, 'Report', report_menu.run),
        Entry('u', 'Undo', bind_fn(ui_undo, expenses)),
        Entry('r', 'Redo', bind_fn(ui_redo, expenses)),
        Entry('x', 'Exit', ui_exit),
    ])

    while True:
        main_menu.run()

ui_run()
