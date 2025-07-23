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
void freeBuffer(Buffer *buffer) {
    free(buffer->buffer);
}
void emptyBuffer(Buffer *buffer) {
    for (int i = 0; i < buffer->bufferEntries; i++) {
        buffer->buffer[i] = 0;
    }
    buffer->bufferEntries = 0;
}
void flushBufferToFile(Buffer *buffer) {
    FILE* file = fopen("chunk.bin","ab");
    fwrite(buffer->buffer,sizeof(uint64_t),buffer->bufferEntries,file);
    fclose(file);
    emptyBuffer(buffer);
}
void writeChunkToBuffer(Buffer *buffer, Chunk *workingChunk) {
    if (buffer->bufferEntries + workingChunk->chunkSize > buffer->bufferSize) {
        flushBufferToFile(buffer);
    }
    uint64_t start = workingChunk->start;
    int size = workingChunk->chunkSize;
    for (int i = 0; i < size; i++) {
        if (getBit(workingChunk, i)) {
            addNumber(buffer, i + start);
        }
    }
}

