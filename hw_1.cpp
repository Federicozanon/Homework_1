#include <hw_1.hpp>

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tuto

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
    ofstream archivo("Homework1/ej2_archivo_salida.txt");
    if (archivo.is_open()){
        archivo<<"["<<nivel<<"] <"<<mensaje<<">\n";
    }
    else{
        cerr<<"Error abriendo el achivo";
    }
}
void prueba_ejercicio_2a(){
    logMessage("Iniciando Valgrind", DEBUG);
    logMessage("Se ha completado la prueba 1",INFO);
    logMessage("El archivo 'hola.txt' no se ha encontrado",WARNING);
    logMessage("Error al acceder a PATH",ERROR);
    logMessage("Se han superado las 10000000 iteraciones, deteniendo el programa",CRITICAL);
}



//EJERCICIO 3 FALTA PRESENTAR EJEMPLOS

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

int insert(lista* lista_ejemplo, unique_ptr<nodo> nuevo_nodo, int pos_lista){
    if(pos_lista<0 || pos_lista>lista_ejemplo->size-1){
        cout<<"la posicion de la lista es invalida";
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
        int i = 0;
        nodo* actual = lista_ejemplo->head.get();
        while(actual->next && i<pos_lista-1){
            actual = actual->next.get();
            i++;
        }
        if(pos_lista>=lista_ejemplo->size){
            cout<<"Se ha superado el largo de la lista, se insertara el nodo al final";
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

int erase(lista* lista_ejemplo, int pos_lista){
    if(pos_lista<0 || lista_ejemplo->size==0){
        cout<<"la posicion de la lista es invalida o la lista esta vacia";
        return 1;
    }
    if (pos_lista==0){
        lista_ejemplo->head = move(lista_ejemplo->head->next);
        if (lista_ejemplo->head == nullptr){
            lista_ejemplo->tail = nullptr;
        }
    }
    else{
        int i = 0;
        nodo* actual = lista_ejemplo->head.get();
        while(actual->next && i<pos_lista-1 && actual->next->next){
            actual = actual->next.get();
            i++;
        }
        
        if (pos_lista>=lista_ejemplo->size){
            cout<<"Se ha superado el largo de la lista, se borrara el ultimo nodo";
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
        cout<<lista_ejemplo->head->value<<" -> ";
        actual = actual->next.get(); 
    }
    cout<<"NULL\n";
    return 0;
}



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
    return 0;
}