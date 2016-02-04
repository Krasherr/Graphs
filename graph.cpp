#include "graph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <QApplication>
#include <QDebug>
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include "maximumindependentset.h"

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

int isPowerOfTwo (unsigned int x)
{
    return ((x != 0) && ((x & (~x + 1)) == x));
}
/*
 * Funkcja słuzaca do wybrania odpowiedniego wezla
 */
int Graph::getTmp(const vector<int> &color, const vector<int> &tmp, const int &V)
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

int Graph::getLFRBitTmp(const vector<int> &tmp, const int &V, const vector<int> &bitSize, const vector<int> &marked, const int &bitSizeMin)
{
    int max = 9999;
    int max_i;
    for (int i =0; i < V; i++)
        if (bitSize[i] == bitSizeMin && marked[i]==bitSizeMin) { // jesli wezel jest niepokolorwany albo jest zaznaczony do dalszego kolorowania
            // oraz ilosc bitow potrzebnych do pokolorowania go jest mniejsza niz innych wezlow
            if (tmp[i]<max) {
                max = tmp[i];
                max_i = i;
            }
        }

    return max_i;
}

int Graph::getEqualBitTmp(const vector<int> &tmp, const int &V, const vector<int> &bitSize, const vector<int> &marked, const int &bitSizeMin)
{
    int max = -1;
    int max_i;
    for (int i =0; i < V; i++)
        if (bitSize[i] == bitSizeMin && marked[i]==bitSizeMin) { // jesli wezel jest niepokolorwany albo jest zaznaczony do dalszego kolorowania
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

void Graph::LFRColoring()
{
    std::vector<std::vector<int>> adjacentNodes = getAdjacentNodes(); //inicjalizacja lokalnej listy wezlow
    int numberOfNodes = getV();
    int uncolored=numberOfNodes; //zmienna sluzaca do okreslenia ile wezlow zostalo do pokolorowania
    int node, pos, cr, u;

    //Tymczasowe tablice do przetrzymywania kolorow i wagi wezlow
    vector<int> color, tmp;

    // Tymczasowa tablica sluzaca do ustalenia czy dany kolor
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(numberOfNodes);

    vector<int>::iterator i;

    for (u = 0; u<numberOfNodes; u++) {
        int size = 0;
        for (int j=0; j<numberOfNodes; j++) {
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
        color.push_back(-1);
        used[u] = false;
    }

    // glowna petla algorytmu
    while (uncolored>0) {

        node = getTmp(color, tmp, numberOfNodes); //wybor wezla

        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {//iteracja po sasiednich wezlach
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1) // czy kolor jest uzyty
                used[color[pos]] = true; // zaznacz uzyty kolor
        }

        //wybierz pierwszy dostepny kolor

        for (cr = 0; cr < numberOfNodes; cr++)
            if (used[cr] == false)
                break;

        //przypisz pierwszy wolny kolor do wezla
        color[node] = cr;
        uncolored--;

        // zresetuj wartosci dla kolejnej iteracji
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1)
                used[color[pos]] = false;
        }
    }

    //wypisz wartosci
    /*for (u = 0; u < numberOfNodes; u++)
        std::cout << "Vertex " << u << " --->  Color "
                  << color[u] << std::endl;*/
    graphToFile(color);
}

void Graph::LFRColoring2()
{
    std::vector<std::vector<int>> adjacentNodes = getAdjacentNodes(); //inicjalizacja lokalnej listy wezlow
    int numberOfNodes = getV();
    int uncolored=numberOfNodes; //zmienna sluzaca do okreslenia ile wezlow zostalo do pokolorowania
    int node, pos, cr, u;

    //Tymczasowe tablice do przetrzymywania kolorow i wagi wezlow
    vector<int> color, tmp;

    // Tymczasowa tablica sluzaca do ustalenia czy dany kolor
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(numberOfNodes);

    vector<int>::iterator i;

    for (u = 0; u<numberOfNodes; u++) {
        int size = 0;
        for (int j=0; j<numberOfNodes; j++) {
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
        color.push_back(-1);
        used[u] = false;
    }

    // glowna petla algorytmu
    while (uncolored>0) {

        node = getTmp(color, tmp, numberOfNodes); //wybor wezla



        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {//iteracja po sasiednich wezlach
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1) // czy kolor jest uzyty
                used[color[pos]] = true; // zaznacz uzyty kolor
        }

        //wybierz pierwszy dostepny kolor
        for (cr = 0; cr < numberOfNodes; cr++)
            if ((cr==0 || isPowerOfTwo(cr)) && used[cr] == false) {
                color[node] = cr;
                break;
            }

        if (color[node] == -1) {
            for (cr = 0; cr < numberOfNodes; cr++)
                if (!isPowerOfTwo(cr) && used[cr] == false) {
                    color[node] = cr;
                    break;
                }
        }
        //przypisz pierwszy wolny kolor do wezla
        uncolored--;

        // zresetuj wartosci dla kolejnej iteracji
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1)
                used[color[pos]] = false;
        }
    }

    //wypisz wartosci
  /*  for (u = 0; u < numberOfNodes; u++)
        std::cout << "Vertex " << u << " --->  Color "
                  << color[u] << std::endl;*/
    graphToFile(color);

}

