//
// alloc.cpp - micro-benchmark for speed of large-block malloc/free
//
// Richard Cownie, Hail Team, 2018-05-03
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double timeMillis() {
  static bool haveFirst;
  static struct timeval tv0;
  if (!haveFirst) {
    haveFirst = true;
    gettimeofday(&tv0, 0);
  }
  struct timeval tv1;
  gettimeofday(&tv1, 0);
  return((tv1.tv_sec-tv0.tv_sec)*1000.0 + (tv1.tv_usec-tv0.tv_usec)*0.001);
}

int main() {
  int mega = (1<<20);
  srandom(0x7b2c531a);
  for (int blockMB = 1; blockMB <= 128; blockMB *= 2) {
    int avgBlocks = 64;
    char* blocks[2*avgBlocks];
    for (int j = 0; j < 2*avgBlocks; ++j) {
      blocks[j] = nullptr;
    }
    auto t0 = timeMillis();
    int numAlloc = 1000000;
    int numSoFar = 0;
    for (;;) {
      long r = (random() & 0x7fffffff) % (2*avgBlocks);
      if (blocks[r]) {
        free(blocks[r]);
        blocks[r] = nullptr;
      } else {
        blocks[r] = (char*)malloc(blockMB<<20);
        if (++numSoFar >= numAlloc) break;
      }
    }
    for (int j = 0; j < 2*avgBlocks; ++j) {
      if (blocks[j]) free(blocks[j]);
    }
    auto t1 = timeMillis();
    printf("%d x %dMB in %.1fms = %.3f us/malloc\n",
      numAlloc, blockMB, t1-t0, (1000.0*(t1-t0))/numAlloc);
  }
  return(0);
}
