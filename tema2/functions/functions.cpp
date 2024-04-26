#include "functions.h"

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

void createMenu(){
    cout << "Welcome to the DFA app, here you can either:\n";
    cout << "+--------------------------+\n"; 
    cout << "|1.Transform NFA into a DFA|\n";
    cout << "|2.Minimize DFA            |\n";
    cout << "+--------------------------+\n"; 
}

string getInputFile(const filesystem :: path& input_path){
    uint16_t file_choice;
    try{
        vector<string> files = inputMenu(input_path / "inputs");
        cout  << "Your choice: "; cin >> file_choice;
        
        return files.at(file_choice - 1);
    } catch (const DirectoryNotFound& e){
        cerr << "Error(getInput): " << e.what() << '\n';
        return "";
    } catch(const out_of_range& e){
        cerr << "Error(getInput): Invalid file choice\n";
        return "";
    }
}


vector<string> inputMenu(const filesystem :: path& input_path){
    if (!filesystem :: is_directory(input_path))
        throw DirectoryNotFound(input_path.string());

    vector<string> files;

    cout << "Choose input file:\n";
    cout << "+------------+\n";

    for (const auto& file : filesystem :: directory_iterator(input_path)){
        string file_path = file.path().string();
        //Pushing only the filename
        files.push_back(file_path);
        cout << "|" << files.size() << "." << file_path.substr(file_path.rfind("\\") + 1) << "|\n";
    }
    cout << "+------------+\n";

    return files;
}
