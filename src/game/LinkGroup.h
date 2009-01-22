/* 
 * Copyright (C) 2005-2008 MaNGOS <http://www.mangosproject.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "GroupReference.h"
#include "GroupRefManager.h"
#include "LootMgr.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "Unit.h"

#include <list>


#ifndef MANGOSSERVER_LINKGROUP_H
#define MANGOSSERVER_LINKGROUP_H



class LinkGroup
{
	struct MemberSlot
    {
		Creature* cr;
		bool respawn;
	};

	typedef std::list<MemberSlot> MemberSlotList;
	MemberSlotList m_memberSlots;
	typedef MemberSlotList::iterator MemberList_witerator;

	public:
	LinkGroup(uint32 linkgroupId, uint32 instanceId);
	~LinkGroup(){};
	void AddMember(Creature* cr, bool respawn);
	void DelMember(Creature* cr);
	void AddHostile(Unit * u);
	bool GetInCombat() {return incombat;}
	void Reset();
	uint32 m_linkgroupID;

	private:
	bool incombat;
	bool m_respawn;


};
class LinkGroupmgr
{

public:
	LinkGroupmgr() {}

	struct linkgroupslot
	{    
		LinkGroup* linkgroup;
		uint32 linkgroupid;
		uint32 instanceid;
	};
	typedef std::list<linkgroupslot> Grouplist;
	typedef Grouplist::iterator Grouplist_witerator;

	static void AddTolist(uint32 linkgroupid, uint32 instanceid, LinkGroup* linkgroup)
	{
		linkgroupslot member;
		member.instanceid = instanceid;
		member.linkgroupid = linkgroupid;
		member.linkgroup = linkgroup;
		GroupList.push_back(member);
	}
	static LinkGroup * Find(uint32 linkgroupid, uint32 instanceid)
	{
		
            for(Grouplist_witerator itr = GroupList.begin(); itr != GroupList.end(); ++itr)
            {
				if(itr->instanceid == instanceid && itr->linkgroupid == linkgroupid)
					return itr->linkgroup;
            }
			return NULL;
	}
private:
	static Grouplist GroupList;

};
#endif
