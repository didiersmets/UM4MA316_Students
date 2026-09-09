#include <iostream>
#include <vector>

int main()
{

    int n {0};

    int count{0};

    std::cin>> n;
    std::vector<int> tableau1(n,0);
    tableau1[0] = 1;

    while (count < n)
    {   
        count = count + 1;

        
        int i{0};
        std::vector<int> tableau2(n,0);


        while (i < count)
        {   
            if (i >0)
            { 
                tableau2[i] = tableau1[i-1] + tableau1[i];
            }
            else
            {
                tableau2[i] = 1;
            }
            std::cout<< tableau2[i] <<' ';

            i = i + 1;

        
        }

    std::cout<<"\n";
    tableau1 = tableau2;
    }



    return 0;
}
