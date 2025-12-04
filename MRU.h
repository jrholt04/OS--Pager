#ifndef MRU_H
#define MRU_H

#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

void mru(Frame frames[], map<string, queue<int>> pages, bool verbose);

#endif