#ifndef MRU_H
#define MRU_H

#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <stack>
#include "frame.h"

using namespace std;

int mru(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose);

int findLeastRecentlyUsed(Frame frames[], stack<int> frameStack, int frameCount);

bool tryMRUHitFrame(Frame frames[], stack<int> frameStack, int page, int frameCount);

#endif
