#include <iostream>
#include <math.h>
using namespace std;

#define ITEM 10
#define BAG 27.5
#define NUM 8

int weight[ITEM];
int value[ITEM];
int parent[NUM][ITEM];
int child[NUM][ITEM];

void init()
{
    // weight and value
    for (int i = 0; i < ITEM; i++)
    {
        weight[i] = i + 1;
        value[i] = (i + 1) + 5;
    }
    // first generation
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < ITEM; j++) 
        {
            parent[i][j] = rand() % 2;
        }
    }
}

// fitness
void fitness()
{
    
}
// crossover
// mutation

int bagpack_problem()
{
    init();
}

int main(int argc, const char** argv) 
{
    int answer = bagpack_problem();
    cout << answer << endl;
    return 0;
}


