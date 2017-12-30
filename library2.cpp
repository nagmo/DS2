#include <new>
#include "library2.h"
#include "Colosseum.h"

void* init(int n, int *trainingGroupsIDs){
    if(n<2) return NULL;
    Colosseum* colosseum = NULL;
    try{
        colosseum = new Colosseum(n, trainingGroupsIDs);
    }catch(std::bad_alloc&){
        return NULL;
    }catch(){

    }
    return (void*) colosseum;
}

StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if(DS == NULL || trainingGroupID < 0) return INVALID_INPUT;
    try{
        ((Colosseum*)DS)->addGroup(trainingGroupID);
    }catch(ColosseumException::InvaldInput&){
        return INVALID_INPUT;
    }catch(ColosseumException::Failure&){
        return FAILURE;
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType addGladiator(void *DS, int gladiatorID,
                        int score, int trainingGroup){
    if(DS == NULL || gladiatorID < 0 || score < 0 || trainingGroup < 0)
        return INVALID_INPUT;
    try{
        ((Colosseum*)DS)->addGlad(gladiatorID, score, trainingGroup);
    }catch(ColosseumException::InvaldInput&){
        return INVALID_INPUT;
    }catch(ColosseumException::Failure&){
        return FAILURE;
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType trainingGroupFight(void *DS, int trainingGroup1,
                              int trainingGroup2, int k1, int k2){
    if(DS == NULL || k1 <= 0 || k2 <= 0 || trainingGroup1 < 0 ||
            trainingGroup2 <0) return INVALID_INPUT;
    try{
        ((Colosseum*)DS)->fight(trainingGroup1, trainingGroup2, k1, k2);
    }catch(ColosseumException::InvaldInput&){
        return INVALID_INPUT;
    }catch(ColosseumException::Failure&){
        return FAILURE;
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType getMinTrainingGroup(void *DS, int *trainingGroup){
    if(DS == NULL || trainingGroup == NULL) return INVALID_INPUT;
    try{
        *trainingGroup = ((Colosseum*)DS)->getMinTrainingGroup();
    }catch(ColosseumException::InvaldInput&){
        return INVALID_INPUT;
    }catch(ColosseumException::Failure&){
        return FAILURE;
    }
    return SUCCESS;
}

/* Description:   Quits and deletes the database.
*                DS should be set to NULL.
* Input:         DS - A pointer to the data structure.
* Output:        None.
* Return Values: None.
*/
void quit(void** DS){
    if(*DS == NULL) return;
    delete (*DS);
    *DS = NULL;
}

