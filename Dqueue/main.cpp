//
//  main.cpp
//  Dqueue
//
//  Created by Angel Trevino on 10/3/17.
//  Copyright © 2017 Angel Odiel Treviño Villanueva. All rights reserved.
//

#include <iostream>

using namespace std;
class Nodo
{	public:
    Nodo *pSig, *pAnt;
    int iInfo;
    Nodo( ) { pSig = NULL; pAnt=NULL; }
    Nodo (int iDato) { iInfo = iDato;  pSig = NULL; pAnt=NULL; }
    Nodo (int iDato, Nodo *pSiguiente, Nodo *pAnterior)
    { iInfo = iDato; pSig = pSiguiente;  pAnt=pAnterior;}
};
class Deque
{
    friend ostream& operator << (ostream & os, const Deque &D)
    {
        Nodo *pP = D.pInicio;
        while (pP != NULL)
        {
            os << pP->iInfo << " ";
            pP = pP->pSig;
        }
        os << endl;
        return os;
    }
private:
    Nodo *pInicio, *pFinal;
public:
    //Inicializando la lista como lista vacía
    Deque() { pInicio = NULL; pFinal=NULL; }
    //Copy constructor
    Deque (const Deque &D)
    {
        pInicio=pFinal=NULL;
        Nodo *pP;
        pP= D.pInicio;
        while (pP!= NULL)
        {
            push_back(pP->iInfo);
            pP=pP->pSig;
        }
    }
    //Sobrecarga del =
    Deque& operator = (const Deque& D)
    {
        if (this != &D)
        {
            //Borrar todos los nodos del this (destructor)
            while ( pInicio != NULL)
                pop_back();
            //Copiar la fila (copy constructor)
            Nodo *pAnterior, *pNuevo;
            Nodo *pP = D.pInicio;
            pInicio = NULL;
            if ( D.pInicio != NULL)
            {   //Crear el primer nodo del this
                pAnterior = new Nodo(pP->iInfo);
                pP = pP->pSig;
                pInicio = pAnterior;
                //Crear los demás nodos del this
                while ( pP != NULL )
                {   //Crea el nodo
                    pNuevo = new Nodo(pP->iInfo);
                    //Enlaza el nuevo con los anteriores
                    pAnterior->pSig = pNuevo;
                    pNuevo->pAnt=pAnterior;
                    //Avanza para crear los siguientes
                    pP = pP->pSig;
                    pAnterior = pAnterior->pSig;
                }
            }
        }
        return *this;
    }
    
    //Borra todos los nodos que queden en la lista
    ~Deque(){
        while (!pInicio != NULL)
            pop_back();
    }
    
    //La lista está vacía cuando pInicio es NULL
    bool empty() { return (pInicio == NULL); }
    
    //Agregar un nodo al inicio de la lista
    void push_front(int iValor)
    {
        //Crear un nodo
        Nodo *pNuevo = new Nodo(iValor);// pInicio);
        if (pInicio!=NULL)
        {
            pNuevo->pSig = pInicio;
            pInicio->pAnt=pNuevo;
            pInicio=pNuevo;
        }
        else
            pInicio=pFinal=pNuevo;
        
    }
    // push back
    void push_back(int iValor)
    {
        Nodo *pNuevo=new Nodo(iValor);
        if (pFinal !=NULL)
        {
            pFinal->pSig=pNuevo;
            pNuevo->pAnt=pFinal;
            pFinal=pNuevo;
        }
        else
            pInicio=pFinal=pNuevo;
    }
    
    //Quita el nodo que está al final pop back
    void pop_back()
    {
        Nodo *pP = pFinal;
        pFinal=pFinal->pAnt;
        if (pFinal ==NULL)
            pInicio=NULL;
        delete pP;
    }
    //Borrar al frente de la lista
    //Precondición: Que la lista no esté vacia
    void pop_front()
    {
        Nodo *pP;
        pP=pInicio;
        pInicio=pInicio->pSig;
        if (pInicio == NULL)
            pFinal=NULL;
        delete(pP);
    }
    
    //Regresa el contenido del nodo apuntado por inicio
    int top_front() { return pInicio->iInfo; }
    
    
    //Regresa el contenido del nodo apuntado por Final
    int top_back() { return pFinal->iInfo; }
    
    //encontrar y regresar el elemento mas chico
    int menor(){
        
        int menor;
        if(pInicio !=NULL){//checa si no esta vacio
            menor = pInicio -> iInfo;
            Nodo *pP = pInicio;
        
            while(pP != NULL){//busca el menor
                if(pP -> iInfo < menor){
                    menor = pP -> iInfo;
                }
            pP = pP -> pSig;
            }
            
        }else{
                menor = -1;//si esta vacio
            }
        return menor;
            
    }
    
    //insertar despues del nodo N donde N es un parametro, el 1 nodo es el 1 no cero
    void inserta(int dato, int posicion){
        Nodo *pNuevo=new Nodo(dato);
        Nodo *pP = pInicio;
        int cont = 1;
        while(cont < posicion && pP != NULL){
            pP = pP -> pSig;
            cont++;
        }
        
        if(cont - posicion == 0){
        
            if(pP -> pSig == NULL){
                pNuevo -> pAnt = pP;
                pP -> pSig = pNuevo;
                pFinal = pNuevo;
            }else{
                pP -> pSig -> pAnt = pNuevo;
                pNuevo -> pSig = pP -> pSig ;
                pP -> pSig = pNuevo;
                pNuevo -> pAnt = pP;
            }
        }
    }
    
    //eliminar duplicados;
    void EliminarRepetidos(){
        Nodo *pP = pInicio; // corre desde el principio hasta el penultimo
        Nodo *pQ; ////corre desde pP hasta el final
        Nodo *pDelete; //auxiliar para borrar
        while(pP != NULL){ //se coloca hasta el penultimo nodo
            
            pQ = pP -> pSig;
            while(pQ != NULL){//corre de pP hasta el final
                if((pQ -> iInfo) == (pP -> iInfo)){//checa si su info es igual
                    if(pQ -> pSig == NULL){
                        pDelete = pFinal;
                        pQ = pQ-> pAnt;
                        pQ -> pSig = NULL;
                        pFinal = pQ;
                        delete pDelete;
                    }else{
                        pDelete = pQ;
                        pQ = pDelete -> pAnt;
                        pQ -> pSig = pDelete -> pSig;
                        pDelete -> pSig -> pAnt = pQ;
                        delete pDelete;
                    }
                }
                pQ = pQ -> pSig;
            }
            pP = pP -> pSig;
        }
    }
};
//////////////////////
int main()
{
    Deque D;
    D.push_back(5);
    D.push_back(3);
    D.push_front(1);
    cout<<D;
    cout << "menor "<< D.menor() << endl;
    D.inserta(3, 2);
    cout << D;
    D.EliminarRepetidos();
    cout << D;
    
    
    return 0;
}
