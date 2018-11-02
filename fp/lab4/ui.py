from expenses import ExpensesCollection, Expense
from history import History
from menu import Menu, Entry
from utils import save_as_json, load_from_json

def ui_input(message, error, validate_fn=None, type_cast=None):
    while True:
        try:
            raw_value = input(message)
            if type_cast is not None:
                value = type_cast(raw_value)
            else:
                value = raw_value

            if validate_fn is not None and not validate_fn(value):
                raise ValueError()
        except ValueError:
            print(error)
            continue

        return value

def ui_input_path(message='Enter a path: ', error='Entered path is invalid.'):
    return ui_input(message, error)

def ui_input_day(message='Enter a day: ', error='Entered day is invalid.'):
    return ui_input(message, error, Expense.is_valid_day, int)

def ui_input_type(message='Select a type: ', error='Selected type is invalid.'):
    print('Valid expense types:')
    for index, type_ in Expense.types.items():
        print('{}. {}'.format(index, type_))

    return ui_input(message, error, Expense.is_valid_type, int)

def ui_input_sum(message='Enter a sum: ', error='Entered sum is invalid.'):
    return ui_input(message, error, Expense.is_valid_sum, int)

def ui_print_expense(expense):
    day = expense.get_day()
    type_ = expense.get_type()
    sum_ = expense.get_sum()
    type_name = Expense.types[type_]
    print('Day: {}, Type: {}, Sum: {}'.format(day, type_name, sum_))

def ui_print_expenses(collection, title=None):
    if len(collection) == 0:
        print('There are no such expenses.')
        return

    if title is not None:
        print(title)

    for expense in collection:
        ui_print_expense(expense)

def ui_add(expenses):
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

def ui_update(expenses):
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

def ui_delete_by_day(expenses):
    day = ui_input_day()
    deleted_expenses = expenses.do('delete', day=day)

    ui_print_expenses(deleted_expenses, 'Deleted expenses:')
    print()

def ui_delete_by_interval(expenses):
    start_day = ui_input_day('Enter the starting day: ')
    end_day = ui_input_day('Enter the ending day: ')

    deleted_expenses = expenses.do('delete', min_day=start_day, max_day=end_day)

    ui_print_expenses(deleted_expenses, 'Deleted expenses:')
    print()

def ui_delete_by_type(expenses):
    type_ = ui_input_type()
    deleted_expenses = expenses.do('delete', type_=type_)

    ui_print_expenses(deleted_expenses, 'Deleted expenses:')
    print()

def ui_find_larger_sum(expenses):
    min_sum = ui_input_sum()

    matching_expenses = expenses.do('find', min_sum=min_sum + 1, keep=False)

    ui_print_expenses(matching_expenses,
            'The expenses larger than {} are:'.format(min_sum))
    print()

def ui_find_before_day_smaller_sum(expenses):
    max_day = ui_input_day()
    max_sum = ui_input_sum()

    matching_expenses = expenses.do('find', max_day=max_day - 1, max_sum=max_sum - 1, keep=False)

    ui_print_expenses(matching_expenses,
            'The expenses before {} and smaller than {} are:'.format(max_day, max_sum))
    print()

def ui_find_by_type(expenses):
    type_ = ui_input_type()
    type_name = Expense.types[type_]

    matching_expenses = expenses.do('find', type_=type_, keep=False)

    ui_print_expenses(matching_expenses,
            'The expenses of type {} are:'.format(type_name))
    print()

def ui_find_sum_by_type(expenses):
    type_ = ui_input_type()
    type_name = Expense.types[type_]

    matching_expenses = expenses.do('find', type_=type_, keep=False)
    sum_ = 0
    for expense in matching_expenses:
        sum_ += expense.get_sum()

    print('The total sum for expenses of type {} is {}.'.format(type_name, sum_))
    print()

def ui_find_day_with_max_sum(expenses):
    max_expense = None

    for expense in expenses.do('get', keep=False):
        if max_expense is None or max_expense.get_sum() < expense.get_sum():
            max_expense = expense

    print('The day with the maximum sum is {}.'.format(max_expense.get_day()))
    print()

def ui_find_by_sum(expenses):
    sum_ = ui_input_sum()

    matching_expenses = expenses.do('find', sum_=sum_, keep=False)

    ui_print_expenses(matching_expenses, 'The expenses of sum {} are:'.format(sum_))
    print()

def ui_print_sorted(expenses):
    collection = expenses.do('find', keep=False)

    def sort_by_type(expense):
        return expense.get_type()

    collection.sort(key=sort_by_type)

    ui_print_expenses(collection, 'The expenses sorted by type are:')
    print()

def ui_print_grouped(expenses):
    sums = [100, 500]
    groups = expenses.do('group_by_sums', sums, keep=False)

    print('The grouped expenses are:')

    for index, sum_ in enumerate(sums):
        print('<= ' + str(sum_))
        ui_print_expenses(groups[index])

    print('>  ' + str(sums[-1]))
    ui_print_expenses(groups[-1])

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

def ui_save(expenses):
    path = ui_input_path()

    serialized = expenses.do('get_serialized', keep=False)
    save_as_json(serialized, path)

def ui_load(expenses):
    path = ui_input_path()

    serialized = load_from_json(path)
    expenses.do('set_serialized', serialized)

def ui_exit():
    print('Goodbye.')
    exit()

def ui_run():
    expenses = History(ExpensesCollection)

    add_menu = Menu([
        Entry(1, 'Add a new expense', ui_add, expenses),
        Entry(2, 'Update an existing expense', ui_update, expenses),
    ])

    delete_menu = Menu([
        Entry(1, 'Delete all expenses for any given day', ui_delete_by_day, expenses),
        Entry(2, 'Delete all expenses made between two days', ui_delete_by_interval, expenses),
        Entry(3, 'Delete all expenses of a given expense type', ui_delete_by_type, expenses),
    ])

    find_menu = Menu([
        Entry(1, 'Find all expenses larger than a given sum', ui_find_larger_sum, expenses),
        Entry(2, 'Find all expenses before a given day and smaller than a given sum', ui_find_before_day_smaller_sum, expenses),
        Entry(3, 'Find all expenses of a given expense type', ui_find_by_type, expenses),
    ])

    report_menu = Menu([
        Entry(1, 'Find the total sum for a given expense type', ui_find_sum_by_type, expenses),
        Entry(2, 'Find the day with the maximum sum', ui_find_day_with_max_sum, expenses),
        Entry(3, 'Find all the expenses with a given sum', ui_find_by_sum, expenses),
        Entry(4, 'Show all the expenses sorted by type', ui_print_sorted, expenses),
        Entry(5, 'Show all expenses grouped by sum', ui_print_grouped, expenses),
    ])

    main_menu = Menu([
        Entry(1, 'Add', add_menu.run),
        Entry(2, 'Delete', delete_menu.run),
        Entry(3, 'Find', find_menu.run),
        Entry(4, 'Report', report_menu.run),
        Entry('u', 'Undo', ui_undo, expenses),
        Entry('r', 'Redo', ui_redo, expenses),
        Entry('s', 'Save', ui_save, expenses),
        Entry('l', 'Load', ui_load, expenses),
        Entry('x', 'Exit', ui_exit),
    ])

    while True:
        main_menu.run()

ui_run()
