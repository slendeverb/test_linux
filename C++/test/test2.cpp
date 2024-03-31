#include <cstdarg>
#include <boost/locale.hpp>
#include <iomanip>
#include <concepts>
#include <cstdio>
#include <ctime>
#include <bit>
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <numbers>
#include <optional>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
using namespace std;

int solve()
{
    std::cin.imbue(std::locale{""});
    std::cout<<std::cin.getloc().name()<<std::endl;
    long double money;
    std::cin>>std::get_money(money);
    std::cout << std::put_money(money) << std::endl;
    std::tm time;
    std::cin>>std::get_time(&time,"%Y-%m-%d %H:%M:%S");
    std::cout<<std::put_time(&time,"%Y-%m-%d %H:%M:%S")<<std::endl;
}

int main()
{
    freopen("./in.txt", "r", stdin);
    freopen("./out.txt", "w", stdout);
    freopen("./err.txt", "w", stderr);
    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "time cost: " << endTime - startTime << std::endl;
    return 0;
}
