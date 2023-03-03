#include <iostream>
#include <stdlib.h>

using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;
};

void menu();
void insertarLista(Nodo *&, int);
void mostrarLista(Nodo *);

Nodo *lista = NULL;

int main() {

    menu();
    return 0;
}

void menu(){
    int opcion, dato;

    do{
        cout<<"\t.:Menu:.\n";
        cout<<"1. Insertar elementos en la lista\n";
        cout<<"2. Mostar los elementos de la lista\n";
        cout<<"3. Salir\n";
        cout<<"Opción: ";
        cin>>opcion;

        switch(opcion){
            case 1:
                cout<<"\nDigite un número: ";
                cin>>dato;
                insertarLista(lista, dato);
                cout<<"\n";
                //std::system("pause");
                break;
            case 2:
                mostrarLista(lista);
                cout<<"\n";
                //std::system("pause");
                break;
        }
        //std::system("cls");
    }while(opcion != 3);

}

void insertarLista(Nodo *&lista, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;

    Nodo *aux1 = lista;
    Nodo *aux2;

    while ((aux1 != NULL) && (aux1->dato < n)) {
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }

    if (lista == aux1) {
        lista = nuevo_nodo;
    } else {
        aux2->siguiente = nuevo_nodo;
    }

    nuevo_nodo->siguiente = aux1;

    cout<<"\tElemento "<<n<<" insertado a la lista correctamente\n";
}

void mostrarLista(Nodo *lista){
    Nodo *actual = new Nodo();
    actual = lista;

    while (actual != NULL){
        cout<<actual->dato<<" -> ";
        actual = actual->siguiente;
    }
}

void pause()
{
    std::cout<<"Press any key to continue";
    std::getchar();
}
