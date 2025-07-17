//
// Created by henri on 7/14/2025.
//


#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>


void initBuffer(Buffer *buffer, int size) {
    buffer->bufferSize = size;
    buffer->buffer = malloc(size * sizeof(uint64_t));
    buffer->bufferEntries = 0;
}
void addNumber(Buffer *buffer, uint64_t number) {
    buffer->buffer[buffer->bufferEntries] = number;
    buffer->bufferEntries++;
}
bool getBitFromBitset(uint64_t *bitset, size_t x) {
    return (bitset[x/64] & (1ULL << (x%64))) != 0;
}
void addNumbersFromArray(Buffer *buffer, uint64_t* numbers, size_t size, size_t offset) {
    if (buffer->bufferEntries + size > buffer->bufferSize) {
        flushBufferToFile(buffer);
    }
    size_t totalBitsInNumbers = size*sizeof(uint64_t)*8;
    for (size_t i = 0; i < totalBitsInNumbers; i++) {
        if (getBitFromBitset(numbers,i)) {
            addNumber(buffer, i + offset);
        }
    }
}

uint64_t getAtIndex(Buffer *buffer, int x) {
    return buffer->buffer[x];
}
void freeBuffer(Buffer *buffer) {
    free(buffer->buffer);
}
bool bufferFull(Buffer *buffer) {
    return buffer->bufferEntries == buffer->bufferSize;
}
void emptyBuffer(Buffer *buffer) {
    for (int i = 0; i < buffer->bufferEntries; i++) {
        buffer->buffer[i] = 0;
    }
    buffer->bufferEntries = 0;
}
void flushBufferToFile(Buffer *buffer) {
    FILE* file = fopen("chunk.bin","ab");
    for (int i = 0; i < buffer->bufferEntries; i++) {
        uint64_t number = buffer->buffer[i];
        fwrite(&number, sizeof(uint64_t), 1, file);
    }
    fclose(file);
    emptyBuffer(buffer);
}

