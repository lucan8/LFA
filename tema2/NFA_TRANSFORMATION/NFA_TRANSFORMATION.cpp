#include "NFA_TRANSFORMATION.h"

Automaton NFA_TRANSFORMATION(const Automaton& NFA){
    Automaton DFA;

    DFA.setAlphabet(NFA.getAlphabet());
    DFA.addState(NFA.getStartState()->getName());
    DFA.setStartState(NFA.getStartState()->getName());

    queue<string> unvisited_states;
    unvisited_states.push(DFA.getStartState()->getName());

    while (!unvisited_states.empty()){
        string curr_state = unvisited_states.front();

        for (const auto& letter : NFA.getAlphabet()){
            //Concatenating all neighbours to create new state(throws error)
            string new_state = createState(curr_state, letter, NFA);
            
            if (!new_state.empty()){
                //Checking if the state already exists
                if (DFA.addState(new_state)){
                    unvisited_states.push(new_state);

                    if (verifFinalState(new_state, NFA))
                        DFA.addFinalState(new_state);
                }
                DFA.addTransition(letter, curr_state, new_state);
            }
        }
        unvisited_states.pop();
    }

    return DFA;
}

bool verifFinalState(const string& states, const Automaton& NFA){
    for (const auto& state : split(states)){
        try{
            if (NFA.searchState(state)->isFinalState())
                return true;
        } catch(string& e){
            cerr << "Error at verifFinalState: " << e << '\n';
            return false;
        }
    }
    return false;
}
string createState(const string& states, char letter, const Automaton& NFA){
    set<shared_ptr<State>, StateComparator> new_states;
    
    for (const auto& state : split(states)){
        try{
            unordered_set<shared_ptr<State>> neighbours = NFA.getNeighbours(state, letter);
            for (const auto& neighbour : neighbours)
                new_states.insert(neighbour);

        } catch(string& e){
            cerr << "Error at createState: " << e << '\n';
        }
    }

    return join(new_states);
}
