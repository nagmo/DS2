#ifndef DS2_TRAININGGROUP_H
#define DS2_TRAININGGROUP_H

#include "utilities.h"
#include "Node.h"

class TrainingGroup {
public:

    explicit TrainingGroup(GroupId ID = -1);

    bool isVoid();

    GroupId GetID();

    bool operator==(TrainingGroup&);

    bool operator>(TrainingGroup&);

    bool operator<(TrainingGroup&);

    void disActivate();
private:
    GroupId id;
    bool isActive;
};


class HashTrainingGroup : public TrainingGroup{
public:
    explicit HashTrainingGroup(GroupId ID = -1);

    ~HashTrainingGroup();

    void addGladiator(Gladiator& gladiator);

    int TopKGladsScore(int k);

private:

    Node*  root;
};

#endif //DS2_TRAININGGROUP_H
