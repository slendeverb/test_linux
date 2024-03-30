#include <stdlib.h>
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

void solve(){
    std::cout<<std::cout.getloc().name()<<std::endl;
    std::cout.imbue(std::locale{""});
    std::cout<<std::cout.getloc().name()<<std::endl;
}

int main() {
    freopen("./in.txt","r",stdin);
    freopen("./out.txt","w",stdout);
    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << endTime - startTime << std::endl;
    return 0;
}
