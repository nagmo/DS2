
#include "Gladiator.h"

Gladiator::Gladiator(GladiatorID id, int score) : id(id), score(score){}


Level Gladiator::GetScore(){
    return score;
}

GladiatorID Gladiator::getId(){
    return id;
}

    /**
     * two gladiators are equal if have the same id
     * @param gladiator
     * @return
     */
bool Gladiator::operator==(Gladiator& gladiator){
    return (id == gladiator.id);
}

    /**
     * compare by id
     * @param gladiator
     * @return
     */
bool Gladiator::operator<(Gladiator& gladiator){
        return id < gladiator.id;
    }
/**
 * compare by id
 * @param gladiator
 * @return
 */
bool Gladiator::operator>(Gladiator& gladiator){
    return !(*this == gladiator || *this < gladiator);
}