/*
 * Algorytm kolorowania bitowego LF
 */

void Graph::LFRBitColoring()
{
    std::vector<std::vector<int>> adjacentNodes = getAdjacentNodes(); //stworzenie lokalnej listy sasiednich wezlow
    // list<int> *coloredAdjacentNodes = new list<int> [V]; //stworzenie listy przetrzymujacej juz pokolorowane sasiednie wezly w danej iteracji
    int numberOfNodes=getV(); //stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int cr, u, j, node, pos, bitSizeMin = 0, rounds=0, size; //zmienna przetrzymujaca numer wezla

    vector<int> tmp, bitSize (V,0), marked (V,0), color (V, -1);
    vector<int>::iterator i;
    vector<boost::dynamic_bitset<> > colorBit (V,boost::dynamic_bitset<>(V,0) );

    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(2);

    int uncolored=numberOfNodes;
    for (u = 0; u<numberOfNodes; u++) {
        size = 0;
        for (j=0; j<numberOfNodes; j++) {
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }

    //glowna petla programu
    while (uncolored>0) {

        node = getLFRBitTmp(tmp, getV(), bitSize, marked, bitSizeMin); //wybranie wezla

        //sprawdzenie czy pierwszy wezel w nowej iteracji ma mniej bitow kolorujacych niz minimalna ilosc dla iteracji
        marked[node]++;
        if (bitSize[node]<bitSizeMin) {
            continue;
        }

        //przypisz bit 0 do pierwszego wybranego wezla ktorego lista pokolorowanych sasiadow jest pusta
        //dla kolejnych wezlow
        //sprawdz czy zostal wolny bit
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            if (used[0]==true && used[1]==true) {
                break; //jesli oba bity zostaly uzyte przejdz dalej
            }

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

        for (cr = 0; cr <= 2; cr++)
            if (used[cr] == false)
                break;

        //jesli jeden z bitow jest dostepny
        if (cr == 0 || cr == 1) {
            colorBit[node][bitSize[node]] = cr; //przypisz wybrany bit
            color[node]=1; //ustaw wezel jako pokolorowany
            uncolored--; //zmniejsz ilosc wezlow do pokolorwania
        } else {
            colorBit[node][bitSize[node]] = 0; //przypisz bit 0 do wezla
            bitSize[node]=bitSize[node]+1; //zwieksz ilosc bitow potrzebnych do pokolorowania wezla o 1
            colorBit[node].resize( bitSize[node]+1);
        }

        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            pos = i - adjacentNodes[node].begin();
            if (*i==1 && marked[pos]==marked[node]) { //sprawdz sasiednie wezly ktore zostaly juz pokolorowane tez tego nie wymagaja (maja ten same bit)

                if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]) {
                    if (bitSize[pos] < bitSize[node]) { //zwieksz liczbe bitow potrzebnych do kolorowania i zaznacz go do dalszego kolorowania
                        bitSize[pos]=bitSize[node];
                        uncolored++;
                        colorBit[pos].resize( bitSize[node]+1);
                    }
                } else {
                    adjacentNodes[node][pos]=0;
                    adjacentNodes[pos][node]=0;
                }
            }
        }


        used[0] = false; //zresetuj wartosci
        used[1] = false;

        rounds++;

        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji
        if (rounds == numberOfNodes && uncolored != 0) {
            numberOfNodes=uncolored;
            bitSizeMin++;
            rounds = 0;
        }
    }
    graphToFile(colorBit, bitSize, bitSizeMin);
    //wypisz wezly - kolory
    /*V=Graph::V;
    for (u = 0; u < V; u++) {
        std::cout << "Vertex " << u << " --->  Size "
                  << colorBit[u].size() << std::endl;
        for (int i = 0; i<=bitSizeMin; i++)
            if(i>bitSize[u]) {
                std::cout << "Vertex " << u << " --->  Color -"
                          << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                          << colorBit[u][i] << std::endl;
    }*/

}

