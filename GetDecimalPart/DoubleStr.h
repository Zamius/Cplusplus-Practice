#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#pragma once

class DoubleDigits
{
private:
	std::vector<double> _numbers{};

	std::string doubleToString(double& num)
	{
		//Convert to string
		std::string element{ std::to_string(num) };

		//Remove trailing zeros
		element.erase(element.find_last_not_of('0') + 1, std::string::npos);
		element.erase(element.find_last_not_of('.') + 1, std::string::npos);

		return element;
	}

	std::string getDecimalPart(std::string number)
	{
		size_t size = number.length();
		return number.substr(number.find('.'), size);
	}
public:
//	//Pretty useless constructor
	DoubleDigits()
	{}

	std::vector<std::string> vectorToStr(std::vector<double>& numbers)
	{
		std::vector<std::string> numbers_str{};
		
		short pos = 0;
		
		for (; pos != numbers.size(); ++pos)
		{
			numbers_str.push_back(getDecimalPart(doubleToString(numbers[pos])));
		}

		return numbers_str;
	}

};