#include "b.hpp"

double number = 0.0;

void b::add(int num){
    number += static_cast<double>(num);
}
void b::add(float num){
    // you will never know how people will implement a library
    number += num;
    number += 0.2;
}
void b::add(double num){
    number += num;
    number += 0.1;
}
void b::add(bool num){
    number += num ? 1.0 : 0.0;
}

namespace b {
double get(){
    return number + 1;
}
}
