class Node:
    def __init__(self, value):
        self.__value = value
        self.__next = None

    def get_next_node(self):
        return self.__next

    def set_next_node(self, next_node):
        self.__next = next_node

    def get_value(self):
        return self.__value

    def print(self, recurse=False):
        if recurse and self.get_next_node():
            self.get_next_node().print(recurse)

class List:
    def __init__(self):
        self.__head = None

    def get_head_node(self):
        return self.__head

    def set_head_node(self, head_node):
        self.__head = head_node

    def get_first_value(self):
        try:
            head_node = self.get_head_node()
            first_value = head_node.get_value()
        except:
            first_value = None

        return first_value

    def add_first_value(self, value):
        head_node = self.get_head_node()
        node = Node(value)
        node.set_next_node(head_node)
        self.set_head_node(node)

    def get_sublist(self):
        try:
            head_node = self.get_head_node()
            second_node = head_node.get_next_node()
        except:
            second_node = None

        sublist = List()
        sublist.set_head_node(second_node)
        return sublist

    def is_empty(self):
        head_node = self.get_head_node()
        return head_node == None

    def print(self):
        self.get_head_node().print(True)

    @staticmethod
    def add_value(l, value):
        l.add_first_value(value)
        return l

    @staticmethod
    def remove_value(l, value):
        if l.is_empty():
            return l

        first_value = l.get_first_value()
        sublist = l.get_sublist()

        if first_value == value:
            return List.remove_value(sublist, value)
        else:
            return List.add_value(List.remove_value(sublist, value), first_value)

    @staticmethod
    def _is_list_included(target_list, current_target_list, current_source_list):
        if current_source_list.is_empty():
            return True

        if current_target_list.is_empty():
            return False

        first_value_in_target = current_target_list.get_first_value()
        first_value_in_source = current_source_list.get_first_value()

        if first_value_in_source == first_value_in_target:
            return List._is_list_included(target_list, target_list, current_source_list.get_sublist())
        else:
            return List._is_list_included(target_list, current_target_list.get_sublist(), current_source_list)

    @staticmethod
    def is_list_included(target_list, source_list):
        return List._is_list_included(target_list, target_list, source_list)
