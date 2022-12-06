#include "headers/preferences.h"
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <algorithm>
#include <bits/stdc++.h> 

using namespace std;

bool fetchWords(str fileName, vector<str> & words)
{
	std::ifstream in(fileName.c_str());

	// Check if file object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<< "words_updated.txt" << endl;
        return false;
    }

    str line;

    //Start inserting lines in vector
    while (getline(in, line))
    {

    	//Means string in current line is not empty!
    	if (line.size() > 0)
    	{
    		words.push_back(line);
    	}
    }

    in.close();
    return true;
}

//Fetch random word from list
str yieldWord(vector<str> param)
{
	int rIndex = rand() % param.size() + 1;
	str word = param[rIndex];

	return word;
}


int main() 
{

	int tries {6};

	//this is required to gather a random word from the list
	std::srand(time(nullptr));	

	//Vector that will hold words
	vector<str> words;

	//Fill with words from file
	bool initWordsGet = fetchWords("words_updated.txt", words);

	//Random word placeholder, word's length and user-input
	str game{}, truncated{}, user_word{};
	short word_length{};


	//Menu
	const char* MENU = "1)Play\n2)View number of words guessed\n3)Exit\n";
	str selection{};

	long points{0};

	vector<str> usedChars;

	//Mainloop
	while (true) 
	{	
		cout << MENU << endl;
		cout << "--> ";

		getline(cin>>ws, selection);

		/* PLAY THE GAME */
		if (selection == "1")
		{

			user_word = "";
			tries = 6;

			if (!(usedChars.empty()))
			{
				usedChars.clear();
			}

			//Gets word in game variable
			game = yieldWord(words);
			word_length = game.length();
			
			//Length check to show initial letters distribution

			if (word_length == 4) 
			{
				truncated = game[0];

				for (int i = 0; i < word_length-1; i++)
				{
					truncated += ".";
				} 
			}

			else 
			{

				truncated = game[0];

				for (int i = 1; i < word_length-1; i++)
				{
					truncated += ".";
				} 
				truncated += game[word_length-1];
			}

			cout << '\n';


			/* Start receiving letter input here */

			while (user_word != game)
			{

				//No tries left
				if (!tries)
				{
					cout << "\nYou did not guess the word! The word was: " << game << "\n" << endl;
					break;
				}

				//Show used characters so far
				if (!(usedChars.empty()))
				{	
					cout << "\nUsed characters: ";
					for (str i : usedChars)
					{	
						cout << i << " ";

					}
					cout << endl;
				}


				cout << "Word:\n" << endl;

				cout << truncated << '\n';

				cout << "\nTries left: " << tries << endl;

				cout << "Enter guess (The entire word, or a letter): ";

				getline(cin, user_word);

				//Show letters if any in word and decrement tries
				if (!(user_word == game))
				{
					//Just fail if the user doesn't input a character but an entire word
					if (user_word.length() > 1)
					{	
						cout << "\nWrong guess!!\n" << endl;
						tries--;
						continue;
					}

					char user = user_word[0];

					//Character already guessed
					if (std::count(usedChars.begin(), usedChars.end(), user_word))
					{
						cout << "\nYou already used this character!\n" << endl;
						continue;
					}

					usedChars.push_back(user_word);

					//Iterate word and find matching characters, display them in "truncated" if found
					bool found_character = false;

					for (int idx = 1; idx != game.length() - 1; idx++)
					{

						if (game[idx] == user)
						{
							truncated[idx] = user;
							found_character = true;

							continue;
						}
					}

					if (!(std::count(truncated.begin(), truncated.end(), '.')))
					{
						cout << "\nYou Guessed the word!!!\nGG!\n" << endl;
						++points;
						break;
					}

					if (found_character)
					{
						str::difference_type n = std::count(game.begin(), game.end(), user);
						cout << "\nFound " << user << " " << n << " times!\n" << endl;
					}

					else { tries--; cout << user_word << " does not appear in the word!\n" << endl; }

				}
			}

			//On word guess or fail

			if (user_word == game)
				{
					cout << "\nYou guessed the word!!!\nGG\n" << endl;
					++points;
				}

		}

		else if (selection == "2")
		{

			//Show points and format plurals

			if (points == 1)
			{
				cout << "\nYou guessed " << points << " word so far!\n" << endl;
				continue;
			}

			cout << "\nYou guessed " << points << " words so far!\n" << endl;
		}

		else if (selection == "3")
		{
			break;
		}

		//exit
		//On exit
		else 
		{
			cout << "\nUnrecognized action, try again!\n" << endl;

			continue;
		}
			
	}

	cout << "\nCYA!!!\n";

	return 0;
}
