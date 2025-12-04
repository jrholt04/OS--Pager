#ifndef RANDOM_H
#define RANDOME_H

#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

void pgRandom(Frame frames[], map<string, queue<int>> pages, bool verbose);

#endif