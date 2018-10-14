import pytest
from RBFS import *


eight_puzzle = EightPuzzle((1, 2, 3, 4, 5, 7, 8, 6, 0))

if __name__ == '__main__':
    sys.stdout.write("Script1")
    sys.stdout.flush()	
	
    assert recursive_best_first_search(
        EightPuzzle((2, 4, 3, 1, 5, 6, 7, 8, 0))).solution() == [
            'UP', 'LEFT', 'UP', 'LEFT', 'DOWN', 'RIGHT', 'RIGHT', 'DOWN'
        ]

    def manhattan(node):
        state = node.state
        index_goal = {0:[2,2], 1:[0,0], 2:[0,1], 3:[0,2], 4:[1,0], 5:[1,1], 6:[1,2], 7:[2,0], 8:[2,1]}
        index_state = {}
        index = [[0,0], [0,1], [0,2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]]
        x, y = 0, 0
        
        for i in range(len(state)):
            index_state[state[i]] = index[i]
        
        mhd = 0
        
        for i in range(8):
            for j in range(2):
                mhd = abs(index_goal[i][j] - index_state[i][j]) + mhd
        
        return mhd

    assert recursive_best_first_search(
        EightPuzzle((2, 4, 3, 1, 5, 6, 7, 8, 0)), h=manhattan).solution() == [
            'LEFT', 'UP', 'UP', 'LEFT', 'DOWN', 'RIGHT', 'DOWN', 'UP', 'DOWN', 'RIGHT'
        ]
