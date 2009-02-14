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


#include "CreatureLinkGroup.h"


LinkGroup::LinkGroup(uint32 linkgroupId, uint32 instanceId)
{
	m_linkgroupID = linkgroupId;
	incombat = false;
	LinkGroupmgr::AddTolist(linkgroupId, instanceId, this);
}
void LinkGroup::AddMember(Creature *cr, bool respawn)
{
	MemberSlot MSlot;
	MSlot.cr = cr;
	MSlot.respawn = respawn;
	m_memberSlots.push_back(MSlot);
}
void LinkGroup::DelMember(Creature * c)
{
	for(MemberList_witerator slot = m_memberSlots.begin(); slot != m_memberSlots.end(); ++slot)
	{
	    if (slot->cr && slot->cr == c && slot != m_memberSlots.end())
            {
                m_memberSlots.erase(slot);
                break;
            }
	}
}
void LinkGroup::AddHostile(Unit *u)
{

	for(MemberList_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
	{
		if(itr->cr->isAlive() && u->isAlive())
		{
			itr->cr->AddThreat(u,0.0f);
		}
	}
	incombat = true;
}


void LinkGroup::Reset()
{
	if(!incombat)
		return;
	incombat = false;
	
	for(MemberList_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
	{
		if(itr->respawn && !itr->cr->isAlive())
			itr->cr->Respawn();
		itr->cr->AI()->EnterEvadeMode();

	}
	

}

//define Static member
std::list<LinkGroupmgr::linkgroupslot> LinkGroupmgr::GroupList;
