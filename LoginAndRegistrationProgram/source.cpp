#include <iostream>
#include <fstream> //To work with file streams
#include <string>
#include <vector>
#include <cstdio> //For the remove() function [delete files]

/*THIS PROGRAM IS FOR PURE PRACTICE AND SHOULDN'T EVER BE USED IN A FINISHED PRODUCT OR REAL LIFE SCENARIO*/

using std::cout;
using std::cin;
using std::string;

static string USER{""}; //Global username for home display message

//File is empty? Means no accounts are present!
bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

int Login()
{
	//Lines placeholder
	string current{""}, usern{""}, passwd{""};
	short index{0};
	std::vector<string> credentials; 

	//File check
	std::ifstream file("cred.auth");

	if (!file)
	{
		cout << "\nCouldn't locate file \"cred.auth\" - Perhaps create an account?\n\n";
		goto FAIL;
	}

	if (is_empty(file))
	{
		cout << "\nFile \"cred.auth\" exists but is empty - Please create an account!\n\n";
		file.close();
		goto FAIL;
	}

	// Read lines (username should always be in line 1 and password in line 2), stop accepting lines after 2!
	while (getline (file, current)) 
	{
		if (index == 2)
		{
			break;
		}

		credentials.push_back(current);
	}

	file.close();

	//Start asking for input
	cout << "\nEnter username: ";
	std::getline(cin>>std::ws, usern);

	cout << "Enter password: ";
	std::getline(cin>>std::ws, passwd);

	//Authorization check
	if (usern == credentials[0] && passwd == credentials[1])
	{
		cout << "\nACCESS GRANTED!!!\n\n";
		USER = usern;
		return 1;
	}

FAIL:
	//On fail (we need a return of 1 in order to show "Home();")
	return -1;
}

//Check username and password strength
bool isUsernameGood(string& username)
{
	bool checkU = username.length() < 3 || username.length() > 32;
	return (checkU ? 0 : 1);
}

bool isPasswordGood(string& password)
{
	bool checkP = password.length() < 8 || password.length() > 16;
	return (checkP ? 0 : 1);
}

int Register()
{
	//Credentials
	string usern{""}, passwd{""}, passwdConfirm{""};

	//First we check if file exists, if it does we're gonna delete it because only 1 account is allowed (cuz i'm lazy)
	const char* filename = "cred.auth";

	std::ifstream file("cred.auth");

	if (file)
	{
		file.close(); //Close file or it won't be deleted

		int result = std::remove(filename);

		// check if file has been deleted successfully
  		if (result != 0) 
  		{

    		// print error message
    		cout << "\nFile deletion failed\n\n";
    		return -1;
  		}

  		else 
  		{
    		cout << "\n" << filename << " removed succesfully...\n\n";
  		}

	}

	while (true)
	{

		cout << "\nEnter new username: ";
		std::getline(cin>>std::ws, usern);
		cout << "Enter new password: ";
		std::getline(cin>>std::ws, passwd);
		cout << "Confirm new password: ";
		std::getline(cin>>std::ws, passwdConfirm);

		//Checks
		if (!isUsernameGood(usern))
		{
			cout << "\nNot a valid username, try again!\n\n";
			continue;
		}

		if (!isPasswordGood(passwd))
		{
			cout << "\nPassword too weak, try again!\n\n";
			continue;
		}

		if (passwd != passwdConfirm)
		{
			cout << "\nPasswords do not match, try again!\n\n";
			continue;
		}

		break;
	}

	cout << "\nUsername: " << usern << "\n";
	cout << "Password: " << passwdConfirm << "\n\n";

	//Start appending to file
	std::ofstream saveToFile("cred.auth", std::ios_base::app); //Apparently this extra junk is used to enable "append mode"...
 	saveToFile << usern << "\n";
 	saveToFile << passwdConfirm;
	
	return 1;
}

//If this function is called it means we logged in succesfully
int Home(string& username)
{

	//Capitalize first letter if it isn't already!
	username[0] = std::toupper(username[0]);
	
	cout << "\nWelcome back, " << username << "!\n\n";
	return 0;
}

int main()
{
	//main loop, ask
	const char* MENU = "1)Login\n2)Make an account\n3)BYE\n--> ";
	string option{""};
	
	while (1)
	{
		cout << MENU;
		cin >> option;

		//Login
		if (option == "1")
		{
			//Access granted
			if (Login() == 1)
			{
				Home(USER);
			}

			else
			{
				cout << "\nYou failed to authenticate! Try again!\n\n";
			}
		}

		//Register
		if (option == "2")
		{
			//Account created
			if (Register() == 1)
			{
				cout << "\nRegistration successful! You may want to login now!\n\n";
			}

			else
			{
				cout << "\nRegistration failed! Try again!\n\n";
			}
		}

		//Quit
		if (option == "3") break;

	}

	cout << "\nCya!\n";
	return 0;
}
