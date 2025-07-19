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
#endif //BUFFER_H
