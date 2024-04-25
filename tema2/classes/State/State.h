#pragma once

#include <iostream>
#include <cstdint>
#include <memory>
using namespace std;

enum state_type_eq {non_final = 0, final = 1};
class State{
private:
    //const static uint16_t eq_class_final = 1, eq_class_non_final = 0;
    string name;
    bool final_state;
    uint16_t eq_class;
public:
    State(const string& name, int eq_class = state_type_eq :: non_final, bool f_state = false) : 
        name(name), eq_class(eq_class), final_state(f_state){}

    const string& getName() const;
    uint16_t getEqClass() const;
    bool isFinalState() const;

    bool equivalent(const shared_ptr<State>& state) const;

    void setFinalState();
    void setEqClass(uint16_t eq_class);

    friend ostream& operator <<(ostream&, const State&);
    friend istream& operator >>(istream&, State&);
};