#include <iostream>
#include <math.h>
using namespace std;

#define CHROMOSOME 10  // # items
#define BAG_LIMITAION 27.5
#define POPULATION_SIZE 8

int weight[CHROMOSOME]; // [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
int value[CHROMOSOME]; // [6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
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
        // cout << i << ":" << weight[i] << ", " << value[i] << endl;
    }
    // first generation
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < CHROMOSOME; j++)
        {
            gen_old[i][j] = rand() % 2;
        }
    }
}

void new_to_old()
{
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < CHROMOSOME; j++)
        {
            gen_old[i][j] = gen_new[i][j];
            gen_new[i][j] = 0;
        }
    }
}

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

// Fitness => taken items' total weight
// if taken(chromosome is 1)
void cal_fitness()
{
    int current_fitness;
    int current_weight;

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        current_fitness = 0;
        current_weight = 0;

        for (int j = 0; j < CHROMOSOME; j++) {
            current_fitness = current_fitness + value[j] * gen_old[i][j];
            current_weight = current_weight + weight[j] * gen_old[i][j];
        }

        if (current_weight > BAG_LIMITAION) {
            fitness[i] = 0;
        } else {
            fitness[i] = current_fitness;
        }
        // cout << current_weight << ": " << fitness[i] << endl;
    }
}

int find_best()
{
    int best = 0;
    cal_fitness();
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (fitness[i] > best) {
            best = fitness[i];
        }
    }
    
    return best;
}

// Selection
int Roulette_Wheel_Selection()
{
    double rndNumber = rand() / (double) RAND_MAX;
    // double rndNumber = (double)(rand() % 100) / 100;
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

    for (int i = 0; i < n; i++)
    {
        selected = Roulette_Wheel_Selection();
        for (int j = 0; j < CHROMOSOME; j++) {
            gen_new[i][j] = gen_old[selected][j];
        }
    }
}

// Crossover
void single_point_crossover(int start, int c_point)
{
    for (int i = 0; i < start; i++) {
        for (int j = 0; j < CHROMOSOME; j++)
        {
            if (j < c_point) {
                gen_new[i+start][j] = gen_new[i][j];
            } else if (j > c_point && i == 0) {
                gen_new[i+start][j] = gen_new[start - 1][j];
            } else {
                gen_new[i+start][j] = gen_new[i-1][j];
            }
        }
    }
}

void crossover()
{
    int children_start_index = POPULATION_SIZE / 2;
    int cross_point = CHROMOSOME / 2;
    single_point_crossover(children_start_index, cross_point);
}

// Mutation
void two_point_mutation(int* population_p)
{
    int p, q;

    p = rand() % CHROMOSOME;
    if (population_p[p]) {
        population_p[p] = 0;
    } else {
        population_p[p] = 1;
    }

    do {
        q = rand() % CHROMOSOME;
    } while (p == q);
    if (population_p[q]) {
        population_p[q] = 0;
    } else {
        population_p[q] = 1;
    }
}

void mutation()
{
    // int start = POPULATION_SIZE / 2;
    int start = 0;
    double threshold = 0.9;
    double rndNumber;
    for (int i = start; i < POPULATION_SIZE; i++)
    {
        double rndNumber = rand() / (double) RAND_MAX;
        // rndNumber = (double)(rand() % 100) / 100;
        if (rndNumber > threshold) {
            two_point_mutation(gen_new[i]);
        }
    }
}

int bagpack_problem()
{
    int count = 0;
    int best = 0;

    init();
    while (count < 100)
    {
        selection(POPULATION_SIZE / 2);
        crossover();
        mutation();
        new_to_old();
        if (find_best() > best) {
            best = find_best();
        }
        count++;
    }
    return best;
}

int main(int argc, const char** argv) 
{
    int answer = bagpack_problem();
    cout << answer << endl;
    return 0;
}


