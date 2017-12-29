
#ifndef DS2_TRAININGGROUPHASHTABLE_H
#define DS2_TRAININGGROUPHASHTABLE_H

#include "DynamicArray.h"
#include "utilities.h"

class TrainingGroup{};
class Gladiator{};

class TrainingGroupHashTable {
public:

    /**
     * constructor for the training groups hash table.
     * initialize the table by the array of ID's received.
     * @param numOfGroups - number of groups to start with
     * @param trainingGroupsID - int array of training groups ID numbers
     */
    TrainingGroupHashTable(int numOfGroups, int* trainingGroupsID);

    /**
     * destructor
     */
    ~TrainingGroupHashTable();

    /**
     * add a group to the table, add by ID.
     * @param trainingGroupID
     */
    void AddTrainingGroup(int trainingGroupID);

    /**
     * add gladiator to a group by group ID.
     * @param gladiator - Gladiator class.
     * @param groupID - group to add to.
     */
    void AddGladiatorToTrainingGroup(Gladiator gladiator, int groupID);

    /**
     * preforms the calculation needed to conduct a fight between two groups
     * returns a pointer to the group that lost.
     * @param group1ID - first group's ID
     * @param group2ID - second group's ID
     * @param numOfGladiators1
     * @param numOfGladiators2
     * @return - pointer to the group that lost.
     */
    TrainingGroup* TrainingGroupFight(int group1ID, int group2ID,
                      int numOfGladiators1, int numOfGladiators2);

private:

    DynamicArray array;
    int sizeOfHashTable;

    int FirstHash(int groupID);
    int SecondHash(int groupID);
};


#endif //DS2_TRAININGGROUPHASHTABLE_H
