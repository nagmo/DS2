#include "library2.h"
#include "Colosseum.h"

void* init(int n, int *trainingGroupsIDs){
    try{
        new Colosseum(n, trainingGroupsIDs);
    }
}

StatusType addTrainingGroup(void *DS, int trainingGroupID);

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup);

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1, int k2);

StatusType getMinTrainingGroup(void *DS, int *trainingGroup);

/* Description:   Quits and deletes the database.
*                DS should be set to NULL.
* Input:         DS - A pointer to the data structure.
* Output:        None.
* Return Values: None.
*/
void quit(void** DS);

