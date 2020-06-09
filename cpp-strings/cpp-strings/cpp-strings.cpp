#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "Functions.h"
#include "Structures.h"
using namespace std;

int main() {
    srand(time(NULL));
    Genre geometry;
    ifstream geo;
    geo.open("Geometry.txt");
    toGenre(geo, geometry);
    while (Menu(geometry));
}