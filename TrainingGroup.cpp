
#include "TrainingGroup.h"

TrainingGroup::TrainingGroup(GroupId ID) : id(ID), isActive(true),
                                           index(-1), heap(NULL){}

TrainingGroup::TrainingGroup(TrainingGroup &group) : id(group.id),
         isActive(group.isActive), index(group.index), heap(group.heap) {}

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

void TrainingGroup::deActivate(){
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

HashTrainingGroup::HashTrainingGroup(GroupId ID, TrainingGroup* trainingGroup):
TrainingGroup(ID), root(NULL), groupFromHeap(trainingGroup) {}

HashTrainingGroup::HashTrainingGroup(HashTrainingGroup &group, TrainingGroup* trainingGroup):
        TrainingGroup(group), root(NULL), groupFromHeap(trainingGroup){
    if(group.root) root = new Node(group.root);
}

HashTrainingGroup::~HashTrainingGroup() {
    delete root;
}

void HashTrainingGroup::addGladiator(Gladiator& gladiator) {
    if(root != NULL){
        root->AddGladiator(gladiator);
    }
    else{
        root = new Node(gladiator);
    }
}

int HashTrainingGroup::TopKGladsScore(int k) {
    if(root == NULL) return 0;
    return (root->GetTopKScore(k));
}

void HashTrainingGroup::setGroupFromHeapPointer(TrainingGroup* trainingGroup){
    groupFromHeap = trainingGroup;
}

TrainingGroup* HashTrainingGroup::getGroupFromHeapPointer(){
    return groupFromHeap;
}


