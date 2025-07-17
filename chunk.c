//
// Created by henri on 12.07.2025.
//

#include "chunk.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"


void initChunk(Chunk* chunk,ULL start, ULL end) {
    chunk->start = start;
    chunk->end = end;
    if (end < start || end - start > INT_MAX) {
        printf("Invalid or too large range\n");
        exit(-1);
    }
    chunk->chunkSize = (int)(end-start); // außer primzahlen bis >10**18
    if (chunk->chunkSize %64!=0) exit(-1);

    int uintsNeeded =chunk->chunkSize /64; // e.g. 1000 numbers / each 8 bytes*8bit, total numbers/BitsPerNum
    chunk->chunkSet = malloc(uintsNeeded * sizeof(uint64_t));
    if (chunk->chunkSet == NULL) {  // Check if malloc succeeded
        exit(-1);
    }
    memset(chunk->chunkSet, 0xFF, uintsNeeded *sizeof(uint64_t));// bits to 1



}
void clearBit(Chunk* chunk,int x) {
    chunk->chunkSet[x/64] &= ~(1ULL << (x%64));
}
void setBit(Chunk* chunk,int x) {
    chunk->chunkSet[x/64] |= (1ULL << (x%64));
}
bool getBit(Chunk* chunk,int x) {
    return (chunk->chunkSet[x/64] & (1ULL << (x%64))) != 0;
}
void calcChunk(Chunk* baseChunk, Chunk* workingChunk) {
    for (int i = 0; i < baseChunk->chunkSize; i++) {
        if (getBit(baseChunk,i)) {
            ULL first = i * i;
            if (first < workingChunk->start)
                first = ((workingChunk->start + i - 1) / i) * i;
            for (ULL j=first;j-workingChunk->start<workingChunk->chunkSize;j+=i) {
                int workingChunkIndex = (int)(j-workingChunk->start);
                if (workingChunkIndex >= workingChunk->chunkSize) {
                    printf("NOT INSIDE BOUNDS");
                    exit(-1);
                }

                clearBit(workingChunk,workingChunkIndex);
            }
        }
    }

}
void calcBaseChunk(Chunk* baseChunk) {
    clearBit(baseChunk,0);
    clearBit(baseChunk,1);
    for (int i = 0; i < baseChunk->chunkSize; i++) {
        if (getBit(baseChunk,i)) {
            if (i<sqrt(INT_MAX)) {
                for (int j=i*i;j<baseChunk->chunkSize;j+=i) {
                    clearBit(baseChunk,j);
                }
            }
        }
    }
}
void printChunk(Chunk* chunk) {
    for (int i = 0; i < chunk->chunkSize; i++) {
        if (getBit(chunk,i)) {
            printf("%llu\n",i+chunk->start);
        }
    }
}
void sieve(ULL upperLimit,int bufferSize) {
    int chunkSize = (int)sqrt((double)upperLimit);
    FILE* t = fopen("chunk.bin","wb");
    if (!t) exit(-1);
    fclose(t);
    Buffer buffer;
    initBuffer(&buffer,bufferSize);

    printf("Calculations start now, %.4f MB of RAM will be needed ( %llu MB for buffer )\n", 2* (chunkSize / (8.0 * 1024 * 1024)),(bufferSize*sizeof(uint64_t))/(8*1000*1000)); //2*, bc. workingChunk(dynamic)+ basechunk ( static)

    Chunk baseChunk;
    initChunk(&baseChunk,0,chunkSize);
    calcBaseChunk(&baseChunk);
    for (int i = 0; i < baseChunk.chunkSize; i++) {
        if (getBit(&baseChunk, i)) {
            addNumber(&buffer, i + baseChunk.start);
        }
    }
    //toFile(&baseChunk);

    Chunk workingChunk;
    for (ULL currentStart= chunkSize; currentStart < upperLimit; currentStart+=chunkSize) {


        initChunk(&workingChunk,currentStart,currentStart+chunkSize);
        calcChunk(&baseChunk,&workingChunk);

        //buffer,file related
        if (buffer.bufferEntries + workingChunk.chunkSize > buffer.bufferSize) {
            flushBufferToFile(&buffer);
        }
        for (int i = 0; i < workingChunk.chunkSize; i++) {
            if (getBit(&workingChunk, i)) {
                addNumber(&buffer, i + workingChunk.start);
            }
        }
        //toFile(&workingChunk);

        free(workingChunk.chunkSet);
    }
    flushBufferToFile(&buffer);
    freeBuffer(&buffer);
    free(baseChunk.chunkSet);
}

void toFile(Chunk* chunk) {
    FILE* file = fopen("chunk.bin","ab");
    for (int i = 0; i < chunk->chunkSize; i++) {
        if (getBit(chunk,i)) {
            uint64_t number = i+chunk->start;
            fwrite(&number, sizeof(uint64_t), 1, file);
        }
    }
    fclose(file);
}

