/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include "GameObject.h"
#include "Transport.h"
#include "DarkmoonIsland.h"
#include "AchievementMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "ScriptedCreature.h"
#include "DarkmoonIsland.h"
#include "Player.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "WorldSession.h"
#include "Item.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "GameEventMgr.h"
#include "AchievementPackets.h"
#include "DB2HotfixGenerator.h"
#include "DB2Stores.h"
#include "CellImpl.h"
#include "ChatTextBuilder.h"
#include "Containers.h"
#include "DatabaseEnv.h"
#include "GameTime.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Language.h"
#include "Mail.h"
#include "ObjectMgr.h"
#include "RBAC.h"
#include "StringConvert.h"
#include "World.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CreatureAI.h"
#include "CreatureAIImpl.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SharedDefines.h"
#include "SpellAuraEffects.h"
#include "PhasingHandler.h"
#include "ObjectAccessor.h"
#include "TemporarySummon.h"
#include <sstream>

enum NPC
{
    /// Race
    BigRaceBunny                    = 3500042, //need find original
    ShortRaceBunny                  = 3500040, //need find original
    NPC_POWERUP_BUNNY_CHECKPOINT    = 75718,
    NPC_POWERUP_BUNNY_LOOT          = 74872,
    NPC_POWERUP_BUNNY_ROCKET        = 74610, // 74678?
};


uint32 RaceQuestId[5]
{
    37819,
    33756,
    37910,
    37868,
    37911
};

 /// Darkmoon Race Phase
class PlayerScript_darkmoon_race_quest : public PlayerScript
{
public:
    PlayerScript_darkmoon_race_quest() :PlayerScript("PlayerScript_darkmoon_race_quest") {}

    void OnQuestAccept(Player* player, Quest const* quest) override
    {
        switch (quest->GetQuestId())
        {
        case QUEST_WELCOME_TO_THE_DARKMOON_RACES:
        case QUEST_LETS_KEEP_RACING:
        case QUEST_THE_REAL_RACE:
        case QUEST_MORE_BIG_RACING:
        case QUEST_THE_REAL_BIG_RACE:
        {
            if (!player->HasAura(SPELL_WANDERLUSTER) && !player->HasAura(SPELL_POWERMONGER) && !player->HasAura(SPELL_ROCKETEER) && !player->HasAura(SPELL_RACINGSTRIDER))
                player->CastSpell(player, SPELL_RACINGSTRIDER, true);

            PhasingHandler::AddPhase(player, 74536, true);
            break;
        }
        default:
            break;
        }
    }

    void OnQuestAbandon(Player* player, Quest const* quest) override
    {
        switch (quest->GetQuestId())
        {
        case QUEST_WELCOME_TO_THE_DARKMOON_RACES:
        case QUEST_LETS_KEEP_RACING:
        case QUEST_THE_REAL_RACE:
        case QUEST_MORE_BIG_RACING:
        case QUEST_THE_REAL_BIG_RACE:
        {
            PhasingHandler::AddPhase(player, 74536, true);
            PhasingHandler::AddPhase(player, 74372, true);
            PhasingHandler::AddPhase(player, 74365, true);
            PhasingHandler::AddPhase(player, 74368, true);
            PhasingHandler::AddPhase(player, 74366, true);
            PhasingHandler::AddPhase(player, 74369, true);
            player->CastSpell(player, SPELL_RACE_CANCELED, true);
            std::list<Creature*> TriggerList;
            //player->GetCreatureListWithEntryInGrid(TriggerList, eCreature::BigRaceBunny, 500.0f);
            //player->GetCreatureListWithEntryInGrid(TriggerList, eCreature::ShortRaceBunny, 500.0f);

            for (auto trigger : TriggerList)
            {
                if (WorldObject* Owner = trigger->ToTempSummon()->GetSummoner())
                    if (Owner->GetGUID() == player->GetGUID())
                        trigger->DespawnOrUnsummon();
            }
            break;
        }
        default:
            break;
        }
    }

    void OnLogout(Player* p_Player) override
    {
        for (uint8 i = 0; i < 5; ++i)
            if (p_Player->GetQuestStatus(RaceQuestId[i]) == QUEST_STATUS_INCOMPLETE)
                p_Player->FailQuest(RaceQuestId[i]);
    }
};

 /// Darkmoon Race Mount - 179750 179751 179752 179256
class  spell_darkmoon_mount_race : public AuraScript
{
    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* Target = GetTarget();

        if (!Target)
            return;

