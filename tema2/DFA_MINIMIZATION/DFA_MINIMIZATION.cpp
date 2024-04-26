#include "DFA_MINIMIZATION.h"

Automaton DFA_MINIMIZATION(const Automaton& dfa){
    Automaton min_dfa;

    if (dfa.getStates().size() == dfa.getFinalStates().size()){
        cout << "Already minimized!" << '\n';
        return dfa;
    }
    //Change to unordered_set
    unordered_map<uint16_t, unordered_set<shared_ptr<State>>> eq_classes;
    //First equivalence division: Final and non-final states
    devideDFA(dfa, eq_classes);

    //Kept it in var to avoid redundant copies
    int nr_eq_classes = eq_classes.size();

    while (true){
        bool any_change = false; //Checking if any of the sets was changed

        //Dividing each class into two subclasses: Equivalent to start, and not equivalent to start
        for (auto& eq_class : eq_classes){
            bool changed_class = false; //Checking if this set was changed
            
            unordered_set<shared_ptr<State>> :: iterator start = eq_class.second.begin();
            const string& pivot_state = (*start)->getName();
            unordered_set<shared_ptr<State>> :: iterator end = eq_class.second.end();

            start ++;
            while (start != end){
                if(!dfa.equivalent(pivot_state, (*start)->getName())){
                    eq_classes[nr_eq_classes].insert(*start);
                    start = eq_class.second.erase(start);
                    changed_class = true;
                    any_change = true;
                }
                else start ++;
            }
            nr_eq_classes += changed_class;
        }
        if (any_change)
            changeEquivalence(eq_classes);
        else
            break;
    }

    createMinimizedDFA(eq_classes, dfa, min_dfa);
    return min_dfa;
}

void changeEquivalence(unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes){
    bool changed = false;

    for (const auto& eq_class : eq_classes)
        for (const auto& state : eq_class.second)
                state->setEqClass(eq_class.first);
}

void devideDFA(const Automaton& dfa, unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes){
    for (const auto& state : dfa.getStates())
        eq_classes[state->getEqClass()].insert(state);
}


void createMinimizedDFA(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes,
                        const Automaton& dfa, Automaton& min_dfa){

    min_dfa.setAlphabet(dfa.getAlphabet());

    //state from dfa, state from min_dfa
    unordered_map<string, string> state_lookup;
    createMinimizedStates(eq_classes, dfa, min_dfa, state_lookup);
    createMinimizedTransitions(eq_classes, dfa, min_dfa, state_lookup);
}

void createMinimizedStates(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes,
                           const Automaton& dfa, Automaton& min_dfa, 
                           unordered_map<string, string>& state_lookup){
    for (const auto& eq_class : eq_classes){
        string new_state = join(eq_class.second);
        min_dfa.addState(new_state);

        if (dfa.getStartState()->getEqClass() == eq_class.first)
            min_dfa.setStartState(new_state);
        //Checking if any of the elem in the set is final_state, an setting it as such if that is the case
        else if ((*eq_class.second.begin())->isFinalState())
            min_dfa.addFinalState(new_state);
        
        //Every elem of set is pointing to concatenated set(min_dfa equivalent state)
        for (const auto& state : eq_class.second)
            state_lookup[state->getName()] = new_state;
    }

}


void createMinimizedTransitions(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes,
                                const Automaton& dfa, Automaton& min_dfa, 
                                const unordered_map<string, string>& state_lookup){

    for (const auto& eq_class : eq_classes){
        const string& arbitrary_set_state = (*eq_class.second.begin())->getName();

        for (const auto& letter : dfa.getAlphabet()){
            const string& neighbour = (*dfa.getNeighbours(arbitrary_set_state, letter).begin())->getName();
            min_dfa.addTransition(letter, state_lookup.at(arbitrary_set_state), state_lookup.at(neighbour));
        }
    }

}


