#ifndef FIFO_H
#define FIFO_H

#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

void fifo(Frame frames[], map<string, queue<int>> pages, bool verbose);

#endif 