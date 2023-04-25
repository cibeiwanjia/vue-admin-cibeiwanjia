#include <iostream>

using namespace std;

int main()
{
    int i, j, s = 0;
    for (int i = 1; i <= 10; i++)
    {
        s += i * i * i;
    }
    cout << s << endl;

    return 0;
}