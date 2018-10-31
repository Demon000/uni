from expenses import ExpensesCollection, Expense
from history import History

def run_tests():
    expenses = History(ExpensesCollection)

    # Populate with data
    added_expense = expenses.do('add_one', 1, 1, 100)
    added_expense = expenses.do('add_one', 1, 2, 100)
    added_expense = expenses.do('add_one', 1, 3, 100)
    added_expense = expenses.do('add_one', 2, 1, 2000)
    added_expense = expenses.do('add_one', 3, 1, 100)
    added_expense = expenses.do('add_one', 4, 1, 500)
    added_expense = expenses.do('add_one', 5, 5, 500)
    added_expense = expenses.do('add_one', 6, 1, 500)
    added_expense = expenses.do('add_one', 7, 1, 500)
    added_expense = expenses.do('add_one', 8, 4, 500)

    # Test addition
    added_expense = expenses.do('add_one', 2, 2, 1000)
    assert added_expense.matches(2, 2, 1000)

    # Test failed addition
    try:
        added_expense = expenses.do('add_one', 2, 2, 2000)
        assert False
    except ValueError:
        pass

    # Test update
    updated_expense = expenses.do('update_one', 2, 2, 500)
    assert updated_expense.get_sum() == 500

    # Test failed update
    try:
        added_expense = expenses.do('update_one', 31, 1, 2000)
        assert False
    except ValueError:
        pass

    # Test deletion for day
    deleted_expenses = expenses.do('delete', 3)
    assert len(deleted_expenses) == 1
    assert deleted_expenses[0].matches(3, 1, 100)
    collection = expenses.do('get')
    assert len(collection) == 10

    # Test deletion for interval
    deleted_expenses = expenses.do('delete', min_day=1, max_day=2)
    assert len(deleted_expenses) == 5
    assert deleted_expenses[0].matches(1, 1, 100)
    assert deleted_expenses[1].matches(1, 2, 100)
    assert deleted_expenses[2].matches(1, 3, 100)
    assert deleted_expenses[3].matches(2, 1, 2000)
    assert deleted_expenses[4].matches(2, 2, 500)
    collection = expenses.do('get')
    assert len(collection) == 5

    # Test deletion for type
    deleted_expenses = expenses.do('delete', type_=5)
    assert len(deleted_expenses) == 1
    assert deleted_expenses[0].matches(5, 5, 500)
    collection = expenses.do('get')
    assert len(collection) == 4

    # Test find larger than a given sum
    matching_expenses = expenses.do('find', min_sum=200)
    assert len(matching_expenses) == 4
    assert matching_expenses[0].matches(4, 1, 500)
    assert matching_expenses[1].matches(6, 1, 500)
    assert matching_expenses[2].matches(7, 1, 500)
    assert matching_expenses[3].matches(8, 4, 500)

    # Test find before a given day and smaller than a given sum
    matching_expenses = expenses.do('find', max_day=4, max_sum=500)
    assert matching_expenses[0].matches(4, 1, 500)

    # Test find all expenses of a given expense type
    matching_expenses = expenses.do('find', type_=4)
    assert matching_expenses[0].matches(8, 4, 500)

run_tests()
print('Tests passed.')
