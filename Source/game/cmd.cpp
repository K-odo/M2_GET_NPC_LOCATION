
//[1]
//Search [->] 
struct command_info

//Add above
#ifdef ENABLE_GET_NPC_LOCATION
ACMD(do_find_npc);
ACMD(do_find_near_npc);
#endif


//[2]
//Search [->] 
{ "\n",						NULL,						0,				POS_DEAD,		GM_IMPLEMENTOR	}

//Add above
#ifdef ENABLE_GET_NPC_LOCATION
	{ "find_npc",				do_find_npc,				0,				POS_DEAD,		GM_IMPLEMENTOR	},
	{ "find_near_npc",			do_find_near_npc,			0,				POS_DEAD,		GM_IMPLEMENTOR	},
#endif

