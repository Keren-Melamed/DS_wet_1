#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "Node.h"
#include <iostream>
#include "exception.h"
 
using namespace std;

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
        AVLTree(Node<T> root);
        /*
        * copy c'tor
        */
        AVLTree(const AVLTree& originalTree);//TODO

        /*
        * d'tor
        */
        ~AVLTree();

        Node<T>* getRoot() const;

        void setRoot(Node<T>* root);
        
        /**** Methods ****/

        /*
        * calculates the height difference between the right and left nodes
        * @param node - the nodes who's son's heights need to be compared
        * @return
        *       height difference between left and right nodes
        */
        int BalanceFactor(Node<T>* node);

        /*
        * calculates the height of a given node
        * @param node - the nodes who's height needs ot be calculated
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
        Node<T>* balance(Node<T>* node, T value);

        void setRightNode(Node<T>* parent, int value);
    
        void setLeftNode(Node<T>* parent, int value);

        void printTheTree();

        ostream& inOrder(ostream& os, const Node<T>* node) const;

        ostream& postOrder(ostream& os, const Node<T>* node) const;

        ostream& preOrder(ostream& os, const Node<T>* node) const;


    private:

        /*
        * different methods for balancing an AVLTree 
        */
        Node<T>* rotateLeft(Node<T>* parent);
        Node<T>* rotateRight(Node<T>* parent);
        
        Node<T>* m_root;
};

template<class T>
AVLTree<T>::AVLTree() : m_root(NULL){}

template<class T>
AVLTree<T>::AVLTree(Node<T> root) : m_root(&root){}

template<class T>
AVLTree<T>::AVLTree(const AVLTree& originalTree)
{
    m_root = originalTree.getRoot();
}

template<class T>
AVLTree<T>::~AVLTree(){}


/**************************AVLTree functions*****************************/

template<class T>
void AVLTree<T>::printTheTree()
{
    cout <<"this is node number 1's value: "<< m_root->getValue()<<endl;
    cout <<"this is node number 2's value: "<< m_root->getLeftNode()->getValue()<<endl;
    cout <<"this is node number 3's value: "<< m_root->getRightNode()->getValue()<<endl;
    cout <<"this is node number 4's value: "<< m_root->getLeftNode()->getLeftNode()->getValue()<<endl;
    cout <<"this is node number 5's value: "<< m_root->getLeftNode()->getRightNode()->getValue()<<endl;
    cout <<"this is node number 6's value: "<< m_root->getRightNode()->getLeftNode()->getValue()<<endl;
    cout <<"this is node number 7's value: "<< m_root->getRightNode()->getRightNode()->getValue()<<endl;
}

template<class T>
void AVLTree<T>::setRightNode(Node<T>* parent, int value)
{
    parent->setRightNode(insertValue(parent->getRightNode(), value));
}

template<class T>
void AVLTree<T>::setLeftNode(Node<T>* parent, int value)
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
        return 0;
    }
    else if (left >= right)
    {
        return node->getLeftNode()->getHeight();
    }
    else
    {
        return node->getRightNode()->getHeight();
    }
}

template<class T>
int AVLTree<T>::BalanceFactor(Node<T>* node)
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
            
            delete tmp;
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

    node->setHeight(1 + calculateHeight(node));
    node = balance(node, value);

    return node;
}

template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node, T value)
{
    int balance = BalanceFactor(node);

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

template<class T>
Node<T>* AVLTree<T>::rotateLeft(Node<T>* parent)
{
	Node<T>* child = parent->getRightNode();
	Node<T>* grandChild = child->getLeftNode();

	child->setLeftNode(parent);
	parent->setRightNode(grandChild);

	parent->setHeight(calculateHeight(parent));
	child->setHeight(calculateHeight(child));

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

	return child;
}

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

template<class T>
Node<T>* FindObject(Node<T>* node, T value)
{
    if(node == NULL){
        return nullptr;
    }

    else if(node->getValue() == value){
        return node;
    }

    else if(node->getValue() > value){
        return FindObject(node->getLeftNode(), value);
    }

    else{
        return FindObject(node->getRightNode(), value);
    }
}

#endif