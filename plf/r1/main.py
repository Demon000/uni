#!/usr/bin/env python3

from List import List, Node

first_list = List()
first_list.add_first_value(1)
first_list.add_first_value(4)
first_list.add_first_value(6)
first_list.add_first_value(2)
first_list.add_first_value(4)
first_list.add_first_value(3)
first_list.add_first_value(7)
first_list.print()

print()

clean_list = List.remove_value(first_list, 4)
clean_list.print()

first_set = List()
first_set.add_first_value(1)
first_set.add_first_value(2)
first_set.add_first_value(3)
first_set.add_first_value(4)
first_set.add_first_value(5)
first_set.add_first_value(6)
first_set.print()

print()

second_set = List()
second_set.add_first_value(2)
second_set.add_first_value(3)
second_set.print()

print()

is_second_set_in_first_set = List.is_list_included(first_set, second_set)
print(is_second_set_in_first_set)
