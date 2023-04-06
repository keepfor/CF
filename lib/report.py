pline = ['uisp', 'usw', 'uacc', 'usp', 'uled']
cont = []

ids = []
idKey = 'TWFCD-'

while 1:
    try:
        t = input()
        if idKey in t:
            ids.append(t)
            break
    except Exception as e:
        print(e)
        break
    cont.append(t)

while 1:
    try:
        t = input()
    except Exception as e:
        print(e)
        break
    ids.append(t)

n = len(cont)
m = len(ids)

try:
    assert n == m, "len does not equal"
except Exception as e:
    print('cont len is {}'.format(n))
    print('ids len is {}'.format(m))
    exit()

print('len is {}'.format(n))

all = {}
cnt = 0
for i in pline:
    all[i] = []
    for ix, j in enumerate(cont):
        k = j.split(',')
        k[0] = k[0].lower()
        if i in k[0]:
            j = j.replace('[', '', 1)
            j = j.replace(']', '', 1)
            all[i].append(ids[ix] + ', ' + j.lower())
            cnt += 1


if cnt != n:
    print('WA, expect len {}, but got {}'.format(n, cnt))
else:
    print('AC, len is {}'.format(n))

for i, j in all.items():
    print(i.upper())
    for k in j:
        print(k)
    print('')
