#include <iostream>
#include <chrono>
#include <cstring>
using namespace std;

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./ej4
//g++ hw_1_ej3.cpp -Wall -g -o ej4


bool comparador_de_strings(string string_1, string string_2, long unsigned int indice = 0){
    if(indice>= string_1.length() || indice>=string_2.length() || string_1[indice]!= string_2[indice]){
        cout<<"Los dos strings no son iguales\n";
        return false;
    }
    if(indice==string_1.length()-1 && indice==string_2.length()-1){
        cout<<"Los dos strings son iguales\n";
        return true;
    }
    return comparador_de_strings(string_1, string_2, indice+1);
}
constexpr bool comparador_de_strings_mejorado(const char* string_1, const char* string_2, long unsigned int indice = 0){
    if(indice>= strlen(string_1) || indice>=strlen(string_2) || string_1[indice]!= string_2[indice]){
        cout<<"Los dos strings no son iguales\n";
        return false;
    }
    if(indice==strlen(string_1)-1 && indice==strlen(string_2)-1){
        cout<<"Los dos strings son iguales\n";
        return true;
    }
    return comparador_de_strings_mejorado(string_1, string_2, indice+1);
}
void tiempo_ejecucion(){
    auto startTime1 = chrono::high_resolution_clock::now(); 
    comparador_de_strings("M", "M", 0);
    auto endTime1 = chrono::high_resolution_clock::now(); 
    auto elapsedTime1 = chrono::duration_cast<chrono::nanoseconds>(endTime1 - startTime1); 
    cout<<"A mi comparador_de_strings le tomó: "<<elapsedTime1.count()<<" nanosegundos\n";
    
    auto startTime2 = chrono::high_resolution_clock::now(); 
    comparador_de_strings_mejorado("M", "M", 0);
    auto endTime2 = chrono::high_resolution_clock::now(); 
    auto elapsedTime2 = chrono::duration_cast<chrono::nanoseconds>(endTime2 - startTime2); 
    cout<<"A mi comparador_de_strings_mejorado le tomó: "<<elapsedTime2.count()<<" nanosegundos\n";
}


int main(){
    cout<<"EJERCICIO 4): \n";
    tiempo_ejecucion();
    return 0;
}