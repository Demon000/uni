def is_prime(n):
    if n < 2:
        return False
    elif n is 2:
        return True
    elif n % 2 is 0:
        return False

    k = 3
    while k * k <= n:
        if n % k is 0:
            return False

        k += 2

    return True

n = int(input('n = '))
n = n - 1
while n > 0:
    if is_prim(n):
        print(n)
        break

    n = n - 1
