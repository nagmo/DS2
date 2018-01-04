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

    void deActivate();

    void setIndex(int);

    int getIndex();

    void setHeapPointer(void* pointer);

    void* getHeapPointer();

    bool isGroupActive();
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
    explicit HashTrainingGroup(GroupId ID = -1, TrainingGroup* = NULL);

    HashTrainingGroup(HashTrainingGroup& group, TrainingGroup* = NULL);

    ~HashTrainingGroup();

    void addGladiator(Gladiator& gladiator);

    int TopKGladsScore(int k);

    void setGroupFromHeapPointer(TrainingGroup*);

    TrainingGroup* getGroupFromHeapPointer();

private:
    Node*  root;
    //pointer to the real group from heap
    TrainingGroup* groupFromHeap;
};

#endif //DS2_TRAININGGROUP_H
