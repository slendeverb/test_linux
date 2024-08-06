#include <bits/stdc++.h>

void solve() {
    size_t size = static_cast<size_t>(-1);
    int *buffer=nullptr;
    try{
        buffer=new int[size/4];
    }catch(const std::bad_alloc& e){
        std::cout<<e.what()<<" "<<__func__<<" "<<__LINE__<<"\n";
    }catch(const std::exception& e){
        std::cout<<e.what()<<" "<<__func__<<" "<<__LINE__<<"\n";
    }
    if(buffer!=nullptr){
        std::cout<<static_cast<void*>(buffer)<<"\n";
        delete buffer;
        buffer=nullptr;
    }
}

int main() {
    solve();
}