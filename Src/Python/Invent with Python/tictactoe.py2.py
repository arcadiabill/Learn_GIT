# Tic Tac Toe
from random import randint

def drawBoard(board):
    # Print the passed board
    print('   |   |')
    print(' ' + board[7] + ' | ' + board[8] + ' | ' + board[9])
    print('   |   |')
    print('-----------')
    print('   |   |')
    print(' ' + board[4] + ' | ' + board[5] + ' | ' + board[6])
    print('   |   |')
    print('-----------')
    print('   |   |')
    print(' ' + board[1] + ' | ' + board[2] + ' | ' + board[3])
    print('   |   |')

def getPlayerLetter():
    letter = ''
    while not (letter == 'X' or letter == 'O'):
        letter = input('Do you want to be X or O?').upper()

    if letter == 'X':
        return ['X', 'O']
    else:
        return ['O', 'X']

def whoGoesFirst():
    if randint(0,1) == 0:
        return 'computer'
    else:
        return 'player'

def playAgain():
    play = ' '
    while play not in 'YN':
        play = input('Do you want to play again (y/n): ').upper()
    return play

def makeMove(board, letter, move):
    board[move] = letter

def isWinner(bo, le):
    won = False
    won = ( (bo[7] == le and bo[8] == le and bo[9] == le) or
            (bo[4] == le and bo[5] == le and bo[6] == le) or
            (bo[1] == le and bo[2] == le and bo[3] == le) or
            (bo[1] == le and bo[4] == le and bo[7] == le) or
            (bo[2] == le and bo[5] == le and bo[8] == le) or
            (bo[3] == le and bo[6] == le and bo[9] == le) or
            (bo[1] == le and bo[5] == le and bo[9] == le) or
            (bo[3] == le and bo[5] == le and bo[7] == le) )
    return won

def canWin(board, le):
    newBoard = duplBoard(board)
    legal = legalMoves(newBoard)
    n = len(legal)
    
    for i in range(0, n):
        newBoard[i] = le
        if isWinner(newBoard, le):
            return legal[i]
        newBoard[i] = ' '
    return 0

def canLoose(board, le):
    newBoard = duplBoard(board)
    legal = legalMoves(newBoard)
    n = len(legal)

    for i in range(0, n):
        pos = legal[i]
        newBoard[pos] = le
        if isWinner(newBoard, le):
            return legal[i]
        newBoard[pos] = ' '
    return 0

def initBoard():
    return [' '] * 10

def duplBoard(board):
    newBoard = [' '] * 10
    
    for i in range(1,10):
        newBoard[i] = board[i]

    return newBoard

def legalMoves(board):
    legal = []
    for i in range(1,10):
        if board[i] == ' ':
            legal.append(i)
    return legal

def playerMove(board, le):
    drawBoard(board)
    move = 0
    legal = legalMoves(board)
    while move not in legal:
        move = int(input('Your move: '))

    makeMove(board, le, move)

def test(board, playerLetter, computerLetter):
    board[5] = playerLetter
    board[3] = playerLetter
    board[1] = computerLetter

def computerMove(board, le):
    pos = canWin(board, le)
    if pos == 0:
        legal = legalMoves(board)
        n = len(legal)
        pos = legal[randint(0, n-1)]

    makeMove(board, le, pos)

def genMove(board, me, op):
    pos = canLoose(board, op)
    if pos > 0:
        return pos
    pos = canWin(board, me)
    if pos > 0:
        return pos
    if board[5] == ' ':
        return 5
    if board[1] == ' ':
        return 1
    if board[3] == ' ':
        return 3
    if board[7] == ' ':
        return 7
    if board[9] == ' ':
        return 9
    v = legalMoves(board)
    return v[0]
    
        
board = initBoard()
drawBoard(board)
playerLetter, computerLetter = getPlayerLetter()
firstPlayer = whoGoesFirst()
