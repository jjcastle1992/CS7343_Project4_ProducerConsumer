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
#include <random> // for PRNG

using namespace std;


class Factory {
public:
    // Constructor
    Factory();

    // Getters/Setters
    void setSleepTime(int);  // set the number of seconds the program should sleep before it terminates

    // Make Producers/Consumers
    void makeProducer();
    void makeConsumer();

    // Interface with production line
    bool bufferAvailable();
    bool insert_item();  // Inserts a random number in the buffer (0 - RAND_MAX)
    bool remove_item();

    // UtilityMethods
    void initializeLocks();  // initialize mutex and empty/full semaphores per spec
    void initializeBuffer(); // Set Buffer values to all -1; (Empty)
    void displayBuffer();
    int randomRangeGen(int, int, unsigned int);  // MaxNum, MinNum, Seed(if want to set)

private:
    int itemsProduced;
    int itemsConsumed;
    int timeToSleep;
    static const int bufferSize = 5;
    mutex bufferLock; // to ensure mutual exclusion during buffer access by prod or consumer
    counting_semaphore<bufferSize> full; // count number of full spaces
    counting_semaphore<bufferSize> empty;  // count number of empty spaces in buffer
    int boundedBuffer[bufferSize];
};

// Critical section is interacting with the buffer

#endif //PROJECT4_MAIN_H
