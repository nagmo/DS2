#ifndef DS2_TRAININGGROUP_H
#define DS2_TRAININGGROUP_H

#include "utilities.h"
#include "Node.h"

class TrainingGroup {
public:

    explicit TrainingGroup(GroupId ID = -1);

    explicit TrainingGroup(TrainingGroup& group);

    bool isVoid();

    GroupId GetID();

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


class HashTrainingGroup : public TrainingGroup{
public:
    explicit HashTrainingGroup(GroupId ID = -1);

    HashTrainingGroup(HashTrainingGroup& group);

    ~HashTrainingGroup();

    void addGladiator(Gladiator& gladiator);

    int TopKGladsScore(int k);

private:

    Node*  root;
};

#endif //DS2_TRAININGGROUP_H
