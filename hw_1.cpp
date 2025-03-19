#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
using namespace std;

enum Nivel_importancia{
    SECURITY, DEBUG, INFO, WARNING, ERROR, CRITICAL
};

string funcion_nivel(Nivel_importancia nivel){
    switch (nivel){
        case DEBUG : return "DEBUG";
        case INFO : return "INFO";
        case WARNING : return "WARNING";
        case ERROR : return "ERROR";
        case CRITICAL : return "CRITICAL";
        default : return "UNKNOWN";
    }
}

struct nodo{
    unique_ptr<nodo> next; 
    int value;

    nodo(int val) : next(nullptr), value(val) {}

};
struct lista{
    unique_ptr<nodo> head;
    nodo*tail;
    size_t size;
    lista() : head(nullptr), tail(nullptr), size(0) {}
};

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tuto

//EJERCICIO 1

vector<vector<int>> ejercicio1a(int n){
    vector<vector<int>> matriz(n,vector<int>(n));
    for(int i=0; i<n*n;i++){
        matriz[i/n][i%n]= i+1;
    }
    return matriz;
}
int ejercicio1b(int n){
    vector<vector<int>> matriz = ejercicio1a(n);
    for (int i=0; i<n*n; i++){
        cout<<"M["<<i/n<<"]["<<i%n<<"] = "<<matriz[i/n][i%n]<<"\n";
    }
    return 0;
}


//EJERCICIO 2

void logMessage(string mensaje, Nivel_importancia nivel){
    ofstream archivo("ej2_archivo_salida.txt", ios::app);
    if (archivo.is_open()){
        archivo<<"["<<funcion_nivel(nivel)<<"] <"<<mensaje<<">\n";
        archivo.close();
    }
    else{
        cerr<<"Error abriendo el achivo";
    }
}
void logMessage(string mensaje_de_error, string archivo, int linea_de_codigo){
    ofstream archivo1("ej2_archivo_salida.txt", ios::app);
    if (archivo1.is_open()){
        archivo1<<"In "<<archivo<<"\nLine "<<linea_de_codigo<<"\nError: "<<mensaje_de_error;
        archivo1.close();
    }
    else{
        cerr<<"Error abriendo el archivo";
    }
}
void logMessage(string mensaje_de_acceso, string nombre_usuario){
    ofstream archivo2("ej2_archivo_salida.txt", ios::app);
    if (archivo2.is_open()){
        archivo2<<"[SECURITY] user: "<< nombre_usuario<<" "<<mensaje_de_acceso<<" ";
        archivo2.close();
    }
    else{
        cerr<<"Error abriendo el archivo";
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
        cout<<"Error al ejecutar la funcion"<<e.what();
        return 1;
    }
    return 0;
}


//EJERCICIO 3 

unique_ptr<nodo> create_node(int valor){
    return unique_ptr<nodo> (new nodo(valor));
}

int push_front(lista *lista_ejemplo, unique_ptr<nodo> nuevo_nodo){
    if (lista_ejemplo->size==0){
        lista_ejemplo->head = move(nuevo_nodo);
        lista_ejemplo->tail = lista_ejemplo->head.get();
    }
    else{
        nuevo_nodo->next = move(lista_ejemplo->head);
        lista_ejemplo->head = move(nuevo_nodo);
    }
    lista_ejemplo->size++;
    return 0;
}

int push_back(lista *lista_ejemplo, unique_ptr<nodo> nuevo_nodo){
    if (lista_ejemplo->size==0){
        lista_ejemplo->head = move(nuevo_nodo);
        lista_ejemplo->tail = lista_ejemplo->head.get();
    }
    else{
        lista_ejemplo->tail->next=move(nuevo_nodo);
        lista_ejemplo->tail=lista_ejemplo->tail->next.get();
    }
    lista_ejemplo->size++;
    return 0;
}

