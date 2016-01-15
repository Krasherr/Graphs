#include "graph.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include "boost/dynamic_bitset.hpp"

Graph::Graph()
{

}

/*
 *  Dodanie krawedzi
 */

void Graph::addEdge(int v, int w)
{
    adjacentNodes[v][w]=1;
    adjacentNodes[w][v]=1;  // Note: the graph is undirected
}


/*
 * Funkcja słuzaca do wybrania odpowiedniego wezla
 */
int Graph::getTmp()
{
    int max = -1; // maksymalna wartosc wezla
    int max_i; //zmienna do przechowywania numeru wezla
    for (int i =0; i < V; i++)
        if (color[i] == -1) //jesli wezel jest niepokolorowany
            if (tmp[i]>max) {
                max = tmp[i];
                max_i = i;
            }
    return max_i;
}

/*
 * Funkcja słuzaca do wybrania odpowiedniego wezla dla algorytmow binarnych
 */

int Graph::getBitTmp()
{
    int max = -1;
    int max_i;
    for (int i =0; i < V; i++)
        if ((color[i] == -1 || marked[i] == true) && bitSize[i] == bitSizeMin) { // jesli wezel jest niepokolorwany albo jest zaznaczony do dalszego kolorowania
                                                                                 // oraz ilosc bitow potrzebnych do pokolorowania go jest mniejsza niz innych wezlow
            if (tmp[i]>max) {
                max = tmp[i];
                max_i = i;
            }
        }

    return max_i;
}


/*
 * Algorytm kolorowania klasycznego LF
 */

/*void Graph::LFRColoring()
{
    list<int> *adjacentNodes = Graph::adjacentNodes; //inicjalizacja lokalnej listy wezlow
    int uncolored=V; //zmienna sluzaca do okreslenia ile wezlow zostalo do pokolorowania
    int node; //wezel
    for (int u = 0; u<V; u++) {
        tmp.push_back(adjacentNodes[u].size()); //lista przechowujaca ilosc sasiadow kazdego z wezlow do pozniejszego wybrania
    }

    //ustawienie wszystkich wezlow jako niepokolorowane
    for (int u = 0; u < V; u++) {
        color.push_back(-1);
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany kolor
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(V);
    for (int cr = 0; cr < V; cr++)
        used[cr] = false;

    // glowna petla algorytmu
    while (uncolored>0) {

        node = getTmp(); //wybor wezla

        list<int>::iterator i;

        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) //iteracja po sasiednich wezlach
            if (color[*i] != -1) // czy kolor jest uzyty
                used[color[*i]] = true; // zaznacz uzyty kolor

        //wybierz pierwszy dostepny kolor
        int cr;
        for (cr = 0; cr < V; cr++)
            if (used[cr] == false)
                break;

        //przypisz pierwszy wolny kolor do wezla
        color[node] = cr;
        uncolored--;

        // zresetuj wartosci dla kolejnej iteracji
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i)
            if (color[*i] != -1)
                used[color[*i]] = false;
    }

    //wypisz wartosci
    for (int u = 0; u < V; u++)
        std::cout << "Vertex " << u << " --->  Color "
                  << color[u] << std::endl;

    //wyczysc listy
    tmp.clear();
    color.clear();

}

/*
 * Algorytm kolorowania bitowego LF
 */

