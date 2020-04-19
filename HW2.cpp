#include <iostream>
#include <math.h>
using namespace std;

#define CHROMOSOME 10  // # items
#define BAG_LIMITAION 27.5
#define POPULATION_SIZE 8

int weight[CHROMOSOME];
int value[CHROMOSOME];
int fitness[POPULATION_SIZE];
int gen_old[POPULATION_SIZE][CHROMOSOME];
int gen_new[POPULATION_SIZE][CHROMOSOME];

void init()
{
    // weight and value
    for (int i = 0; i < CHROMOSOME; i++)
    {
        weight[i] = i + 1;
        value[i] = (i + 1) + 5;
    }
    // first generation
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < CHROMOSOME; j++)
        {
            gen_old[i][j] = rand() % 2;
        }
    }
}

// Fitness => taken items' total weight
// if taken(chromosome is 1)
void cal_fitness()
{
    int current_fitness;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        current_fitness = 0;

        for (int j = 0; j < CHROMOSOME; j++) {
            current_fitness = weight[j] * gen_old[i][j];
        }

        if (current_fitness > BAG_LIMITAION) {
            fitness[i] = 0;
        } else {
            fitness[i] = current_fitness;
        }
    }
}

// Selection
int Roulette_Wheel_Selection()
{
    double rndNumber = rand() / (double) RAND_MAX;
    double offset = 0.0;
    int pick = 0;
    
    int sum = 0;
    cal_fitness();
    for (int i = 0; i < POPULATION_SIZE; i++) {
        sum += fitness[i];
    }

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        offset += (double)fitness[i] / sum;
        if (rndNumber < offset)
        {
            pick = i;
            break;
        }
    }
    // printf("Chromosome %d selected.\n", pick);
    return pick;
}
// select n to new generation
void selection(int n)
{
    int selected;
    for (int i = 0; i < n; i++) {
        selected = Roulette_Wheel_Selection();
        for (int j = 0; j < CHROMOSOME; j++)
        {
            gen_new[i][j] = gen_old[selected][j];
        }
    }
}

// Crossover

// mutation

// debug
void show_one(int *num) 
{
    for (int i = 0; i < CHROMOSOME; i++) {
        cout << *num++;
    }
    cout << endl;
}
void show_all_parent()
{
    for (int i = 0; i < POPULATION_SIZE; i++) {
        show_one(gen_old[i]);
    }
}
void show_all_child()
{
    for (int i = 0; i < POPULATION_SIZE; i++) {
        show_one(gen_new[i]);
    }
}

int bagpack_problem()
{
    init();
    // show_all_parent();
    selection(POPULATION_SIZE / 2);
    // show_all_child();

    return 0;
}

int main(int argc, const char** argv) 
{
    int answer = bagpack_problem();
    // cout << answer << endl;
    return 0;
}


