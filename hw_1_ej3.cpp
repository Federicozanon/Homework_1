#include <memory>
#include <iostream>
using namespace std;

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./ej3
//g++ hw_1_ej3.cpp -Wall -g -o ej3

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
    while(actual!=nullptr /*|| actual->next!=nullptr*/){
        cout<<actual->value<<" -> ";
        actual = actual->next.get(); 
    }
    cout<<"\n";
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
int main(){
    cout<<"EJERCICIO 3): \n";
    ejemplo_uso_lista();
    return 0;
}