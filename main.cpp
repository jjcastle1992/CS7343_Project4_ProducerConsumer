/*********************
Name: James Castle
CS 7343 Programming Assignment 2 - Project 4
Purpose: Implementaation of the Producer-Consumer Problem (Project 4)
**********************/
#include "main.h"

Factory::Factory() : full(0), empty(bufferSize) {
    this-> itemsProduced = 0;
    this-> itemsConsumed = 0;
    this-> bufferLock; // to ensure mutual exclusion during buffer access by prod or consumer
    this-> boundedBuffer[bufferSize];
    this-> timeToSleep = 0;
    this-> bufferIndex = 0;
}

void Factory::setSleepTime(int seconds) {
    this->timeToSleep = seconds;
}


void Factory::makeProducer(int numProducers) {
    for(int i = 0; i < numProducers; i++){
        unique_ptr<thread> producer (new thread([this]() {
            while(true){
                // Do all the things
                // Check for buffer lock
                empty.acquire();
                bufferLock.lock();

                // Critical Section
                string message = "Inserting item";
                atomPrint(&message);
                this->insert_item();

                bufferLock.unlock();
                this_thread::sleep_for(chrono::seconds(1));
            }
        }));
        producer->detach();
    }
}

void Factory::makeConsumer(int numConsumers) {
    ;
}

void Factory::insert_item() {
    // Inserts a random number in the buffer (0 - RAND_MAX)
    int number = randomRangeGen(RAND_MAX, 0, 42);
    int index = this->bufferIndex;
    this->boundedBuffer[index] = number;
    this->bufferIndex++;
}

void Factory::remove_item() {
    ;
}


void Factory::initializeBuffer() {
    for(int & i : this->boundedBuffer) {
        i = -1; // Initialize each item to "-1" or empty
    }
}

void Factory::displayBuffer() {
    string message = "\n Final Buffer Layout: [ ";
    for(int i = 0; i < (sizeof (this->boundedBuffer) / sizeof (int)); i++){
        message += to_string(this->boundedBuffer[i]) + ", ";
    }
    message += "]";
    atomPrint(&message);
}

int Factory::randomRangeGen(int endRange, int startRange, unsigned int seed) {
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

void atomPrint(std::string *message) {
    // Modified to atomically print
    lock_guard<mutex> lock(outputMutex); // Lock the mutex
    cout << *message << endl; // Print the message
}

int main() {
    int seconds = 0;
    // Get inputs RE:
    cout << "Please Enter how long to sleep (in seconds): ";
    cin >> seconds;
        // 1. time to sleep (seconds) before terminating
        // 2. Number of producer threads
        // 3. Number of consumer threads

    // Build factory
    Factory ourFactory;
    ourFactory.setSleepTime(seconds);

    // Initialize Buffer
    ourFactory.initializeBuffer();

    // Create producers
    ourFactory.makeProducer(1);

    // Create Consumers

    // Sleep
    this_thread::sleep_for(chrono::seconds(seconds));

    // Exit
    ourFactory.displayBuffer();
    string message = "\nDone";
    atomPrint(&message);

    return 0;
}
