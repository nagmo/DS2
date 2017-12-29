#ifndef DS2_TRAININGGROUP_H
#define DS2_TRAININGGROUP_H

#include "utilities.h"

class TrainingGroup {
public:

    TrainingGroup();

    TrainingGroup(int n);

    bool isVoid();

private:
    GroupId id;
    bool isActive;
};


#endif //DS2_TRAININGGROUP_H
