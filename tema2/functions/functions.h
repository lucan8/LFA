#pragma once
#include <iostream>
#include "../classes/Automaton/Automaton.h"
#include "../classes/fileExceptions/fileExceptions.h"
#include "../classes/State/StateComparator.h" 
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>

void changeEquivalence(unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes);
void devideDFA(Automaton& dfa, unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes);

void myOpenInput(const string& file, ifstream& fin);
void myOpenOutput(const string& file, ofstream& fout);

string join(const unordered_set<shared_ptr<State>>& elements, const string& sep = "_");
string join(const set<shared_ptr<State>, StateComparator>& elements, const string& sep = "_");
unordered_set<string> split(const string& str, char sep = '_');

void createMinimizedDFA(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>&,
                        const Automaton&, Automaton&);
void createMinimizedStates(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>&,
                                const Automaton&, Automaton&, 
                                unordered_map<string, string>&);
void createMinimizedTransitions(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>&,
                                const Automaton&, Automaton&, 
                                const unordered_map<string, string>&);

string createState(const string& states, char letter, const Automaton& NFA);
bool verifFinalState(const string& states, const Automaton& NFA);