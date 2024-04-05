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

void Factory::setSleepTime(unsigned int seconds) {
    this->timeToSleep = seconds;
}


void Factory::makeProducer(unsigned int numProducers) {
    for(int i = 0; i < numProducers; i++){
        unique_ptr<thread> producer (new thread([this]() {
            while(true){
                // Do all the things
                // Check for buffer lock
                empty.acquire();
                bufferLock.lock();

                // Critical Section
                string message = "Inserting item [" + to_string(this->bufferIndex) + "]: ";

                int number = this->insert_item();
                message += to_string(number);
                atomPrint(&message);
                int sleepTime = randomRangeGen(3, 1, 42);

                bufferLock.unlock();
                full.release();
                this_thread::sleep_for(chrono::seconds(sleepTime));
            }
        }));
        producer->detach();
    }
}

void Factory::makeConsumer(unsigned int numConsumers) {
    for(int i = 0; i < numConsumers; i++){
        unique_ptr<thread> consumer (new thread([this]() {
            while(true){
                // Do all the things
                // Check for buffer lock
                full.acquire();
                bufferLock.lock();

                // Critical Section
                string message = "Grabbing item from queue [" + to_string(this->bufferIndex - 1) + "]: ";
                int payload = this->remove_item();
                message += to_string(payload) + "\n";
                atomPrint(&message);
                int sleepTime = randomRangeGen(3, 1, 42);

                bufferLock.unlock();
                empty.release();
                this_thread::sleep_for(chrono::seconds(sleepTime));
            }
        }));
        consumer->detach();
    }
}

int Factory::insert_item() {
    // Inserts a random number in the buffer (0 - RAND_MAX)
    int number = randomRangeGen(RAND_MAX, 0, 42);
    int index = this->bufferIndex;
    this->boundedBuffer[index] = number;
    this->bufferIndex++;

    return number;
}

int Factory::remove_item() {
    this->bufferIndex--;
    int index = this->bufferIndex;
    int payload = this->boundedBuffer[index];
    this->boundedBuffer[index] = -1;

    return payload;
}


void Factory::initializeBuffer() {
    for(int & i : this->boundedBuffer) {
        i = -1; // Initialize each item to "-1" or empty
    }
}

void Factory::displayBuffer() {
    bufferLock.lock();  // to ensure this is the last thing
    string message = "\nFinal Buffer Layout: [ ";
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
    unsigned int seconds = 0;
    unsigned int numProducers = 0;
    unsigned int numConsumers = 0;
    // Get inputs RE:
    // 1. time to sleep (seconds) before terminating
    cout << "Please Enter how long to sleep before terminating (in seconds): ";
    cin >> seconds;

    // 2. Number of producer threads
    cout << "\nPlease Enter how many producer threads to create: ";
    cin >> numProducers;

    // 3. Number of consumer threads
    cout << "\nPlease Enter how many consumer threads to create: ";
    cin >> numConsumers;

    // Build factory
    Factory ourFactory;
    ourFactory.setSleepTime(seconds);

    // Initialize Buffer
    ourFactory.initializeBuffer();

    // Create producers
    ourFactory.makeProducer(numProducers);

    // Create Consumers
    ourFactory.makeConsumer(numConsumers);

    // Sleep
    this_thread::sleep_for(chrono::seconds(seconds));

    // Exit
    ourFactory.displayBuffer();
    string message = "\nDone";
    atomPrint(&message);

    return 0;
}
