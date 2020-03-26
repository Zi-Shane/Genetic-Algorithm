#include <iostream>
#include <math.h>
using namespace std;

#define SIZE 8
#define NUM 4
bool A[NUM][SIZE];

void init() 
{
    for (int i = 0; i < NUM; i++){
        for (int j = 0; j < SIZE; j++){
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

int bin_to_dec(bool *p)
{
    int decimal = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (*p++) {
            decimal += pow(2.0, i);
        }
    }
    
    return decimal;
}

int main(int argc, const char** argv) 
{
    init();
    show_all();
    cout << A[0];


    return 0;
}


