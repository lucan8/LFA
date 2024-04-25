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

//La fiecare pas punem intr-un vector nodurile
vector<int> NFA_verif(unordered_map<char, map<int, vector<int>>>& adiacenta, int start,  vector<int>& finale, string& cuv, int index){
    //Am ajuns la finalul cuvantului
    if (index == cuv.size()){ 
        if (find(finale.begin(), finale.end(), start) != finale.end()) //Verificam daca am ajuns intr-un nod terminal
                return vector<int>(1, start); ///Cream vectorul de afisare
    }
    //Verificam daca este muchie cu acest simbol, cu nod de inceput start
    else if (adiacenta.find(cuv[index]) != adiacenta.end() && adiacenta[cuv[index]].find(start) != adiacenta[cuv[index]].end()){
        for (auto& y : adiacenta[cuv[index]][start]){//Mergem pe toate nodurile vecine
            //Daca cuvantul este valid reconstruim drumul
            vector<int> path = NFA_verif(adiacenta, y, finale, cuv, index + 1);

            if (!path.empty()){
                path.push_back(start);
                return path;
            }
        }
    }
    return vector<int>();
}
int main(){
    ifstream fin("automate.in");
    ofstream fout("automate.out");

    int n = 0, m = 0, x, y, start, nrf = 0, nrcuv = 0;
    string cuv;
    char l;

    fin >> n;

    //map[simbol] = {nod1:[nod2, nod3...] toate nodurile vecine cu nod1 ce au ca muchie simbol}
   unordered_map<char, map<int, vector<int>>> adiacenta;

    for (int i = 0; i < n; i++){
        fin >> x; //Nu imi trebuie sa stiu nodurile
    }

    fin >> m;
    for (int i = 0 ; i < m; i++){
        fin >> x >> y >> l;
        //Prima muchie de cost l cu nod stang x creeaza vectorul de noduri vecine cu x
        if (adiacenta[l].find(x) == adiacenta[l].end())
            adiacenta[l].insert({x, vector<int>(1, y)});
        else//Restul nodurilor sunt doar inserate in lista creata
            adiacenta[l][x].push_back(y);
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
            path = NFA_verif(adiacenta, start, finale, cuv, 0);

            if (path.empty())
                fout << "NU" << endl;
            else{
                reverse(path.begin(), path.end());
                fout << "DA: " << path << endl;
            }
        }
    }
    
}