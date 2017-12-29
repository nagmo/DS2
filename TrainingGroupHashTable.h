
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
    TrainingGroupHashTable(int numOfGroups, TrainingGroup& *trainingGroupsID);

    ~TrainingGroupHashTable();

    /**
     * add a group to the table.
     * @param trainingGroupID - group to add.
     */
    void AddTrainingGroup(TrainingGroup& trainingGroupID);

    /**
     * add gladiator to a group by group ID.
     * @param gladiator - Gladiator class.
     * @param groupID - group to add to.
     */
    void AddGladiatorToTrainingGroup(Gladiator& gladiator, GroupId groupID);

    /**
     * preforms the calculation needed to conduct a fight between two groups
     * returns a reference to the group that lost.
     * @param group1ID - first group's ID
     * @param group2ID - second group's ID
     * @param numOfGladiators1
     * @param numOfGladiators2
     * @return - pointer to the group that lost.
     */
    TrainingGroup& TrainingGroupFight(GroupId group1ID, GroupId group2ID,
                      int numOfGladiators1, int numOfGladiators2);

private:

    DynamicArray* array;
    int sizeOfHashTable;

    /**
     * first hashing function is: h(x) = x mod m
     * when "m" is the size of the hash table.
     * @param groupID - the "x" in the equation.
     * @return
     */
    int FirstHash(int groupID);

    /**
     * second hashing function for jump factor is: r(x) = 1+(x mod (m-c))
     * when "m" is the size of the hash table, "c" is 2
     * @param groupID - the "x" in the equation.
     * @return
     */
    int SecondHash(int groupID);

    /**
    * find the group in the array by ID.
    * if groups doesn't exist throws an exception.
    * @param ID
    * @return - reference to the group in the array.
    * @exception - HashTableException::GroupDoesntExist
    */
    TrainingGroup& findGroup(GroupId Id);

    void rehash();
};

namespace HashTableException {
    class GroupDoesntExist{};
};
#endif //DS2_TRAININGGROUPHASHTABLE_H
