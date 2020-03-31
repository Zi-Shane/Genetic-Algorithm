#include <iostream>
#include <math.h>
using namespace std;

#define SIZE 8
#define NUM 4
int gen_parent[NUM][SIZE];
int gen_child[NUM][SIZE];
int A_decimal[NUM];

// convert binary to decimal
int bin_to_dec(int *p)
{
    int decimal = 0;
    for (int i = SIZE - 1; i >= 0; i--, p++) {
        if (*p) {
            decimal += *p << i;
        }
    }

    return decimal;
}

// decimal
void cal_decimal()
{
    for (int i = 0; i < NUM; i++) {
        A_decimal[i] = bin_to_dec(gen_parent[i]);
    }
}

// initialize A[NUM][SIZE]
void init()
{
    for (int i = 0; i < NUM; i++){
        for (int j = 0; j < SIZE; j++){
            gen_parent[i][j] = rand() % 2;
        }
    }
    cal_decimal();
}

// printout binary
void show_one(int *num) 
{
    for (int i = 0; i < SIZE; i++) {
        cout << *num++;
    }
    cout << endl;
}

// printout all binaries
void show_all_parent()
{
    show_one(gen_parent[0]);
    show_one(gen_parent[1]);
    show_one(gen_parent[2]);
    show_one(gen_parent[3]);
}
void show_all_child()
{
    show_one(gen_child[0]);
    show_one(gen_child[1]);
    show_one(gen_child[2]);
    show_one(gen_child[3]);
}

void find_smallest()
{
    int temp = A_decimal[0], first_min = 0, second_min = 0;
    for (int i = 0; i < NUM; i++) {
        if (temp > A_decimal[i]) {
            temp = A_decimal[i];
            first_min = i;
        }
    }
    temp = A_decimal[0];
    for (int i = 0; i < NUM; i++) {
        if (temp > A_decimal[i] && i != first_min) {
            temp = A_decimal[i];
            second_min = i;
        }
    }
    cout << "first_smallest:  ";show_one(gen_parent[first_min]);
    cout << "second_smallest: ";show_one(gen_parent[second_min]);
    cout << "============================" << endl;

    for (int i = 0; i < SIZE; i++)
    {
        gen_child[0][i] = gen_parent[first_min][i];
        gen_child[1][i] = gen_parent[second_min][i];
    }
    
}

void one_point_crossover()
{
    find_smallest();
    for (int i = 0; i < SIZE; i++)
    {
        gen_child[2][i] = gen_child[0][i];
        gen_child[3][i] = gen_child[1][i];
        if (i > 3) 
        {
            gen_child[2][i] = gen_child[1][i];
            gen_child[3][i] = gen_child[0][i];
        }
    }
}

int main(int argc, const char** argv) 
{
    init();
    show_all_parent();
    one_point_crossover();
    show_all_child();

    return 0;
}


