//File: LFU.h
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  the fifo is a page swapping algorithm that swaps out the first item in the queue
//  this is the interface of that algorithm
#ifndef LFU_H
#define LFU_H

#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

// Simulate the fifo page swapping algorithm
int lfu(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose);

int findLeastFreqUsed(Frame frames[], int frameCount);

#endif 
