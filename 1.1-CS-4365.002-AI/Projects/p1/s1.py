import pytest
from RBFS import *


eight_puzzle = EightPuzzle((1, 2, 3, 4, 5, 7, 8, 6, 0))

# Alex Lundin
# Notes to TA
# inputFileName holds the name of the file to read

def fileReader():
   # edit this variable to whatever input necessary
   inputFileName = './input.txt'
   stringAccumulator = ""
   
   # read loop
   with open(inputFileName) as f:
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
   
# Main program for script file   
if __name__ == '__main__':
    # sys.stdout.write("Script started\n")
    # sys.stdout.flush()
	# call fileReader and store return value into boardValues
    boardValues = fileReader()
	# pass input to RBFS file
    recursive_best_first_search(EightPuzzle((boardValues)))
	