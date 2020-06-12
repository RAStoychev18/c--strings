#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

struct WORDS {
    string word;
    string description;
    string copWord;
};


struct Genre {
    vector<WORDS> words;
};

enum WORDS_OUTPUT
{
    DIFFERENT_LETTER_COUNT,
    DIFFERENT_LETTERS,
    GUESSED_WORD,
    GUESSED_LETTERS,
    FAILSE_GUESS,
    ALREADY_GUESSED
};
