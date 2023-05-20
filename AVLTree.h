#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "Node.h"
#include <iostream>
#include "exception.h"
 
using namespace std;




//might need to change NULLs to nullptr.....



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

        explicit AVLTree(Node<T> root);
        /*
        * copy c'tor
        */
        AVLTree(const AVLTree& originalTree);//TODO

        /*
        * d'tor
        */
        ~AVLTree() = default;//not actually default

        Node<T>* getRoot() const;

        void setRoot(Node<T>* root);
        
        /**** Methods ****/

        /*
        * calculates the height difference between the right and left nodes
        * @param node - the nodes whose son's heights need to be compared
        * @return
        *       height difference between left and right nodes
        */
        int balanceFactor(Node<T>* node);

        /*
        * calculates the height of a given node
        * @param node - the nodes whose height needs ot be calculated
        * @return
        *       the node's height
        */
        int calculateHeight(Node<T>* node) const;

        /*
        * removes the node from the tree and rebalances it via recursion
        * @param node - the node that needs to be removed
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        Node<T>* removeValue(Node<T>* node, T value);

        /*
        * inserts node into the tree with the corresponding value and rebalances it via recursion
        * @param node - the node that needs to be added
        *        value - the value of the added node
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        Node<T>* insertValue(Node<T>* node, T value);

        /*
        * balances the tree from this root downwards
        * @param node - the root that is to be balanced
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        Node<T>* balance(Node<T>* node, T value);

        Node<T>* findObject(Node<T>* node, T value);

        void setRightNode(Node<T>* parent, T value);
    
        void setLeftNode(Node<T>* parent, T value);

        ostream& inOrder(ostream& os, const Node<T>* node) const;

        ostream& postOrder(ostream& os, const Node<T>* node) const;

        ostream& preOrder(ostream& os, const Node<T>* node) const;


    private:

        Node<T>* nodeWithMinimumValue(Node<T>* node);
        Node<T>* deletionBalance(Node<T>* node);

        /*
        * different methods for balancing an AVLTree 
        */
        Node<T>* rotateLeft(Node<T>* parent);
        Node<T>* rotateRight(Node<T>* parent);
        
        Node<T>* m_root;
};


/***********************AVLTree C'tors and D'tors************************/


template<class T>
AVLTree<T>::AVLTree() : m_root(NULL){}

template<class T>
AVLTree<T>::AVLTree(Node<T> root) : m_root(&root){}

template<class T>
AVLTree<T>::AVLTree(const AVLTree& originalTree)
{
    m_root = originalTree.getRoot();
}


/**************************AVLTree Functions*****************************/


template<class T>
void AVLTree<T>::setRightNode(Node<T>* parent, T value)
{
    parent->setRightNode(insertValue(parent->getRightNode(), value));
}

template<class T>
void AVLTree<T>::setLeftNode(Node<T>* parent, T value)
{
    parent->setLeftNode(insertValue(parent->getLeftNode(), value));
}

template<class T>
Node<T>* AVLTree<T>::getRoot() const
{
    return m_root;
}

template<class T>
void AVLTree<T>::setRoot(Node<T>* root)
{
    m_root = root;
}

template<class T>
int AVLTree<T>::calculateHeight(Node<T>* node) const
{
    int left, right;
    if(node->getLeftNode() == NULL)
    {
        left = 0;
    }
    else
    {
        left = node->getLeftNode()->getHeight();
    }

    if(node->getRightNode() == NULL)
    {
        right = 0;
    }
    else
    {
        right = node->getRightNode()->getHeight();
    }

    if (left == 0 && right == 0)
    {
        return 1;//maybe 0
    }

    else if (left >= right)
    {
        return (1 + node->getLeftNode()->getHeight());
    }
    else
    {
        return (1 + node->getRightNode()->getHeight());
    }
}

template<class T>
int AVLTree<T>::balanceFactor(Node<T>* node)
{
    if(node == NULL)
    {
        return 0;
    }

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
Node<T>* AVLTree<T>::nodeWithMinimumValue(Node<T>* node)
{
    Node<T>* current = node;
    while (current->getLeftNode() != NULL)
        current = current->getLeftNode();
    return current;
}

template<class T>
Node<T>* AVLTree<T>::removeValue(Node<T>* node, T value)
{
    if(node == NULL)
    {
        throw NodeDoesntExists();//might break the code
        return node;
    }

    else if(value > node->getValue())
    {
        node->setRightNode(removeValue(node->getRightNode(), value));
    }

    else if(value < node->getValue())
    {
        node->setLeftNode(removeValue(node->getLeftNode(), value));
    }
    // ^^ can probably be implemented with the find method ^^
    else
    {
        if (node->getLeftNode() == NULL && node->getRightNode() == NULL)
        {
            return NULL;//might need to be nullptr
        }
        else if (node->getLeftNode() == NULL)
        {
            Node<T>* tmp = node->getRightNode();
            delete (node);
            tmp->setHeight(calculateHeight(tmp));
            return tmp;
        }
        else if (node->getRightNode() == NULL)
        {
            Node<T>* tmp = node->getLeftNode();
            delete node;
            tmp->setHeight(calculateHeight(tmp));
            return tmp;
        }

        Node<T> *tmp = nodeWithMinimumValue(node->getRightNode());
        node->setValue(tmp->getValue());
        node->setRightNode(removeValue(node->getRightNode(), tmp->getValue()));
    }
    node->setHeight(calculateHeight(node));

    node = deletionBalance(node);

    return node;
}

template<class T>
Node<T>* AVLTree<T>::insertValue(Node<T>* node, T value)
{
    if(node == NULL)
    {
        node = new Node<T>(value);
        if(node == NULL){
            throw BadAllocation();
        }
        return node;
    }

    else if(node->getValue() == value){
        throw NodeAlreadyExists();
    }

    else if (node->getValue() > value )
    {
        setLeftNode(node, value);

    }

    else if (node->getValue() < value)
    {        
        setRightNode(node, value);
    }

    node = balance(node, value);

    node->setHeight(calculateHeight(node));
    
    node = balance(node, value);

    return node;
}

template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node, T value)
{
    int balance = balanceFactor(node);

	if (balance > 1 && value < node->getLeftNode()->getValue())
    {
		return rotateRight(node);
    }

	if (balance < -1 && value > node->getRightNode()->getValue())
    {
		return rotateLeft(node);
    }

	if (balance > 1 && value > node->getLeftNode()->getValue())
	{
		node->setLeftNode(rotateLeft(node->getLeftNode()));
		return rotateRight(node);
	}

	if (balance < -1 && value < node->getRightNode()->getValue())
	{
		node->setRightNode(rotateRight(node->getRightNode()));
		return rotateLeft(node);
	}

    return node;
}

