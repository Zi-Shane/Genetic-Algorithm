#include <iostream>
#include <math.h>
using namespace std;

#define SIZE 8
#define NUM 4
int gen_parent[NUM][SIZE];
int gen_child[NUM][SIZE];
int parent_decimal[NUM];
int child_decimal[NUM];

// function for convert binary to decimal
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

// parents' decimal
void cal_decimal_parent()
{
    for (int i = 0; i < NUM; i++) {
        parent_decimal[i] = bin_to_dec(gen_parent[i]);
    }
}
// children's decimal
void cal_decimal_child()
{
    for (int i = 0; i < NUM; i++) {
        child_decimal[i] = bin_to_dec(gen_child[i]);
    }
}

// initialize gen_parent[NUM][SIZE]
void init()
{
    for (int i = 0; i < NUM; i++){
        for (int j = 0; j < SIZE; j++){
            gen_parent[i][j] = rand() % 2;
        }
    }
    cal_decimal_parent();
}

// printout binary
void show_one(int *num) 
{
    for (int i = 0; i < SIZE; i++) {
        cout << *num++;
    }
    cout << endl;
}
void show_all_parent()
{
    for (int i = 0; i < NUM; i++) {
        show_one(gen_parent[i]);
    }
}
void show_all_child()
{
    for (int i = 0; i < NUM; i++) {
        show_one(gen_child[i]);
    }
}

// set childern to next generation's parent
void new_parent()
{
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < SIZE; j++) {
            gen_parent[i][j] = gen_child[i][j];
        }
    }
    cal_decimal_parent();
}

// find smallest number and secondary smallest number
void find_smallest()
{
    // find smallest number
    int temp = parent_decimal[0], first_min = 0, second_min = 0;
    for (int i = 0; i < NUM; i++) {
        if (temp > parent_decimal[i]) {
            temp = parent_decimal[i];
            first_min = i;
        }
    }
    temp = parent_decimal[0];
    // find secondary smallest number
    for (int i = 0; i < NUM; i++) {
        if (temp > parent_decimal[i] && i != first_min) {
            temp = parent_decimal[i];
            second_min = i;
        }
    }
    // cout << "first_smallest:  ";show_one(gen_parent[first_min]);
    // cout << "second_smallest: ";show_one(gen_parent[second_min]);
    // cout << "============================" << endl;
    
    // set smallest number and secondary smallest number to parent of next generation
    for (int i = 0; i < SIZE; i++)
    {
        gen_child[0][i] = gen_parent[first_min][i];
        gen_child[1][i] = gen_parent[second_min][i];
    }
}

// randonly change one bit
void mutation()
{
    for (int i = 0; i < NUM; i++)
    {
        int p = rand() % SIZE;
        if (gen_child[i][p]) {
            gen_child[i][p] = 0;
        } else {
            gen_child[i][p] = 1;
        }
    }
}

void one_point_crossover()
{
    find_smallest();
    // crossover smallest number and secondary smallest number
    for (int i = 0; i < SIZE; i++)
    {
        gen_child[2][i] = gen_child[0][i];
        gen_child[3][i] = gen_child[1][i];
        if (i > 3) { // cross point
            gen_child[2][i] = gen_child[1][i];
            gen_child[3][i] = gen_child[0][i];
        }
    }
    cal_decimal_child();
    // if smallest number and secondary smallest number are same, do mutaion
    if (child_decimal[0] == child_decimal[1]) {
        mutation();
        cal_decimal_child();
    }
    // setting childrend to parents of next generation
    new_parent();
}

// the function you want to solve
int func(int n)
{
    return pow(n, 2) - 64;
}

int main(int argc, const char** argv) 
{
    init();
    for (int i = 0; i < 100; i++)
    {
        show_all_parent();
        cout << "========================" << endl;
        one_point_crossover();
        // show_all_child();
        for (int j = 0; j < NUM; j++)
        {
            if (func(child_decimal[j]) == 0)
            {
                cout << "find answer, at generation " << i+1 << endl;
                cout << "answer is: " << child_decimal[j] << ", ";
                cout << "binary: ";
                show_one(gen_child[j]);
                // show_all_child();
                return 0;
            }
        }
    }
    return 0;
}


