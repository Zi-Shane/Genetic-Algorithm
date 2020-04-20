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
    int w = 1, count = 0;
    for (int i = 0; i < CHROMOSOME; i++)
    {
        // 10 items
        if (CHROMOSOME == 10)
        {
            weight[i] = i + 1;       // [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
            value[i] = (i + 1) + 5;  // [6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
        }

        // 100 items
        if (CHROMOSOME == 100)
        {
            if (count < 10) {
                count++;
            } else {
                count = 0;
                w += 1;
            }
            weight[i] = w;             // 10 * ([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
            value[i] = weight[i] + 5;  // 10 * ([6, 7, 8, 9, 10, 11, 12, 13, 14, 15])
        }
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

// copy children to parent
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

// Fitness => items' total weight
// if taken(chromosome is 1)
void cal_fitness()
{
    int current_fitness;
    int current_weight;

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        current_fitness = 0;
        current_weight = 0;

        for (int j = 0; j < CHROMOSOME; j++) 
        {
            current_fitness = current_fitness + value[j] * gen_old[i][j];  // total weight
            current_weight = current_weight + weight[j] * gen_old[i][j];   // total value
        }

        // when overweight, fitness = 0
        if (current_weight > BAG_LIMITAION) {
            fitness[i] = 0;
        } else {
            fitness[i] = current_fitness;
        }

        // cout << "weight: " << current_weight << ", fitness: " << fitness[i] << endl;
    }
}

// find best fitness at each generation
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

// select 'n' items to new generation
void selection(int n)
{
    int selected;

    for (int i = 0; i < n; i++)
    {
        selected = Roulette_Wheel_Selection();
        for (int j = 0; j < CHROMOSOME; j++) {
            gen_new[i][j] = gen_old[selected][j];  // copy to new generation
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
                gen_new[i+start][j] = gen_new[i][j];  // copy
            } else if (j > c_point && i == 0) {
                gen_new[i+start][j] = gen_new[start - 1][j];  // change with last
            } else {
                gen_new[i+start][j] = gen_new[i-1][j];  // change with previous
            }
        }
    }
}
void uniform_crossover(int start)
{
    int mask[CHROMOSOME];
    int temp;
    for (int i = 0; i < CHROMOSOME; i++) {
        mask[i] = rand() % 2;
    }
    
    for (int i = 0; i < start; i++) {
        for (int j = 0; j < CHROMOSOME; j++)
        {
            if (!mask[j]) {
                gen_new[i+start][j] = gen_new[i][j];  //copy
            } else if (mask[j] && i == 0) {
                gen_new[i+start][j] = gen_new[start - 1][j];  // change with last
            } else {
                gen_new[i+start][j] = gen_new[i-1][j];  // change with previous
            }
        }
    }
}

void crossover()
{
    int children_start_index = POPULATION_SIZE / 2;  // start index for crossover result in gen_new[][]
    int cross_point = CHROMOSOME / 2;  // for single point crossover
    single_point_crossover(children_start_index, cross_point);
    // uniform_crossover(children_start_index);
}

// Mutation
bool check(int* p, int n, int new_num)
{
    for (int i = 0; i < n; i++){
        if (p[i] == new_num) {
            return true;
        }
    }
    return false;
}
void n_point_mutation(int* population_p, int n)
{
    int mutation_points[n] = {0};
    int temp;

    for (int i = 0; i < n; i++)
    {
        do { 
            temp = rand() % CHROMOSOME;
        } while (check(mutation_points, n, temp));
    }

    for (int i = 0; i < n; i++) {
        population_p[mutation_points[i]] = 1 - population_p[mutation_points[i]];
    }
}
void two_point_mutation(int* population_p)
{
    int p, q;  // randomly choose two mutation point
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
void uniform_mutation(int* population_p)
{
    int mask[CHROMOSOME];  // mutation by mask
    for (int i = 0; i < CHROMOSOME; i++) {
        mask[i] = rand() % 2;
    }
    
    for (int i = 0; i < CHROMOSOME; i++) {
        if (mask[i]) {
            population_p[i] = 1 - population_p[i];
        }
    }
}

void mutation()
{
    // int start = POPULATION_SIZE / 2;  // mutation only children population
    int start = 0;  // mutation all population
    double threshold = 0.8;
    double rndNumber;
    for (int i = start; i < POPULATION_SIZE; i++)
    {
        rndNumber = rand() / (double) RAND_MAX;
        // rndNumber = (double)(rand() % 100) / 100;
        if (rndNumber > threshold) {
            // uniform_mutation(gen_new[i]);
            // n_point_mutation(gen_new[i], 30);
            two_point_mutation(gen_new[i]);
        }
    }
}

int bagpack_problem()
{
    int count = 0;  // maximum rounds
    int best = 0; // final best value
    int best_round = 0;
    int temp = 0, temp_count = 0;  // count best in same value

    init();
    // show_all_parent();
    while (count < 10000 && temp_count < 500)
    {
        selection(POPULATION_SIZE / 2);
        crossover();
        mutation();
        new_to_old();

        if (find_best() > best) {
            best = find_best();
            best_round = count + 1;
        }

        if (temp == best) {
            temp_count++;
        } else {
            temp = best;
            // cout << temp_count << endl;
            temp_count = 0;
        }

        count++;
    }

    cout << "best round: " << best_round << endl;
    return best;
}

int main(int argc, const char** argv) 
{
    int answer = bagpack_problem();
    cout << "best answer: " << answer << endl;
    return 0;
}


