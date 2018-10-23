class GenericSequence():
    def compare(self, other):
        return len(self.values) - len(other.values)

    def add(self, value):
        self.values.append(value)

    def __init__(self, start, value, last_sequence=None):
        self.values = [value]
        self.start = start

class StrictlyLarger(GenericSequence):
    def accepts(self, value):
        if value > self.values[-1]:
            return True

        return False

class ConsecutivePrimes(GenericSequence):
    def accepts(self, value):
        def gcd(a, b):
            while a != b:
                if a > b:
                    a -= b
                else:
                    b -= a
    
            return a

        if gcd(value, self.values[-1]) is 1:
            return True

        return False

class AllEqual(GenericSequence):
    def accepts(self, value):
        if value is self.values[-1]:
            return True

        return False

class AllDistinct(GenericSequence):
    def accepts(self, value):
        try:
            index = self.values.index(value)
        except ValueError:
            return True

        return False

    def __init__(self, start, value, last_sequence=None):
        super().__init__(start, value, last_sequence)

        if last_sequence:
            index = last_sequence.values.index(value)
            carry_values = last_sequence.values[index + 1:]
            self.values = carry_values + self.values

class SameDigits(GenericSequence):
    @staticmethod
    def extract_digits(value):
        string = str(value)
        if string[0] is '-':
            string = string[1:]
        chars = list(string)
        digits = set(chars)
        return digits

    def accepts(self, value):
        digits = SameDigits.extract_digits(value)

        if digits == self.digits:
            return True

        return False

    def __init__(self, start, value, last_sequence=None):
        super().__init__(start, value, last_sequence)
        self.digits = SameDigits.extract_digits(value)

class DifferentSign(GenericSequence):
    def accepts(self, value):
        last_value = self.values[-1]
        if (last_value < 0 and value >= 0) or \
                (last_value >= 0 and value < 0):
            return True

        return False

def find_longest_sequences(numbers, SequenceType):
    sequences = []
    current_sequence = None
    last_sequence = None

    for index, number in enumerate(numbers):
        if not current_sequence:
            current_sequence = SequenceType(index, number, last_sequence)
            continue

        if current_sequence.accepts(number):
            current_sequence.add(number)
        else:
            sequences.append(current_sequence)
            last_sequence = current_sequence
            current_sequence = SequenceType(index, number, last_sequence)

    sequences.append(current_sequence)

    longest_sequences = []
    for sequence in sequences:
        if len(longest_sequences) is 0:
            comparison = 1
        else:
            longest_sequence = longest_sequences[0]
            comparison = sequence.compare(longest_sequence)

        if comparison is 0:
            longest_sequences.append(sequence)
        elif comparison > 0:
            longest_sequences = [sequence]

    return longest_sequences

def run_tests():
    test_list_all_distinct = [2, 3, 4, 5, 6, 2, 1, 9, 10]
    longest_sequences = find_longest_sequences(test_list_all_distinct, AllDistinct)
    assert longest_sequences[0].values == [3, 4, 5, 6, 2, 1, 9, 10]

    test_list_same_digits = [3313, 3111, 31131, 33331, 345, 543, 5534, 2, 2, 2, 2, 2, 2, 2, 2]
    longest_sequences = find_longest_sequences(test_list_same_digits, SameDigits)
    assert longest_sequences[0].values == [2, 2, 2, 2, 2, 2, 2, 2]

    test_list_different_sign = [-1, 2, -1, 2, 2, -3, 1, -1, 0, -1, -2, -3, -4]
    longest_sequences = find_longest_sequences(test_list_different_sign, DifferentSign)
    assert longest_sequences[0].values == [2, -3, 1, -1, 0, -1]

def ui_print_operations():
    print('Select an operation.')
    print('1. Introduce a list of integers separated by space.')
    # 6.
    print('2. Find the longest sequences in the given list in which all the integers are distinct.')
    # 16.
    print('3. Find the longest sequences in the given list in which all the integers use the same digits.')
    print('4. Find the longest sequences in the given list in which all consecutive integers have a different sign.')
    print('x. Exit.')
    print()

def ui_read_operation():
    while True:
        try:
            raw_operation = input('Your operation: ')
            if raw_operation is 'x':
                return raw_operation

            operation = int(raw_operation)
            if operation < 1 or operation > 4:
                raise ValueError()

            return operation
        except ValueError:
            print('Your operation is invalid.')
            print()

def ui_read_list():
    while True:
        values = []
        user_input = input('Your list: ')
        all_valid = True

        strings = user_input.split(' ')
        for string in strings:
            try:
                value = int(string)
            except ValueError:
                all_valid = False
                print('Your list contains invalid characters.')
                print()
                break

            values.append(value)

        if all_valid:
            return values

def ui_start():
    current_list = None
    ui_print_operations()
    
    while True:
        operation = ui_read_operation()
        if operation is 'x':
            print('Goodbye.')
            break
    
        if operation is 1:
            current_list = ui_read_list()
            
            continue
    
        if 2 <= operation <= 4 and not current_list:
            print('Your haven\'t introduced a list.')
            print()
            continue
    
        if operation == 2:
            SequenceType = AllDistinct
        elif operation == 3:
            SequenceType = SameDigits
        elif operation == 4:
            SequenceType = DifferentSign

        longest_sequences = find_longest_sequences(current_list, SequenceType)
    
        print('Your longest sequences are:')
        for sequence in longest_sequences:
            printed_sequence = ', '.join(str(value) for value in sequence.values)
            print(printed_sequence)

        print()

run_tests()
ui_start()
