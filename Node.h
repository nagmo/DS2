
#ifndef DS2_NODE_H
#define DS2_NODE_H

#include <clocale>

class Gladiator;

namespace TreeExceptions{
    class GladiatorExists{};
}

class Node{
public:

    explicit Node(Gladiator& gladiator, Node* left=NULL, Node* right=NULL):
            gladiator(new Gladiator(gladiator)), left(left), right(right){}

    ~Node(){
        delete gladiator;
    }

    Gladiator& GetGlad(){
        return (*gladiator);
    }

    Node* GetLeft(){
        return left;
    }

    Node* GetRight(){
        return right;
    }

    void SetLeft(Node* node){
        left = node;
    }

    void SetRight(Node* node){
        right = node;
    }

    void AddGladiator(Gladiator& gladiator){
        if(gladiator == this->gladiator)
            throw TreeExceptions::GladiatorExists();
        if(gladiator > this->gladiator){
            if(right == NULL){
                right = new Node(gladiator);
                return;
            }
            return right->AddGladiator(gladiator);
        }
        if(left == NULL){
            left = new Node(gladiator);
            return;
        }
        return left->AddGladiator(gladiator);
    }

private:
    Gladiator* gladiator;
    Node* left;
    Node* right;
};



#endif //DS2_NODE_H
