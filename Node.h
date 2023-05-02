#ifndef WET1_NODE_H
#define WET1_NODE_H

template <class T>
class Node {
    public:
        
        /**** c'tors amd d'tors ****/

        /*
        *c'tor of the Node class
        *
        * @result
        *       an instance of Node
        */
        Node();

        /*
        * c'tor of theNode class with a set value
        *
        * @param value - the value to be saved in the node
        * @result
        *       an instance of Node with a saved value
        */
        Node(T& value);

        /*
        * c'tor of theNode class with a set const value
        *
        * @param value - the value to be saved in the node
        * @result
        *       an instance of Node with a saved value
        */
        Node(const T& value);

        /*
        * copy c'tor
        */
        Node(const Node& originalNode);

        /*
        * d'tor
        */
        ~Node();


        /**** Getters and Setters ****/

        /*
        * returns the pointer to th enext node
        *
        * @return
        *       m_nextNode
        */
        Node* getLeftNode() const;
        Node* getRightNode() const;

        /*
        * returns the value saved in the node
        *
        * @return
        *       m_value
        */
        T& getValue();

        /*
        * setter for next node pointer
        *
        * @param nextNode - pointer for the next node
        * @result
        *       void
        */
        void setLeftNode(Node* leftNode);
        void setRightNode(Node* rightNode);

        /*
        * setter for the current value saved in the node
        *
        * @param value - the new Node value
        * @result
        *       void
        */
        void setValue(T value);

    protected:

        Node* m_leftNode;
        Node* m_rightNode;

    private:
        T m_value;

};


/*************************Node c'tors & d'tor****************************/


template<class T>
Node<T>::Node() :
    m_leftNode(NULL), m_rightNode(NULL), m_value(NULL)
{}  

template<class T>
Node<T>::Node(T& value) :
    m_leftNode(NULL), m_rightNode(NULL), m_value(value)
{}

template<class T>
Node<T>::Node(const T& value) :
    m_leftNode(NULL), m_rightNode(NULL), m_value(value),
{}

template<class T>
Node<T>::Node(const Node& originalNode) :
    m_leftNode(originalNode.m_leftNode), m_rightNode(originalNode.m_rightNode), m_value(originalNode.m_value)
{}

template<class T>
Node<T>::~Node()
{}


/*******************************Node Functions***************************/


template<class T>
Node<T>* Node<T>::getLeftNode() const
{
    return (m_leftNode);
}

template<class T>
Node<T>* Node<T>::getRightNode() const
{
    return (m_rightNode);
}

template<class T>
void Node<T>::setLeftNode(Node* leftNode)
{
    m_leftNode = leftNode;
}

template<class T>
void Node<T>::setRightNode(Node* rightNode)
{
    m_rightNode = rightNode;
}

template<class T>
T& Node<T>::getValue()
{
    return (m_value);
}

template<class T>
void Node<T>::setValue(T value)
{
    m_value == value;
}








#endif