def __cmp(a, b):
    if a < b:
        return -1

    if a > b:
        return 1

    return 0

def quicksort(l, *, key=lambda x: x, reverse=False, cmp_=__cmp):
    '''
    Create a new sorted list from the items in the given list.

    Args:
        l (list): The list to sort.
        key (function, optional): A function of one argument that is used
            to extract a comparison key from an element of the given list.
        reverse (bool, optional): Whether to sort the elements in reverse order.
        cmp (function, optional): A function with two arguments that can be used
            to compare two elements of the given list for figuring out their order.

    Returns:
        list: A new sorted list from the items in the given list.
    '''
    if l == []:
        return []

    pivot = key(l[0])
    first_part_list = [x for x in l[1:] if cmp_(key(x), pivot) < 0]
    second_part_list = [x for x in l[1:] if cmp_(key(x), pivot) > 0]
    first_part = quicksort(first_part_list, key=key, reverse=reverse, cmp_=cmp_)
    second_part = quicksort(second_part_list, key=key, reverse=reverse, cmp_=cmp_)

    if reverse == True:
        first_part, second_part = second_part, first_part

    return first_part + [l[0]] + second_part

def __gnome(l, last_pos, key, reverse, cmp_):
    pos = last_pos
    while pos > 0:
        first = key(l[pos - 1])
        second = key(l[pos])
        if not reverse and cmp_(first, second) < 0 or \
               reverse and cmp_(first, second) > 0:
            break

        l[pos], l[pos - 1] = l[pos - 1], l[pos]
        pos -= 1

def gnomesort(l, *, key=lambda x: x, reverse=False, cmp_=__cmp):
    '''
    Create a new sorted list from the items in the given list.

    Args:
        l (list): The list to sort.
        key (function, optional): A function of one argument that is used
            to extract a comparison key from an element of the given list.
        reverse (bool, optional): Whether to sort the elements in reverse order.
        cmp (function, optional): A function with two arguments that can be used
            to compare two elements of the given list for figuring out their order.

    Returns:
        list: A new sorted list from the items in the given list.
    '''
    result = l[:]

    for i in range(len(result)):
        __gnome(result, i, key=key, reverse=reverse, cmp_=cmp_)

    return result
