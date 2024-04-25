#include "Transition.h"

const shared_ptr<State> Transition :: getState2(char letter, const string& state1) const{
    if (letter == this->letter)
        if (state1 == this->State1->getName())
            return this->State2;
    return {};
}

ostream& operator <<(ostream& out, const Transition& tran){
    out << tran.State1->getName() <<
    ' ' << tran.letter <<
    ' ' << tran.State2->getName();
    return out;
}


