#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
using namespace std;

typedef enum Nivel_importancia{
    DEBUG, INFO, WARNING, ERROR, CRITICAL
};

struct nodo{
    unique_ptr<nodo> next; 
    int value;

    nodo(int val) : value(val), next(nullptr) {}

};
struct lista{
    unique_ptr<nodo> head;
    nodo*tail;
    size_t size;
    lista() : head(nullptr), tail(nullptr), size(0) {}
};