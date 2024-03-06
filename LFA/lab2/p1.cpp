#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

bool DFA_verif(unordered_map<char, unordered_map<int, int>>& adiacenta, int start,  vector<int>& finale, string& cuv){
    for (auto& x : cuv)
        start = adiacenta[x][start]; //Mergem prin grafic la urmatoarea stare pe muchia x(simbol x)

    //Verificam daca am ajuns intr-o stare finala cu acest cuvant caz in care returnam true    
    for (auto& x : finale)
        if (x == start)
            return true;
    return false;
}
int main(){
    ifstream fin("automate.in");
    ofstream fout("automate.out");

    int n, m, x, y, start, nrf, nrcuv;
    string cuv;
    char l;

    fin >> n;

    //map[simbol] = {nod1:nod2}
   unordered_map<char, unordered_map<int, int>> adiacenta;

    for (int i = 0; i < n; i++){
        fin >> x;
    }

    //Daca avem numere random parsam si le facem sa fie consecutive, pana la n

    fin >> m;
    for (int i = 0 ; i < m; i++){
        fin >> x >> y >> l;
        adiacenta[l].insert({x, y});
    }
    fin >> start >> nrf;
    vector<int> finale;

    for (int i = 0; i < nrf; i++){
        fin >> x;
        finale.push_back(x);
    }
    
    fin >> nrcuv;

    for (int i = 0; i < nrcuv; i++){
        fin >> cuv;
        fout << DFA_verif(adiacenta, start, finale, cuv) << endl;
    }
    


}