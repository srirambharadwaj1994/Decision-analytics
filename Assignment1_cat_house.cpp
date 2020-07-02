#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/minimodel.hh>

using namespace Gecode;
using namespace std;

class Houses : public Space {

protected:
    // Array initialisation for Nationality
    IntVarArray n;

    // Array initialisation for Color of house
    IntVarArray c;

    // Array initialisation for Pets
    IntVarArray p;

    // Array initialisation for Drinks
    IntVarArray d;

    // Array initialisation for Cigarette
    IntVarArray cig;

public:
    Houses(void) : n(*this, 5, 0, 4), c(*this, 5, 0, 4), p(*this, 5, 0, 4), d(*this, 5, 0, 4),
    cig(*this, 5, 0, 4)
    {
        //Initialising value_index to values in the integer arrays
        IntVar English(n[0]), Spaniard(n[1]), Ukranian(n[2]), Norway(n[3]), Japan(n[4]);
        IntVar Red(c[0]), Green(c[1]), Ivory(c[2]), Blue(c[3]), Yellow(c[4]);
        IntVar Dog(p[0]), Snail(p[1]), Fox(p[2]), Horse(p[3]), Cat(p[4]);
        IntVar Coffee(d[0]), Tea(d[1]), Milk(d[2]), Orangejuice(d[3]), unk(d[4]);
        IntVar OldGold(cig[0]), Kools(cig[1]), Chesterfields(cig[2]), Parliaments(cig[3]), Lucystrike(cig[4]);

        // Constraint that each of nationalities, house color, pets, drinks and cigarettes
        // should take distinct values
        distinct(*this, n);
        distinct(*this, c);
        distinct(*this, p);
        distinct(*this, d);
        distinct(*this, cig);

        //constraints specified in the problem

        ////The Englishman lives in the red house
        rel(*this, English == Red);

        ////The Spaniard owns the dog
        rel(*this, Spaniard == Dog);

        ////Coffee is drunk in the green house
        rel(*this, Coffee == Green);

        ////The Ukrainian drinks tea
        rel(*this, Ukranian == Tea);

        //// The green house is immediately to the right of the ivory house
        rel(*this, Green == (Ivory + 1));

        ////The Old Gold smoker owns snails
        rel(*this, OldGold == Snail);

        ////Kools are smoked in the yellow house
        rel(*this, Kools == Yellow);

        ////Milk is drunk in the middle house
        rel(*this, Milk == 2);

        ////The Norwegian lives in the first house on the left
        rel(*this, Norway == 0);

        ////The man who smokes Chesterfields lives in the house next to the man with the fox
        rel(*this, abs(Chesterfields - Fox) == 1);

        ////Kools are smoked in the house next to the house where the horse is kept
        rel(*this, abs(Kools - Horse) == 1);

        ////The Lucky Strike smoker drinks orange juice
        rel(*this, Lucystrike == Orangejuice);

        ////The Japanese smoke Parliaments
        rel(*this, Japan == Parliaments);

        ////The Norwegian lives next to the blue house.
        rel(*this, abs(Norway - Blue) == 1);

        //NEW CONSTRAINT
        //the house where you smoke chesterfields is 1 position to the right of Lucystrike
        rel(*this, Chesterfields == (Lucystrike + 1));

        //Branching the propagation
        branch(*this, n, INT_VAR_MIN_MIN(), INT_VAL_MIN());
        branch(*this, c, INT_VAR_MIN_MIN(), INT_VAL_MIN());
        branch(*this, p, INT_VAR_MIN_MIN(), INT_VAL_MIN());
        branch(*this, d, INT_VAR_MIN_MIN(), INT_VAL_MIN());
        branch(*this, cig, INT_VAR_MIN_MIN(), INT_VAL_MIN());
    }

    // search support for all five variable arrays
    Houses (bool share, Houses& s) : Space(share, s)
    {
        n.update(*this, share, s.n);
        c.update(*this, share, s.c);
        p.update(*this, share, s.p);
        d.update(*this, share, s.d);
        cig.update(*this, share, s.cig);
    }
    virtual Space* copy(bool share) {
        return new Houses (share, *this);
    }

    // print solution
    void print(void) {

        cout << "Nationality   : "<<n << endl;
        cout << "Color of House: "<< c << endl;
        cout << "Pet           : "<<p << endl;
        cout << "Drink         : "<< d << endl;
        cout << "Cigarette     : "<< cig ;
        cout << " " << endl;

        string Nationalities[5] = {"English", "Spaniard", "Ukranian", "Norwegian", "Japanese"};

        //cat is the variable. It is assigned as the 4th value in the array of pets
        int cat_index = p[4].val();
        int N_index;
        cout << "Index Value for Cat: "<< cat_index << endl; ;

        for(int i = 0; i < 5; i++)
        {
            if(cat_index == n[i].val())
                N_index = i;
        }

        cout << Nationalities[N_index] << " owns the cat";
    }
};

// main function
int main(int argc, char *argv[]) {

    // create model and search engine
    Houses* h = new Houses();
    DFS<Houses> e(h);
    delete h;

    // search and print all solutions
    if (Houses* s = e.next()) {
        s->print();
        delete s;
    }
    return 0;

}
