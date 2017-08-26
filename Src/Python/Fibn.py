def fib(n):
    a,b = 0,1
    for i in range(n):
        a,b = b, a+b
    return a

def Main():
    fibon = input('Index Number of Fibonacci Sequence ')
    num = int(fibon)
    result = fib(num)
    print("The %dth fib number is %d" % (num, result))

if __name__ == '__main__':
        Main()
