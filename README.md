# OVERVIEW

![menudemo](https://github.com/kyphii/pokeemerald/assets/8711258/9b18dc46-1344-4e6e-b3f0-b90c01c8fa84)

This is a modification for the [Pokemon Emerald Decompilation Project](https://github.com/pret/pokeemerald). This modification adds a framework for assembling palettes from a collection of predefined parts, allowing for features such as custom player character colors. This branch includes:
- Dynamic palette framework code
- Sample palette part files and definitions
- Modifications to override base game player palettes with dynamic palettes (overworld, battle back and front, trainer card)
- Several options for a menu interface for custom player colors. A menu in the intro sequence is added. There are also options for individual part menus, both directly through code and callable via script special.

This modification is *not* a plug-and-play feature - it will be necessary to make some code changes to use it effectively, as the implementation will be specific to your particular sprite and palette setup.

# PART PALETTE SETUP

Part palettes are defined in graphics/dynpal using the same file format as normal palettes. The part files are divided into 3 sections:
* Index 1-5: Normal overworld colors
* Index 6-10: Reflection colors
* Index 11-15: Underwater colors

![image](https://github.com/kyphii/pokeemerald/assets/8711258/ce4207ac-30d2-4083-9e55-19e845867e09)

![image](https://github.com/kyphii/pokeemerald/assets/8711258/8e640f8d-1fd3-4fcb-872d-16b0e76f2cba)

This modification provides for 4 different categories of part palette:
* 3 Preset lists, A, B, and C: Lists which can contain any number of parts. I recommend using them for skin, hair, and clothes tones, though you can use them for whatever you want.
* Base Palette: A single part palette containing colors that will always be present on the player palette. White and Black should always be present. You may also want to include a red for the battle front poke-ball and character mouth, as well as any other colors that should remain consistent.

# MENU OPTIONS

There are multiple options provided to allow the player to set their custom colors:
* 3 functions to call the menus, for each of the preset lists. Use these if you want text or other tasks in between the menus.
* 1 function to call all 3 list menus in sequence, with no interruptions. Use this if you want to call the menus with no interruptions. Using this allows the player to back out of all three menus, without saving their changes.

By default, the full menu sequence is called in the intro scene, after selecting the player gender. There are also script special definitions, so you can call the menus again via script:
```
special DynPal_ShowToneMenuA
waitstate
```
```
special DynPal_ShowToneMenuB
waitstate
```
```
special DynPal_ShowToneMenuC
waitstate
```
```
special DynPal_ShowFullToneMenu
waitstate
```

# NECESSARY CODE MODIFICATIONS

The palettes are defined in code in `dynamic_palettes.c`. When you define your own part palettes, you'll need to update all the references at the top of this file for each part:
* Palette definition (INCBIN)
* Text definitions for menus
* Add palette definition to one of the 3 Preset arrays
* Add text definition to corresponding ListMenuItem array
* Update COUNT define for appropriate preset array.

You'll also need to modify the following functions based on your sprite setup:
* `DynPal_InitOverworld`: Assemble the overworld sprite from each of the 3 preset groups and the base color file.
* `DynPal_InitBattleFront`: Add any differences between the overworld and battle front sprite here.
* `DynPal_InitBattleBack`: Same as above for the battle back sprite.
* `DynPal_ReloadPlayerFrontForMenu`: Another function specifically for hot reloading the player sprite while customizing the palette in menu. This should reflect the code in `DynPal_InitOverworld` and `DynPal_InitBattleFront`.
* `DynPal_LoadIntroToneIndices`: Defines the presets used by the player sprites in the intro sequence, prior to the user selecting their own colors. Split up between the male and female player character.

# OPTIONAL CODE MODIFICATIONS

The branch includes five dynamic palettes for the player character to use:
* `sDynPalPlayerOverworld`
* `sDynPalPlayerReflection`
* `sDynPalPlayerUnderwater`
* `sDynPalPlayerBattleFront`
* `sDynPalPlayerBattleBack`

If you want to add more for other characters or applications, you can add a definition in both `dynamic_palettes.h` and `dynamic_palettes.c`. You can also add these to `DynPal_InitAllDynamicPalettes`, which is called when the game starts.

# MODIFICATIONS FOR RHH EMERALD-EXPANSION

[Emerald Expansion](https://github.com/rh-hideout/pokeemerald-expansion) changes how palettes are handled, and also moves around some code. If you're using it, make the following changes when you merge this branch:

* battle_controller_player.c: Do not include these changes, this code has moved. Instead, make these changes in battle_controllers.c:
    * Add `#include "dynamic_palettes.h"`
    * BtlController_HandleIntroTrainerBallThrow: replace the call to LoadCompressedPalette() with `DynPal_LoadPaletteByOffset(sDynPalPlayerBattleBack, OBJ_PLTT_ID(paletteNum));`
* battle_gfx_sfx_util.c: In place of `OBJ_PLTT_ID(battler)`, use `OBJ_PLTT_ID(battlerId)`
* field_effect.c: In place of `gTrainerFrontPicPaletteTable[trainerSpriteID].tag`, use `gTrainerSprites[trainerSpriteID].palette.tag`

# NOTES

* The base game's player sprites were, of course, not designed with this modification in mind, so the sample palette parts provided can't perfectly fit them. If you use just the base game and this, there will be some visual oddities, and they don't perfectly match the original game. This modification is intended for use with custom sprites designed with it in mind.
* The base character sprites also have different colors in the overworld versus in battle. This modification does not include this distinction, so they will be made the same in both.
* In base Emerald, the player and rival share the same overworld palette slot and tags, so Brendan/May will also have the same colors as the player.
* The same also applies to the arrow and emote icons in the overworld.
* By default, the 3 player character tones are saved to Save Block 2, using 3 bytes.
