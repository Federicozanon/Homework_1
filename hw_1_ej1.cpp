#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> ejercicio1a(int n){
    /*Usando el tipo vector, creo una matriz de n vectores
    luego completo la misma, empezando desde el 0, de forma  ascendente empezando desde el [0,0] hasta el [n,n]
    */
    vector<vector<int>> matriz(n,vector<int>(n));
    for(int i=0; i<n*n;i++){
        matriz[i/n][i%n]= i+1;
    }
    return matriz;
}
int ejercicio1b(int n){
    /*resultados de i/n y de i%n desde el n*n-1 hasta el 0 (ejemplo con n=3)
    i/n= 2 2 2 1 1 1 0 0 0
    i%n= 2 1 0 2 1 0 2 1 0
    Teniendo en cuenta los resultados de i/n e i%n, imprimo la matriz de forma descendente,
    desde la posicion [n,n] hasta el [0,0]
    */
    vector<vector<int>> matriz = ejercicio1a(n);
    for (int i=n*n-1; i>=0; i--){
        cout<<"M["<<i/n<<"]["<<i%n<<"] = "<<matriz[i/n][i%n]<<"\n";
    }
    return 0;
}

int main(){
    int n;
    cout<<"\ningrese el valor de n: ";
    cin>>n;
    cout<<"\nEJERCICIO 1) a: \n";
    vector<vector<int>> matriz = ejercicio1a(n);

    for (int i=0;i<n*n;i++){
        cout<<matriz[i/n][i%n]<<" ";
        if((i+1)%n==0){
            cout<<endl;
        } 
    }
    cout<< "\nEJERCICIO 1) b: \n";
    ejercicio1b(n);

    cout<<"\n";
    return 0;
}