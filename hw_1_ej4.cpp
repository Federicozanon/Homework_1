#include <iostream>
#include <chrono>
#include <cstring>
using namespace std;

/*Tanto en mi funcion de comparador_de_string como en la mejorada, simplemente
me fijo primero que el indice no supere el largo de ninguno de los dos strings
y que en ese indice los dos strings sean iguales, caso contrario retorno false.
Sino, en la siguiente iteracion me fijo si el indice es igual al largo de los 
strings por igual, si no se ha retornado false y se cumple lo anterior, retorno true.
Si no pasa ninguno de estos casos, retorno la misma funcion con los 2 mismos
strings pero le sumo 1 al indice
*/
bool comparador_de_strings(string string_1, string string_2, long unsigned int indice = 0){
    //En este primer caso elegi usar string, ya que puedo gestionar dinámicamente la memoria.  
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
    //En este caso tuve que usar char* ya que string no es compatible con constexpr
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
    comparador_de_strings("Ingenieria en inteligencia artificial", "Ingenieria en inteligencia artificial", 0);
    auto endTime1 = chrono::high_resolution_clock::now(); 
    auto elapsedTime1 = chrono::duration_cast<chrono::nanoseconds>(endTime1 - startTime1); 
    cout<<"A mi comparador_de_strings le tomó: "<<elapsedTime1.count()<<" nanosegundos\n";
    
    auto startTime2 = chrono::high_resolution_clock::now(); 
    comparador_de_strings_mejorado("Ingenieria en inteligencia artificial", "Ingenieria en inteligencia artificial", 0);
    auto endTime2 = chrono::high_resolution_clock::now(); 
    auto elapsedTime2 = chrono::duration_cast<chrono::nanoseconds>(endTime2 - startTime2); 
    cout<<"A mi comparador_de_strings_mejorado le tomó: "<<elapsedTime2.count()<<" nanosegundos\n";
}
int main(){
    /*La diferencia en los tiempos de compilacion de las dos funciones
    se debe a que al usar constexpr, yo declaro que las variables, funciones y/o
    objetos se pueden evaluar en tiempo de compilacion, lo que reduce el tiempo
    que tarda la funcion en completarse.
    */
    cout<<"EJERCICIO 4): \n";
    tiempo_ejecucion();
    return 0;
}