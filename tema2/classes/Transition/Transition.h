#pragma once
#include "../State/State.h"

class Transition{
private:
    char letter;
    shared_ptr<State> State1, State2;
public:
    Transition(char letter, const shared_ptr<State> State1, const shared_ptr<State> State2) :
    letter(letter), State1(move(State1)), State2(move(State2)){}

    const shared_ptr<State> getState2(char, const string&) const; 
    friend ostream& operator <<(ostream&, const Transition&);
};