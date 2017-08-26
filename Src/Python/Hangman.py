# Hangman Game
import random
HANGMANPICS = ['''

  +---+
  |   |
      |
      |
      |
      |
=========''', '''

  +---+
  |   |
  O   |
      |
      |
      |
=========''', '''

  +---+
  |   |
  O   |
  |   |
      |
      |
=========''', '''

  +---+
  |   |
  O   |
 /|   |
      |
      |
=========''', '''

  +---+
  |   |
  O   |
 /|\  |
      |
      |
=========''', '''

  +---+
  |   |
  O   |
 /|\  |
 /    |
      |
=========''', '''

  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========''']

words = 'ant baboon badger bat bear beaver camel cat clam cobra cougar \
coyote crow deer dog donkey duck eagle ferret fox frog goad goose hawk lion \
lizard llama mole monkey moose mouse mule newt otter owl panda parrot pigeon \
python rabbit ram rat raven rhino salmon seal shark sheep skunk sloth snake \
spider stork swan tiger toad trout turkey turtle weasel whale wolf wombat \
zebra'.split()

def getRandomWord(wordList):
    # Return a random list from the passed list of strings
    wordIndex = random.randint(0, len(wordList) - 1)
    return wordList[wordIndex]

def displayBoard(HANGMANPICS, missedLetters, correctLetters, secretWord):
    print(HANGMANPICS[len(missedLetters)])
    print()

    print('Missed letters:', end=' ')
    for letter in missedLetters:
        print(letter, end=' ')
    print()

    blanks = '_' * len(secretWord)
    for i in range(len(secretWord)): # replace blanks with correctly guessed letters
        if secretWord[i] in correctLetters:
            blanks = blanks[:i] + secretWord[i] + blanks[i+1:]

    for letter in blanks: # show secret word with spaces between each letter
        print(letter, end=' ')
    print()

def getGuess(alreadyGuessed):
    #Return letter entered making sure it's a single letter and not already entered
    while True:
        print('Guess a letter.', end = ' ')
        guess = input()
        guess = guess.lower()
        if len(guess) != 1:
            print('Please enter a single letter.')
        elif guess in alreadyGuessed:
            print('You have already guessed that letter. Choose again.')
        elif guess not in 'abcdefghijklmnopqrstuvwxyz':
            print('Please enter a letter')
        else:
            return guess

def playAgain():
    # Return True if player wants to play again
    print('Do you want to play again? (yes or no)')
    return input().lower().startswith('y')

print('H A N G M A N')
missedLetters = ''
correctLetters = ''
secretWord = getRandomWord(words)
gameIsDone = False

while True:
    displayBoard(HANGMANPICS, missedLetters, correctLetters, secretWord)

    # Let play type in a letter
    guess = getGuess(missedLetters + correctLetters)

    if guess in secretWord:
        correctLetters = correctLetters + guess

        # Check if player has won
        foundAllLetters = True
        for i in range(len(secretWord)):
            if secretWord[i] not in correctLetters:
               foundAllLetters = False
               break
        if foundAllLetters:
            print('Yes! The secret word is "' + secretWord + '"! You have won')
            gameIsDone = True
    else:
        missedLetters = missedLetters + guess

        # Check if player has guessed too many times and lost
        if len(missedLetters) == len(HANGMANPICS) - 1:
            displayBoard(HANGMANPICS, missedLetters, correctLetters, secretWord)
            print('You have run out of guesses~\nAfter ' + str(len(missedLetters)) + ' missed guesses and ' + str(len(correctLetters)) + 'correct guesses, the word was "' + secretWord + '"')
            gameIsDone = True
    # Ask is they want to play again
    if gameIsDone:
        if playAgain():
            missedLetters = ''
            correctLetters = ''
            gameIsDone = False
            secretWord = getRandomWord(words)
        else:
            break
               
