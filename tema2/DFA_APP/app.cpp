#include "../DFA_MINIMIZATION/DFA_MINIMIZATION.h"
#include "../NFA_TRANSFORMATION/NFA_TRANSFORMATION.h"

enum APP_CHOICES{NFA_TO_DFA = 1, DFA_MIN = 2};

int main(){
    ifstream fin;
    ofstream fout;
    Automaton DFA, NFA;

    //Assuming we are in the "build" folder
    filesystem :: path dir_path = filesystem :: current_path().parent_path();
    try{
        myOpenOutput((dir_path / "automat.out").string(), fout);
    } catch(const FileOpenException& e){
        cerr << "Error(main): " << e.what() << '\n';
        return 1;
    }

    uint16_t app_choice, file_choice;
    createMenu();
    cout << "Your choice: "; cin >> app_choice;

    switch (app_choice){
        case NFA_TO_DFA:
            try{
                myOpenInput(getInputFile(dir_path / "NFA_TRANSFORMATION"), fin);
            } catch(const FileOpenException& e){
                cerr << "Error(main): " << e.what() << '\n';
                return 1;
            }

            fin >> NFA;
            fout << NFA_TRANSFORMATION(NFA);

            break;
        case DFA_MIN:
            try{
                myOpenInput(getInputFile(dir_path / "DFA_MINIMIZATION"), fin);
            } catch(const FileOpenException& e){
                    cerr << "Error(main): " << e.what() << '\n';
                return 1;
            }

            fin >> DFA;
            fout << DFA_MINIMIZATION(DFA);
            
            break;
        default:
            cerr << "Error: Invalid choice!\n";
            return 1;
    }
}
