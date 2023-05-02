#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "Node.h"

template<class T>
class AVLTree 
{
    public:

        AVLTree();

        ~AVLTree();
        
        Node<T>* insertValue(Node<T>* root, T value);
        void removeValue(*Node<T> value);

        void roll_RR();;
        void roll_LR();
        void roll_RL();;
        void roll_LL();;
        
    private:
        Node<T>* m_root;



};

template<class T>
AVLTree<T>::AVLTree(){}

template<class T>
AVLTree<T>::~AVLTree(){}


/**************************AVLTree functions*****************************/

template<class T>
Node<T>* AVLTree<T>::insertValue(Node<T>* root, T value)
{
    if(root == NULL)
    {
        root = new Node*(value);
        return root;
    }
    else if (root->getValue() >= value )
    {

    }
    else if (root->getValue() < value)
}




#endif