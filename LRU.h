//File: LRU.h
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
//
// Interface for LRU (Least Recently Used) page replacement algorithm
// This algorithm replaces the frame that was used the longest time ago

#ifndef LRU_H
#define LRU_H

#include <string>
#include <iostream>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

// Simulate the LRU page swapping algorithm
// frames: array of physical frames
// pages: map of process IDs to queues of page numbers
// frameNumbers: number of physical frames
// verbose: if true, prints detailed step-by-step output
int lru(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose);

#endif
