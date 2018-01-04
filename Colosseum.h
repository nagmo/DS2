
#ifndef DS2_COLOSSEUM_H
#define DS2_COLOSSEUM_H

#include "MinHeap.h"
#include "TrainingGroupHashTable.h"
#include "TrainingGroup.h"
#include "utilities.h"

class Colosseum {
public:
    Colosseum(int, int*);

    ~Colosseum();

    void addGroup(int);

    void addGlad(GladiatorID, Level, GroupId);

    void fight(GroupId, GroupId, int, int);

    int getMinTrainingGroup();

private:
    MinHeap* heapGroup;
    TrainingGroupHashTable* hashGroup;
    Node* gladiators;
};

namespace ColosseumException{
    class InvaldInput{};
    class Failure{};

}

#endif //DS2_COLOSSEUM_H
