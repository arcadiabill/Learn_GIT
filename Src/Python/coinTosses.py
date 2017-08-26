# Flip a coin 1,000 times
# Heads == 1 & Tails == 0
import random
print('I will flip a coin 1,000 times. Guess the number of heads.')
print('Press enter to begin')
input()
flips = 0
heads = 0
while flips < 1000:
    if random.randint(0,1) == 1:
        heads += 1
    flips += 1

    if flips == 900:
        print('900 flips with ' + str(heads) + ' heads.')
    if flips == 100:
        print('100 flips with ' + str(heads) + ' heads.')
    if flips == 500:
        print('500 flips with ' + str(heads) + ' heads.')
print()
print('1,000 tosses produced ' + str(heads))
