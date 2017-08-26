import random

guessesTaken = 0

print("Hello, What is your name?")
myName = input()

number = random.randint(1,100)
print('Hello ' + myName + ', I am thinking of a number between 1 & 20.')

while guessesTaken < 6:
    print('Take a guess.')
    guess = input()
    guess = int(guess)

    guessesTaken = guessesTaken + 1

    if guess < number:
        print('Too low')

    if guess > number:
        print('Too high')

    if guess == number:
        print('Good guess')
        break

    if guessesTaken == 6:
        print('I was thinking of the number ' + str(number))
    
