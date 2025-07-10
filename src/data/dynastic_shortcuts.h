#ifndef GUARD_DYNASTIC_SHORTCUTS_H
#define GUARD_DYNASTIC_SHORTCUTS_H

#include "difficulty.h"
#include "constants/difficulty.h"
#include "script.h"
#include "event_data.h"
#include "constants/global.h"

static inline u32 IsEasyMode(void)
{
    return GetCurrentDifficultyLevel() == DIFFICULTY_EASY; //IsDifficultyLevel(DIFFICULTY_EASY);
}

static inline u32 IsNormalMode(void)
{
    return GetCurrentDifficultyLevel() == DIFFICULTY_NORMAL; //IsDifficultyLevel(DIFFICULTY_NORMAL);
}

static inline u32 IsHardMode(void)
{
    return GetCurrentDifficultyLevel() == DIFFICULTY_HARD; //IsDifficultyLevel(DIFFICULTY_HARD);
}

static inline u32 IsMinimalGrindingMode(void)
{
    return FlagGet(FLAG_MINIMAL_GRINDING_MODE);
}

static inline u32 IsFollowerEnabled(void)
{
    return FlagClear(FLAG_DISABLED_FOLLOWERS);
}

static inline u32 SetFollowerToDisabled(void)
{
    return FlagSet(FLAG_DISABLED_FOLLOWERS);
}

static inline u32 IsFollowerDisabled(void)
{
    return FlagGet(FLAG_DISABLED_FOLLOWERS);
}


#endif // GUARD_DYNASTIC_SHORTCUTS_H