int insert(lista* lista_ejemplo, unique_ptr<nodo> nuevo_nodo, long unsigned int pos_lista){
    if(pos_lista<0 || pos_lista>lista_ejemplo->size-1){
        cout<<"la posicion de la lista es invalida\n";
        return 1;
    }
    if (pos_lista==0){
        nuevo_nodo->next = move(lista_ejemplo->head);
        lista_ejemplo->head = move(nuevo_nodo);
        if (lista_ejemplo->size==0){
            lista_ejemplo->tail = lista_ejemplo->head.get();
        }
    }
    else{
        long unsigned int i = 0;
        nodo* actual = lista_ejemplo->head.get();
        while(actual->next && i<pos_lista-1){
            actual = actual->next.get();
            i++;
        }
        if(pos_lista>=lista_ejemplo->size){
            cout<<"Se ha superado el largo de la lista, se insertara el nodo al final\n";
        }
        nuevo_nodo->next = move(actual->next);
        actual->next = move(nuevo_nodo);
        if (!actual->next->next){
            lista_ejemplo->tail = actual->next.get();
        }
    }
    lista_ejemplo->size++;
    return 0;
}

int erase(lista* lista_ejemplo, long unsigned int pos_lista){
    if(pos_lista<0 || lista_ejemplo->size==0){
        cout<<"la posicion de la lista es invalida o la lista esta vacia\n";
        return 1;
    }
    if (pos_lista==0){
        lista_ejemplo->head = move(lista_ejemplo->head->next);
        if (lista_ejemplo->head == nullptr){
            lista_ejemplo->tail = nullptr;
        }
    }
    else{
        long unsigned int i = 0;
        nodo* actual = lista_ejemplo->head.get();
        while(actual->next && i<pos_lista-1 && actual->next->next){
            actual = actual->next.get();
            i++;
        }
        
        if (pos_lista>=lista_ejemplo->size){
            cout<<"Se ha superado el largo de la lista, se borrara el ultimo nodo\n";
        }
        actual->next = nullptr;
        lista_ejemplo->tail = actual;
    }
    lista_ejemplo->size--;
    return 0;
}

int print_list(lista *lista_ejemplo){
    cout<<"Lista completa: \n";
    nodo* actual = lista_ejemplo->head.get();
    while(actual!=nullptr){
        cout<<actual->value<<" -> ";
        actual = actual->next.get(); 
    }
    cout<<"NULL\n";
    return 0;
}

int ejemplo_uso_lista(){
    lista ejemplo_lista;
    cout<<"Creando lista\n";
    print_list(&ejemplo_lista);

    cout<<"Agrego nodos con push_front\n";
    push_front(&ejemplo_lista, create_node(40));
    push_front(&ejemplo_lista, create_node(30));
    push_front(&ejemplo_lista, create_node(20));
    push_front(&ejemplo_lista, create_node(10));
    print_list(&ejemplo_lista);
    
    cout<<"Agrego nodos con push_back\n";
    push_back(&ejemplo_lista, create_node(50));
    push_back(&ejemplo_lista, create_node(60));
    push_back(&ejemplo_lista, create_node(70));
    push_back(&ejemplo_lista, create_node(80));
    print_list(&ejemplo_lista);
    
    cout<<"Agrego nodos usando insert\n";
    insert(&ejemplo_lista, create_node(15), 1);
    insert(&ejemplo_lista, create_node(35), 4);
    insert(&ejemplo_lista, create_node(55), 7);
    insert(&ejemplo_lista, create_node(75), 10);
    print_list(&ejemplo_lista);

    cout<<"elimino nodos con erase\n";
    erase(&ejemplo_lista, 2);
    erase(&ejemplo_lista, 4);
    erase(&ejemplo_lista, 6);
    erase(&ejemplo_lista, 8);
    print_list(&ejemplo_lista);
    
    return 0;
}

//EJERCICIO 4


int main(){
    int n;
    cout<<"ingrese el valor de n: ";
    cin>>n;
    vector<vector<int>> matriz = ejercicio1a(n);

    ejercicio1b(n);
    
    for (int i=0;i<n*n;i++){
        cout<<matriz[i/n][i%n]<<" ";
        if((i+1)%n==0){
            cout<<endl;
        }
        
    }
    prueba_ejercicio_2a();

    prueba_ejercicio_2b();

    ejemplo_uso_lista();

    return 0;
}