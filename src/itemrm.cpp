/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "Group.h"
#include "MapMgr.h"
#include "Chat.h"
#include "Config.h"
#include "Player.h"
#include "Creature.h"
#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Define.h"

// Add player scripts
class itemrm : public PlayerScript
{
public:
    itemrm() : PlayerScript("itemrm") { }

    void OnLogin(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("MyModule.Enable", false))
        {
            ChatHandler(player->GetSession()).SendSysMessage("Hello World from Skeleton-Module!");
        }
    }
};

class itemuse : public ItemScript {
public:
    itemuse() : ItemScript("itemuse") { }

    bool OnUse(Player* p, Item* i, const SpellCastTargets&) override
    {
        if (p->GetMap()->IsRaidOrHeroicDungeon() == 1) {

            if (p->IsInCombat() || p->IsInFlight() || p->GetMap()->IsBattlegroundOrArena())
            {
                ChatHandler(p->GetSession()).PSendSysMessage("Estás en combate.!");
                return true;
            }

            Map::PlayerList const& player_list = p->GetMap()->GetPlayers();

            if (!player_list.IsEmpty()) {
                for (const auto& player_iteration : player_list) {
                    if (Player* player_handle = player_iteration.GetSource()) {
                        if (player_handle->IsInCombat()) {
                            ChatHandler(p->GetSession()).PSendSysMessage("Hay miembros en combate.!");
                            return true;
                        }
                    }
                }
            }

            return false;

        }

        ChatHandler(p->GetSession()).PSendSysMessage("No se puede usar en esta Zona.!");
        return true;        
    }
};

void AdditemuseScripts() {
    new itemuse();
}

// Add all scripts in one
void AdditemrmScripts()
{
    new itemrm();
}
