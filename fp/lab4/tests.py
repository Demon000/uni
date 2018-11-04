from expenses import ExpensesCollection, Expense
from history import History

def test_populate(expenses):
    expenses.add_one(1, 1, 100)
    expenses.add_one(2, 1, 200)
    expenses.add_one(3, 1, 300)
    expenses.add_one(4, 2, 400)
    expenses.add_one(5, 2, 500)

def test_add_one():
    expenses = ExpensesCollection()

    # Test addition
    added_expense = expenses.add_one(1, 1, 100)
    assert added_expense.matches(1, 1, 100)

    # Test invalid addition
    try:
        added_expense = expenses.add_one(1, 1, 1000)
        assert False
    except ValueError:
        pass

def test_update_one():
    expenses = ExpensesCollection()
    test_populate(expenses)

    # Test update
    updated_expense = expenses.update_one(1, 1, 500)
    assert updated_expense.get_sum() == 500

    # Test invalid update
    try:
        expenses.update_one(31, 1, 500)
        assert False
    except ValueError:
        pass

def test_delete():
    expenses = ExpensesCollection()
    test_populate(expenses)

    # Test delete for day
    deleted_expenses = expenses.delete(day=1)
    assert len(deleted_expenses) == 1
    assert deleted_expenses[0].matches(1, 1, 100)

    # Test delete for day interval
    deleted_expenses = expenses.delete(min_day=2, max_day=3)
    assert len(deleted_expenses) == 2
    assert deleted_expenses[0].matches(2, 1, 200)
    assert deleted_expenses[1].matches(3, 1, 300)

    # Test delete for type
    deleted_expenses = expenses.delete(type_=2)
    assert len(deleted_expenses) == 2
    assert deleted_expenses[0].matches(4, 2, 400)
    assert deleted_expenses[1].matches(5, 2, 500)

def test_find():
    expenses = ExpensesCollection()
    test_populate(expenses)

    # Test find larger than sum
    matching_expenses = expenses.find(min_sum=400)
    assert len(matching_expenses) == 2
    assert matching_expenses[0].matches(4, 2, 400)
    assert matching_expenses[1].matches(5, 2, 500)

    # Test find before day and smaller than sum
    matching_expenses = expenses.find(max_day=2, max_sum=300)
    assert matching_expenses[0].matches(1, 1, 100)
    assert matching_expenses[1].matches(2, 1, 200)

    # Test find of type
    matching_expenses = expenses.find(type_=2)
    assert len(matching_expenses) == 2
    assert matching_expenses[0].matches(4, 2, 400)
    assert matching_expenses[1].matches(5, 2, 500)

    # Test find with sum
    matching_expenses = expenses.find(sum_=500)
    assert len(matching_expenses) == 1
    assert matching_expenses[0].matches(5, 2, 500)

def test_find_total():
    expenses = ExpensesCollection()
    test_populate(expenses)

    # Test find sum for type
    sum_ = expenses.find_total(type_=1)
    assert sum_ == 600

def test_find_max_sum():
    expenses = ExpensesCollection()
    test_populate(expenses)

    # Test find sum for type
    max_sum_expenses = expenses.find_max_sum()
    assert len(max_sum_expenses) == 1
    assert max_sum_expenses[0].matches(5, 2, 500)

def test_group_by_sums():
    expenses = ExpensesCollection()
    test_populate(expenses)

    # Test group expenses in buckets by sums
    sums = [100, 300]
    groups = expenses.group_by_sums(sums)
    assert len(groups[0]) == 1
    assert groups[0][0].matches(1, 1, 100)
    assert len(groups[1]) == 2
    assert groups[1][0].matches(2, 1, 200)
    assert groups[1][1].matches(3, 1, 300)
    assert len(groups[2]) == 2
    assert groups[2][0].matches(4, 2, 400)
    assert groups[2][1].matches(5, 2, 500)

def run_tests():
    test_add_one()
    test_update_one()
    test_delete()
    test_find()
    test_find_total()
    test_find_max_sum()
    test_group_by_sums()

run_tests()
print('Tests passed.')
