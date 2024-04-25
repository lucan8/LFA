#include "functions.h"

void changeEquivalence(unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes){
    bool changed = false;

    for (const auto& eq_class : eq_classes)
        for (const auto& state : eq_class.second)
                state->setEqClass(eq_class.first);
}

void devideDFA(Automaton& dfa, unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes){
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


string createState(const string& states, char letter, const Automaton& NFA){
    auto cmp = [](shared_ptr<State> s1, shared_ptr<State> s2) { return  s1->getName() < s2->getName();};
    set<shared_ptr<State>, StateComparator> new_states;
    
    for (const auto& state : split(states)){
        try{
            unordered_set<shared_ptr<State>> neighbours = NFA.getNeighbours(state, letter);
            for (const auto& neighbour : neighbours)
                new_states.insert(neighbour);
        } catch(string& e){
            //cerr << "Error at createState: " << e << '\n';
        }
    }

    return join(new_states);
}

unordered_set<string> split(const string& str, char sep){
    istringstream str_stream(str);
    string split_elem;
    unordered_set<string> split_string;

    while (getline(str_stream, split_elem, sep))
        split_string.insert(split_elem);

    return split_string;
}


string join(const unordered_set<shared_ptr<State>>& elements, const string& sep){
    string res;
    for (const auto& elem : elements)
        res += elem->getName() + sep;
    
    //Getting rid of last separator
    if (!res.empty())
        res.pop_back();

    return res;
}

string join(const set<shared_ptr<State>, StateComparator>& elements, const string& sep){
    string res;
    for (const auto& elem : elements)
        res += elem->getName() + sep;
    
    //Getting rid of last separator
    if (!res.empty())
        res.pop_back();

    return res;
}


void myOpenInput(const string& file, ifstream& fin){
    fin.open(file);
    if (!fin)
        throw FileOpenException(file);
}


void myOpenOutput(const string& file, ofstream& fout){
    fout.open(file);
    if (!fout)
        throw FileOpenException(file);
}
//Only for p1
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
