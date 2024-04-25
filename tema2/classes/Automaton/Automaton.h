#pragma once
#include "../Transition/Transition.h"
#include <unordered_set>

class Automaton{
private:
    unordered_set<shared_ptr<State>> States, FinalStates;
    unordered_set<char> Alphabet;
    shared_ptr<State> StartState;
    unordered_set<shared_ptr<Transition>> Transitions;

    void readStates(istream&);
    void readFinalStates(istream&);
    void readAlphabet(istream&);
    void readTransitions(istream&);
    void readStartState(istream&);

    void printStates(ostream&) const;
    void printFinalStates(ostream&) const;
    void printAlphabet(ostream&) const;
    void printTransitions(ostream&) const;

public:
    void setStartState(const string&);
    void setAlphabet(const unordered_set<char>& Alphabet);

    void addFinalState(const string&);
    void addLetter(char);
    bool addState(const string&);
    
    shared_ptr<State> searchState(const string&) const;
    void addTransition(char, const string&, const string&);

    const unordered_set<shared_ptr<State>>& getStates() const;
    const shared_ptr<State>& getStartState() const;

    bool equivalent(const string& state1, const string& state2) const;

    const unordered_set<shared_ptr<State>>& getFinalStates() const;
    const unordered_set<char>& getAlphabet() const;
    unordered_set<shared_ptr<State>> getNeighbours(const string& start, char letter) const;

    friend istream& operator >>(istream&, Automaton&);
    friend ostream& operator <<(ostream&, const Automaton&);
};