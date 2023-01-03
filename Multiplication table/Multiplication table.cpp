#include <iostream>
#include <fstream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

static constexpr long long MAX = std::numeric_limits<long long>::max() / 100;
#define MIN 1

int main()
{
	//Accept user input
	long long number{};

	do
	{
		cout << "Enter number: ";
		cin >> number;

		if (cin.fail())
		{
			std::cerr << "\nNot a valid value!\n" << endl;
			cin.clear();

			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (number < MIN || number > MAX)
		{
			std::cerr << "\nPlease enter a reasonable number!\n" << endl;
			continue;
		}

		break;

	} while (true);

	//Open file and do multiplication table
	std::ofstream* write_file = new std::ofstream("results.txt", std::ios_base::app);
	
	if (!write_file->is_open())
	{
		std::cerr << "\nThere was an error while saving to file! ABORTED\n" << endl;
		delete write_file;
		return -1;
	}

	short start{ 1 };
	for (; start <= 10; ++start)
	{
		*write_file << number << " X " << start << " = " << number * start << endl;
	}

	*write_file << "\n";
	write_file->close();

	delete write_file;
	
	cout << "\nSuccesfully stored output in results.txt" << endl;
	return 0;
}