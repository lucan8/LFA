#pragma once
#include <iostream>
#include "../functions/functions.h"

Automaton DFA_MINIMIZATION(const Automaton& dfa);

void changeEquivalence(unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes);
void devideDFA(const Automaton& dfa, unordered_map<uint16_t, unordered_set<shared_ptr<State>>>& eq_classes);

void createMinimizedDFA(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>&,
                        const Automaton&, Automaton&);
void createMinimizedStates(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>&,
                                const Automaton&, Automaton&, 
                                unordered_map<string, string>&);
void createMinimizedTransitions(const unordered_map<uint16_t, unordered_set<shared_ptr<State>>>&,
                                const Automaton&, Automaton&, 
                                const unordered_map<string, string>&);