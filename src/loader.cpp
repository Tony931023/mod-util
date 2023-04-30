/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

// From SC
void AdditemrmScripts();
void AdditemuseScripts();
void AddPvp_ffaScripts();
void AddpromoScripts();



// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void Addmod_utilScripts()
{
    AdditemrmScripts();
    AdditemuseScripts();
    AddPvp_ffaScripts();
    AddpromoScripts();
}

