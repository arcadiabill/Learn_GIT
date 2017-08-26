def permute(num):
    if len(num) == 2:
        # get the permutations of the last 2 numbers by swapping them
        yield num
        num[0], num[1] = num[1], num[0]
        yield num
    else:
        for i in range(0, len(num)):
            # fix the first number and get the permutations of the rest of numbers
            for perm in permute(num[0:i] + num[i+1:len(num)]):
                yield [num[i]] + perm

for p in permute([1, 2, 3, 4]):
    print(p)
