% Q9: Clue
% Facts go here

married(profPlum, msGreen).
rich(mrBoddy).
greedy(colMustard).
affair(mrBoddy,msGreen).
affair(missScarlett, mrBoddy).

spouse(X,Y):- married(X,Y).
spouse(X,Y):- married(Y,X).

%fact that will give unique suspect is

% Predicate rules go here
affair(X3,Y3):- affair(Y3,X3),!.
hate(X1,Y1) :- spouse(X1,Spouse), spouse(Y1,Spouse).
greed(X,YY) :- greedy(X), not(rich(X)), rich(YY).
suspect(Killer,Y):- greed(Killer,Y);hate(Killer,Y),!.