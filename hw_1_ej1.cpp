#include <iostream>
#include <vector>
using namespace std;

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./ej1
//g++ hw_1_ej1.cpp -Wall -g -o ej1


vector<vector<int>> ejercicio1a(int n){
    vector<vector<int>> matriz(n,vector<int>(n));
    for(int i=0; i<n*n;i++){
        matriz[i/n][i%n]= i+1;
    }
    return matriz;
}
int ejercicio1b(int n){
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