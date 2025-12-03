// FILE: frame.cpp
// Author: J Holt, N Neagle, and A Seng, Transy U
// CS 3074, Fall 2025
//
// Implementation - frame class

#include "frame.h"

Frame::Frame(void) {
    id = "";
    frequency = 0;
    valid = false;
}

Frame::~Frame(void) {}

string Frame::getId(void) const {
    return id;
}

int Frame::getFreq(void) const {
    return frequency;
}

bool Frame::getValid(void) const {
    return valid;
}

void Frame::toggleValid(void) {
    valid = !valid;
}

void Frame::setId(string inputId) {
    id = inputId;
}

void Frame::setFrequency(int inputFreq) {
    frequency = inputFreq;
}
