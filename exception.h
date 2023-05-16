#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <exception>
#include <string>

class AVLTreeException : public std::runtime_error {
    public:
        AVLTreeException(const std::string& msg) : runtime_error(msg) {}
};

class NodeAlreadyExists : public AVLTreeException {
    public:
        NodeAlreadyExists() : AVLTreeException("AVLTree Error: adding a node that already exists") {}
};

class BadAllocation : public AVLTreeException {
    public:
        BadAllocation() : AVLTreeException("AVLTree Error: allocation failed") {}
};


#endif