/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "Config.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include <Item.h>

class promo : public CreatureScript {
public:
    promo() : CreatureScript("promo") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        std::string pname = player->GetName();        
        std::string player_ip = player->GetSession()->GetRemoteAddress();        
        uint32 paic = player->GetSession()->GetAccountId();
        uint8 fecha = 0;
        uint8 act = 0;
        bool ipc = false;
        bool paicc = false;        

        if (QueryResult t_query = CharacterDatabase.Query("SELECT `id_cuenta`, `active` FROM `promo_80` WHERE `id_cuenta` = '{}' and `active` = 0", paic))
        {
            do {
                Field* t_fields = t_query->Fetch();
                uint32 active = t_fields[1].Get<uint32>();

                if (active == 0)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("Aun no has activado el Item de la Promoción");
                    break;
                }

            } while (t_query->NextRow());

        }
        else {
            // IP
            if (QueryResult t_query = CharacterDatabase.Query("SELECT `ip` FROM `promo_80` WHERE `ip` = '{}'", player_ip))
            {
                do {
                    Field* t_fields = t_query->Fetch();
                    std::string ip = t_fields[0].Get<std::string>();

                    if (ip == player_ip)
                    {
                        ipc = true;
                        break;
                    }

                } while (t_query->NextRow());

            }
            //
            if (QueryResult t_query = CharacterDatabase.Query("SELECT `id_cuenta` FROM `promo_80` WHERE `id_cuenta` = '{}'", paic))
            {
                do {
                    Field* t_fields = t_query->Fetch();
                    uint16 pic = t_fields[0].Get<int32>();

                    if (pic == paic)
                    {
                        paicc = true;
                        break;
                    }

                } while (t_query->NextRow());

            }

            if (ipc || paicc) {
                ChatHandler(player->GetSession()).PSendSysMessage("No puedes recibir la Promoción de Lvl 80, ya la recibiste en algún momento, ya se encuentra registrada la IP o la Cuenta");

            }
            else {
                ChatHandler(player->GetSession()).PSendSysMessage("Recibes el item de Promoción de Lvl 80");
                player->AddItem(909090,1);
                player->AddItem(43308,30);
                player->AddItem(43307,30);
                player->ModifyMoney(100000);
                CharacterDatabase.Execute("INSERT INTO promo_80 (id_cuenta, personaje, ip, fecha, active) VALUES ({}, \"{}\", \"{}\", {}, {})", paic, pname, player_ip, fecha, act);

            }
        }
        player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
        return true;
    }
};

void AddpromoScripts() {
    new promo();
}
