#include <iostream>
#include <limits>

using std::cout;
using std::cin;

void printTable(int& number)
{
	short i{1};
	for (; i <= 10; ++i)
	{
		cout << number << " x " << i << " = " << number * i << '\n'; 
	}
}

int main()
{

	int number{0};

	//Simple multiplication table calculator in C++
	do 
	{
		cout << "Number to calculate: ";
		cin >> number;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nCin failed, try again...\n\n";

			continue;
		}

		if (number <= 0 || number > 1000000)
		{
			cout << "\nPlease enter a reasonable number! (Example: 2)\n\n";
			continue;
		}

		break;
	} while (true);

	cout << "\n*-*-* TABLE *-*-*\n";
	printTable(number);

	return 0;
}
