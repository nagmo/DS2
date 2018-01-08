
#include <new>
#include "Colosseum.h"
using ColosseumException::Failure;
using ColosseumException::InvaldInput;


void validateIds(int n, int* ids){
    for (int i = 0; i < n; ++i) {
        if(ids[i] < 0) throw InvaldInput();
    }
}

Colosseum::Colosseum(int n, int* ids) :
        heapGroup(NULL), hashGroup(NULL), gladiators(NULL){
    validateIds(n, ids);
    //now ids are valid
    TrainingGroup** groupIds = new TrainingGroup*[n]();
    for (int i = 0; i < n; ++i) {
        try{
            groupIds[i] = new TrainingGroup(ids[i]);
        }
        catch (std::bad_alloc&){
            for(; i > 0; i--){
                delete groupIds[i-1];
            }
            delete [] groupIds;
            throw std::bad_alloc(); //TODO: I added a new throw in order for us to know that there was an allocation failure
        }
    }
    //dont check with try because we assume that id are valid
    heapGroup = new MinHeap(n, groupIds);
    //delete heap groups
    for(int i=0; i<n; i++){
        delete groupIds[i];
    }
    delete [] groupIds;

    HashTrainingGroup** hashTrainingGroups = new HashTrainingGroup*[n];
    DynamicArray<TrainingGroup>* groupFromHeapArray = heapGroup->getDataArray();
    for (int k = 0; k < n; ++k) {
        try {
            hashTrainingGroups[k] = new HashTrainingGroup((*groupFromHeapArray)[k].GetID(),
                                                          &(*groupFromHeapArray)[k]);
        }
        catch (std::bad_alloc&){
            for(; k > 0; k--){
                delete hashTrainingGroups[k-1];
            }
            delete [] hashTrainingGroups;
            throw std::bad_alloc();
        }
    }
    hashGroup = new TrainingGroupHashTable(n, hashTrainingGroups);
    //deleteing hash groups
    for(int i=0; i<n; i++){
        delete hashTrainingGroups[i];
    }
    delete [] hashTrainingGroups;
}

Colosseum::~Colosseum() {
    delete hashGroup;
    delete heapGroup;
}

void Colosseum::addGroup(GroupId id){
    //check that id is valid
    if(id < 0) throw InvaldInput();
    HashTrainingGroup* group = new HashTrainingGroup(id);
    int index = -1;
    try{
        index = hashGroup->AddTrainingGroup(group);
    }
    catch (HashTableException::GroupAlreadyExist){
        delete group;
        throw Failure();
    }
    delete group;
    TrainingGroup trainingGroup(id);
    //get the pointer to the group
    TrainingGroup* newGroup = heapGroup->addGroup(trainingGroup);
    hashGroup->GetGroupByIndex(index).setGroupFromHeapPointer(newGroup);
}

void Colosseum::addGlad(GladiatorID gladiatorID, Level level, GroupId groupId){
    Gladiator gladiator = Gladiator(gladiatorID, level);
    //add glad to tree
    try{
        try{
            hashGroup->getGroupIndex(groupId);
            if(gladiators == NULL) gladiators = new Node(gladiator);
            else gladiators->AddGladiator(gladiator);
        }
        //if group doesnt exist dont add glad
        catch (HashTableException::GroupDoesntExist&){
            throw Failure();
        }
    }catch(TreeExceptions::GladiatorExists&){
        throw Failure();
    }
    //add glad to hash
    try {
        hashGroup->AddGladiatorToTrainingGroup(gladiator, groupId);
    }
    catch (HashTableException::GroupDoesntExist&){
        throw Failure();
    }
    catch(HashTableException::GladiatorExist&){
        throw Failure();
    }
}

void Colosseum::fight(GroupId id1, GroupId id2, int i, int j){
    //check if ID's are the same
    if(id1 == id2) throw Failure();

    HashTrainingGroup* trainingGroup;
    try{
        trainingGroup = hashGroup->TrainingGroupFight(id1, id2, i, j);
    }
    catch (HashTableException::GroupDoesntExist&){
        throw Failure();
    }
    catch (HashTableException::NotEnoghGladiators){
        throw Failure();
    }
    catch (HashTableException::GroupCantFight&){
        throw Failure();
    }
    //deactivate the loosing teem
    heapGroup->deActiveGroup((trainingGroup->getGroupFromHeapPointer())->getIndex());
}

int Colosseum::getMinTrainingGroup(){
    TrainingGroup* trainingGroup = NULL;
    try {
        TrainingGroup& bestTrainingGroup = heapGroup->getMinGroup();
        trainingGroup = &bestTrainingGroup;
    }
    catch (MinHeapExceptions::FailureException&){
        throw Failure();
    }
    if(trainingGroup == NULL || trainingGroup->isVoid()) throw Failure();
    return trainingGroup->GetID();
}
