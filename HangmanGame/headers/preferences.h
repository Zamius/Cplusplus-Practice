//Preprocessed libraries includes

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::ws;
using std::size_t;
using std::vector;


typedef std::string str;

namespace def 
{


	//Ready-to-use for loop for array of any type
	template <typename A>
	void aloop(A param, size_t size)
	{

		for (int idx = 0; idx != size; idx++)
		{
			cout << param[idx] << '\n';
		}

	}

	//Ready-to-use for loop for vector of any type
	template <typename B>
	void vloop(vector<B> param) 
	{
		
		for (auto it = param.begin(); it != param.end(); it++)
		{
			cout << *it << '\n';
		}
	}

	//Ready-to-use foreach loop for array of any type
	template <typename C, size_t SIZE>
	void forarr(const C (&param)[SIZE])
	{
		for (auto i : param)
		{
			cout << i << '\n';
		}
	}

	//Ready-to-use foreach loop for vector of any type
	template <typename D>
	void forvect(vector<D> param)
	{
		for (auto i : param)
		{
			cout << i << '\n';
		}
	}

	void coutprecision(double number, int precision)
	{
		cout << std::setprecision(precision+1) << number;
	}
}

namespace ranges
{

	vector<int> intrange(int limit1, int limit2)
	{
		vector<int> vc(limit2);
		std::iota(vc.begin(), vc.end(), 1);

		return vc;
	}
}
