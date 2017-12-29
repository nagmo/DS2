#ifndef DS2_TRAININGGROUP_H
#define DS2_TRAININGGROUP_H

#include "utilities.h"

class TrainingGroup {
public:

    /**
     * empty constructor that sais this element is void
     */
    TrainingGroup();

    TrainingGroup(int n);

    bool isVoid();

    bool operator==(TrainingGroup&);

    bool operator>(TrainingGroup&);

    bool operator<(TrainingGroup&);

    void disActivate();
private:
    GroupId id;
    bool isActive;
};


#endif //DS2_TRAININGGROUP_H
