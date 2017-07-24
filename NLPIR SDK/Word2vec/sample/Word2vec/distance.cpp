//
//  distance.cpp
//  Word2vec
//
//  Created by 潘洪岩 on 2017/5/1.
//  Copyright © 2017年 Hongyan Pan. All rights reserved.
//

#include "distance.hpp"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <math.h>
//#include <sys/malloc.h>
#include <malloc.h>

int Distance::loadModel(const char *model){
    FILE *f;
    f = fopen(model, "rb");
    if (f == NULL) {
        printf("Input file not found\n");
        return 0;
    }
    fscanf(f, "%lld", &words);
    std::cout<<"here"<<std::endl;
    fscanf(f, "%lld", &size);
    vocab = (char *)malloc((long long)words * max_w * sizeof(char));
    M = (float *)malloc((long long)words * (long long)size * sizeof(float));
    if (M == NULL) {
        printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
        return 0;
    }
    for (b = 0; b < words; b++) {
        a = 0;
        while (1) {
            vocab[b * max_w + a] = fgetc(f);
            if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
            if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
        }
        vocab[b * max_w + a] = 0;
        for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
        len = 0;
        for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
        len = sqrt(len);
        for (a = 0; a < size; a++) M[a + b * size] /= len;
    }
    fclose(f);
    return 1;
}

const char * Distance::calculateDistance(const char * word){
    for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
        st[cn][b] = word[c];
        b++;
        c++;
        st[cn][b] = 0;
        if (word[c] == 0) break;
        if (word[c] == ' ') {
            cn++;
            b = 0;
            c++;
        }
    }
    cn++;
    for (a = 0; a < cn; a++) {
        for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
        if (b == words) b = -1;
        bi[a] = b;
        //printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
        if (b == -1) {
            printf("Out of dictionary word!\n");
            break;
        }
    }
    for (a = 0; a < size; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
        if (bi[b] == -1) continue;
        for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
    }
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    for (a = 0; a < size; a++) vec[a] /= len;
    for (a = 0; a < N; a++) bestd[a] = -1;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
        a = 0;
        for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
        if (a == 1) continue;
        dist = 0;
        for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
        for (a = 0; a < N; a++) {
            if (dist > bestd[a]) {
                for (d = N - 1; d > a; d--) {
                    bestd[d] = bestd[d - 1];
                    strcpy(bestw[d], bestw[d - 1]);
                }
                bestd[a] = dist;
                strcpy(bestw[a], &vocab[c * max_w]);
                break;
            }
        }
    }
    std::string result;
    char tempbuf[15];
    for (a = 0; a < N; a++) {
        if(bestw[a][0]=='\0') continue;
        result.append(bestw[a]);
        result.append("/");
        sprintf(tempbuf, "%.6f", bestd[a]);
        result.append(tempbuf);
        result.append("#");
    }
    long long unsigned length=result.size();
    char * rlt=new char[length+1];
    result.copy(rlt, length);
    rlt[length+1]='\0';
    return rlt;
}
