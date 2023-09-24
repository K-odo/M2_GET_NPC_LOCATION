
// [1]
// Search [->]
bool SECTREE_MANAGER::SaveAttributeToImage(int lMapIndex, const char * c_pszFileName, LPSECTREE_MAP pMapSrc)

// Add below
#ifdef ENABLE_GET_NPC_LOCATION
bool SECTREE_MANAGER::GetNpcLocationByVnum(long lMapIndex, DWORD npcVnum, std::vector<std::pair<long, long>>& positions)
{
	LPSECTREE_MAP sectree = SECTREE_MANAGER::instance().GetMap(lMapIndex);
	if (sectree != nullptr)
	{
		struct FFindNPCByVnum
		{
			DWORD specifiedVnum;
			std::vector<std::pair<long, long>>& npcPositions;
			FFindNPCByVnum(DWORD vnum, std::vector<std::pair<long, long>>& positions)
				: specifiedVnum(vnum), npcPositions(positions) {}

			void operator()(LPENTITY ent)
			{
				if (ent->IsType(ENTITY_CHARACTER))
				{
					LPCHARACTER pChar = static_cast<LPCHARACTER>(ent);
					if (pChar->IsNPC() && pChar->GetMobTable().dwVnum == specifiedVnum)
					{
						npcPositions.emplace_back(pChar->GetX(), pChar->GetY());
					}
				}
			}
		};
		std::vector<std::pair<long, long>> npcPositions; // We are creating a temporary vector to store NPC positions.
		FFindNPCByVnum finder(npcVnum, npcPositions);
		sectree->for_each(finder);

		positions.insert(positions.end(), npcPositions.begin(), npcPositions.end());    // Here is NPC's positions
		
		return !positions.empty(); // Returns true if any NPC position found
	}
	return false;
}
#endif

