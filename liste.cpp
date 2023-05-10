#ifndef LISTE_CPP
#define LISTE_CPP
#include "liste.h"

using namespace std;

template <typename T>
Liste <T>::Liste():head(NULL), count(0) {}

template <typename T>
Liste<T>::~Liste() {
    Node<T>* del = head;
    while(head) {
        head = head->next;
        delete del;
        del = head;
    }
}

template <typename T>
Node <T>* Liste <T>::createNode(const T& value) {
    Node<T>* temp = new Node<T>;
    temp->data = value;
    temp->parent = NULL;
    temp->next = NULL;
    return temp;
} 

template <typename T>
void Liste<T>::insert(const T& value) {
    Node <T>* nouveau = createNode(value);
    if (!head) {
        nouveau->next = head;
        head = nouveau;
        count++;
        return;
    }
    Node <T>* courant = head;
    while (courant->next) courant = courant->next;
    courant->next = nouveau;
    nouveau->parent = courant;
    count++;
}

template <typename T>
void Liste <T> :: insert (int pos, const T& value)
{
    if (pos < 0 || pos > count){
        cout << "Erreur! La position est invalide." << endl;
        return;
    }
    Node <T>* nouveau = createNode(value);
 
    //Insertion au début
    if (pos == 0){
        nouveau->next = head;
        head = nouveau;
    }
    // Insertion au milieu 
    else{
        Node <T>* courant = head;
        for (int i = 1; i < pos; i++){
            courant = courant->next;
        }
        nouveau->next = courant->next;
        nouveau->parent = courant;
        courant->next = nouveau;
    }
    count++;
}

template <typename T>
void Liste<T> :: remove(T value) {
    Node <T>* courant = head;
    Node <T>* preced;
    while(courant->next) {
        preced = courant;
        if (courant->data == value) break;
        courant = courant->next;
    }
    Node<T>* del = courant;
    preced->next = courant->next;
    courant->next->parent = preced;
    delete del;
}

template <typename T>
void Liste <T> :: remove(int pos) {
    if (pos < 0 || pos > count-1){
        cout << "Erreur! La position est invalide." << endl;
        return;
    }
    if (pos == 0){
        Node <T>* del = head;
        head = head->next;
        head->parent = NULL;
        delete del;
    }
    else{
        Node <T>* courant = head;
        for (int i = 0; i < pos-1; i++){
            courant = courant->next;
        }
        Node <T>* del = courant->next;
        courant->next = courant->next->next;
        courant->next->next->parent = courant;
        delete del;
    }
    count--;
}

template <typename T>
T& Liste<T>::getNode(int pos) const {
    if (pos < 0 || pos > count-1) {
        cout << "Error! La position est invalide";
        assert(false);
    }
    else if (pos == 0) return head->data;
    else {
        Node<T>* courant = head;
        for (int i=0; i<pos; i++) {
            courant = courant->next;
        }
        return courant->data;
    }
}

template <typename T>
void Liste<T>::print() const{
    if (count == 0) {
        cout << "La liste est vide!" << endl;
    }
    Node <T>* courant = head;
    while(courant) {
        cout << courant->data << endl;
        courant = courant->next;
    }
}

template<typename T>
int Liste<T>::length() const {
    return count;
}
#endif