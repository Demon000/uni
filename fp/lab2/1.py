def palindrom(s):
    r = ''
    for k in reversed(s):
        r = r + k
    return r

s = input('s = ')
print(palindrom(s))
