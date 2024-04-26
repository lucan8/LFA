#pragma once
#include "../functions/functions.h"
#include <queue>

Automaton NFA_TRANSFORMATION(const Automaton& NFA);
string createState(const string& states, char letter, const Automaton& NFA);
bool verifFinalState(const string& states, const Automaton& NFA);