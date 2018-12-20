def quicksort(l, key=lambda x: x, reverse=False):
    if l == []:
        return []

    first_part = quicksort([x for x in l[1:] if key(x) < key(l[0])], key, reverse)
    second_part = quicksort([x for x in l[1:] if key(x) > key(l[0])], key, reverse)

    if reverse == True:
        first_part, second_part = second_part, first_part

    return first_part + [l[0]] + second_part

def __gnome(l, last_pos, key, reverse):
    pos = last_pos
    while pos > 0:
        first = key(l[pos - 1])
        second = key(l[pos])
        if not reverse and first < second or \
               reverse and first > second:
            break

        l[pos], l[pos - 1] = l[pos - 1], l[pos]
        pos -= 1

def gnomesort(l, key=lambda x: x, reverse=False):
    result = l[:]

    for i in range(len(result)):
        __gnome(result, i, key, reverse)

    return result
