#include "DoubleStr.h";

using std::cout;
using std::endl;

std::vector<double> rVect();

int main()
{
    //Initialize random seed
    srand(time(NULL));


    std::vector<double> testNumbers{ 25.87, 1.777, 13.85, 222.9432};
    DoubleDigits* worker = new DoubleDigits();

    auto update_nums = worker->vectorToStr(testNumbers);

    static short index = 0;

    for (; index != testNumbers.size(); ++index)
    {
        cout << "The decimal part of " << testNumbers[index] << " is " << update_nums[index] << '\n';
    }

    return 0;
}