void Graph::LFRBitColoring()
{
   // list<int> *adjacentNodes = Graph::adjacentNodes; //stworzenie lokalnej listy sasiednich wezlow
   // list<int> *coloredAdjacentNodes = new list<int> [V]; //stworzenie listy przetrzymujacej juz pokolorowane sasiednie wezly w danej iteracji

    int V=Graph::V; //stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int node; //zmienna przetrzymujaca numer wezla
    int pos;
    const boost::dynamic_bitset<> bZero(1, 0ul); //0 zapisane binarnie

    int uncolored=V;
    for (int u = 0; u<V; u++) {
        tmp.push_back(adjacentNodes[u].size()); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }


    for (int u = 0; u < V; u++) {
        color.push_back(-1); //lista ktora ustala czy wezel zaczal byc kolorowany
        colorBit.push_back(bZero);  // lista przetrzymujaca kolor wezla w danym momencie (w bitach)
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(2);
    for (int cr = 0; cr < 2; cr++)
        used[cr] = false;


    for (int cr = 0; cr < V; cr++) {
        bitSize.push_back(0); //lista do przetrzymywania wielkosci koloru w bitach (zaczyna się od 0, a nie od 1)
        marked.push_back(true); //oznaczenie wezla do dalszego kolorowania
    }
    bitSizeMin=0; //zmienna ustalajaca jaka jest najmniejsza ilosc bitow do pokolorowania wezla

    int rounds = 0; //ilosc rund w iteracji

    //glowna petla programu
    while (uncolored>0) {
        cout << "petla, uncolored: " << uncolored << endl;
        node = getBitTmp(); //wybranie wezla
        cout << "petla, vector: " << node << endl;

        vector<int>::iterator i, j;
        vector<int> it;

        //sprawdzenie czy pierwszy wezel w nowej iteracji ma mniej bitow kolorujacych niz minimalna ilosc dla iteracji
        if (colorBit[node].size()<bitSize[node]+1) {
            colorBit[node].resize(bitSize[node]+1); //zwiekszenie ilosci bitow kolorujacych

            //sprawdzenie czy sasiednie wezly sa pokolorowane
            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                pos = i - adjacentNodes[node].begin();
                if (marked[pos]==false){
                    adjacentNodes[node][pos]=0;
                    adjacentNodes[pos][node]=0; //zaznacz je do usuniecia
                }
            }

            //wyczysc listy pokolorowanych sasiadow
            continue;

        }

        //przypisz bit 0 do pierwszego wybranego wezla ktorego lista pokolorowanych sasiadow jest pusta
  //dla kolejnych wezlow
            //sprawdz czy zostal wolny bit
            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                if (used[0]==true && used[1]==true) {
                    break; //jesli oba bity zostaly uzyte przejdz dalej
                }
             //   cout << "i: " << i - adjacentNodes[node].begin() << endl;
                pos = i - adjacentNodes[node].begin();
                if (color[pos] != -1 && *i == 1) { //jesli sasiad jest pokolorowany zaznacz uzyty bit
                    if (colorBit[pos][bitSize[node]]==0) {
                        used[0] = true;
                    } else if (colorBit[pos][bitSize[node]]==1) {
                        used[1] = true;
                    }
                }
            }



        //wybierz bit
        int cr;
        for (cr = 0; cr <= 2; cr++)
            if (used[cr] == false)
                break;


       // cout << "kolor dostepny: " << cr << endl;
        //jesli jeden z bitow jest dostepny
        if (cr == 0 || cr == 1) {
            colorBit[node][bitSize[node]] = cr; //przypisz wybrany bit
            color[node]=1; //ustaw wezel jako pokolorowany
            marked[node]=false;
            uncolored--; //zmniejsz ilosc wezlow do pokolorwania
        } else {
            colorBit[node][bitSize[node]] = 0; //przypisz bit 0 do wezla
            bitSize[node]=bitSize[node]+1; //zwieksz ilosc bitow potrzebnych do pokolorowania wezla o 1
            colorBit[node].resize( bitSize[node]+1);
        //    cout << "bitSize: " << bitSize[node]<<endl;
        }

        if (marked[node]==true && bitSize[node]>0) { //jesli jest wezel zaznaczony dla dalszego kolorowania

            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) { //sprawdz sasiednie wezly ktore zostaly juz pokolorowane tez tego nie wymagaja (maja ten same bit)
                pos = i - adjacentNodes[node].begin();
                if (*i==1){
                if (bitSize[pos]>bitSize[node]-2 && color[pos]==1 && colorBit[pos][bitSize[node]-1]==colorBit[node][bitSize[node]-1]) { //jesli sasiedni wezel byl kolorowany w tej iteracji i ma ten sam bit

                    if (bitSize[pos] < bitSize[node]) { //zwieksz liczbe bitow potrzebnych do kolorowania i zaznacz go
                        bitSize[pos]=bitSize[node];
                        marked[pos]=true;
                        uncolored++;
                       // break;
           //             cout << "powiekszam wezel numer: " << pos<<endl;
                    }

                } else { //jesli nie spelnia tych wymogow zaznacz go do usuniecia z listy sasiednich wezlow dla nastepnej iteracji

                    if (color[pos] != -1) {
                        adjacentNodes[node][pos]=0;
                        adjacentNodes[pos][node]=0;
           //             cout << "usuwam wezel numer: " << pos<<endl;
                    }
                }

                }
            }
        }


        used[0] = false; //zresetuj wartosci
        used[1] = false;

       // cout << "rounds" << rounds << endl;
        rounds++;

        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji
        if (rounds == V && uncolored != 0) {
            V=uncolored;
            bitSizeMin++;
         //   cout << "V" << V << endl;
            rounds = 0;
        }
    }

    //wypisz wezly - kolory
    V=Graph::V;
    for (int u = 0; u < V; u++) {
        std::cout << "Vertex " << u << " --->  Size "
                  << colorBit[u].size() << std::endl;
        for (int i = 0; i<=bitSizeMin; i++)
            if(i>bitSize[u]) {
                std::cout << "Vertex " << u << " --->  Color -"
                          << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                          << colorBit[u][i] << std::endl;
    }

    //wyczysc listy pomocniczne
    colorBit.clear();
    color.clear();
    bitSize.clear();
    marked.clear();
}

