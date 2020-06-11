#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "Structures.h"
using namespace std;

int randomInt(int minimum, int maximum)
{
    return rand() % (maximum - minimum + 1) + minimum;
}

void scrambleWord(string original, string& word)
{
    int rand;
    int coutSpaces = 0;
    word += original[0];
    for (int i = 1; i < original.size(); i++)
    {
        rand = randomInt(0, 100);
        if (rand <= 40)
        {
            coutSpaces++;
            word += '-';
        }
        else
        {
            word += original[i];
        }
    }
    if (coutSpaces == 0)
    {
        rand = randomInt(1, original.size() - 1);
        word[rand] = '-';
    }
}
bool toGenre(ifstream& file, Genre& genre)
{
    if (!file.is_open())
    {
        return false;
    }


    string line;

    size_t indexDel;
    while (getline(file, line))
    {
        indexDel = line.find(":");
        if (indexDel != string::npos)
        {
            WORDS word;
            word.word = line.substr(0, indexDel);
            scrambleWord(word.word, word.copWord);
            word.description = line.substr(indexDel + 1, line.size() - indexDel);
            genre.words.push_back(word);
        }
    }
    file.close();
    return true;
}

void SetupFiles(ifstream& geo, ifstream& ani, ifstream& fod, ifstream& trans, ifstream& sport, Genre& geometry, Genre& animals, Genre& food, Genre& transport, Genre& sports)
{
    geo.open("Geometry.txt");
    ani.open("Animals.txt");
    fod.open("food.txt");
    trans.open("Means of transport.txt");
    sport.open("sportAndGames.txt");
    toGenre(geo, geometry);
    toGenre(ani, animals);
    toGenre(fod, food);
    toGenre(trans, transport);
    toGenre(sport, sports);
}

void checkWord(int index, string word, Genre& genre)
{
    if (word.size() != genre.words[index - 1].word.size())
    {
        cout << "Look at the letter count";
        return;
    }
    int guessed = 0;
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] == genre.words[index - 1].word[i])
        {
            if (genre.words[index - 1].copWord[i] != '-' && genre.words[index - 1].copWord[i] != word[i])
            {
                cout << "\nEnter a word which letters are the same as the example";
                return;
            }
        }
    }
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] == genre.words[index - 1].word[i] && genre.words[index - 1].copWord[i] == '-')
        {
            genre.words[index - 1].copWord[i] = genre.words[index - 1].word[i];
            guessed++;
        }
    }
    if (genre.words[index - 1].copWord == genre.words[index - 1].word)
    {
        cout << "\nCONGRATS you guessed the word: " << genre.words[index - 1].word << endl << endl;
    }
    else if (guessed != 0)
    {
        cout << "\nGOOD JOB you guessed " << guessed << " letters" << endl << endl;
    }
    else
    {
        cout << "\nYou didn't guess any letters" << endl << endl;
    }
}
void printTopicWords(Genre& topic)
{
    string dis = "DESCRIPTION", woord = "WORDS";
    string piecedis, piecewrd;
    bool doneids, donewr, printed,printTen;
    for (int i = 0; i < 65; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < 65; i++)
    {

        if (i == 0 || i == 0 + 5 || i == 45 + 5 || i == 59 + 5)
        {
            cout << "|";
        }
        else if (i == 2)
        {
            cout << "0";
        }
        else if (i - 47 - 5 >= 0 && i - 47 - 5 < woord.size())
        {
            cout << woord[i - 47 - 5];
        }
        else if (i - 2 - 5 >= 0 && i - 2 - 5 < dis.size())
        {
            cout << dis[i - 2 - 5];
        }
        else cout << " ";
    }
    cout << endl;
    for (int i = 0; i < 65; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int m = 0; m < topic.words.size(); m++)
    {
        piecewrd = topic.words[m].copWord;
        piecedis = topic.words[m].description;
        doneids = false;
        donewr = false;
        printed = false;
        printTen = false;
        while (!doneids || !donewr)
        {
            for (int i = 0; i < 65; i++)
            {
                if (i == 0 || i == 0 + 5 || i == 45 + 5 || i == 59 + 5)
                {
                    cout << "|";
                }
                else if (!printed && i == 2)
                {
                    cout << m + 1;

                    printed = true;
                }
                else if (i == 1 || i == 4 || i == 1 + 5 || i == 44 + 5 || i == 46 + 5 || i == 58 + 5)
                {
                    if (!printTen && i == 4 && m + 1 >= 10)
                    {
                        printTen = true;
                    }
                    else
                    {
                        cout << " ";
                    }
                }
                else if (i <= 57 + 5 && i >= 47 + 5 && i - 47 - 5 < topic.words[m].copWord.size())
                {
                    cout << piecewrd[0];
                    if (!donewr)
                    {
                        piecewrd.erase(0, 1);
                    }
                }
                else if (i >= 2 + 5 && i <= 43 + 5 && i - 2 - 5 < topic.words[m].description.size())
                {
                    cout << piecedis[0];
                    if (!doneids)
                    {
                        piecedis.erase(0, 1);
                    }
                }
                else
                {
                    cout << " ";
                }


                if (piecewrd.empty() && !donewr)
                {
                    donewr = true;
                    piecewrd = " ";
                }

                if (piecedis.empty() && !doneids)
                {
                    doneids = true;
                    piecedis = " ";
                }
            }
            cout << endl;
        }
        for (int i = 0; i < 65; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
    cout << endl;
}
void insertWord(Genre& topic) {
    string word;
    int index;
    cout << "Enter the number of your word" << endl;
    cin >> index;
    cout << "Enter the word" << endl;
    cin >> word;
    checkWord(index, word, topic);
}
bool Menu(Genre& geometry ,Genre& animals, Genre& food, Genre& transport, Genre& sports) {

    //Greetings and the menu options
    int choice;
    cout << "----------WELCOME  TO  OUR  PROGRAM---------- " << endl;
    cout << endl;
    cout << "Choose the topic:" << endl;
    cout << "1.Geometry" << endl;
    cout << "2.Animals" << endl;
    cout << "3.Means of transport" << endl;
    cout << "4.Food" << endl;
    cout << "5.Sports and games" << endl;
    cout << "6.Quit" << endl;
    cout << "Enter your choice:";
    cin >> choice;
    if (choice <1 or choice>6 ) {
        cout << "There is no such option here! Bye for now!";
    }
    else {
        //this is the case for the menu options
        switch (choice) {
            case 1:
                printTopicWords(geometry);
                insertWord(geometry);
                return true;
            case 2:
                printTopicWords(animals);
                insertWord(animals);
                return true;
            case 3:
                printTopicWords(transport);
                insertWord(transport);
                return true;
            case 4:
                printTopicWords(food);
                insertWord(food);
                return true;
            case 5:
                printTopicWords(sports);
                insertWord(sports);
                return true;
            case 6:
                cout << "Bye for now!" << endl;
                return false;

            default:
                break;
        }
    }
    //stops the main menu from repeating
    return false;
}


