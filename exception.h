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

class  : public AVLTreeException {
    public:
        DeckFileFormatError(int line) : 
            AVLTreeException("Deck File Error: File format error in line " + to_string(line)), line(line) {}
};

class DeckFileInvalidSize : public DeckException{
    public:
        DeckFileInvalidSize() : DeckException("Deck File Error: Deck size is invalid") {}
};

#endif