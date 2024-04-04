/*********************
Name: James Castle
CS 7343 Programming Assignment 2 - Project 4
Purpose: Implementaation of the Producer-Consumer Problem (Project 4)
**********************/
#include "main.h"

Factory::Factory() : full(0), empty(bufferSize) {
    const int bufferSize = 5;
    int itemsProduced = 0;
    int itemsConsumed = 0;
    mutex bufferLock; // to ensure mutual exclusion during buffer access by prod or consumer
    int boundedBuffer[bufferSize];
}

void Factory::makeProducer() {
    ;
}

void Factory::makeConsumer() {
    ;
}

bool Factory::bufferAvailable() {
    ;
}

bool Factory::insert_item() {
    // Inserts a random number in the buffer (0 - RAND_MAX)
    ;
}

bool Factory::remove_item() {
    ;
}

void Factory::initializeLocks() {
    ;
}

void Factory::initializeBuffer() {
    for(int & i : this->boundedBuffer) {
        i = -1; // Initialize each item to "-1" or empty
    }
}

void Factory::displayBuffer() {
    ;
}

int randomRangeGen(int endRange, int startRange = 0, unsigned int seed = 42) {
    // General implementation borrowed from:
    // https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus
    int random;

    // Random pathway
    if (seed == 42) {
        random = startRange + (rand() % ((endRange - startRange) + 1));
    }
        // Set seed pathway
    else {
        // Modified with ChatGPT to take in a seed.
        // Initialize the random number generator with the provided seed
        std::mt19937 gen(seed);
        // Retrieve a random number between startRange and EndRange
        random = startRange + (gen() % ((endRange - startRange) + 1));
    }
    return random;
}

int main() {

    // Get inputs RE:
        // 1. time to sleep (seconds) before terminating
        // 2. Number of producer threads
        // 3. Number of consumer threads

    // Build factory
    Factory ourFactory;

    // Initialize Buffer
    ourFactory.initializeBuffer();

    // Check Semaphores ready

    // Create producers

    // Create Consumers

    // Sleep

    // Exit
    cout << "Done" << endl;

    return 0;
}
