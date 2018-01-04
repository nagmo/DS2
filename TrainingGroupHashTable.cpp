
#include <clocale>
#include "TrainingGroupHashTable.h"

TrainingGroupHashTable::TrainingGroupHashTable() : array(NULL), sizeOfHashTable(0){}

/**
 * constructor for the training groups hash table.
 * initialize the table by the array of training groups received.
 * @param numOfGroups - number of groups to start with
 * @param trainingGroups - training group array of training groups
 */
TrainingGroupHashTable::TrainingGroupHashTable(int numOfGroups,
                                               HashTrainingGroup** trainingGroups):
array(NULL),
sizeOfHashTable(numOfGroups*4)
{
    array = new DynamicArray<HashTrainingGroup>(numOfGroups);
    for(int i=0; i<numOfGroups; i++){
        AddTrainingGroup(trainingGroups[i]);
    }
}

TrainingGroupHashTable::~TrainingGroupHashTable(){
    delete array;
}

/**
 * add a group to the table.
 * @param trainingGroup - group to add.
 * @return index of the group after adding, -1 if rehash occurred.
 */
int TrainingGroupHashTable::AddTrainingGroup(HashTrainingGroup* trainingGroup) {
    //calculate the hash number for the group and the jump factor
    int index = FirstHash(trainingGroup->GetID());
    int jumpFactor =  SecondHash(trainingGroup->GetID());

    //loop until finds an empty slot.
    while(!(array->isEmpty(index))){
        if((*array)[index] == *trainingGroup)
            throw HashTableException::GroupAlreadyExist();
        index = (index + jumpFactor) % sizeOfHashTable;
        if(index == FirstHash(trainingGroup->GetID())) break;
    }
    //insert to the array, if array expands then do re-hashing.
    try{
        array->insert(*trainingGroup,index);
    }catch(DynamicArrayException::ArrayExpand&){
        rehash();
        return getGroupIndex(trainingGroup->GetID());
    }
    return index;
}

/**
 * add gladiator to a group by group ID.
 * @param gladiator - Gladiator class.
 * @param groupID - group to add to.
 */
void TrainingGroupHashTable::AddGladiatorToTrainingGroup(Gladiator& gladiator,
                                                    GroupId groupID) {
    try {
        findGroup(groupID).addGladiator(gladiator);
    }catch(TreeExceptions::GladiatorExists&){
        throw HashTableException::GladiatorExist();
    }
}

/**
 * preforms the calculation needed to conduct a fight between two groups
 * returns a reference to the group that lost.
 * @param group1ID - first group's ID
 * @param group2ID - second group's ID
 * @param numOfGladiators1
 * @param numOfGladiators2
 * @return - pointer to the group that lost.
 */
HashTrainingGroup& TrainingGroupHashTable::TrainingGroupFight(GroupId group1ID,
                                          GroupId group2ID, int k1, int k2) {
    //find groups
    HashTrainingGroup& group1 = findGroup(group1ID);
    HashTrainingGroup& group2 = findGroup(group2ID);

    //get top ki score.
    int group1Score = group1.TopKGladsScore(k1);
    int group2Score = group2.TopKGladsScore(k2);

    //check for failure (not enough gladiators)
    if(group1Score == 0 || group2Score == 0)
        throw HashTableException::NotEnoghGladiators();

    //check who is better and return the looser.
    if(group1Score > group2Score) return group2;
    else if(group1Score < group2Score) return group1;

    //if we got a tie, the winner is the one with the smaller ID.
    return (group1ID < group2ID) ? group2 : group1;
}

/**
 * first hashing function is: h(x) = x mod m
 * when "m" is the size of the hash table.
 * @param groupID - the "x" in the equation.
 * @return
 */
int TrainingGroupHashTable::FirstHash(GroupId groupID) {
    return (groupID % sizeOfHashTable);
}

/**
 * second hashing function for jump factor is: r(x) = 1+(x mod (m-c))
 * when "m" is the size of the hash table, "c" is 2
 * @param groupID - the "x" in the equation.
 * @return
 */
int TrainingGroupHashTable::SecondHash(GroupId groupID) {
    return (1+(groupID % (sizeOfHashTable -2)));
}


/**
 * find the group in the array by ID.
 * if groups doesn't exist throws an exception.
 * @param ID
 * @return - reference to the group in the array.
 * @exception - HashTableException::GroupDoesntExist
 */
HashTrainingGroup& TrainingGroupHashTable::findGroup(GroupId ID){
    //get hashed number for group and jump factor
    int index = FirstHash(ID);
    int jumpFactor =  SecondHash(ID);
    //loop until finds the group or gets to an empty slot.
    while(!(array->isEmpty(index)) && ((*array)[index]).GetID() != ID ){
        index = (index + jumpFactor) % sizeOfHashTable;
        if(index == FirstHash(ID)) throw HashTableException::GroupDoesntExist();
    }
    //if the slot is empty then the group doesn't exist.
    if(array->isEmpty(index)) throw HashTableException::GroupDoesntExist();

    //found the group, return it.
    return ((*array)[index]);
}

/**
 * preform re-hash to the hash table with the new array size.
 * to use after the array returns an "Expand" value.
 */
void TrainingGroupHashTable::rehash() {
    //update to the new array size.
    sizeOfHashTable = array->length();
    //save the old array.
    DynamicArray<HashTrainingGroup>* temp = array;
    //create a new empty array
    array = new DynamicArray<HashTrainingGroup>(sizeOfHashTable);
    //loop through all of the items in the table and insert with the new index.
    for(int i=0; i<sizeOfHashTable; i++){
        if(!(temp->isEmpty(i))) AddTrainingGroup(&(*temp)[i]);
    }
    delete temp;
}

HashTrainingGroup &TrainingGroupHashTable::GetGroupByIndex(int index) {
    if(array)
        return (*array)[index];
}

int TrainingGroupHashTable::getGroupIndex(GroupId id) {
    //get hashed number for group and jump factor
    int index = FirstHash(id);
    int jumpFactor = SecondHash(id);
    //loop until finds the group or gets to an empty slot.
    while (!(array->isEmpty(index)) && ((*array)[index]).GetID() != id) {
        index = (index + jumpFactor) % sizeOfHashTable;
        if (index == FirstHash(id)) throw HashTableException::GroupDoesntExist();
    }
    //if the slot is empty then the group doesn't exist.
    if (array->isEmpty(index)) throw HashTableException::GroupDoesntExist();

    //found the group, return it.
    return index;
}
