#include <iostream>
#include <filesystem>
#include <string>

/// <summary>
/// USING ISO C++20 Standard (/std:c++20)
/// </summary>

namespace fs = std::filesystem;

using std::cout, std::endl, std::string;

int main()
{
	const fs::path VOLUME = "C://"; //change accordingly
	const string EXT = ".exe"; //We'll be looking for executables

	int counter{ 0 }, r_errors{ 0 };

	fs::recursive_directory_iterator path(VOLUME, fs::directory_options::skip_permission_denied);
	
	for (const auto& e : path)
	{
		try
		{
			if (fs::is_regular_file(e.path()) && e.path().extension() == EXT)
			{
				counter++;
				cout << e.path().filename().string() << endl;
			}
		}

		//Important! Although we're using fs::directory_options::skip_permission_denied there are still other errors that might occur.
		catch (fs::filesystem_error& e)
		{
			r_errors++;
			continue;
		}
	}

	cout << "\n\nFound " << counter << " " << EXT << " files!" << endl;
	cout << "Could not show: " << r_errors << " files!" << endl;
	return 0;
}
