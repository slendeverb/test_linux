#include <algorithm>
#include <array>
#include <bit>
#include <boost/locale.hpp>
#include <charconv>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <initializer_list>
#include <iomanip>
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

using namespace std;

int main() {
    std::ifstream in{"./in.txt"};
    clock_t startTime{clock()};

    in.imbue(std::locale{""});
    std::cout << in.getloc().name() << std::endl;
    long double money;
    in >> std::get_money(money);
    std::cout << std::put_money(money) << std::endl;
    std::tm time;
    in >> std::get_time(&time, "%Y-%m-%d %H:%M:%S");
    std::cout << std::put_time(&time, "%Y-%m-%d %H:%M:%S") << std::endl;
    
    clock_t endTime{clock()};
    std::cout << "time cost: " << endTime - startTime << std::endl;
    in.close();
}
