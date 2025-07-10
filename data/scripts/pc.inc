EventScript_PC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_OTHER
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox Text_BootUpPC, MSGBOX_DEFAULT
	goto EventScript_PCMainMenu
	end

EventScript_PCMainMenu::
	message gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto EventScript_AccessPC
	end

EventScript_AccessPC::
	switch VAR_RESULT
	case 0, EventScript_AccessPokemonStorage
	case 1, EventScript_AccessPlayersPC
	case 2, EventScript_AccessHallOfFame
	case 3, EventScript_TurnOffPC
	case MULTI_B_PRESSED, EventScript_TurnOffPC
	end

EventScript_AccessPlayersPC::
	playse SE_PC_LOGIN
	msgbox gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_AccessPokemonStorage::
	playse SE_PC_LOGIN
	call_if_unset FLAG_SYS_PC_LANETTE, EventScript_AccessSomeonesPC
	call_if_set FLAG_SYS_PC_LANETTE, EventScript_AccessLanettesPC
	msgbox gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_AccessSomeonesPC::
	msgbox gText_AccessedSomeonesPC, MSGBOX_DEFAULT
	return

EventScript_AccessLanettesPC::
	msgbox gText_AccessedLanettesPC, MSGBOX_DEFAULT
	return

EventScript_TurnOffPC::
	setvar VAR_0x8004, PC_LOCATION_OTHER
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

EventScript_AccessHallOfFame::
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_TurnOffPC
	playse SE_PC_LOGIN
	special AccessHallOfFamePC
	waitstate
	goto EventScript_AccessPC
	end

EventScript_AccessPokemonBoxLink::
	playse SE_PC_LOGIN
	msgbox gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto EventScript_TurnOffPC
	end

EventScript_AccessTimeChanger::
	lock
	playse SE_PC_LOGIN
	message EventScript_AccessTimeChanger_Text_0
	waitmessage
	dynmultipush EventScript_AccessTimeChanger_Text_1, 1
	dynmultipush EventScript_AccessTimeChanger_Text_2, 2
	dynmultipush EventScript_AccessTimeChanger_Text_3, 3
	dynmultipush EventScript_AccessTimeChanger_Text_4, 4
	dynmultipush EventScript_AccessTimeChanger_Text_5, 127
	dynmultistack 0, 0, FALSE, 5, FALSE, 0xFF, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 1, EventScript_AccessTimeChanger_2
	case 2, EventScript_AccessTimeChanger_3
	case 3, EventScript_AccessTimeChanger_4
	case 4, EventScript_AccessTimeChanger_5
	case 127, EventScript_AccessTimeChanger_6
	return

EventScript_AccessTimeChanger_2:
	callnative FakeRtc_ManuallySetTimeDay
	closemessage
	release
	end

EventScript_AccessTimeChanger_3:
	callnative FakeRtc_ManuallySetTimeNight
	closemessage
	release
	end

EventScript_AccessTimeChanger_4:
	callnative FakeRtc_ManuallySetTimeDusk
	closemessage
	release
	end

EventScript_AccessTimeChanger_5:
	callnative RtcReset
	closemessage
	release
	end

EventScript_AccessTimeChanger_6:
	closemessage
	release
	end


EventScript_AccessTimeChanger_Text_0:
	.string "Wich time of day would you like to\n"
	.string "change too?$"

EventScript_AccessTimeChanger_Text_1:
	.string "Day$"

EventScript_AccessTimeChanger_Text_2:
	.string "Night$"

EventScript_AccessTimeChanger_Text_3:
	.string "Dusk$"

EventScript_AccessTimeChanger_Text_4:
	.string "Reset$"

EventScript_AccessTimeChanger_Text_5:
	.string "Cancel$"
