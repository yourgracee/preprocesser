#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream out("a.txt");
    for (int i = 0;i<=64;i++)
    {
    out <<   i << ", " ;
    }
    out.close();
    return 0;
}