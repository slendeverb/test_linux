#include <bits/stdc++.h>

struct TestA{
    TestA(){
        std::cout<<"The constructor of TestA\n";
    }
    ~TestA(){
        std::cout<<"The destructor of TestA\n";
    }
    [[nodiscard]] int getA(){
        return this->numA;
    }
private:
    int numA=0;
};

int main(int argc, char** argv) {
    TestA* testA_ptr=new TestA;
    auto x=testA_ptr->getA();

    std::cout<<"The first numA is: "<<x<<std::endl;
    delete testA_ptr;

    void* ptrB=operator new(sizeof(TestA));
    TestA* ptrC=new (ptrB) TestA;
    auto y=ptrC->getA();
    std::cout<<"The second numA is: "<<y<<std::endl;
    ptrC->~TestA();    
    operator delete(ptrB);
}