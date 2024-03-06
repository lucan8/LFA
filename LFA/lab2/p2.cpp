#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

//Incearca cu DFS, vezi daca merge
bool NFA_verif(unordered_map<char, unordered_map<int, int>>& adiacenta, int start,  vector<int>& finale, string& cuv){
    for (auto& x : cuv)
        //Daca exista muchia cu simbolul x trecem laa nodul urmator
        if (adiacenta.find(x) != adiacenta.end()){
            NFA_verif(adiacenta[x][start]); //Mergem prin grafic la urmatoarea stare pe muchia x(simbol x)
        }
        
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
        fin >> x; //Nu imi trebuie sa stiu nodurile
    }

    //Daca avem numere random parsam si le facem sa fie consecutive, pana la n

    fin >> m;
    for (int i = 0 ; i < m; i++){
        fin >> x >> y >> l;
        adiacenta[l].insert({x, y}); //Fiecarui simbol atribuim perechea de noduri (x,y)
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
        fout << NFA_verif(adiacenta, start, finale, cuv) << endl;
    }
    


}