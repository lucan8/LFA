#include "Automaton.h"

bool Automaton :: addState(const string& state_name){
    try{
        this->searchState(state_name);
        return false;
    } catch(string& e){
        this->States.insert(make_shared<State>(state_name)).second;
        return true;
    }
}


void Automaton :: addFinalState(const string& state_name){
    try{
        shared_ptr<State> state = this->searchState(state_name);
        state->setFinalState();
        state->setEqClass(state_type_eq :: final);
        
        this->FinalStates.insert(state);
    } catch(string& e){
        cerr << "Error at addFinalState: " << e << '\n';
    }
}


void Automaton :: addLetter(char letter){
    Alphabet.insert(letter);
}


void Automaton :: addTransition(char letter, const string& st_name1, const string& st_name2){
    try{
        this->Transitions.insert(make_shared<Transition>(
            letter, 
            this->searchState(st_name1), 
            this->searchState(st_name2)
            )
        );
    } catch(string& e){
        cerr <<"Error at addTransition: " << e << '\n';
    }
}

//Equivalent will be used only on DFAs so there will be only one neighbour
bool Automaton :: equivalent(const string& state1, const string& state2) const{
    for (const auto& letter : this->Alphabet){
        try{
            shared_ptr<State> neighbour1 = *(this->getNeighbours(state1, letter).begin());
            shared_ptr<State> neighbour2 = *(this->getNeighbours(state2, letter).begin());
            if (!neighbour1->equivalent(neighbour2))
                return false;
        } catch(string& e){
            cerr << "Error at equivalent: " << e << '\n';
            return false;
        }
    }
    return true;
}


const unordered_set<char>& Automaton :: getAlphabet() const{
    return Alphabet;
}


const unordered_set<shared_ptr<State>>& Automaton :: getFinalStates() const{
    return FinalStates;
}


unordered_set<shared_ptr<State>> Automaton :: getNeighbours(const string& start, char letter) const{
    unordered_set<shared_ptr<State>> neighbours;

    for (const auto& tran : this->Transitions){
        shared_ptr<State> neighbour = tran->getState2(letter, start);
        if (neighbour)
            neighbours.insert(neighbour);
    }

    if (neighbours.empty())
        throw "No transition from " + start + " with letter " + letter;
    else
        return neighbours;
}


const unordered_set<shared_ptr<State>>& Automaton :: getStates() const{
    return States;
}


const shared_ptr<State>& Automaton :: getStartState() const{
    return StartState;
}

  
void Automaton :: readStates(istream& in){
    string state;
    int nr_states;

    in >> nr_states;
    for (int i = 0; i < nr_states; i++){
        in >> state;
        this->addState(state);
    }
}

void Automaton :: readStartState(istream& in){
    string state;
    in >> state;

    this->setStartState(state);
}


void Automaton :: readAlphabet(istream& in){
    int nr_letters;
    char letter;

    in >> nr_letters;
    for (int i = 0; i < nr_letters; i++){
        in >> letter;
        this->addLetter(letter);
    }
}


void Automaton :: readTransitions(istream& in){
    int nr_transitions;
    char letter;
    string start_state, end_state;

    in >> nr_transitions;
    for (int i = 0; i < nr_transitions; i++){
        in >> start_state >> letter >> end_state;
        this->addTransition(letter, start_state, end_state);
    }
}


void Automaton :: readFinalStates(istream& in){
    int nr_final_states;
    string state_name;

    in >> nr_final_states;

    for (int i = 0; i < nr_final_states; i++){
        in >> state_name;
        this->addFinalState(state_name);
    }

}


void Automaton :: setAlphabet(const unordered_set<char>& Alphabet){
    this->Alphabet = Alphabet;
}


void Automaton :: setStartState(const string& state_name){
    try{
        this->StartState = this->searchState(state_name);
    } catch(string& e){
        cerr << "Error at setStartState: " << e << '\n';
    }
}


shared_ptr<State> Automaton :: searchState(const string& state_name) const{
    for (const auto& state : this->States)
        if (state->getName() == state_name)
            return state;
    throw "State: " + state_name +  " not found!";
}


void Automaton :: printStates(ostream& out) const{
    for (const auto&  state : this->States)
        out << *state << ' ';
}


void Automaton :: printFinalStates(ostream& out) const{
    for (const auto&  f_state : this->FinalStates)
        out << *f_state << ' ';
}


void Automaton :: printAlphabet(ostream& out) const{
    for (const auto& letter : this->Alphabet)
        out << letter << ' ';
}


void Automaton :: printTransitions(ostream& out) const{
    for (const auto& tran : this->Transitions)
        out << *tran << '\n';
}


istream& operator >>(istream& in, Automaton& dfa){
    dfa.readStates(in);
    dfa.readAlphabet(in);

    dfa.readTransitions(in);

    dfa.readStartState(in);
    dfa.readFinalStates(in);

    return in;
}


ostream& operator <<(ostream& out, const Automaton& dfa){
    
    out << "Automaton States: ";
    dfa.printStates(out);
    out << '\n';

    out << "Automaton Alphabet: " ;
    dfa.printAlphabet(out);
    out << '\n';

    out << "Automaton Transitions:\n";
    dfa.printTransitions(out);

    out << "Automaton Start State: " << *dfa.StartState << '\n';

    out << "Automaton Final States: ";
    dfa.printFinalStates(out);

    return out;
}


