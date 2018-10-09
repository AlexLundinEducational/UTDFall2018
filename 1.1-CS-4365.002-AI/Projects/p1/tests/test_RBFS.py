import pytest
from RBFS import *


romania_problem = GraphProblem('Arad', 'Bucharest', romania_map)
eight_puzzle = EightPuzzle((1, 2, 3, 4, 5, 7, 8, 6, 0))
eight_puzzle2 = EightPuzzle((1, 0, 6, 8, 7, 5, 4, 2), (0, 1, 2, 3, 4, 5, 6, 7, 8))



def test_recursive_best_first_search():
    print ("Test1")
    assert recursive_best_first_search(
        romania_problem).solution() == ['Sibiu', 'Rimnicu', 'Pitesti', 'Bucharest']
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


    


# TODO: for .ipynb:
"""
>>> compare_graph_searchers()
    Searcher                      romania_map(A, B)        romania_map(O, N)         australia_map
    breadth_first_tree_search     <  21/  22/  59/B>   <1158/1159/3288/N>    <   7/   8/  22/WA>
    breadth_first_graph_search          <   7/  11/  18/B>   <  19/  20/  45/N>    <   2/   6/   8/WA>
    depth_first_graph_search      <   8/   9/  20/B>   <  16/  17/  38/N>    <   4/   5/  11/WA>
    iterative_deepening_search    <  11/  33/  31/B>   < 656/1815/1812/N>    <   3/  11/  11/WA>
    depth_limited_search          <  54/  65/ 185/B>   < 387/1012/1125/N>    <  50/  54/ 200/WA>
    recursive_best_first_search   <   5/   6/  15/B>   <5887/5888/16532/N>   <  11/12/  43/WA>

>>> ' '.join(f.words())
'LID LARES DEAL LIE DIETS LIN LINT TIL TIN RATED ERAS LATEN DEAR TIE LINE INTER
STEAL LATED LAST TAR SAL DITES RALES SAE RETS TAE RAT RAS SAT IDLE TILDES LEAST
IDEAS LITE SATED TINED LEST LIT RASE RENTS TINEA EDIT EDITS NITES ALES LATE
LETS RELIT TINES LEI LAT ELINT LATI SENT TARED DINE STAR SEAR NEST LITAS TIED
SEAT SERAL RATE DINT DEL DEN SEAL TIER TIES NET SALINE DILATE EAST TIDES LINTER
NEAR LITS ELINTS DENI RASED SERA TILE NEAT DERAT IDLEST NIDE LIEN STARED LIER
LIES SETA NITS TINE DITAS ALINE SATIN TAS ASTER LEAS TSAR LAR NITE RALE LAS
REAL NITER ATE RES RATEL IDEA RET IDEAL REI RATS STALE DENT RED IDES ALIEN SET
TEL SER TEN TEA TED SALE TALE STILE ARES SEA TILDE SEN SEL ALINES SEI LASE
DINES ILEA LINES ELD TIDE RENT DIEL STELA TAEL STALED EARL LEA TILES TILER LED
ETA TALI ALE LASED TELA LET IDLER REIN ALIT ITS NIDES DIN DIE DENTS STIED LINER
LASTED RATINE ERA IDLES DIT RENTAL DINER SENTI TINEAL DEIL TEAR LITER LINTS
TEAL DIES EAR EAT ARLES SATE STARE DITS DELI DENTAL REST DITE DENTIL DINTS DITA
DIET LENT NETS NIL NIT SETAL LATS TARE ARE SATI'

>>> boggle_hill_climbing(list('ABCDEFGHI'), verbose=False)
(['E', 'P', 'R', 'D', 'O', 'A', 'G', 'S', 'T'], 123)
"""

if __name__ == '__main__':
    sys.stdout.write("test_RBFS")
    sys.stdout.flush()	
    pytest.main()
