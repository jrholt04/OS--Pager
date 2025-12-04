#ifndef LRU_H
#define LRU_H

#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

void lru(Frame frames[], map<string, queue<int>> pages, bool verbose);

#endif