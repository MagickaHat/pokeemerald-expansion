#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Bone Zone bypasses immunities")
{
    s16 turnOneHit;
    s16 turnTwoHit;

    GIVEN {
        PLAYER(SPECIES_MAROWAK_ALOLA) { Ability(ABILITY_BONE_ZONE); };
        OPPONENT(SPECIES_FLYGON) { Ability(ABILITY_LEVITATE); };
    } WHEN {
        TURN { MOVE(player, MOVE_BONEMERANG); MOVE(opponent, MOVE_THUNDER_PUNCH);}
        TURN { MOVE(player, MOVE_BONEMERANG); MOVE(opponent, MOVE_TACKLE); }

    } SCENE {
        HP_BAR(player, captureDamage: &turnOneHit);
        //ABILITY_POPUP(player, ABILITY_BONE_ZONE);
        //MESSAGE("The players Marowak attacked trough immunities!");
        HP_BAR(player, captureDamage: &turnTwoHit);
    } THEN {
        EXPECT_EQ(turnOneHit, turnTwoHit);
    }
}
