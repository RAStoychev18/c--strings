#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "Functions.h"
using namespace std;

struct WORDS {
    string word;
    string description;
    string copWord;
};


struct Genre {
    vector<WORDS> words;
};
