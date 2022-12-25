#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>
#include <vector>

//C++ std 20

using std::cout, std::endl, std::transform, std::string;
using wordslist = std::vector<std::string>;

//Convert string to lower!
string toLower(string& msg)
{
	transform(begin(msg), end(msg), begin(msg),
		[&](char c) {
			return tolower(c);
		}
	);

	return msg;
}

//Get words
wordslist swears(std::shared_ptr<std::ifstream> file)
{
	string line{};
	wordslist words{};

	while (getline(*file, line))
	{
		words.push_back(line);
	}

	file->close();
	return words;
}

int main()
{
	const char* FILE_PATH = "words.txt";
	const char* PROMPT = "Enter a sentence: ";
	string sentence{};

	std::shared_ptr<std::ifstream> filePtr = std::make_shared<std::ifstream>(FILE_PATH);

	//Missing dependency (words.txt containing swear words)
	if (!*filePtr)
	{
		std::cerr << "The profanity list was not found! Find one and save it as words.txt in the program's directory!" << endl;
		return 0;
	}

	//Load words else
	wordslist profanity = swears(filePtr);
	
	bool not_found{};
	//Main
	while (1)
	{
		cout << PROMPT;
		getline(std::cin >> std::ws, sentence);
		
		not_found = true;
		for (auto w : profanity)
		{
			if (toLower(sentence).find(w) != string::npos)
			{
				cout << "\nFound profanity!!!\n" << endl;
				not_found = false;
				break;
			}
		}

		if (not_found)
		{
			cout << "\nYou're in the clear, cowboy! Your sentence does not contain profanity!\n" << endl;
		}
		
	}

	return 0;
}