/*
 * Algorytm kolorowania bitowego równomiernego
 */

/*
void Graph::EqualBitColoring()
{
    list<int> *adjacentNodes = Graph::adjacentNodes; //stworzenie lokalnej listy sasiednich wezlow
    list<int> *coloredAdjacentNodes = new list<int> [V]; //stworzenie listy przetrzymujacej juz pokolorowane sasiednie wezly w danej iteracji
    int V=Graph::V;//stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int node; //zmienna przetrzymujaca numer wezla
    const boost::dynamic_bitset<> bZero(1, 0ul); //0 zapisane binarnie

    int uncolored=V;

    for (int u = 0; u<V; u++) {
        tmp.push_back(adjacentNodes[u].size()); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }


    int zero = 0, one = 0; //zainicjowanie zmiennych przetrzymujących ilość bitów o wartości 0 oraz 1

    for (int u = 0; u < V; u++) {
        color.push_back(-1);//lista ktora ustala czy wezel zaczal byc kolorowany
        colorBit.push_back(bZero);  // lista przetrzymujaca kolor wezla w danym momencie (w bitach)
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(2);
    for (int cr = 0; cr < 2; cr++)
        used[cr] = false;

    for (int cr = 0; cr < V; cr++) {
        bitSize.push_back(0);//lista do przetrzymywania wielkosci koloru w bitach (zaczyna się od 0, a nie od 1)
        marked.push_back(true); //oznaczenie wezla do dalszego kolorowania
    }

    bitSizeMin=0; //zmienna ustalajaca jaka jest najmniejsza ilosc bitow do pokolorowania wezla
    int rounds=0; //ilosc rund w iteracji

        //glowna petla programu
    while (uncolored>0) {
        cout << "petla, uncolored: " << uncolored << endl;
        node = getBitTmp(); //wybranie wezla
        vector<int> it;

        cout << "petla, vector: " << node << endl;
        list<int>::iterator i, j;

          //sprawdzenie czy pierwszy wezel w nowej iteracji ma mniej bitow kolorujacych niz minimalna ilosc dla iteracji
        if (colorBit[node].size()<bitSize[node]+1) {
            colorBit[node].resize(bitSize[node]+1); //zwiekszenie ilosci bitow kolorujacych

             //sprawdzenie czy sasiednie wezly sa pokolorowane
            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {

                if (colorBit[*i][bitSize[node]-1]!=colorBit[node][bitSize[node]-1])
                    it.push_back(*i);//zaznacz je do usuniecia
            }
            for (int j = 0; j < it.size(); j++) {
                adjacentNodes[node].remove(it[j]);//usun zaznaczone pokolorowane wezly z listy sasiadow
            }

            //wyczysc listy pokolorowanych sasiadow
            coloredAdjacentNodes[node].clear();
            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                coloredAdjacentNodes[*i].clear();
            }

            continue;
        }

        //przypisz bit do pierwszego wybranego wezla ktorego lista pokolorowanych sasiadow jest pusta
        if (coloredAdjacentNodes[node].empty()) {

            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                coloredAdjacentNodes[*i].push_back(node);
            }
        }

        else {//dla kolejnych wezlow
                //sprawdz czy zostal wolny bit
            for (i = coloredAdjacentNodes[node].begin(); i != coloredAdjacentNodes[node].end(); ++i) {

                if (used[0]==true && used[1]==true) {
                    break; //jesli oba bity zostaly uzyte przejdz dalej
                }
                if (color[*i] != -1) { //jesli sasiad jest pokolorowany zaznacz uzyty bit
                    if (colorBit[*i][bitSize[node]]==0) {
                        used[0] = true;
                    } else if (colorBit[*i][bitSize[node]]==1) {
                        used[1] = true;
                    }
                }
            }

            //dodaj wezel do listy pokolorwanych sasiadow
            for (j = adjacentNodes[node].begin(); j != adjacentNodes[node].end(); ++j) {
                coloredAdjacentNodes[*j].push_back(node);
                }
        }


        //jesli oba bity są dostępne
        if (used[0] == false && used[1] == false) {
            if (zero<=one) {
                colorBit[node][bitSize[node]] = 0; // przypisz bit 0
                color[node]=1; //ustaw wezel jako pokolorowany
                marked[node]=false;
                uncolored--; //zmniejsz ilosc wezlow do pokolorwania
                zero++; //zwieksz ilosc wykorzystanych bitow 0

            } else {
                colorBit[node][bitSize[node]] = 1; // przypisz bit 1
                color[node]=1;
                marked[node]=false;
                uncolored--;
                one++; //zwieksz ilosc wykorzystanych bitow 1

            }
        } else if (used[0] == false) { //jesli tylko bit 0 jest dostepny
            colorBit[node][bitSize[node]] = 0;
            color[node]=1;
            marked[node]=false;
            uncolored--;
            zero++;

        } else if (used[1] == false) { //jesli tylko bit 1 jest dostepny
            colorBit[node][bitSize[node]] = 1; // Assign the found color
            color[node]=1;
            marked[node]=false;
            uncolored--;
            one++;

        } else { //jesli oba bity sa uzyte
            if (zero<=one) { //jesli jest wiecej bitow 1 niz 0 lub jest ich tyle samo
                colorBit[node][bitSize[node]] = 0;
                zero++;
            } else { //jesli jest wiecej bitow 0 niz 1
                colorBit[node][bitSize[node]] = 1;
                one++;
            }

            bitSize[node]=bitSize[node]+1; //zwieksz ilosc bitow potrzebnych do pokolorowania wezla o 1
            cout << "bitSize: " << bitSize[node]<<endl;
            colorBit[node].resize( bitSize[node]+1);
        }
        if (marked[node]==true && bitSize[node]>0) { //jesli jest wezel zaznaczony dla dalszego kolorowania

            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) { //sprawdz sasiednie wezly ktore zostaly juz pokolorowane tez tego nie wymagaja (maja ten same bit)
                if (bitSize[node] < 2) { //jesli jest to iteracja 0 albo 1 porownaj bity w tej iteracji
                    if (bitSize[*i]>bitSize[node]-2 && color[*i] != -1 && colorBit[*i][bitSize[node]-1]==colorBit[node][bitSize[node]-1]) {
                        if (bitSize[*i] < bitSize[node]) { //zwieksz liczbe bitow potrzebnych do kolorowania i zaznacz go do dalszego kolorowania
                            bitSize[*i]=bitSize[node];
                            marked[*i]=true;
                            uncolored++;
                            cout << "powiekszam wezel numer: " << *i<<endl;
                        }
                    } else {

                        if (color[*i] != -1) { //jesli nie spelnia tych wymogow zaznacz go do usuniecia z listy sasiednich wezlow dla nastepnej iteracji
                            it.push_back(*i);
                            cout << "usuwam wezel numer: " << *i<<endl;
                        }

                    }
                } else { //jesli jest to iteracja wyzsza niz 0 albo 1 porownaj bity z danej iteracji i z poprzedniej
                    if (bitSize[*i]>bitSize[node]-2 && color[*i] != -1 && colorBit[*i][bitSize[node]-1]==colorBit[node][bitSize[node]-1] && colorBit[*i][bitSize[node]-2]==colorBit[node][bitSize[node]-2]) {
                        if (bitSize[*i] < bitSize[node]) { //zwieksz liczbe bitow potrzebnych do kolorowania i zaznacz go
                            bitSize[*i]=bitSize[node];
                            marked[*i]=true;
                            uncolored++;
                            cout << "powiekszam wezel numer: " << *i<<endl;
                        } else {

                            if (color[*i] != -1) { //jesli nie spelnia tych wymogow zaznacz go do usuniecia z listy sasiednich wezlow dla nastepnej iteracji
                                it.push_back(*i);
                                cout << "usuwam wezel numer: " << *i<<endl;
                            }

                        }
                    }
                }


            }
        }

        for (int j = 0; j < it.size(); j++) { //usun zaznaczony wezel
            adjacentNodes[node].remove(it[j]);
        }

        used[0] = false;
        used[1] = false;

        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji
        cout << "rounds" << rounds << endl;
        rounds++;
        if (rounds == V && uncolored != 0) {
            V=uncolored;
            bitSizeMin++;
            cout << "V" << V << endl;
            rounds = 0;
        }
    }


    //wypisz wezly - kolory
    V=Graph::V;
    for (int u = 0; u < V; u++) {
        std::cout << "Vertex " << u << " --->  Size "
                  << colorBit[u].size() << std::endl;
        for (int i = 0; i<=bitSizeMin; i++)
            if(i>bitSize[u]) {
                std::cout << "Vertex " << u << " --->  Color -"
                          << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                          << colorBit[u][i] << std::endl;
    }

    colorBit.clear();
    color.clear();
    bitSize.clear();
    marked.clear();
}
*/
