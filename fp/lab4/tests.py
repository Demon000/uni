from expenses import ExpensesCollection, Expense
from history import History

def run_tests():
    expenses = History(ExpensesCollection)

    # Test addition
    added_expense = expenses.do('add_one', 1, 1, 100)
    assert added_expense.matches(1, 1, 100)

    added_expense = expenses.do('add_one', 2, 2, 1000)
    assert added_expense.matches(2, 2, 1000)

    added_expense = expenses.do('add_one', 2, 3, 2000)
    assert added_expense.matches(2, 3, 2000)

    added_expense = expenses.do('add_one', 3, 1, 100)
    assert added_expense.matches(3, 1, 100)

    added_expense = expenses.do('add_one', 4, 3, 500)
    assert added_expense.matches(4, 3, 500)

    try:
        added_expense = expenses.do('add_one', 2, 2, 2000)
        assert False
    except ValueError:
        pass

    # Test update
    updated_expense = expenses.do('update_one', 2, 2, 500)
    assert updated_expense.get_sum() == 500

    try:
        added_expense = expenses.do('add_one', 5, 1, 2000)
        assert False
    except ValueError:
        pass

    # Test deletion for day
    expenses.do('delete', 3)
    collection = expenses.do('get')
    assert len(collection) == 4

    # Test deletion for interval
    expenses.do('delete', min_day=1, max_day=2)
    collection = expenses.do('get')
    assert len(collection) == 1

    serialization = expenses.do('serialize')
    print(serialization)

run_tests()
print('Tests passed.')