/*
 * Algorytm kolorowania bitowego równomiernego
 */


void Graph::EqualBitColoring()
{
    std::vector<std::vector<int>> adjacentNodes = getAdjacentNodes(); //stworzenie lokalnej listy sasiednich wezlow
    // list<int> *coloredAdjacentNodes = new list<int> [V]; //stworzenie listy przetrzymujacej juz pokolorowane sasiednie wezly w danej iteracji
    int numberOfNodes=getV(); //stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int cr, u, j, node, pos, bitSizeMin = 0, rounds=0, size; //zmienna przetrzymujaca numer wezla

    vector<int> tmp, bitSize (V,0), marked (V,0), color (V, -1);
    vector<int>::iterator i;
    vector<boost::dynamic_bitset<> > colorBit (V,boost::dynamic_bitset<>(V,0) );
    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(2);

    int uncolored=numberOfNodes;
    for (u = 0; u<numberOfNodes; u++) {
        size = 0;
        for (j=0; j<numberOfNodes; j++) {
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }

    int zero = 0, one = 0; //zainicjowanie zmiennych przetrzymujących ilość bitów o wartości 0 oraz 1

    //  vector<int> marked(V);
    for (cr = 0; cr < 2; cr++)
        used[cr] = false;
    //glowna petla programu
    while (uncolored>0) {
        // cout << "petla, uncolored: " << uncolored << endl;
        node = getEqualBitTmp(tmp, getV(), bitSize, marked, bitSizeMin); //wybranie wezla
        marked[node]++;


        //cout << "petla, vector: " << node << endl;

        if (bitSize[node]<bitSizeMin) {
            continue;
        }

        //przypisz bit do pierwszego wybranego wezla ktorego lista pokolorowanych sasiadow jest pusta
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


        //jesli oba bity są dostępne
        if (used[0] == false && used[1] == false) {
            if (zero<=one) {
                colorBit[node][bitSize[node]] = 0; // przypisz bit 0
                color[node]=1; //ustaw wezel jako pokolorowany
                uncolored--; //zmniejsz ilosc wezlow do pokolorwania
                zero++; //zwieksz ilosc wykorzystanych bitow 0

            } else {
                colorBit[node][bitSize[node]] = 1; // przypisz bit 1
                color[node]=1;
                uncolored--;
                one++; //zwieksz ilosc wykorzystanych bitow 1

            }
        } else if (used[0] == false) { //jesli tylko bit 0 jest dostepny
            colorBit[node][bitSize[node]] = 0;
            color[node]=1;
            uncolored--;
            zero++;

        } else if (used[1] == false) { //jesli tylko bit 1 jest dostepny
            colorBit[node][bitSize[node]] = 1; // Assign the found color
            color[node]=1;
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
            //cout << "bitSize: " << bitSize[node]<<endl;
        }

        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            pos = i - adjacentNodes[node].begin();
            if (*i==1 && marked[pos]==marked[node]) { //sprawdz sasiednie wezly ktore zostaly juz pokolorowane tez tego nie wymagaja (maja ten same bit)

                if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]) {
                    if (bitSize[pos] < bitSize[node]) { //zwieksz liczbe bitow potrzebnych do kolorowania i zaznacz go do dalszego kolorowania
                        bitSize[pos]=bitSize[node];
                        uncolored++;
                        //   cout << "powiekszam wezel numer: " << *i<<endl;
                    }
                } else {
                    adjacentNodes[node][pos]=0;
                    adjacentNodes[pos][node]=0;
                }
            }
        }

        used[0] = false;
        used[1] = false;

        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji
        // cout << "rounds" << rounds << endl;
        rounds++;
        if (rounds == numberOfNodes && uncolored != 0) {
            numberOfNodes=uncolored;
            bitSizeMin++;
            rounds = 0;
        }
    }

        graphToFile(colorBit, bitSize, bitSizeMin);
    //wypisz wezly - kolory
    /* V=Graph::V;
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
     }*/

}

