def get_smallest_number_using_digits_of(number):
    '''
    Get the smallest natural number able to be built using the
    digits of the given natural number.
    '''

    # 10 digits, 0 to 9
    digits_count = [0] * 10

    # Keep track of the smallest digit to put it at the start
    # of the smallest number
    # Default value is 10 to make sure any digit will actually be smaller
    smallest_digit = 10
    
    while number:
        digit = number % 10
        digits_count[digit] += 1
    
        # 0 cannot be the first digit of a number
        if digit is not 0 and digit < smallest_digit:
            smallest_digit = digit
    
        number = number // 10

    # Do not use the smallest digit twice
    digits_count[smallest_digit] -= 1
    
    # Start the smallest number with the smallest digit
    smallest_number = smallest_digit
    
    for digit, digit_count in enumerate(digits_count):
        while digit_count:
            # Shift the number left and add the new digit
            smallest_number *= 10
            smallest_number += digit

            digit_count -= 1

    return smallest_number

def is_prime(number):
    # Any number smaller than 2 is not prime
    if number < 2:
        return False
    # 2 is prime
    elif number is 2:
        return True
    # Any multiple of 2 is not prime
    elif number % 2 is 0:
        return False

    d = 3
    while d * d <= number:
        if number % number is 0:
            return False

        d += 2

    return True

def get_prime_smaller_than(number):
    '''
    Get the smallest prime number smaller than the given number.
    '''
    number -= 1

    if number < 2:
        raise ValueError()

    while number > 1:
        if is_prime(number):
            break
    
        number = number - 1

    return number

while True:
    print()
    print('Select an operation.')
    print('1. ' + get_smallest_number_using_digits_of.__doc__)
    print('2. ' + get_prime_smaller_than.__doc__)
    print('3. Exit.')
    print()

    operation = int(input('Your operation: '))

    if operation is 3:
        print('Goodbye.')
        break

    number = int(input('Your number: '))
    try:
        if operation is 1:
            result = get_smallest_number_using_digits_of(number)
        elif operation is 2:
            result = get_prime_smaller_than(number)
    except ValueError:
        print('Your number is invalid.')
        continue

    print('The result is {}'.format(result))
