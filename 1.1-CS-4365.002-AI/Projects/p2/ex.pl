/*
   Turbo Prolog 2.0 Chapter 3, Example Program 4
*/
   
predicates
   male(symbol)
   female(symbol)
   parent(symbol, symbol)

clauses
   male(bill).
   male(joe).

   female(sue).
   female(tammy).

   parent(bill, joe).
   parent(sue, joe).
   parent(joe, tammy).







/*
   Turbo Prolog 2.0 Chapter 3, Example Program 2
*/
   
predicates
   can_buy(symbol, symbol)
   person(symbol)
   car(symbol)
   likes(symbol, symbol)
   for_sale(symbol)

clauses
   can_buy(X, Y) :-
	    person(X),
	    car(Y),
	    likes(X, Y),
   	 for_sale(Y).
   
   person(kelly).
   person(judy).

   car(lemon).
   car(hot_rod).

   likes(kelly, hot_rod).
   likes(judy, pizza).

   for_sale(pizza).
   for_sale(lemon).
   for_sale(hot_rod).











/*
   Turbo Prolog 2.0 Chapter 3, Example Program 5
*/

predicates
   car(symbol,real,integer,symbol,integer)
   truck(symbol,real,integer,symbol,integer)

clauses
   car(chrysler, 130000, 3, red, 12000).
   car(ford, 90000, 4, gray, 25000).
   car(datsun, 8000, 1, red, 30000).
   truck(ford, 80000, 6, blue, 8000).
   truck(datsun, 50000, 5, orange, 20000).
   truck(toyota, 25000, 2, black, 25000).


/*
   Turbo Prolog 2.0 Chapter 5, Example Program 10
   Copyright (c) 1986, 88 by Borland International, Inc
*/
   
domains
   name = symbol
   gpa  = real

predicates
   honor_student(name)
   student(name, gpa)
   probation(name)

clauses
   honor_student(Name):- 
      student(Name, GPA),
      GPA>=3.5,
      not(probation(Name)).

   student("Betty Blue", 3.5).
   student("David Smith", 2.0).
   student("John Johnson", 3.7).
   probation("Betty Blue").
   probation("David Smith").




/*
   Turbo Prolog 2.0 Chapter 7, Example Program 3
   Copyright (c) 1986, 88 by Borland International, Inc
*/
/* Recursive program to compute factorials.
   Ordinary recursion, not tail recursion. */

predicates
   factorial(integer, real)

clauses
   factorial(1, 1) :- !.

   factorial(X, FactX) :-
      Y = X-1,
      factorial(Y, FactY),
      FactX = X*FactY.




/*
   Turbo Prolog 2.0 Chapter 5, Example Program 12
   Copyright (c) 1986, 88 by Borland International, Inc
*/
   
trace
domains
   name, sex, occupation, object, vice, substance = symbol
   age=integer

predicates
   person(name, age, sex, occupation)
   had_affair(name, name)
   killed_with(name, object)
   killed(name)
   killer(name)
   motive(vice)
   smeared_in(name, substance)
   owns(name, object)
   operates_identically(object, object)
   owns_probably(name, object)
   suspect(name)

/* * * Facts about the murder * * */
clauses
   person(bert, 55, m, carpenter).
   person(allan, 25, m, football_player).
   person(allan, 25, m, butcher).
   person(john, 25, m, pickpocket).

   had_affair(barbara, john).
   had_affair(barbara, bert).
   had_affair(susan, john).

   killed_with(susan, club).
   killed(susan).

   motive(money).
   motive(jealousy).
   motive(righteousness).

   smeared_in(bert, blood).
   smeared_in(susan, blood).
   smeared_in(allan, mud).
   smeared_in(john, chocolate).
   smeared_in(barbara, chocolate).

   owns(bert, wooden_leg).
   owns(john, pistol).

/* * * Background knowledge * * */

   operates_identically(wooden_leg, club).
   operates_identically(bar, club).
   operates_identically(pair_of_scissors, knife).
   operates_identically(football_boot, club).

   owns_probably(X, football_boot) :-
      person(X, _, _, football_player).
   owns_probably(X, pair_of_scissors) :-
      person(X, _, _, hairdresser).
   owns_probably(X, Object) :-
      owns(X, Object).

/* * * * * * * * * * * * * * * * * * * * * * *
 * Suspect all those who own a weapon with   *
 * which Susan could have been killed.       *
 * * * * * * * * * * * * * * * * * * * * * * */

   suspect(X) :-
      killed_with(susan, Weapon) ,
      operates_identically(Object, Weapon) ,
      owns_probably(X, Object).

/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * Suspect men who have had an affair with Susan.  *
 * * * * * * * * * * * * * * * * * * * * * * * * * */

   suspect(X) :-
      motive(jealousy) ,
      person(X, _, m, _) ,
      had_affair(susan, X).

/* * * * * * * * * * * * * * * * * * * * *
 * Suspect females who have had an       *
 * affair with someone that Susan knew.  *
 * * * * * * * * * * * * * * * * * * * * */

   suspect(X) :-
      motive(jealousy) ,
      person(X, _, f, _) ,
      had_affair(X, Man) ,
      had_affair(susan, Man).

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Suspect pickpockets whose motive could be money.  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */

   suspect(X) :-
      motive(money) , person(X, _, _, pickpocket).

   killer(Killer) :-
      person(Killer, _, _, _) ,
      killed(Killed) ,
      Killed <> Killer , /* It is not a suicide */
      suspect(Killer) ,
      smeared_in(Killer, Goo) ,
      smeared_in(Killed, Goo).