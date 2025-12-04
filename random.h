//File: random.h
//Author: J Holt, N Neagle, and A Seng, Transy U
//Course: CS 3074 Operating Systems
// 
//  random is a page swapping algorithm that swaps a page into a random frame 
//  this is the interface of that algorithm
#ifndef RANDOM_H
#define RANDOME_H

#include <string>
#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include "frame.h"

using namespace std;

//simulates the random page swapping algorithm
int pgRandom(Frame frames[], map<string, queue<int>>& pages, int frameNumbers, bool verbose);

#endif