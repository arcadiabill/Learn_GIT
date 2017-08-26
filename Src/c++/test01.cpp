#include <iostream>
class Simple
{
private:
    int variable{ 0 };

public:
    Simple()
    {
        std::cout << "Constructed" << std::endl;
    }
    
    ~Simple()
    {
        std::cout << "Destroyed" << std::endl;
    }
};

int main(int argc, char* argv[])
{
    Simple* pSimple = new Simple();
    delete pSimple;
    pSimple = nullptr;
    return 0;
}
