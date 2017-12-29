
#include "TrainingGroup.h"

TrainingGroup::TrainingGroup() : id(-1), isActive(true){}

TrainingGroup::TrainingGroup(int n) : id(n), isActive(true){}

bool TrainingGroup::isVoid(){
    return id == -1;
}