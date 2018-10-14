import pytest
from RBFS import *


eight_puzzle = EightPuzzle((1, 2, 3, 4, 5, 7, 8, 6, 0))

# Alex Lundin
# Edit input.txt to whatever filename you would like to read
def fileReader():
   stringAccumulator = ""
   with open('./input.txt') as f:
      for l in f:
          # replace \n with \t so the stringAccumulator is consistent
          l = l.replace('\n','\t')
          stringAccumulator = stringAccumulator + l

   # split the string on \t and strip the extra spaces then put it into a char array
   stringAccumulator = stringAccumulator.strip().split("\t")

   # convert each item at index i from char to int
   for i in range(len(stringAccumulator)):
    stringAccumulator[i] = int(stringAccumulator[i])
   # return the converted stringAccumulator
   return stringAccumulator  
   
   
if __name__ == '__main__':
    sys.stdout.write("Script1\n")
    sys.stdout.flush()
    boardValues = fileReader()	
    recursive_best_first_search(EightPuzzle((boardValues)))
	