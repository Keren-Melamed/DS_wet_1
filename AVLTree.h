#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "Node.h"

template<class T>
class AVLTree 
{
    public:

        AVLTree();

        ~AVLTree();
        
        int height(Node<T>* node);//maybe we should change it so that each node contains the height so the time complexity is lower

        int heightDiff(Node<T>* node);

        Node<T>* nodeWithMimumValue(Node<T>* node);

        Node<T>* removeValue(Node<T>* node, T value);

        Node<T>* insertValue(Node<T>* root, T value);

        Node<T>* balance(Node<T>* node);

        Node<T>* roll_RR(Node<T>* node);
        Node<T>* roll_LR(Node<T>* node);
        Node<T>* roll_RL(Node<T>* node);
        Node<T>* roll_LL(Node<T>* node);
        //assuming there's an = operator for node, the default should work i think, might cause a leak though cause copying pointers
        
    private:
        Node<T>* m_root;



};

template<class T>
AVLTree<T>::AVLTree(){}

template<class T>
AVLTree<T>::~AVLTree(){}


/**************************AVLTree functions*****************************/

template<class T>
int AVLTree<T>::height(Node<T>* node)
{
    int nodeHeight = 0;

    if (node != NULL)
    {
       int leftNodeHeight = height(node->getLeftNode());
       int rightNodeHeight = height(node->getRightNode());
       if (leftNodeHeight >= rightNodeHeight)
       {
            nodeHeight = leftNodeHeight + 1;
       }
       else
       {
            nodeHeight = rightNodeHeight +1;
       }
    }

    return nodeHeight;
}

template<class T>
int AVLTree<T>::heightDiff(Node<T>* node)
{
    return (height(node->getLeftNode()) - height(node->getRightNode()));
}

template<class T>
Node<T>* AVLTree<T>::nodeWithMimumValue(Node<T>* node)
{
    Node<T>* current = node;
    while (current->getLeftNode() != NULL)
    {
        current = current->getLeftNode();
    }
    return current;
}

template<class T>
Node<T>* AVLTree<T>::removeValue(Node<T>* node, T value)
{
    if(node == NULL)
    {
        return node;
    }

    else if(value > node->getValue())
    {
        node->getRightNode() = removeValue(node->getRightNode(), value);
    }

    else if(value < node->getValue())
    {
        node->getLeftNode() = removeValue(node->getLeftNode(), value);
    }

    else
    {
        if(node->getLeftNode() == NULL || node->getRightNode() == NULL)
        {
            Node<T>* tmp = node->getLeftNode() ? node->getLeftNode() : node->getRightNode();
            if(tmp == NULL)
            {
                tmp = node;
                node = NULL;
            }
            else
            {
                *root = *tmp;
            }
            free(tmp);
        }

        else
        {
            Node *temp = nodeWithMimumValue(node->getRightNode());
            node->getValue() = temp->getValue();
            node->getRightNode() = deleteNode(node->getRightNode(), temp->getValue());
        }
    }
    if (node = NULL)
    {
        return node;
    }

    balance(node);
    return node;
}

template<class T>
Node<T>* AVLTree<T>::insertValue(Node<T>* node, T value)
{
    if(node == NULL)
    {
        node = new Node*(value);
        return node;
    }
    else if (node->getValue() > value )
    {
        node->setLeftNode() = insertValue(node->getLeftNode(), value);
        node = balance(node);
    }
    else if (node->getValue() <= value)
    {
        node->setRightNode() = insertValue(node->getRightNode(), value);
        node = balance(node);
    }
    return node;
}

template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node)
{
    int diff = heightDiff(node);

    else if (diff >= 2)
    {
        if (heightDiff(node->getLeftNode()) >= 1)
        {
            node = roll_LL(node);
        }
        else
        {
            node = roll_LR(node);
        }
    }

    else if(diff <= -2)
    {
        if(heightDiff(node->getRightNode()) >= 1)
        {
            node = roll_RR(node);
        }
        else
        {
            node = roll_RL(node);
        }
    }
    return node;
}

template<class T>
Node<T>* AVLTree<T>::roll_RR(Node<T>* node)
{
    Node<T>* parent = node, topParent = node->getRightNode();
    parent->setRightNode() = topParent.getLeftNode();
    topParent.setLeftNode() = parent;
    return topParent;
    
}

template<class T>
Node<T>* AVLTree<T>::roll_LR(Node<T>* node)
{
    Node<T>* parent = node, topParent = node->getLeftNode(), topParent2 = node->getLeftNode()->getRightNode();
    parent->setLeftNode() = topParent2.getRightNode();
    topParent.setRightNode() = topParent2.getLeftNode();
    topParent2.setRightNode() = parent;
    topParent2.setLeftNode() = topParent;

    return topParent2;
}

template<class T>
Node<T>* AVLTree<T>::roll_RL(Node<T>* node)
{
    Node<T>* parent = node, topParent = node->getRightNode(), topParent2 = node->getRightNode()->getLeftNode();
    parent->getRightNode() = topParent2.getLeftNode();
    topParent.setLeftNode() = topParent2.getRightNode();
    topParent2.setLeftNode() = parent;
    topParent2.setRightNode() = topParent;

    return topParent2;
}

template<class T>
Node<T>* AVLTree<T>::roll_LL(Node<T>* node)
{
    Node<T>* parent = node, topParent = node->getLeftNode();
    parent->setLeftNode() = topParent.getRightNode();
    topParent.setRightNode() = parent;
    return topParent;
}


#endif