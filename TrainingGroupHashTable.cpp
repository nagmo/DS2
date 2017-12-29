//
// Created by Nevo Agmon on 28/12/2017.
//

#include <clocale>
#include "TrainingGroupHashTable.h"

/**
 * constructor for the training groups hash table.
 * initialize the table by the array of training groups received.
 * @param numOfGroups - number of groups to start with
 * @param trainingGroups - training group array of training groups
 */
TrainingGroupHashTable::TrainingGroupHashTable(int numOfGroups,
                                               TrainingGroup *trainingGroups):
array(DynamicArray<TrainingGroup>(numOfGroups)),
sizeOfHashTable(numOfGroups)
{
    for(int i=0; i<numOfGroups; i++){
        AddTrainingGroup(trainingGroups[i]);
    }
}

TrainingGroupHashTable::~TrainingGroupHashTable() {

}

void TrainingGroupHashTable::AddTrainingGroup(TrainingGroup trainingGroup) {
    //calculate the hash number for the group and the jump factor
    int index = FirstHash(trainingGroup.GetID);
    int jumpFactor =  SecondHash(trainingGroup.GetID);

    //loop until finds an empty slot.
    while(!array.isEmpty(index)){
        index = (index + jumpFactor) % sizeOfHashTable;
    }
    try{
        array[index] = trainingGroup;
    }catch{
        //TODO: how do I know when to do re-hashing?
    }
}

void TrainingGroupHashTable::AddGladiatorToTrainingGroup(Gladiator gladiator,
                                                    GroupId groupID) {
    //get hashed number for group and jump factor
    int index = FirstHash(groupID);
    int jumpFactor =  SecondHash(groupID);
    //loop until finds the group or gets to an empty slot.
    while((array[index]).GetID != groupID && !array.isEmpty(index)){
        index = (index + jumpFactor) % sizeOfHashTable;
    }
    //if the slot is empty then the group doesn't exist.
    if(array.isEmpty(index)) //TODO: what exception to throw?

    //found the right index. add gladiator to the array.
    (array[index]).addGladiator(gladiator);
}

TrainingGroup *TrainingGroupHashTable::TrainingGroupFight(int group1ID,
                                          int group2ID, int k1, int k2) {
    return NULL;
}

int TrainingGroupHashTable::FirstHash(int groupID) {
    return 0;
}

int TrainingGroupHashTable::SecondHash(int groupID) {
    return 0;
}
