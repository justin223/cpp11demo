
#include <iostream>
#include <tuple>
#include<string>

using namespace std;

int main()
{
    tuple<bool, bool, string, string> names{ false, false, "string", "" };
    std::get<1>(names) = true;
    std::get<3>(names) = "tuple";

    decltype(std::get<1>(names)) a1 = std::get<1>(names);
    decltype(std::get<3>(names)) a4 = std::get<3>(names);
    cout << boolalpha << a1 << "\t" << a4 << endl;

    std::tie(a1, std::ignore, a4, std::ignore) = names;
    cout << boolalpha << a1 << "\t" << a4 << endl;
    
    return 0;
}