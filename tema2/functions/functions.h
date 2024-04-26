#pragma once
#include <iostream>
#include "../classes/fileExceptions/fileExceptions.h"
#include "../classes/Automaton/Automaton.h"
#include "../classes/State/StateComparator.h" 
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <filesystem>



void myOpenInput(const string& file, ifstream& fin);
void myOpenOutput(const string& file, ofstream& fout);

string join(const unordered_set<shared_ptr<State>>& elements, const string& sep = "_");
string join(const set<shared_ptr<State>, StateComparator>& elements, const string& sep = "_");
unordered_set<string> split(const string& str, char sep = '_');

void createMenu();
vector<string> inputMenu(const filesystem :: path& input_path);
string getInputFile(const filesystem :: path& input_path);