        if (Player* Player = Target->ToPlayer())
        {
            for (uint8 i = 0; i < 5; ++i)
                if (Player->GetQuestStatus(RaceQuestId[i]) == QUEST_STATUS_INCOMPLETE)
                    Player->FailQuest(RaceQuestId[i]);

            std::list<Creature*> triggerList;
            //Player->GetCreatureListWithEntryInGrid(triggerList, eCreature::BigRaceBunny, 500.0f);
            //Player->GetCreatureListWithEntryInGrid(triggerList, eCreature::ShortRaceBunny, 500.0f);

            for (auto trigger : triggerList)
            {
                if (WorldObject* Owner = trigger->ToTempSummon()->GetSummoner())
                    if (Owner->GetGUID() == Player->GetGUID())
                        trigger->DespawnOrUnsummon();
            }
        }
    }

    void Register() override
    {
        switch (m_scriptSpellId)
        {
        case SPELL_WANDERLUSTER:
            AfterEffectRemove += AuraEffectRemoveFn(spell_darkmoon_mount_race::OnRemove, EFFECT_1, SPELL_AURA_MOUNTED, AURA_EFFECT_HANDLE_REAL);
            break;
        case SPELL_POWERMONGER:
        case SPELL_ROCKETEER:
        case SPELL_RACINGSTRIDER:
            AfterEffectRemove += AuraEffectRemoveFn(spell_darkmoon_mount_race::OnRemove, EFFECT_0, SPELL_AURA_MOUNTED, AURA_EFFECT_HANDLE_REAL);
            break;
        default:
            break;
        }
    }
};

/// Jump To PowerUp - 152725
class spell_darkmoon_jump_to_powerup : public SpellScript
{
    void HandleOnHit()
    {
        Unit* l_Caster = GetCaster();
        if (!l_Caster)
            return;

        std::list<Creature*> goodPowerUpLootList;
        std::list<Creature*> powerUpLootList;
        l_Caster->GetCreatureListWithEntryInGrid(powerUpLootList, NPC_POWERUP_BUNNY_LOOT, 100.0f);

        if (powerUpLootList.empty())
            return;

        for (auto powerUpLoot : goodPowerUpLootList)
        {
            if (l_Caster->isInFront(powerUpLoot))
                goodPowerUpLootList.push_back(powerUpLoot);
        }

        if (goodPowerUpLootList.empty())
            return;

        goodPowerUpLootList.sort(Trinity::ObjectDistanceOrderPred(l_Caster));
        l_Caster->CastSpell(goodPowerUpLootList.front(), SPELL_HAZARD_IMMUNITY, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_darkmoon_jump_to_powerup::HandleOnHit);
    }
};

/// Jump To Racer - 179804
class spell_darkmoon_jump_to_racer : public SpellScript
{
    void HandleOnHit()
    {
        Unit* l_Caster = GetCaster();
        if (!l_Caster)
            return;

        std::list<Player*> playerList;
        std::list<Player*> GoodplayerList;
        l_Caster->GetPlayerListInGrid(playerList, 100.0f);

        if (playerList.empty())
            return;

        for (auto plr : playerList)
        {
            if (plr->HasAura(SPELL_ROCKETEER))
                if (l_Caster->isInFront(plr))
                    GoodplayerList.push_back(plr);
        }

        if (GoodplayerList.empty())
            return;
        GoodplayerList.sort(Trinity::ObjectDistanceOrderPred(l_Caster));
        l_Caster->CastSpell(GoodplayerList.front(), SPELL_HAZARD_IMMUNITY, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_darkmoon_jump_to_racer::HandleOnHit);
    }
};

/// Lasso Powerup - 152943
/// Lasso Powerup - 150288
class spell_darkmoon_lasso_powerup : public SpellScript
{
    void FilterTarget(std::list<WorldObject*>& p_Targets)
    {
        Unit* Caster = GetCaster();
        if (!Caster || p_Targets.empty())
            return;

        p_Targets.sort(Trinity::ObjectDistanceOrderPred(Caster));
        p_Targets.resize(1);
    }

    void HandleOnHit()
    {
        Unit* Caster = GetCaster();
        if (!Caster)
            return;

        Position CasterPos = Caster->GetPosition();

        if (Unit* Target = GetHitUnit())
            if (Creature* PowerUpHit = Target->ToCreature())
                Caster->SummonCreature(PowerUpHit->GetEntry(), CasterPos, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 2000ms);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_darkmoon_lasso_powerup::FilterTarget, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
        OnHit += SpellHitFn(spell_darkmoon_lasso_powerup::HandleOnHit);
    }
};

/// Jump To Banner - 179748
/// Jump To Hazard - 153397
class spell_darkmoon_jump_to_checkpoint : public SpellScript
{
    void HandleOnHit()
    {
        Unit* l_Caster = GetCaster();
        if (!l_Caster)
            return;

        std::list<Creature*> checkpointList;
        std::list<Creature*> GoodcheckpointList;
        l_Caster->GetCreatureListWithEntryInGrid(checkpointList, NPC_POWERUP_BUNNY_CHECKPOINT, 100.0f);

        if (checkpointList.empty())
            return;

        for (auto checkpoint : checkpointList)
        {
            if (l_Caster->isInFront(checkpoint))
                GoodcheckpointList.push_back(checkpoint);
        }

        if (GoodcheckpointList.empty())
            return;
        GoodcheckpointList.sort(Trinity::ObjectDistanceOrderPred(l_Caster));
        l_Caster->CastSpell(GoodcheckpointList.front(), SPELL_HAZARD_IMMUNITY, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_darkmoon_jump_to_checkpoint::HandleOnHit);
    }
};

void AddSC_darkmoon_mount_race()
{
    new spell_darkmoon_mount_race();

    new spell_darkmoon_jump_to_powerup();
    new spell_darkmoon_jump_to_racer();
    new spell_darkmoon_lasso_powerup();
    new spell_darkmoon_jump_to_checkpoint();
};
