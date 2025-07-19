//
// Created by henri on 12.07.2025.
//

#ifndef CHUNK_H
#define CHUNK_H
#define ULL unsigned long long
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    ULL start,end;
    int chunkSize;
    uint64_t* chunkSet;
} Chunk;
void initChunk(Chunk* chunk,ULL start, ULL end);
void clearBit(Chunk* chunk, int x);
bool getBit(Chunk* chunk, int x);
void calcChunk(Chunk* baseChunk, Chunk* workingChunk);
void calcBaseChunk(Chunk* baseChunk);
#endif //CHUNK_H
