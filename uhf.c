#include "uhf.h"

int P, M, A, B;

int Universal_Hashing_Function(int key)
{
    /* Για κάθε αριθµό a ∈ {1,…,p-1} και b ∈ {0,…,p-1} έστω ha,b(x) = ((ax+b) mod p) mod m.
     Τότε, το σύνολο συναρτήσεων H = {ha,b: 1 ≤ a < p και 0 ≤ b < p}
      είναι µια καθολική κλάση συναρτήσεων κατακερµατισµού. */
    return ((A * key + B) % P) % M;
}
