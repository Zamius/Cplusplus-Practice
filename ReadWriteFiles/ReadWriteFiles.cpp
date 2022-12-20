#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using stringlist = std::vector<string>;

namespace fs = std::filesystem;

constexpr auto _ERROR = "\nNot a valid selection!\n\n";;

//Empty file?
bool isEmpty(std::fstream& file)
{
	return (file.peek() == std::ifstream::traits_type::eof() ? true : false);
}

//File is present?
bool isFile(fs::path& myPath)
{
	return fs::is_regular_file(myPath);
}

//Get the current path
static fs::path get_cwd{ fs::current_path() };
//...and convert it to string
static const string cwd{ get_cwd.string() };

/*...Define functions for later...*/

//Create an empty file
void makeFile(fs::path);

//read file contents and return a string vector
stringlist readFile(fs::path);

//write to file
void writeFile(fs::path);

int main(int argc, char** argv)
{
	//Change clear screen command by checking the OS
	#ifdef _WIN32
		const char* cmd = "cls";
	#elif __linux__
		const char* cmd = "clear";
	#else
	#endif // _WIN32

	//Fetch script's name
	const string _SCRIPTNAME{ argv[0] };
	//Get index of the last occurrence of "\" or "/"
	const short idx{ (short)_SCRIPTNAME.find_last_of("\\/") };

	//Welcome messages and cut everything before the last / or \ with substr to print this program's name
	cout << "Welcome to " << _SCRIPTNAME.substr(idx + 1, _SCRIPTNAME.length()) << "\n\n";
	cout << "What would you like to do?\n";

	//Required
	const string MENU = "1)Create empty file in the current directory.\n2)Read file"
		"\n3)Append to file\n4)Exit\n--> ";
	short selection{0};

	string yourFilePath{};
	fs::path current_path{};
	
	//Program Start
	while (1)
	{
		cout << MENU;
		cin >> selection;

		//Clear cin on fail and re-ask
		if (cin.fail())
		{
			cout << "\n\nYou have to select one of the 4 available options!\n\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			continue;
		}

		//Options
		switch (selection)
		{
		//Create an empty file
		case 1:
			//Ask for filepath
			cout << "Enter your file's path: ";
			std::getline(cin >> std::ws, yourFilePath);

			//Convert to fs::path
			current_path = yourFilePath;

			makeFile(current_path);

			break;
		//Read file contents
		case 2:
			//Ask for filepath
			cout << "Enter your file's path: ";
			std::getline(cin >> std::ws, yourFilePath);

			//Convert to fs::path
			current_path = yourFilePath;

			system(cmd); //cls or clear
			
			//Iterate readFile returned content
			for (string i : readFile(current_path))
			{
				cout << i << std::endl;
			}

			system(cmd);

			cout << "\nPress any key to continue...";
			cin.get();

			break;
		//Write to a filestream
		case 3:
			//Ask for filepath
			cout << "Enter your file's path: ";
			std::getline(cin >> std::ws, yourFilePath);

			//Convert to fs::path
			current_path = yourFilePath;
			
			system(cmd);

			writeFile(current_path);

			break;
		//Exit >:(
		case 4:
			goto EXIT; //Exit the while loop and proceed to return 0;

		//Error, A number other than 1 to 4 is entered...
		default:
			cout << ::_ERROR;
			break;
		}

	}

//Program Finish
EXIT:
	cout << "\n\nBye!\n";
	return 0;
}

void makeFile(fs::path saveIn)
{
	//fs::path to string
	string path{ saveIn.string() };

	if (!path.ends_with(".txt"))
	{
		path = path.append(".txt");
	}

	//Create full path
	string full_path{ cwd + "\\" + path };
	fs::path full_path_check{ full_path };

	//file exists???
	if (isFile(full_path_check))
	{
		std::cerr << "\nFile " << path << " already exists!\n\n";
		return;
	}

	std::ofstream output(full_path);
	output.close();

	cout << "\nSuccesfully created file in " << full_path << "\n\n";
}

stringlist readFile(fs::path filePath)
{
	//Vector that will hold lines 
	stringlist lines{};
	string line{};

	//Not found
	if (!isFile(filePath))
	{
		lines.push_back("File doesn't exist!");
		return lines;
	}

	std::fstream openF(filePath);

	if (isEmpty(openF))
	{
		lines.push_back("File is empty, nothing to read!");

		openF.close();
		return lines;
	}

	//Read lines and save to vector
	while (std::getline(openF, line))
	{
		lines.push_back(line);
	}

	openF.close();
	return lines;

}

void writeFile(fs::path fileToWrite)
{
	string yesNo{}, line{};
	//Usual checks
	if (isFile(fileToWrite))
	{
		cout << "\n*Warning* file already exists! Do you want to append to it? [Y/YES] (default NO) -> ";
		cin >> yesNo;

		//Capitalize user-input
		short idx = 0;
		for (; idx < yesNo.length(); ++idx)
		{
			yesNo[idx] = toupper(yesNo[idx]);
		}

		if (!(yesNo == "Y" || yesNo == "YES"))
		{
			cout << "\nAborted\n\n";
			return;
		}
	}

	std::ofstream input(fileToWrite, std::ios_base::app);

	cout << "\nEnter lines! (type !END! to stop)\n";

	//Write to file with a loop
	int counter{ 1 };
	while (1)
	{
		cout << "Enter line " << counter << ": ";
		getline(cin >> std::ws, line);

		if (line == "!END!")
		{
			input.close();
			break;
		}

		line += "\n";
		input << line;

		counter++;
	}
	
	cout << "\nStopped appending lines\n\n";

	}