/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Part A - Facts and Rules                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
married(profPlum,msGreen).
affair(mrBoddy,msGreen).
affair(missScarlet,mrBoddy).
spouse(X,Y):-married(X,Y).
spouse(Y,X):-married(X,Y).
hatred(X,Y):-spouse(X,Z),affair(Y,Z).
rich(mrBoddy).
greedy(colMustard).
greed(X,Y):-not(rich(X)),rich(Y).

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Part B - Suspect Predicate                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
 suspect(X,Y):-
				hatred(X,Y);
				greed(X,Y).
/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Part C - Single Fact                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*not(rich(colMustard)). */