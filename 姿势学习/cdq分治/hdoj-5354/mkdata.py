import sys
from random import randint
if __name__=='__main__':
	T = 2
	with open("1.in","w") as output:
		print>>output,T
		for _t in range(0,T):
			n = 100
			m = n
			print>>output,n,m
			e = {}
			for i in range(0,m):
				x = randint(1,n)
				y = randint(1,n)
				while (x == y):
					y = randint(1,n)
				while (e.has_key((x,y))):
					x = randint(1,n)
					y = randint(1,n)
					while (x == y):
						y = randint(1,n)
				e[(x,y)] = 1
				e[(y,x)] = 1
				print>>output,x,y
			
		