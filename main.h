/*********************
Name: James Castle
CS 7343 Programming Assignment 2 - Project 4
Purpose: Interface for the Producer-Consumer Problem (Project 4)
**********************/
#ifndef PROJECT4_MAIN_H
#define PROJECT4_MAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <semaphore> // For counting semaphores empty and full
#include <mutex>  // for mutex lock for access to bounded buffer.

using namespace std;


class Factory {
public:
    // Constructor
    Factory();

    // Getters/Setters

    // Interface with production line
    bool bufferAvailable();
    bool insert_item();  // Inserts a random number in the buffer (0 - RAND_MAX)
    bool remove_item();

    // UtilityMethods
    void initializeLocks();  // initialize mutex and empty/full semaphores per spec
    void displayBuffer();
    int randomRangeGen(int, int, unsigned int);  // MaxNum, MinNum, Seed(if want to set)

private:
    int itemsProduced;
    int itemsConsumed;
    mutex bufferLock; // to ensure mutual exclusion during buffer access by prod or consumer
    counting_semaphore<5> full(); // count number of full spaces
    counting_semaphore<5> empty();  // count number of empty spaces in buffer
    int boundedBuffer[5]{};
    enum prodOrConsumer{producer, consumer};
};

// Critical section is interacting with the buffer

#endif //PROJECT4_MAIN_H