void Graph::MaxCutBitColoring()
{
    std::vector<std::vector<int>> adjacentNodes = getAdjacentNodes(); //stworzenie lokalnej listy sasiednich wezlow
    MaximumIndependentSet maxSet;
    int numberOfNodes=getV(); //stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int cr, u, j, node, pos, bitSizeMin = 0; //zmienna przetrzymujaca numer wezla
    vector<int> tmp, bitSize (V,0), marked (V,0);
    vector<int>::iterator i;
    vector<boost::dynamic_bitset<> > colorBit (V,boost::dynamic_bitset<>(V,0) );
    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(2);



    int uncolored=numberOfNodes;
    for (u = 0; u<numberOfNodes; u++) {
        int size = 0;
        for (j=0; j<numberOfNodes; j++) {
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }

    for (cr = 0; cr < 2; cr++)
        used[cr] = false;
    vector<int> cover;

    //glowna petla programu
    while (uncolored>0) {

        cover = maxSet.process(adjacentNodes, getV(), getV());
        for(node=0; node<cover.size(); node++) {
            if(cover[node]==0) {
                cout<<node<<" ";
                //sprawdzenie czy pierwszy wezel w nowej iteracji ma mniej bitow kolorujacych niz minimalna ilosc dla iteracji
                if (bitSize[node]<bitSizeMin) {
                    continue;
                }

                colorBit[node][bitSize[node]] = 0; // Assign the found color
                marked[node]++;
                uncolored--;


                for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                    pos = i - adjacentNodes[node].begin();
                    if (*i==1 && marked[pos]==marked[node]) {
                        if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]) {
                            if (bitSize[node]==bitSizeMin) {
                                bitSize[node]=bitSize[node]+1;
                                colorBit[node].resize(bitSize[node]+1);
                                uncolored++;

                            }
                            if (bitSize[pos]<bitSize[node]) {
                                bitSize[pos]=bitSize[node];
                                colorBit[pos].resize(bitSize[node]+1);
                                uncolored++;

                            }
                        } else {

                            //jesli nie spelnia tych wymogow zaznacz go do usuniecia z listy sasiednich wezlow dla nastepnej iteracji
                            adjacentNodes[node][pos]=0;
                            adjacentNodes[pos][node]=0;
                        }
                    }
                }
            } else {
                if (bitSize[node]<bitSizeMin) {
                    continue;
                }

                colorBit[node][bitSize[node]] = 1; // Assign the found color
                marked[node]++;
                uncolored--;

                for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                    pos = i - adjacentNodes[node].begin();
                    if (*i==1 && marked[pos]==marked[node]) {
                        if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]) {
                            if (bitSize[node]==bitSizeMin) {
                                bitSize[node]=bitSize[node]+1;
                                colorBit[node].resize(bitSize[node]+1);
                                uncolored++;

                            }
                            if (bitSize[pos]<bitSize[node]) {
                                bitSize[pos]=bitSize[node];
                                colorBit[pos].resize(bitSize[node]+1);
                                uncolored++;

                            }
                        } else {

                            //jesli nie spelnia tych wymogow zaznacz go do usuniecia z listy sasiednich wezlow dla nastepnej iteracji

                            adjacentNodes[node][pos]=0;
                            adjacentNodes[pos][node]=0;
                        }
                    }
                }

            }
        }


        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji

        bitSizeMin++;


    }

    graphToFile(colorBit, bitSize, bitSizeMin);
    //wypisz wezly - kolory
    /*  V=getV();
      for (int u = 0; u < V; u++) {
          std::cout << "Vertex " << u << " --->  Size "
                    << colorBit[u].size() << std::endl;
          for (int i = 0; i<=bitSizeMin-1; i++)
              if(i>bitSize[u]) {
                  std::cout << "Vertex " << u << " --->  Color -"
                            << std::endl;
              } else
                  std::cout << "Vertex " << u << " --->  Color "
                            << colorBit[u][i] << std::endl;
      }*/
}

void Graph::graphToFile(const vector<boost::dynamic_bitset<>> &colorBit,const vector<int> &bitSize,  const int &bitSizeMin) {
    ofstream outfile ("graph_coloring.txt");

    int V = getV();
    for (int u = 0; u < V; u++) {
           outfile << "Vertex " << u << " --->  Size "
                     << colorBit[u].size() << std::endl;
           for (int i = 0; i<=bitSizeMin; i++)
               if(i>bitSize[u]) {
                   outfile << "-";
               } else
                   outfile << colorBit[u][i];

           outfile << std::endl;
   }
}

void Graph::graphToFile(const vector<int> &color) {
    ofstream outfile ("graph_coloring.txt");

    int numberOfNodes = getV();
    for (int u = 0; u < numberOfNodes; u++)
        outfile << "Vertex " << u << " --->  Color "
                  << color[u] << std::endl;
}
