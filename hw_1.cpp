#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
#include <hw_1.hpp>
using namespace std;
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./mi_programa

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

//EJERCICIO 3

int create_node(){
    unique_ptr<int> nuevo_nodo(new int);
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