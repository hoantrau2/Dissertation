#define _CRT_SECURE_NO_WARNINGS

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.141592

// sphere #1
#define STRATEGY 1 // function number
#define D 3        // D:Dimention
#define NP 5       // NP:Number of population
#define F 0.9      // F:controls the amplification of the differential variation
#define CR 0.1     // CR:Crossover constant
#define VTR 0.000001      // VTR:Value to reach
#define NAME "sphere.csv" // output file name
#define GEN_MAX 200       // generation max number

// Rosenbrock's saddle #2
/*
#define STRATEGY 2  // function number
#define D 2    //D:Dimention
#define NP 10   // NP:Number of Population
#define F 0.9// F:coctrols the amplification of the differential variation
#define CR 0.9   // CR:Crossover constant
#define VTR 0.000001  // VTR:Value to reach
#define NAME "Rosenbrock.csv"  // output file name
#define GEN_MAX 200  // generation max number
*/

// Griewangk's #7
/*
#define STRATEGY 7  // function number
#define D 10    //D:Dimention
#define NP 25   // NP:Number of Population
#define F 0.5// F:coctrols the amplification of the differential variation
#define CR 0.2   // CR:Crossover constant
#define VTR 0.000001  // VTR:Value to reach
#define NAME "Griewangk.csv"  // output file name
#define GEN_MAX 1000  // generation max number
*/

// Rastrigin's #13
/*
#define STRATEGY 13  // function number
#define D 20    //D:Dimention
#define NP 25   // NP:Number of Population
#define F 0.5// Fccontrols the amplification of the differential variation
#define CR 0.0   // CR:crossover constant
#define VTR 0.9  // VTR:Value to reach
#define NAME "Rastrigin.csv"  // output file name
#define GEN_MAX 1000  // generation max number
*/

// Griewangk's #14
/*
#define STRATEGY 14                  // function number
#define D 20                         //D:Dimention
#define NP 20                        // NP:Number of Population
#define F 0.5                        // F:ccntrols the amplification of the
differential variation #define CR 0.1                       // CRCcrossover
constant #define VTR 0.001                    // VTR:Value to reach #define NAME
"Griewangk_general.csv" // output file name #define GEN_MAX 1000 // generation
max number
*/

double evaluate(double *trial) {
  double value = 0.0;
  double sigma = 0.0, pi = 1.0;

  switch (STRATEGY) {
  // sphere
  case 1:
    for (int k = 0; k < D; k++)
      value += pow(trial[k], 2.0);
    break;
  // Rosenbrock's saddle
  case 2:
    value = 100 * pow(pow(trial[0], 2) - trial[1], 2.0) + pow(1 - trial[0], 2);
    break;
  // Griewangk's
  case 7:
    for (int k = 0; k < D; k++) {
      sigma += pow(trial[k], 2) / 4000.0;
      pi *= cos(trial[k] / sqrt(k + 1));
    }
    value = sigma - pi + 1;
    break;
  // Rastrigin's
  case 13:
    for (int k = 0; k < D; k++)
      sigma += pow(trial[k], 2) - 10 * cos(2 * PI * trial[k]);
    value = 10 * D + sigma;
    break;
  // Griewangk's
  case 14:
    for (int k = 0; k < D; k++) {
      sigma += pow(trial[k], 2) / 4000.0;
      pi *= cos(trial[k] / sqrt(k + 1));
    }
    value = sigma - pi + 1;
    break;
  }

  return value;
}

// generate [0,1]
double rnd_uni() { return ((double)rand()) / ((double)RAND_MAX); }

// initialize 1st generation vectors
void initialize(double array[NP][D]) {
  for (int i = 0; i < NP; i++) {
    for (int j = 0; j < D; j++) {
      switch (STRATEGY) {
      case 1:
        array[i][j] = (rnd_uni() * 2.0 - 1.0) * 5.12;
        break;
      case 2:
        array[i][j] = (rnd_uni() * 2.0 - 1.0) * 2.048;
        break;
      case 7:
        array[i][j] = (rnd_uni() * 2.0 - 1.0) * 400.0;
        break;
      case 13:
        array[i][j] = (rnd_uni() * 2.0 - 1.0) * 600.0;
        break;
      case 14:
        array[i][j] = (rnd_uni() * 2.0 - 1.0) * 600.0;
        break;
      }
    }
  }
}

int main() {
  int generation = 0, i = 0;
  int final_generation = 0;
  int nfe;
  double trial[D];
  double x1[NP][D]; // for calculation
  double x2[NP][D]; // for buffer
  double score;
  double cost[NP];
  FILE *fp;

  fp = fopen(NAME, "a");

  srand(time(NULL));
  initialize(x1);
  initialize(x2);

  // initialize cost[]
  while (i < NP) {
    cost[i] = pow(10, 10);
    i++;
  }

  while (generation < GEN_MAX) {
    // generate trial vectors from existing vectors
    int i, j, k;
    for (i = 0; i < NP; i++) { // vectors loop
      // choose a,b,c randomly(a != b != c != i)
      int a, b, c;
      do
        a = (int)(rnd_uni() * NP);
      while (a == i);
      do
        b = (int)(rnd_uni() * NP);
      while (b == i || b == a);
      do
        c = (int)(rnd_uni() * NP);
      while (c == i || c == a || c == b);

      // choose j randomly (j is a dimension index of a vector)
      j = (int)(rnd_uni() * D);

      // mutation
      for (k = 1; k <= D; k++) { // dimention loop
        if (rnd_uni() < CR || k == D)
          trial[j] = x1[c][j] + F * (x1[a][j] - x1[b][j]);
        else
          trial[j] = x1[i][j];
        j = (j + 1) % D;
      }

      // evaluate trial vector
      score = evaluate(trial);

      // update x2 & the cost of vector
      if (score <= cost[i]) {
        for (j = 0; j < D; j++)
          x2[i][j] = trial[j];
        cost[i] = score;
      } else
        for (j = 0; j < D; j++)
          x2[i][j] = x1[i][j];
    }

    // copy x2 -> x1
    for (i = 0; i < NP; i++)
      for (j = 0; j < D; j++)
        x1[i][j] = x2[i][j];

    generation++;

    // choose best vector
    double best = cost[0];
    for (i = 0; i < NP; i++)
      if (best > cost[i])
        best = cost[i];

    // record of generation(rearch to VTR)
    if (best < VTR && final_generation == 0)
      final_generation = generation;

    // output each generation log
    printf("%f\n", best);
    fprintf(fp, "%f,", best);
  }
  fprintf(fp, "\n");
  fclose(fp);

  nfe = NP * final_generation;
  printf("final generation:%d\nNP:%d\nnfe:%d\n", final_generation, NP, nfe);

  return 0;
}