
#include "TrainingGroup.h"

TrainingGroup::TrainingGroup(GroupId ID) : id(ID), isActive(true){}

bool TrainingGroup::isVoid(){
    return id == -1;
}

bool TrainingGroup::operator==(TrainingGroup& trainingGroup){
    return id == trainingGroup.id;
}

bool TrainingGroup::operator>(TrainingGroup& trainingGroup){
    if(!isActive) return true;
    if(!trainingGroup.isActive) return false;
    return id > trainingGroup.id;
}

bool TrainingGroup::operator<(TrainingGroup& trainingGroup){
    return !(*this > trainingGroup || *this == trainingGroup);
}

void TrainingGroup::disActivate(){
    isActive = false;
}

void TrainingGroup::setIndex(int i){
    index = i;
}

int TrainingGroup::getIndex(){
    return index;
}

void TrainingGroup::setHeapPointer(void* pointer){
    heap = pointer;
}

void* TrainingGroup::getHeapPointer() {
    return heap;
}

GroupId TrainingGroup::GetID() {
    return id;
}

HashTrainingGroup::HashTrainingGroup(GroupId ID):
TrainingGroup(ID), root(NULL) {}

HashTrainingGroup::~HashTrainingGroup() {
    delete root;
}

void HashTrainingGroup::addGladiator(Gladiator& gladiator) {
    root->AddGladiator(gladiator);
}

int HashTrainingGroup::TopKGladsScore(int k) {
    return (root->GetTopKScore(k));
}
