
#ifndef DS2_GLADIATOR_H
#define DS2_GLADIATOR_H

#include "utilities.h"

class Gladiator {

public:
    Gladiator(GladiatorID, Level);

    Level getLevel();

    GladiatorID getId();
    /**
     * two gladiators are equal if have the same id
     * @param gladiator
     * @return
     */
    bool operator==(Gladiator& gladiator);
    /**
     * compare by id
     * @param gladiator
     * @return
     */
    bool operator<(Gladiator& gladiator);
    /**
     * compare by id
     * @param gladiator
     * @return
     */
    bool operator>(Gladiator& gladiator);

private:

    GladiatorID id;
    Level level;
};

#endif //DS2_GLADIATOR_H
