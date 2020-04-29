def check_same_size(first, second, bi_dimensional=True):
    assert len(first) == len(second)
    assert len(first) != 0

    if not bi_dimensional:
        return

    first_element = first[0]
    if not isinstance(first_element, list):
        return

    l = len(first[0])
    for i in range(len(first)):
        assert len(first[i]) == l
        assert len(second[i]) == l
