# Automated theorem prover for propositinal logic
The program check wheter the propositial formula is tautology and in negative case prints all countermodels for it (i.e. all interpretation for which the formula is false).
The method of analytic tableaux is used for that and program will generate complete tableaux for a given formula.

## Running
Everything was written in C++, so any standard compiler can do the job. In this case, we used GCC and included the *Makefile* for easier compilation with `make`.

## Input
Fist line should contain propositional formula.
It can contain all english letters (lowecase or uppercase), logical constants (`0` and `1`), logical symbols (`*`, `&`, `|`, `>`, `~` that represent logical *negation*, *conjunction*, *disjuntion*, *implication* and *equivalence* respectively), brackets and arbitary number of spaces.
Entered input is then checked for validity in a way that formula is considered valid (well-formed) if and only if:
* is a letter (english letter character, either lowercase or capital)
* is a logical constant (`0` or `1`)
* if `A` and `B` are well-formed propositinal formulae then `(*A)`, `(A & B)`, `(A | B)`, `(A > B)` and `(A ~ B)` are also well-formed formulae
* every well-formed propositinal formula can be obtained by applying finitely many of above rules.

For example, formula `(A > B) & (A ~ *C)` is well-formed, but `A & (B &)` is not.

## Output
Program will output wheter the inserted formula is tautology or not and then offer the option for printing all countermodels.
Default option won't find countermodels, but if chosen it will print all possible truth values for all occuring letters in formula for which its value is false.

The last part will generate LaTeX file *tableaux.tex* for visual representation of tableaux.

## How it works?
Method of analytic tableaux works by creating a binart tree called *tableaux* in which every node consists of propositional formula and symbol *F* or *T*.
Initial formula is places in root of tableaux with symbol *F*.
Then all other nodes are obtained by applying one of two rules, alpha and beta, both of them geretating two nodes as shown in picture bellow.

<img src="https://user-images.githubusercontent.com/44095197/127530688-09437a81-778f-4001-a4b0-577691f7efad.png" width="48" style="display: block; margin:auto">
