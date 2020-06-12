#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "Functions.h"
#include "DataTypes.h"
using namespace std;


int main() {
    srand(time(NULL));
    Genre geometry, animals, food, transoprt, sportsAndGames;
    ifstream geo, ani, fod, trans, sport;
    SetupFiles(geo, ani, fod, trans, sport, geometry, animals, food, transoprt, sportsAndGames);
    int correct = 0;
    while (Menu(geometry, animals, food, transoprt, sportsAndGames, correct));
}