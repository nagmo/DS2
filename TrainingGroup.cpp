
#include "TrainingGroup.h"

TrainingGroup::TrainingGroup() : id(-1), isActive(true){}

TrainingGroup::TrainingGroup(int n) : id(n), isActive(true){}

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
