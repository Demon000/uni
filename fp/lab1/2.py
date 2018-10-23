n = int(input('n = '))
prim = 1
if n < 2:
    prim = 0
else:
    for k in range(2, n):
        if n % k is 0:
            prim = 0
            break

print(prim)
