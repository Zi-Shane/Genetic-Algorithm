#include <iostream>
using namespace std;

#define SIZE 8
#define NUM 4
bool A[NUM][SIZE];

void init() 
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            A[i][j] = rand() % 2;
        }
    }
}

void show_one(bool *num) 
{
    for (int i = 0; i < SIZE; i++) {
        cout << *num++;
    }
    cout << endl;
}

void show_all()
{
    show_one(A[0]);
    show_one(A[1]);
    show_one(A[2]);
    show_one(A[3]);
}

int main(int argc, const char** argv) 
{
    init();
    show_all();


    return 0;
}