template <class T>
Node<T>* AVLTree<T>::deletionBalance(Node<T>* node)
{
    if(balanceFactor(node->getLeftNode()) > 1 || balanceFactor(node->getLeftNode()) < -1)
    {
        node->setLeftNode(balance(node->getLeftNode(), node->getLeftNode()->getValue()));

    }
    if(balanceFactor(node->getRightNode()) > 1 || balanceFactor(node->getRightNode()) < -1)
    {
        node->setRightNode(balance(node->getRightNode(), node->getRightNode()->getValue()));

    }
    if(balanceFactor(node) == 2 && balanceFactor(node->getLeftNode()) == 1)
    {
        node = rotateLeft(node);
    }
    else if(balanceFactor(node) == 2 && balanceFactor(node->getLeftNode()) == -1)
    {
        node->setLeftNode(rotateLeft(node->getLeftNode()));
        node = rotateRight(node);
    }
    else if(balanceFactor(node) == 2 && balanceFactor(node->getLeftNode()) == 0)
    {
        node = rotateLeft(node);
    }
    else if(balanceFactor(node) == -2 && balanceFactor(node->getLeftNode()) == -1)
    {
        node = rotateRight(node);
    }
    else if(balanceFactor(node) == -2 && balanceFactor(node->getLeftNode()) == 1)
    {
        node->setRightNode(rotateRight(node->getRightNode()));
        node = rotateRight(node);
    }
    else if(balanceFactor(node) == -2 && balanceFactor(node->getLeftNode()) == 0)
    {
        node = rotateLeft(node);
    }
    return node;
}

template<class T>
Node<T>* AVLTree<T>::findObject(Node<T>* node, T value)
{
    if(node == NULL)
    {
        throw NodeDoesntExists();
    }

    else if(node->getValue() == value)
    {
        return node;
    }

    else if(node->getValue() > value)
    {
        return findObject(node->getLeftNode(), value);
    }

    else
    {
        return findObject(node->getRightNode(), value);
    }
}

template<class T>
Node<T>* AVLTree<T>::rotateLeft(Node<T>* parent)
{
	Node<T>* child = parent->getRightNode();
	Node<T>* grandChild = child->getLeftNode();

	child->setLeftNode(parent);
	parent->setRightNode(grandChild);

	parent->setHeight(calculateHeight(parent));
	child->setHeight(calculateHeight(child));
    if( grandChild != nullptr)
    {
        grandChild->setHeight(calculateHeight(grandChild));
    }


	return child;
}

template<class T>
Node<T>* AVLTree<T>::rotateRight(Node<T>* parent)
{
    Node<T>* child = parent->getLeftNode();
	Node<T>* grandChild = child->getRightNode();

	child->setRightNode(parent);
	parent->setLeftNode(grandChild);

	parent->setHeight(calculateHeight(parent));
	child->setHeight(calculateHeight(child));
    if( grandChild != nullptr)
    {
        grandChild->setHeight(calculateHeight(grandChild));
    }

	return child;
}


/************************AVLTree Print Functions*************************/


template<class T>
ostream& AVLTree<T>::inOrder(ostream& os, const Node<T>* node) const
{
    if (node == NULL)
    {
        return os;
    }
    else
    {
        inOrder(os, node->getLeftNode());
        os << node->getValue() << " ";
        inOrder(os, node->getRightNode());
        return os;
    }
}

template<class T>
ostream& AVLTree<T>::postOrder(ostream& os, const Node<T>* node) const
{
    if (node == NULL)
    {
        return os;
    }
    else
    {
        postOrder(os, node->getLeftNode());
        postOrder(os, node->getRightNode());
        os << node->getValue() << " ";
        return os;
    }
}

template<class T>
ostream& AVLTree<T>::preOrder(ostream& os, const Node<T>* node) const
{
    if(node == NULL)
    {
        return os;
    }
    else
    {  
        os << node->getValue() << " ";
        preOrder(os, node->getLeftNode());
        preOrder(os, node->getRightNode());
        return os;
    }
}



#endif