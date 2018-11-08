from expenses import ExpensesCollection, Expense
from history import History

def cli_print_expenses(collection):
    for expense in collection:
        print(expense)

def cli_add(expenses, day, type_, sum_):
    if not Expense.is_valid_day(day):
        raise ValueError('Invalid day.')

    if not Expense.is_valid_type(type_):
        raise ValueError('Invalid type.')

    if not Expense.is_valid_sum(sum_):
        raise ValueError('Invalid sum.')

    expenses.do('add_one', day, type_, sum_)

def cli_update(expenses, day, type_, sum_):
    if not Expense.is_valid_day(day):
        raise ValueError('Invalid day.')

    if not Expense.is_valid_type(type_):
        raise ValueError('Invalid type.')

    if not Expense.is_valid_sum(sum_):
        raise ValueError('Invalid sum.')

    expenses.do('update_one', day, type_, sum_)

def cli_delete(expenses, day, type_):
    if not Expense.is_valid_day(day):
        raise ValueError('Invalid day.')

    if not Expense.is_valid_type(type_):
        raise ValueError('Invalid type.')

    expenses.do('delete', day=day, type_=type_)

def cli_list(expenses):
    collection = expenses.do('get', keep=False)
    cli_print_expenses(collection)

def cli_undo(expenses):
    expenses.undo()
    pass

def cli_exit(expenses):
    print('Goodbye.')
    exit()

def execute_line(expenses, line):
    commands = {
        'add': [3, cli_add],
        'update': [3, cli_update],
        'delete': [2, cli_delete],
        'list': [0, cli_list],
        'undo': [0, cli_undo],
        'exit': [0, cli_exit],
    }

    arguments_list = line.split()

    i = 0
    while i < len(arguments_list):
        command = arguments_list[i]
        if  command not in commands:
            print('Invalid command.')
            return

        i += 1

        fn = commands[command][1]
        needed_arguments = commands[command][0]
        raw_arguments = arguments_list[i:i + needed_arguments]
        passed_arguments = []
        for raw_argument in raw_arguments:
            try:
                argument = int(raw_argument)
            except ValueError:
                print('Invalid argument.')
                return

            passed_arguments.append(argument)

        try:
            fn(expenses, *passed_arguments)
        except ValueError as ve:
            print(ve)

        i += needed_arguments

def cli_run():
    expenses = History(ExpensesCollection)

    while True:
        line = input('>>>')
        execute_line(expenses, line)
