#include "Vincia/Vincia.h"

using namespace Vincia;

void print_usage() {
  cerr << endl << "Usage:" << endl;
  cerr << "  pspoint <s> <in> <out> <n>" << endl;
  cerr << endl;
  cerr << "Arguments:" << endl;
  cerr << "  <s>    total energy" << endl;
  cerr << "  <in>   incoming particles count (1 or 2)" << endl;
  cerr << "  <out>  outgoing particles count (up to 8)" << endl;
  cerr << "  <n>    total points to generate" << endl;
}

int parse_args(int argc, char *argv[], double *s, int *in, int *out, int *n) {
  if (argc == 1) return -1;
  if (argc < 5) {
    cerr << "ERROR: not enough arguments" << endl;
    return -1;
  }
  if (argc > 5) {
    cerr << "ERROR: too many arguments" << endl;
    return -1;
  }
  *s = atof(argv[1]);
  if (*s <= 0) {
    cerr << "ERROR: <s> should be positive" << endl;
    return -1;
  }

  *in = atoi(argv[2]);
  if (*in <= 0) {
    cerr << "ERROR: <in> should be positive" << endl;
    return -1;
  } else if (*in > 2) {
    cerr << "ERROR: <in> should be 1 or 2" << endl;
    return -1;
  }

  *out = atoi(argv[3]);
  if ((*out < 2) || (*out > 8)) {
    cerr << "ERROR: <out> should be from 2 to 8" << endl;
    return -1;
  }

  *n = atoi(argv[4]);
  if (*n < 0) {
    cerr << "ERROR: <n> should be positive" << endl;
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  cerr << "pspoint v17.08.17 by O.Gituliar <oleksandr@gituliar.net>" << endl;

  int in, out, n;
  double s;

  if (parse_args(argc, argv, &s, &in, &out, &n) < 0) {
    print_usage();
    return -1;
  }

  double e = sqrt(s);
  double p[4][8];
  Rambo  rambo;
  Rndm   rndmPtr;
  rambo.initPtr(&rndmPtr);

  printf("{\n");
  for (int j=1; j<=n; j++) {
    if (j>1) printf(",\n");
    printf("  {\n");
    if (in == 1) {
      printf("    q -> {%10f, 0., 0., 0.},\n", e);
    } else {
      printf("    p1 -> {%10f, 0., 0., %10f},\n", e/2,  e/2);
      printf("    p2 -> {%10f, 0., 0., %10f},\n", e/2, -e/2);
    }
    rambo.genPoint(s, out, p);
    for (int i=0; i<out; i++) { 
      if (i > 0) printf(",\n");
      printf("    k%d -> {%.10f, %.10f, %.10f, %.10f}", i+1, p[0][i], p[1][i], p[2][i], p[3][i]);
    }
    printf("\n  }");
  }
  printf("\n}\n");
  return 0;
}
