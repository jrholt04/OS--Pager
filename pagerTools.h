// File pagerTools.h
// Author: J Holt, N Neagle, and A Seng, Transy U
// Course: CS 3074 Operating Systems
//
// Header file for OS Pager Tools
#ifndef PAGERTOOLS_h
#define PAGERTOOLS_H

#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include "frame.h"
using namespace std;

map<string, queue<int>> readMemoryLocations(string fileName, int pageNumbers, int framesize);

void printVerbose(void);

void printPagerHelp(void);

#endif 