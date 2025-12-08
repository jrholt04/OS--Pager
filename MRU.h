// File MRU.h
// Author: J Holt, N Neagle, and A Seng, Transy U
// Course: CS 3074 Operating Systems
//
// Interface for MRU (Most Recently Used) page replacement algorithm

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

// Simulate tje MRU page swaping algorithm 
int mru(Frame frames[], map<string, queue<int>>& pages, int frameCount, bool verbose);

// Returns either the most recently used frame or an emtpy frame
int findMostRecentlyUsed(Frame frames[], stack<int> frameStack, int frameCount);

// Returns true if the page is found in a frame puts that frame on top of the stack, and false if the page is not found
// Requires a seperate function from tryHitFrame due to having to reorder the stack
bool tryMRUHitFrame(Frame frames[], stack<int> frameStack, int page, int frameCount);

#endif
