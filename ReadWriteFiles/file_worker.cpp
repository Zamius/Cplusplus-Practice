#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::getline;
using std::cin;
using std::ws;

int main()
{
	const char* MENU = "1)Read file.\n2)Write to file.\n---> ";
	string filename{""};
	string choice{""};
	string line{""};
	string appending{""};
	std::vector<string> content{};


	while (1)
	{
		cout << MENU;
		cin >> choice;

		//Read
		if (choice == "1")
		{
			cout << "Enter file name: ";
			getline(cin>>ws, filename);

			std::ifstream myFile(filename);

			if (myFile)
			{
				cout << '\n';

				//Save lines to vector
				while(getline(myFile, line))
				{
					content.push_back(line);    
				}

				myFile.close();

				for (string l : content)
				{
					cout << l << '\n';
				}

				content.clear();
				cout << '\n';
			}

			else 
			{
				cout << "\nFile doesn't exist or couldn't be opened!\n\n";
			}
		}

		//Write
		else if (choice == "2")
		{
			cout << "Enter file name: ";
			getline(cin>>ws, filename);

			std::ofstream outfile;
			outfile.open(filename, std::ios_base::app); // append instead of overwrite

  			cout << "\nEnter lines (type END to stop)\n\n";

  			int line_count = 1;
  			while (true)
  			{

  				cout << "Enter line " << line_count << " --> ";
  				getline(cin >> ws, appending);

  				if (appending == "END")
  				{
  					break;
  				}
  				
  				outfile << appending << '\n';
  				line_count++;
  			} 

  			outfile.close();
  			cout << "\nStopped entering text...\n\n";
		}

		else 
		{
			cout << "\nInvalid\n\n";
		}
	}


	return 0;
}
