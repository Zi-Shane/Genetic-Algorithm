#include <iostream>
#include <math.h>
using namespace std;

#define SIZE 8
#define NUM 4
int gen_parent[NUM][SIZE];
int gen_child[NUM][SIZE];
int parent_decimal[NUM];
int child_decimal[NUM];
int best = 256;

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

// the function you want to solve
int func(int n)
{
    // return pow(n, 3) - 216;
    return pow(n, 2) - 225;
    // return n - 177;
    // return n - 255;
}

// find smallest number and secondary small number
void find_smallest()
{
    // find smallest number
    int temp_abs = abs(func(parent_decimal[0])), first_min = 0, second_min = 0;
    int answer_abs;
    for (int i = 0; i < NUM; i++) {
        answer_abs = abs(func(parent_decimal[i]));
        if (temp_abs > answer_abs) {
            temp_abs = answer_abs;
            first_min = i;
        }
    }
    temp_abs = func(parent_decimal[0]);
    // find secondary small number
    for (int i = 0; i < NUM; i++) {
        answer_abs = abs(func(parent_decimal[i]));
        if (temp_abs > answer_abs && i != first_min) {
            temp_abs = answer_abs;
            second_min = i;
        }
    }
    cout << "first_smallest:  ";show_one(gen_parent[first_min]);
    cout << "second_smallest: ";show_one(gen_parent[second_min]);
    cout << "============================" << endl;
    
    // set smallest number and secondary small number to parent of next generation
    for (int i = 0; i < SIZE; i++)
    {
        gen_child[0][i] = gen_parent[first_min][i];
        gen_child[1][i] = gen_parent[second_min][i];
    }
}

// randomly change one bit
void single_point_mutation()
{
    int p;
    for (int i = 0; i < NUM; i++)
    {
        p = rand() % SIZE;
        if (gen_child[i][p]) {
            gen_child[i][p] = 0;
        } else {
            gen_child[i][p] = 1;
        }
    }
}
void two_point_mutation()
{
    int p, q;
    for (int i = 0; i < NUM; i++)
    {
        p = rand() % SIZE;
        if (gen_child[i][p]) {
            gen_child[i][p] = 0;
        } else {
            gen_child[i][p] = 1;
        }

        do {
            q = rand() % SIZE;
        } while (p == q);
        if (gen_child[i][q]) {
            gen_child[i][q] = 0;
        } else {
            gen_child[i][q] = 1;
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
        if (i > 5) { // cross point
            gen_child[2][i] = gen_child[1][i];
            gen_child[3][i] = gen_child[0][i];
        }
    }
    cal_decimal_child();
    // setting childrend to parents of next generation
    new_parent();
}

void multi_point_crossover()
{
    find_smallest();
    // crossover smallest number and secondary smallest number
    for (int i = 0; i < SIZE; i++)
    {
        if (i < 2) {
            gen_child[2][i] = gen_child[0][i];
            gen_child[3][i] = gen_child[1][i];
        }
        if (i >= 2 && i <= 3) {
            gen_child[2][i] = gen_child[1][i];
            gen_child[3][i] = gen_child[0][i];
        }
        gen_child[2][i] = gen_child[0][i];
        gen_child[3][i] = gen_child[1][i];
        if (i > 5) { // cross point
            gen_child[2][i] = gen_child[1][i];
            gen_child[3][i] = gen_child[0][i];
        }
    }
    cal_decimal_child();
    // setting childrend to parents of next generation
    new_parent();
}

int algorithm(int iteration)
{
    int func_output;
    int mutaion_rate = 0.9;
    init();
    cout << "parent" << endl;
    show_all_parent();
    for (int i = 0; i < iteration; i++)
    {
        // crossover
        one_point_crossover();
        // multi_point_crossover();

        // mutation
        // if smallest number and secondary smallest number are same, do mutaion
        if (child_decimal[0] == child_decimal[1] || (rand() % 100) / 100 > mutaion_rate) {
            cout << "mutaion" << endl;
            // single_point_mutation();
            two_point_mutation();
            new_parent();
        }

        // printout each generation
        cout << "gen" << i + 1 << endl;
        show_all_parent();
        cout << "========================" << endl;

        // find answers
        for (int j = 0; j < NUM; j++)
        {
            func_output = func(parent_decimal[j]);
            if (func_output == 0)  // found global best answer
            {
                cout << "find answer, at generation " << i+1 << endl;
                cout << "answer is: " << parent_decimal[j] << ", ";
                cout << "binary: ";
                show_one(gen_parent[j]);
                return 0;
            } else {  // found best answer
                if (abs(func_output) < abs(func(best))) {
                    best = parent_decimal[j];
                }
            }
        }
    }
    cout << "not found, " << "best is: " << best << endl;
    return 1;
}

int main(int argc, const char** argv) 
{
    // genetic algorithm run 200 iterations
    algorithm(200);
    return 0;
}


