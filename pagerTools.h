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

// reads in the file of form:
//  P_id
//  memlocation
//  memlocation
//  memlocation
//      ...
// and produces a map where the key is the P_id and the Value is the page each memory location is on
// in the order that they appear.
map<string, queue<int>> readMemoryLocations(string fileName, int pageNumbers, int framesize);

void printPagerHelp(void);

void swapFrame(Frame frames[], int page, string pId, int frameCount, int victim);

bool tryHitFrame(Frame frames[], int page, int frameCount);

#endif 
