#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

const string LAMBDA_WORD = "-";
const char LAMBDA_MUCHIE = '0';

ostream& operator<<(ostream& op, vector<int>& v){
    for (auto& x : v)
        op << x << ' ';
    return op;
}

vector<int> LNFA_verif(unordered_map<char, map<int, vector<int>>>& adiacenta, int start,  vector<int>& finale, string& cuv, int index, vector<char> lnodes){
    //Am ajuns la finalul cuvantului
    if (index == cuv.size()){
        if (find(finale.begin(), finale.end(), start) != finale.end()) //Verificam nod terminal
            return vector<int>(1, start); ///Cream vectorul de afisare
    }
    //Verificam daca este muchie cu acest simbol, cu nod de inceput start
    else {
        if (adiacenta.find(cuv[index]) != adiacenta.end() && adiacenta[cuv[index]].find(start) != adiacenta[cuv[index]].end()){//Verificam daca este muchie cu acest simbol
            for (auto& x : adiacenta[cuv[index]][start]){//Mergem pe toate nodurile vecine
                //Daca cuvantul este valid reconstruim drumul
                vector<int> path = LNFA_verif(adiacenta, x, finale, cuv, index + 1, vector<char>());

                if (!path.empty()){
                    path.push_back(start);
                    return path;
                }
            }
        }
        //Verifcam muchiile lambda
        if (adiacenta.find(LAMBDA_MUCHIE) != adiacenta.end() && adiacenta[LAMBDA_MUCHIE].find(start) != adiacenta[LAMBDA_MUCHIE].end())
            //Verificam daca start se afla in lista de noduri vizitate cu lambda,daca nu e il punem si continuam alg
            if (find(lnodes.begin(), lnodes.end(), start) == lnodes.end()){
                lnodes.push_back(start);

                for (auto& x :adiacenta[LAMBDA_MUCHIE][start]){
                    vector<int> path = LNFA_verif(adiacenta, x, finale, cuv, index, lnodes);

                    if (!path.empty()){
                        path.push_back(start);
                        return path;
                    }
                }
            }
    }
    return vector<int>();
}
int main(){
    ifstream fin("automate.in");
    ofstream fout("automate.out");

    int n, m, x, y, start, nrf, nrcuv;
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
        if (l != LAMBDA_MUCHIE || x != y) //Ignoram ciclurile lambda catre sine
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
    //Daca primim lambda ca input verificam daca nodul de start e si terminal si afisam
    for (int i = 0; i < nrcuv; i++){
        fin >> cuv;
        
        if (cuv == LAMBDA_WORD) //Input lambda
            if (find(finale.begin(), finale.end(), start) != finale.end())//Vedem daca suntem in stare finala
                fout << "DA(lambda)" << endl;
            else
                fout << "NU(lambda)" << endl;
        else{
            path = LNFA_verif(adiacenta, start, finale, cuv, 0, vector<char>());

            if (path.empty())
                fout << "NU" << endl;
            else{
                reverse(path.begin(), path.end());
                fout << "DA: " << path << endl;
            }
        }
    }
    
}