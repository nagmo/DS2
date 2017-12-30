
#include "TrainingGroup.h"


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

<<<<<<< HEAD
void TrainingGroup::setIndex(int i){
    index = i;
}

int TrainingGroup::getIndex(){
    return index;
}

void TrainingGroup::setHeapPointer(void* pointer){
    heap = pointer;
}

void* TrainingGroup::getHeapPointer(){
    return heap;
=======
>>>>>>> 43b6ee6943aba5c57c85b31a3352e90047f32336
}