#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream myfile;
    myfile.open("test-tp0.txt");
    std::string line;

    if (myfile.is_open())
    {
        std::cout<<"ooook";
    }
    
    while (std::getline(myfile,line))
    {
        std::cout<<line<<"\n";
    }
    myfile.close();

    return 0;
}
