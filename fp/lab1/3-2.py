a = int(input('a = '))
b = int(input('b = '))

while b:
    c = a
    a = b
    b = c % b

print(a)
