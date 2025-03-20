#include <iostream>
#include <fstream>
using namespace std;

enum Nivel_importancia{
    DEBUG, INFO, WARNING, ERROR, CRITICAL
};
string funcion_nivel(Nivel_importancia nivel){
    //usando esta funcion, paso el nivel (int) a un string
    switch (nivel){
        case DEBUG : return "DEBUG";
        case INFO : return "INFO";
        case WARNING : return "WARNING";
        case ERROR : return "ERROR";
        case CRITICAL : return "CRITICAL";
        default : return "UNKNOWN";
    }
}
void logMessage(string mensaje, Nivel_importancia nivel){
    //imprimo al final de ej2_archivo_salida el mensaje
    ofstream archivo("ej2_archivo_salida.txt", ios::app);
    if (archivo.is_open()){
        archivo<<"["<<funcion_nivel(nivel)<<"] <"<<mensaje<<">\n";
        archivo.close();
    }
    else{
        cerr<<"Error abriendo el achivo\n";
    }
}
void logMessage(string mensaje_de_error, string archivo, int linea_de_codigo){
    //imprimo al final de ej2_archivo_salida el mensaje junto con la linea y el archivo donde sucedio el error
    ofstream archivo1("ej2_archivo_salida.txt", ios::app);
    if (archivo1.is_open()){
        archivo1<<"In "<<archivo<<"\nLine "<<linea_de_codigo<<"\nError: "<<mensaje_de_error;
        archivo1.close();
    }
    else{
        cerr<<"Error abriendo el archivo\n";
    }
}
void logMessage(string mensaje_de_acceso, string nombre_usuario){
    ofstream archivo2("ej2_archivo_salida.txt", ios::app);
    if (archivo2.is_open()){
        archivo2<<"[SECURITY] user: "<< nombre_usuario<<" "<<mensaje_de_acceso<<" ";
        archivo2.close();
    }
    else{
        cerr<<"Error abriendo el archivo\n";
    }
}
void prueba_ejercicio_2a(){
    logMessage("Iniciando Valgrind", DEBUG);
    logMessage("Se ha completado la prueba 1",INFO);
    logMessage("El archivo 'hola.txt' no se ha encontrado",WARNING);
    logMessage("Error al acceder a PATH",ERROR);
    logMessage("Se han superado las 10000000 iteraciones, deteniendo el programa",CRITICAL);
}
int prueba_ejercicio_2b(){
    /*uso try y throw para agarrar el error, 
    para luego con catch tomar el error e imprimirlo en ej2_archivo_salida y retorno 1.
    */
    try{
        int numerador = 1;
        logMessage("Access Granted", "Federico Zanon");
        int denominador = 0;
        if (denominador == 0){
            throw runtime_error("Division por cero ");
        }
        int resultado = numerador/denominador;  
        cout<<"El resultado es: "<<resultado;
    }
    catch(const exception& e){
        logMessage(e.what(),"hw_1.cpp", __LINE__);
        return 1;
    }
    return 0;
}
int main(){
    logMessage("EJERCICIO 2a: ", INFO);
    prueba_ejercicio_2a();
    logMessage("EJERCICIO 2b: ", INFO);
    prueba_ejercicio_2b();
    return 0;
}