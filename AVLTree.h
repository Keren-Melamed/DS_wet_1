#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "Node.h"
#include <iostream>

template<class T>
class AVLTree 
{
    public:

        /**** c'tors amd d'tors ****/

        /*
        *c'tor of the AVLTree class
        *
        * @result
        *       an instance of AVLTree
        */
        AVLTree();

        /*
        * copy c'tor
        */
        AVLTree(const AVLTree& originalTree);//TODO

        /*
        * d'tor
        */
        ~AVLTree();

        Node<T>* getRoot() const;
        
        /**** Methods ****/

        /*
        * calculates the height difference between the right and left nodes
        * @param node - the nodes who's son's heights need to be compared
        * @return
        *       height difference between left and right nodes
        */
        int heightDiff(Node<T>* node);

        /*
        * calculates the height of a given node
        * @param node - the nodes who's height needs ot be calculated
        * @return
        *       the node's height
        */
        int calculateHeight(Node<T>* node) const;

        /*
        * finds the node with the lowest value
        * @param node - node to start counting from
        * @return
        *       pointer to the node with thte lowest value in the tree
        */
        Node<T>* nodeWithMinimumValue(Node<T>* node) const;

        /*
        * removes the node from the tree and rebalances it via recursion
        * @param node - the node that needs to be removed
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        Node<T>* removeValue(Node<T>* node, T value);

        /*
        * inserts node into the tree with the corrosponding value and rebalances it via recursion
        * @param node - the node that needs to be added
        *        value - the value of the added node
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        Node<T>* insertValue(Node<T>* root, T value);

        /*
        * balances the tree from this root downwards
        * @param node - the root that is to be balanced
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        Node<T>* balance(Node<T>* node);

        std::ostream& inOrder(std::ostream& os, const Node<T>* node) const;

        std::ostream& postOrder(std::ostream& os, const Node<T>* node) const;

        std::ostream& preOrder(std::ostream& os, const Node<T>* node) const;


    private:

        /*
        * different methods for balancing an AVLTree 
        */
        Node<T>* roll_RR(Node<T>* node);
        Node<T>* roll_LR(Node<T>* node);
        Node<T>* roll_RL(Node<T>* node);
        Node<T>* roll_LL(Node<T>* node);
        //assuming there's an = operator for node, the default should work i think, might cause a leak though cause copying pointers
        
        Node<T>* m_root;
};

template<class T>
AVLTree<T>::AVLTree() :
    m_root(NULL)
{}

template<class T>
AVLTree<T>::~AVLTree(){}


/**************************AVLTree functions*****************************/

template<class T>
Node<T>* AVLTree<T>::getRoot() const
{
    return m_root;
}

template<class T>
int AVLTree<T>::calculateHeight(Node<T>* node) const
{
    if (node->getLeftNode()->getHeight() >= node->getRightNode()->getHeight())
    {
        return node->getLeftNode()->getHeight();
    }
    else
    {
        return node->getRightNode()->getHeight();
    }
}
//maybe make this -1 at the end? cause the height of a single node should be zero

template<class T>
int AVLTree<T>::heightDiff(Node<T>* node)
{
    int left, right;
    if (node->getLeftNode() == NULL)
    {
        left = 0;
    }
    else
    {
        left = node->getLeftNode()->getHeight();
    }

    if (node->getRightNode() == NULL)
    {
        right = 0;
    }
    else
    {
        right = node->getRightNode()->getHeight();
    }
    return (left - right);
}

template<class T>
Node<T>* AVLTree<T>::nodeWithMinimumValue(Node<T>* node) const
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
                *node = *tmp;
            }
            delete(tmp);
        }

        else
        {
            Node<T>* temp = nodeWithMimumValue(node->getRightNode());
            node->getValue() = temp->getValue();
            node->setRightNode(deleteNode(node->getRightNode(), temp->getValue()));
        }
    }
    if (node == NULL)
    {
        return node;
    }

    balance(node);
    return node;
}

template<class T>
Node<T>* AVLTree<T>::insertValue(Node<T>* node, T value)
{
    std::cout << "insertValue has been accessed" << std::endl;
    if(node == NULL)
    {
        std::cout << " the node was null" << std::endl;
        node = new Node<T>(value);
        //if not throw excpetion
        return node;
    }

    //if ( node already exits throw already exits exceptions)
    if(node->getValue() == value){
        //throw 
    }

    else if (node->getValue() > value )
    {
        std::cout << "the value inserted was smaller" << std::endl;
        node->setLeftNode(insertValue(node->getLeftNode(), value));
        node->setHeight(calculateHeight(node));
        node = balance(node);
    }

    else if (node->getValue() <= value)
    {
        std::cout << "the value inserted was bigger" << std::endl;
        node->setRightNode(insertValue(node->getRightNode(), value));
        node->setHeight(calculateHeight(node));
        node = balance(node);
    }

    return node;
}
//might need to check that the right and eft nodes arnt null

template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node)
{
    int diff = heightDiff(node);

    if (diff >= 2)
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
    Node<T>* parent = node;
    Node<T>* topParent = node->getRightNode();
    parent->setRightNode(topParent->getLeftNode());
    topParent->setLeftNode(parent);
    return topParent;
    
}

template<class T>
Node<T>* AVLTree<T>::roll_LR(Node<T>* node)
{
    Node<T>* parent = node;
    Node<T>* topParent = node->getLeftNode();
    Node<T>* topParent2 = node->getLeftNode()->getRightNode();
    parent->setLeftNode(topParent2->getRightNode());
    topParent->setRightNode(topParent2->getLeftNode());
    topParent2->setRightNode(parent);
    topParent2->setLeftNode(topParent);

    return topParent2;
}

template<class T>
Node<T>* AVLTree<T>::roll_RL(Node<T>* node)
{
    Node<T>* parent = node;
    Node<T>* topParent = node->getRightNode();
    Node<T>* topParent2 = node->getRightNode()->getLeftNode();
    parent->setRightNode(topParent2->getLeftNode());
    topParent->setLeftNode(topParent2->getRightNode());
    topParent2->setLeftNode(parent);
    topParent2->setRightNode(topParent);

    return topParent2;
}

template<class T>
Node<T>* AVLTree<T>::roll_LL(Node<T>* node)
{
    Node<T>* parent = node;
    Node<T>* topParent = node->getLeftNode();
    parent->setLeftNode(topParent->getRightNode());
    topParent->setRightNode(parent);
    return topParent;
}

template<class T>
std::ostream& AVLTree<T>::inOrder(std::ostream& os, const Node<T>* node) const
{
    //std::cout << "inorder has been accessed" << std::endl;
    if (node == NULL)
    {
        return os;
    }
    else
    {
        os << inOrder(os, node->getLeftNode());
        os << node->getValue() << " ";
        os << inOrder(os, node->getRightNode());
        return os;
    }
}

template<class T>
std::ostream& AVLTree<T>::postOrder(std::ostream& os, const Node<T>* node) const
{
    if (node == NULL)
    {
        return os;
    }
    else
    {
        os << postOrder(os, node->getLeftNode());
        os << postOrder(os, node->getRightNode());
        os << node->getValue() << " ";
        return os;
    }
}

template<class T>
std::ostream& AVLTree<T>::preOrder(std::ostream& os, const Node<T>* node) const
{
    if(node == NULL)
    {
        return os;
    }
    else
    {  
        os << node->getValue() << " ";
        os << preOrder(os, node->getLeftNode());
        os << preOrder(os, node->getLeftNode());
        return os;
    }
}


#endif