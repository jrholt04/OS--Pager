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
int lru(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose);

// Returns true if the page is found in a frame puts that frame at the front of the queue, and false if the page is not found
// Requires a seperate function from tryHitFrame due to having to reorder the queue
bool tryLRUHitFrame(Frame frames[], queue<int> frameQueue, int page, int frameCount);

#endif
