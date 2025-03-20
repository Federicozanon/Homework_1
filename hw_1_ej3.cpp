#include <memory>
#include <iostream>
using namespace std;

/*
Para la implementacion de la lista, uso coomo unique pointer head y como raw pointer tail
Uso move() mover el nodo y transferir la propiedad de unique pointer del nodo a otro
y uso .get para simplemente agarrar un puntero
*/
struct nodo{
    unique_ptr<nodo> next; 
    int value;
    // inicializo el nodo con el puntero next a null
    nodo(int val) : next(nullptr), value(val) {}

};
struct lista{
    unique_ptr<nodo> head;
    nodo*tail;
    size_t size;
    //inicializo la lista con head y tail como punteros a null y con tamanio de la lista a 0
    lista() : head(nullptr), tail(nullptr), size(0) {}
};

unique_ptr<nodo> create_node(int valor){
    return unique_ptr<nodo> (new nodo(valor));
}

int push_front(lista *lista_ejemplo, unique_ptr<nodo> nuevo_nodo){
    /*Si la lista es 0, inserto el nodo directamente al head y apunto tail a head
    sino primero pongo al siguiente de nuevo_nodo como head
    y al head como nuevo_nodo
    */
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
    /*Si la lista es 0 mismo caso que el anterior
    sino primero pongo al siguiente del tail como nuevo_nodo
    y el tail ahora lo apunto a nuevo_nodo
    */
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
    /*Si la pos_lista es 0, pongo al siguiente del nuevo nodo como head
    y el head lo apunto a nuevo_nodo
    Si ademas de eso el size de la lista era 0, apunto tail a head
    Caso contrario, mientras la lista no termine o todavia no haya llegado al anterior de pos_lista,
    itero hasta que pase uno de los dos.
    Pongo al siguiente de mi nuevo_nodo como el siguiente de mi nodo actual
    y al siguiente de actual como nuevo nodo. Si me paso del largo de la lista,
    apunto mi tail a mi nuevo_nodo, que seria el nodo actual->next
    */
    if(pos_lista<0){
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
            cout<<"Se ha superado el largo de la lista, se insertara el nodo con el valor "<<nuevo_nodo->value<< " al final\n";
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
    /*Si la pos_inicial es 0 muevo mi head al siguiente de head,
    lo que haria que el head inicial, que quedo sin puntero, 
    al terminar la funcion se haga free automaticamente ya que estoy usando smart pointers.
    En el caso de que al eliminar el nodo se haga una lista vacia, apunto el tail a null
    Sino, mientras la lista no termine o todavia no haya llegado al anterior de pos_lista,
    itero hasta que pase uno de los dos.
    Si me paso del largo de la lista, apunto el siguiente del actual a null
    y apunto el tail a mi nodo actual.
    Si no pasa esto, simplemente apunto el siguiente del actual al actual->next->next
    lo que haria que el nodo que quiera eliminar quede resferenciado,
    y al final de la ejecucion se haga free automatico
    */
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
            actual->next = nullptr;
            lista_ejemplo->tail = actual;
        }
        else{
            actual->next = move(actual->next->next);
        }
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
    insert(&ejemplo_lista, create_node(95), 12);
    insert(&ejemplo_lista, create_node(75), 10);
    print_list(&ejemplo_lista);

    cout<<"elimino nodos con erase\n";
    erase(&ejemplo_lista, 2);
    erase(&ejemplo_lista, 4);
    erase(&ejemplo_lista, 6);
    print_list(&ejemplo_lista);
    erase(&ejemplo_lista, 10);
    print_list(&ejemplo_lista);
    
    
    return 0;
}
int main(){
    cout<<"EJERCICIO 3): \n";
    ejemplo_uso_lista();
    return 0;
}