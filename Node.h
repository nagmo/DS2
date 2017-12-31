
#ifndef DS2_NODE_H
#define DS2_NODE_H

#include <clocale>
#include "Gladiator.h"

namespace TreeExceptions{
    class GladiatorExists{};
}

/**
 * rank tree for gladiators.
 * keeps the gladiators and the weight of every sub tree +
 * the total score of the sub tree
 */
class Node{
public:

    explicit Node(Gladiator& gladiator, Node* left=NULL, Node* right=NULL):
            gladiator(new Gladiator(gladiator)), left(left), right(right),
            weight(1), subTreeScore(gladiator.GetScore()){}

    Node(Node* node): gladiator(new Gladiator(*(node->gladiator))),
          weight(node->weight), subTreeScore(node->subTreeScore),
                      left(NULL), right(NULL){
        if(node->left) left = new Node(node->left);
        if(node->right) right = new Node(node->right);
    }

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
        //if gladiator exist throw exception
        if(gladiator == *(this->gladiator))
            throw TreeExceptions::GladiatorExists();
        //find the place for the gladiator.
        if(gladiator > *(this->gladiator)){
            if(right == NULL){
                right = new Node(gladiator);
                //if added a gladiator update weight and score.
                weight++;
                subTreeScore += gladiator.GetScore();
                return;
            }
            right->AddGladiator(gladiator);
            weight++;
            subTreeScore = left->subTreeScore + right->subTreeScore + (this->gladiator)->GetScore();
            return;
        }
        if(left == NULL){
            left = new Node(gladiator);
            weight++;
            subTreeScore += gladiator.GetScore();
            return;
        }
        left->AddGladiator(gladiator);
        weight++;
        subTreeScore = left->subTreeScore + right->subTreeScore + (this->gladiator)->GetScore();
    }

    int GetTopKScore(int k){
        if(left != NULL){
            if(left->weight == k-1) return subTreeScore;
            else if(left->weight > k-1) return left->GetTopKScore(k);
            else {
                if (right != NULL)
                    return right->GetTopKScore(k - (left->weight) - 1);
            }
        }
        //in case of failure
        return  0;
    }

private:
    Gladiator* gladiator;
    int weight;
    int subTreeScore;
    Node* left;
    Node* right;
};



#endif //DS2_NODE_H
