#include "Random.h"
using namespace BalisongEngine;
using namespace BalisongEngineFramework;

using namespace std;

// ===============================================================================

random_device Random::rd;
mt19937 Random::rng(rd()); // Initialize rng with a seed from the random device

// ===============================================================================

float Random::Range(float min, float max)
{
    if (min > max)
        swap(min, max); // prevent crash if min is more than max

    uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

int Random::Range(int min, int max)
{
    if (min > max)
        swap(min, max); // prevent crash if min is more than max

    uniform_int_distribution<int> dist(min, max-1);
    return dist(rng);
}