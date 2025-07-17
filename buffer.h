//
// Created by henri on 7/14/2025.
//

#ifndef BUFFER_H
#define BUFFER_H
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int bufferSize;
    uint64_t* buffer;
    size_t bufferEntries;
} Buffer;

void initBuffer(Buffer *buffer, int size);
void addNumber(Buffer *buffer, uint64_t number);
void freeBuffer(Buffer *buffer);
void flushBufferToFile(Buffer *buffer);
bool bufferFull(Buffer *buffer);
void addNumbersFromArray(Buffer *buffer, uint64_t* numbers, size_t size,size_t offset);
#endif //BUFFER_H
