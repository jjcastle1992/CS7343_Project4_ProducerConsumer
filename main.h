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
    void makeProducer(int);
    void makeConsumer(int);

    // Interface with production line
    void insert_item();  // Inserts a random number in the buffer (0 - RAND_MAX)
    void remove_item();

    // UtilityMethods
    void initializeBuffer(); // Set Buffer values to all -1; (Empty)
    void displayBuffer();
    int randomRangeGen(int, int, unsigned int);  // MaxNum, MinNum, Seed(if want to set)

private:
    int itemsProduced;
    int itemsConsumed;
    int timeToSleep;
    static const int bufferSize = 5;
    mutex bufferLock; // to ensure mutual exclusion during buffer access by prod or consumer
    counting_semaphore<bufferSize> full; // count number of full spaces (For Consumer)
    counting_semaphore<bufferSize> empty;  // count number of empty spaces in buffer (Producer)
    int boundedBuffer[bufferSize]{};
    int bufferIndex;
};

void atomPrint(string*); // to atomically print
mutex outputMutex; // Mutex for synchronizing output
// Critical section is interacting with the buffer

#endif //PROJECT4_MAIN_H
