
// [1]
// Add on the end of this file

#ifdef ENABLE_GET_NPC_LOCATION
ACMD(do_find_npc)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "usage: find_npc <vnum>");
		return;
	}

	DWORD npcVnum = atoi(arg1);
	std::vector<std::pair<long, long>> npcPositions;

	if (SECTREE_MANAGER::instance().GetNpcLocationByVnum(ch->GetMapIndex(), npcVnum, npcPositions))
	{
		int positionIndex = 1;

		ch->ChatPacket(CHAT_TYPE_INFO, "On the map found NPC(%d)", npcVnum);
		for (const auto& position : npcPositions)
		{
			//DEBUG INFO
			ch->ChatPacket(CHAT_TYPE_INFO, "[%d] - Position: %d, %d", positionIndex, position.first, position.second);
			positionIndex++;
		}
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "NPC(%d) not found on this map", npcVnum);
	}
}

ACMD(do_find_near_npc)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "usage: find_near_npc <vnum>");
		return;
	}

	DWORD npcVnum = atoi(arg1);
	std::vector<std::pair<long, long>> npcPositions;

	if (SECTREE_MANAGER::instance().GetNpcLocationByVnum(ch->GetMapIndex(), npcVnum, npcPositions))
	{
		if (npcPositions.empty())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "NPC(%d) not found on this map", npcVnum);
			return;
		}

		std::sort(npcPositions.begin(), npcPositions.end(),
			[ch](const std::pair<long, long>& a, const std::pair<long, long>& b)
			{
				return DISTANCE_APPROX(a.first - ch->GetX(), a.second - ch->GetY()) < DISTANCE_APPROX(b.first - ch->GetX(), b.second - ch->GetY());
			});

		//DEBUG INFO
		ch->ChatPacket(CHAT_TYPE_INFO, "On the map found NPC(%d)", npcVnum);
		ch->ChatPacket(CHAT_TYPE_INFO, "Nearest NPC position from us: X=%ld, Y=%ld, Distance=%d", npcPositions[0].first, npcPositions[0].second, DISTANCE_APPROX(npcPositions[0].first - ch->GetX(), npcPositions[0].second - ch->GetY()));
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "NPC(%d) not found on this map", npcVnum);
	}
}
#endif

