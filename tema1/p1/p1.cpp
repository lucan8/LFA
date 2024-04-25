#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

const string LAMBDA_WORD = "-";

ostream& operator<<(ostream& op, vector<int>& v){
    for (auto& x : v)
        op << x << ' ';
    return op;
}

vector<int> DFA_verif(unordered_map<char, unordered_map<int, int>>& adiacenta, int start,  vector<int>& finale, string& cuv){
    vector<int> path(1, start);

    for (auto& x : cuv){
        start = adiacenta[x][start]; //Mergem prin grafic la urmatoarea stare pe muchia x(simbol x)
        path.push_back(start);
    }

    //Verificam daca am ajuns intr-o stare finala cu acest cuvant caz in care returnam drumul  
    if (find(finale.begin(), finale.end(), start) != finale.end())
        return path;

    return vector<int>();
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


    fin >> m;
    for (int i = 0 ; i < m; i++){
        fin >> x >> y >> l;
        adiacenta[l].insert({x, y});
    }
    fin >> start >> nrf;
    vector<int> finale, path;

    for (int i = 0; i < nrf; i++){
        fin >> x;
        finale.push_back(x);
    }
    
    fin >> nrcuv;

    for (int i = 0; i < nrcuv; i++){
        fin >> cuv;

        if (cuv == LAMBDA_WORD) //Cuvant lambda
            if (find(finale.begin(), finale.end(), start) != finale.end())
                fout << "DA(lambda)" << endl;
            else
                fout << "NU(lambda)" << endl;
        else{
            path = DFA_verif(adiacenta, start, finale, cuv);

            if (path.empty())
                fout << "NU" << endl;
            else
                fout << "DA: " << path << endl;
        }
    }
    


}