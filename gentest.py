import sys
from random import randint


f = open('input.txt', 'w')
n = int(sys.argv[1])
max_value = n
print(n, file=f)
for i in range(n):
	print(randint(-max_value, max_value), end=" ", file=f)

q = int(sys.argv[2])
print("\n"+str(q), file=f)
for i in range(q):
	t = randint(1, 7)
	l = randint(0, n-1)
	r = randint(l, n-1)
	x = randint(-max_value, max_value)
	if t == 1 or t == 6 or t == 7:
		print(t, l, r, file=f)
	if t == 4 or t == 5:
		print(t, x, l, r, file=f)
	if t == 2:
		print(t, x, l, file=f)
		n+=1
	if t == 3:
		print(t, l, file=f)
		n-=1

f.close()
