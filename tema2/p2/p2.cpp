#include <iostream>
#include "../classes/Automaton/Automaton.h"
#include "../classes/fileExceptions/fileExceptions.h"
#include "../functions/functions.h"
#include <fstream>
#include <unordered_map>
#include <filesystem>
//More tests
//Code refactor and split
//Assumption: Getting normal DFA
#define INPUT_FOLDER "inputs"

int main(){
    filesystem :: path dir_path = filesystem :: current_path().parent_path() / "p2";
    ofstream fout;
    ifstream fin;
    try{
        myOpenOutput("automat.out", fout);

        string input_file;
        cout << "Enter file name for input: "; cin >> input_file;
        myOpenInput((dir_path / "inputs" / input_file).string(), fin);
    }
    catch(FileOpenException& e){
        cerr << e.what() << '\n';
        return 1;
    }

    Automaton dfa, min_dfa;
    fin >> dfa;

    if (dfa.getStates().size() == dfa.getFinalStates().size()){
        cout << "Already minimized!" << '\n';
        fout << dfa;
        return 0;
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
    fout << min_dfa;
}

