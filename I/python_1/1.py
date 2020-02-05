def swap(j, k):
    ii = c[j]
    c[j] = c[k]
    c[k] = ii
n = int(input("Enter n: "))
m = int(input("Enter m: "))
t = n - m
b = []
for i in range(m):
    b.append(i)
a = []
for i in range(n):
    a.append(0)
flag_1 = 1
flag_2 = 1
flag_3 = 1
while flag_1 == 1:
    for i in range(m):
        a[b[i]] = b[i] + 1
    c1 = []
    c = []
    for i in range(n):
        if a[i] == 0:
            c.append(i)
            c1.append(i)
    flag_2 = 1
    while flag_2 == 1:
        flag_3 = 1
        while flag_3 == 1:
            y = t - 2
            u = t - 1
            while y != -1 and c[y] >= c[y + 1]:
                y -= 1
            if y == -1:
                flag_2 = 0
                break
            while c[y] >= c[u]:
                u -= 1
            swap(y, u)
            y += 1
            u = t - 1
            while y < u:
                swap(y, u)
                y += 1
                u -= 1
            flag_3 = 0
            for i in range(t):
                if c[i] == c1[i]:
                    flag_3 = 1
                    break
        if flag_2 == 1:
            for i in range(t):
                a[c1[i]] = c[i] + 1
            print (a)
    for i in range(n):
        a[i] = 0
    ii = m - 1
    b[-1] += 1
    while b[-1] > n - 1:
        ii -= 1
        if ii < 0:
            flag_1 = 0
            break
        b[ii] += 1
        i = ii + 1
        while i < m:
            b[i] = b[i - 1] + 1
            i += 1
    del c
    del c1
print ("The end")