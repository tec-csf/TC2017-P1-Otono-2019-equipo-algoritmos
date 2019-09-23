#include "AVLNode.h"
#include <algorithm>
#include <iostream>

using namespace std;

/* AVL tree */
template <class T>
class AVLTree {
public:
    AVLTree(void);
    ~AVLTree(void);
    bool insertAVL(T key);
    void deleteKey(const T key);
    void printBalance();
    void ordenarAsc();
    void ordenarDes();
    int calculaAltura();
    AVLnode<T>* buscarNodo(const T key);
    int calculaAlturaDeNodo(const T key);
    int nivelDeNodo(const T key);

private:
    AVLnode<T>* root;

    AVLnode<T>* rotateLeft( AVLnode<T> *a );
    AVLnode<T>* rotateRight( AVLnode<T> *a );
    AVLnode<T>* rotateLeftThenRight( AVLnode<T> *n );
    AVLnode<T>* rotateRightThenLeft( AVLnode<T> *n );
    void rebalance( AVLnode<T> *n );
    int height( AVLnode<T> *n );
    void setBalance( AVLnode<T> *n );
    void printBalance( AVLnode<T> *n );
    void clearNode( AVLnode<T> *n );
    void ascendente( AVLnode<T> *n );
    void descendente( AVLnode<T> *n );
    int calculaAltura( AVLnode<T> *n );
    int calculaAlturaDeNodo( AVLnode<T> *n, const T key );
    int nivelDeNodo(AVLnode<T> *n, const T key);
    AVLnode<T>* buscarNodo(AVLnode<T> *n, const T key);
};

/* AVL class definition */
template <class T>
void AVLTree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
AVLnode<T>* AVLTree<T>::rotateLeft(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLTree<T>::rotateRight(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLTree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
AVLnode<T>* AVLTree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLTree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <class T>
void AVLTree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}

template <class T>
void AVLTree<T>::printBalance(AVLnode<T> *n) {
    if (n != NULL) {
        printBalance(n->left);
        std::cout << n->balance << " ";
        printBalance(n->right);
    }
}

template <class T>
AVLTree<T>::AVLTree(void) : root(NULL) {}

template <class T>
AVLTree<T>::~AVLTree(void) {
    delete root;
}

template <class T>
bool AVLTree<T>::insertAVL(T key) {
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
            *n = root,
            *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

template <class T>
void AVLTree<T>::deleteKey(const T delKey) {
    if (root == NULL)
        return;

    AVLnode<T>
        *n       = root,
        *parent  = root,
        *delNode = NULL,
        *child   = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}

template <class T>
void AVLTree<T>::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}


template <class T>
void AVLTree<T>::ordenarAsc(){
    ascendente(root);
}

template <class T>
void AVLTree<T>::ascendente(AVLnode<T> *n){
    if(n != NULL){
        ascendente(n->left);
        cout << n->key << " ";
        ascendente(n->right);
    }
}

template <class T>
void AVLTree<T>::ordenarDes(){
    descendente(root);
}

template <class T>
void AVLTree<T>::descendente(AVLnode<T> *n){
    if(n != NULL)
     {
        descendente(n->right);
        cout << n->key << " ";
        descendente(n->left);
     }
}

template <class T>
int AVLTree<T>::calculaAltura(){
    return calculaAltura(root);
}

template <class T>
int AVLTree<T>::calculaAltura(AVLnode<T> *n) {
   int h = 0;
   if (n != NULL) {
      int l_height = calculaAltura(n->left);
      int r_height = calculaAltura(n->right);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}

template <class T>
int AVLTree<T>::calculaAlturaDeNodo(const T key){
    return calculaAlturaDeNodo(root, key);
}

template <class T>
int AVLTree<T>::calculaAlturaDeNodo(AVLnode<T> *n, const T key){
    int altura=1;
	while( n ){
		if( key == n->key ) return altura;
		else{
			altura++;
			if( key < n->key ) n = n->left;
			else n = n->right;
        }
	}
	return 0;
}

template <class T>
int AVLTree<T>::nivelDeNodo(const T key){
    nivelDeNodo(root, key);
    return 1;
}

template <class T>
int AVLTree<T>::nivelDeNodo(AVLnode<T> *n, const T key){
    int nivel = 0;
    while(n){
        if(n->key == key){
            return nivel;
        }else{
            nivel++;
            if(key < n->key){
                n = n->left;
            }else{
                n = n->right;
            }
        }
    }
    return -1;
}

template <class T>
AVLnode<T>* AVLTree<T>::buscarNodo(const T key){
    return buscarNodo(root, key);
}

template <class T>
AVLnode<T>* AVLTree<T>::buscarNodo(AVLnode<T> *n, const T key){
    if(n == NULL){
        return NULL;
    }else if(n->key == key){
        return n;
    }else if(key < n->key ){
        return buscarNodo(n->left, key);
    }else{
        return buscarNodo(n->right, key);
    }
}
