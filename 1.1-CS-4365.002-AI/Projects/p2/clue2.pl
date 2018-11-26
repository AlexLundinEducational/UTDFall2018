/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Part A - Facts and Rules                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
rich(mrBoddy).
affair_with(msGreen, mrBoddy).
affair_with(missScarlet, mrBoddy).
married_to(profPlum, msGreen).
greedy(colMustard).


affair(X, Y) :- affair_with(X, Y).
affair(X, Y) :- affair_with(Y, X), !.

married(X, Y) :- married_to(X, Y).
married(X, Y) :- married_to(Y, X), !.

greed(X, Victim) :-
    greedy(X),
    not(rich(X)),
    rich(Victim).

hate(X, Victim) :- 
    married(X, Someone),
    affair(Someone, Victim).

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Part B - Suspect Predicate                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
murder(X, Victim) :-
    hate(X, Victim);
    greed(X, Victim).

suspect_found(X) :-
    X = missScarlet;
    X = msGreen;
    X = colMustard;
	X = profPlum.

suspect(Killer, mrBoddy) :-
    murder(Killer, mrBoddy),
    suspect_found(Killer).
	
/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Part C - Extra Rule    rich(colMustard).                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
