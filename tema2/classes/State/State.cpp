#include "State.h"

const string& State :: getName() const {return name;}
uint16_t State :: getEqClass() const {return eq_class;}
bool State :: isFinalState() const {return final_state;}

bool State :: equivalent(const shared_ptr<State>& state) const{return this->eq_class == state->eq_class;};

void State :: setFinalState() {this->final_state = true;}
void State :: setEqClass(uint16_t eq_class) {this->eq_class = eq_class;}

ostream& operator <<(ostream& out, const State& state){
    out << state.name;
    return out;
}

istream& operator >>(istream& in, State& state){
    in >> state.name;
    return in;
}