#include <iostream>
#include <fstream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>


int main()
{
    int n {0};
    std::cin>>n;

    double pi = M_PI;
    
    std::vector<double> tabx(n,0);
    std::vector<double> taby(n,0);

    int count = 0;

    std::ofstream myfile;
    myfile.open("fonction.txt");

    while (count < n)
    {
        tabx[count] = (-6*pi) + (count*12*pi)/(n-1);
        if (tabx[count] != 0)
        {
            taby[count] = std::sin(tabx[count])/tabx[count];

        }
        else
        {
            taby[count] = 1;

        }
        myfile<<tabx[count]<<"   "<<taby[count]<<"\n";
        count = count + 1;

    }

    
    myfile.close();



    return 0;
}
