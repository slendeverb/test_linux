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
    std::cout << std::cin.getloc().name() << std::endl;
    long double money;
    std::cin >> std::get_money(money);
    std::cout << std::put_money(money) << std::endl;
    std::tm time;
    std::cin >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    std::cout << std::put_time(&time, "%Y-%m-%d %H:%M:%S") << std::endl;
}

int main()
{
    // std::ifstream in{"./in.txt"};
    // std::streambuf* oldIn{std::cin.rdbuf(in.rdbuf())};
    // std::ofstream out{"./out.txt"};
    // std::streambuf* oldOut{std::cout.rdbuf(out.rdbuf())};
    // std::ofstream err{"./err.txt"};
    // std::streambuf* oldErr{std::cerr.rdbuf(err.rdbuf())};
    // std::streambuf* oldLog{std::clog.rdbuf(err.rdbuf())};
    
    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "time cost: " << endTime - startTime << std::endl;

    // in.close();
    // std::cin.rdbuf(oldIn);
    // out.close();
    // std::cout.rdbuf(oldOut);
    // err.close();
    // std::cerr.rdbuf(oldErr);
    // std::clog.rdbuf(oldLog);
    return 0;
}
