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
    string piecedis,piecewrd;
    bool doneids,donewr;
    for (int i = 0; i < 60; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i <60 ; i++)
    {
    
        if (i == 0 || i == 45 || i == 59)
        {
            cout << "|";
        }
        else if (i - 47 >= 0 &&  i-47 < woord.size())
        {
            cout << woord[i - 47];
        }
        else if (i - 2 >= 0 && i-2 <dis.size())
        {
            cout << dis[i - 2];
        }
        else cout << " ";
    }
    cout << endl;
    for (int i = 0; i < 60; i++)
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
        while (!doneids || !donewr)
        {
            for (int i = 0; i < 60; i++)
            {
                if (i == 0 || i == 45 || i == 59)
                {
                    cout << "|";
                }
                else if (i == 1 || i == 44 || i == 46 || i == 58)
                {
                    cout << " ";
                }
                else if (i <= 57 && i >= 47 && i - 47 < topic.words[m].copWord.size())
                {
                    cout << piecewrd[0];
                    if (!donewr)
                    {
                        piecewrd.erase(0, 1);
                    }
                }
                else if (i >= 2 && i <= 43 && i - 2 < topic.words[m].description.size())
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
        for (int i = 0; i < 60; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
    cout << endl;
}

bool Menu(Genre& geometry) {

    //Greetings and the menu options
    int choice;
    cout << "----------WELCOME  TO  OUR  PROGRAM---------- " << endl;
    cout << endl;
    cout << "Choose the topic:" << endl;
    cout << "1.Geometry" << endl;
    cout << "4.Quit" << endl;
    cout << "Enter your choice:";
    cin >> choice;
    if (choice != 1 && choice != 4) {
        cout << "There is no such option here! Bye for now!";
    }
    else {
        //this is the case for the menu options
        switch (choice) {
            case 1:
                for (int i = 0; i < geometry.words.size(); i++)
                {
                    cout << i + 1 << ". " << geometry.words[i].description << "\n    " << "| " << geometry.words[i].copWord << " | \n" << endl;

                }
                return true;
            case 4:
                cout << "Bye for now!" << endl;
                return false;

            default:
                break;
        }
    }
    //stops the main menu from repeating
    return false;
}