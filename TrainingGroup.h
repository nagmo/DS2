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

    void setIndex(int);

    int getIndex();

    void setHeapPointer(void* pointer);

    void* getHeapPointer();
private:
    GroupId id;
    bool isActive;
    /**
     * the group index in the heap
     */
    int index;
    /**
     * pointer to the heap that this group is in it
     */
    void* heap;
};


#endif //DS2_TRAININGGROUP_H
