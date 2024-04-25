//Converting NFA to DFA
#include <fstream>
#include <iostream>
#include "../classes/Automaton/Automaton.h"
#include "../functions/functions.h"
#include "../classes/fileExceptions/fileExceptions.h"
#include <queue>
#include <filesystem>
using namespace std;

#define INPUT_PATH "inputs/"

int main(){
    filesystem :: path dir_path = filesystem :: current_path().parent_path() / "p1";
    ofstream fout;
    ifstream fin;
    try{
        myOpenOutput((dir_path / "automat.out").string(), fout);

        string input_file;
        cout << "Enter file name for input: "; cin >> input_file;
        myOpenInput((dir_path / "inputs" / input_file).string(), fin);
    }
    catch(FileOpenException& e){
        cerr << e.what() << '\n';
        return 1;
    }

    Automaton NFA, DFA;
    
    fin >> NFA;

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

    fout << DFA << '\n';
}
