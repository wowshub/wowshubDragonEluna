/*
 * Copyright 2021 ShadowCore
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
#include "ObjectAccessor.h"
#include "TemporarySummon.h"
#include <sstream>

// npc - 55089 55093 55397 55398 
class npc_fire_juggler_darkmoon : public CreatureScript
{
public:
    npc_fire_juggler_darkmoon() : CreatureScript("npc_fire_juggler_darkmoon") { }

    enum eNPC
    {
        SPELL_JUGGLE_TORCH_AURA = 46322, //  102905,
        EVENT_START_FIRE_JUGGLING = 101,
    };

    struct npc_fire_juggler_darkmoonAI : public ScriptedAI
    {
        npc_fire_juggler_darkmoonAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset() override
        {
            events.Reset();
            events.ScheduleEvent(EVENT_START_FIRE_JUGGLING, 1s);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_FIRE_JUGGLING:
                {
                    if (!me->HasAura(SPELL_JUGGLE_TORCH_AURA))
                        me->AddAura(SPELL_JUGGLE_TORCH_AURA, me);
                    events.ScheduleEvent(EVENT_START_FIRE_JUGGLING, 3s);
                    break;
                }
                }
            }

            UpdateVictim();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fire_juggler_darkmoonAI(creature);
    }
};

 // Whee! - 46668
class spell_darkmoon_carousel_whee : public SpellScriptLoader
{
public:
    spell_darkmoon_carousel_whee() : SpellScriptLoader("spell_darkmoon_carousel_whee") { }

    class spell_darkmoon_carousel_whee_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_darkmoon_carousel_whee_AuraScript);

        uint32 update;

        bool Validate(SpellInfo const* /*spell*/) override
        {
            update = 0;
            return true;
        }

        void OnUpdate(uint32 diff)
        {
            update += diff;

            if (update >= 5000)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Transport* transport = dynamic_cast<Transport*>(_player->GetTransport()))
                    {
                        if (transport->GetEntry() == GOB_DARKMOON_CAROUSEL)
                        {
                            if (Aura* aura = GetAura())
                            {
                                uint32 currentMaxDuration = aura->GetMaxDuration();
                                uint32 newMaxDurantion = currentMaxDuration + (5 * MINUTE * IN_MILLISECONDS);
                                newMaxDurantion = newMaxDurantion <= (60 * MINUTE * IN_MILLISECONDS) ? newMaxDurantion : (60 * MINUTE * IN_MILLISECONDS);

                                aura->SetMaxDuration(newMaxDurantion);
                                aura->SetDuration(newMaxDurantion);
                            }
                        }
                    }
                }

                update = 0;
            }
        }

        void Register() override
        {
            OnAuraUpdate += AuraUpdateFn(spell_darkmoon_carousel_whee_AuraScript::OnUpdate);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_darkmoon_carousel_whee_AuraScript();
    }
};

// To the Staging Area! - 101260
class spell_darkmoon_staging_area_teleport : public SpellScriptLoader
{
public:
    spell_darkmoon_staging_area_teleport() : SpellScriptLoader("spell_darkmoon_staging_area_teleport") { }

    class spell_darkmoon_staging_area_teleport_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_darkmoon_staging_area_teleport_SpellScript);

        bool Load() override
        {
            return GetCaster() != nullptr;
        }

        void RelocateDest(SpellEffIndex /*effIndex*/)
        {
            if (Player* caster = GetCaster()->ToPlayer())
            {
                switch (caster->GetMapId())
                {
                    case 974: //Darkmoon Island
                        if (caster->GetTeamId() == TEAM_HORDE)
                            GetHitDest()->WorldRelocate(WorldLocation(1, -1454.415894f, 207.967484f, -7.790083f, 0.689538f));
                        else
                            GetHitDest()->WorldRelocate(WorldLocation(0, -9517.5f, 82.3f, 59.51f, 2.92168f));
                        break;
                    default:
                        GetHitDest()->WorldRelocate(WorldLocation(974, -3618.669922f, 6315.669922f, 113.190002f, 3.204420f));
                        break;
                }
            }
        }

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_darkmoon_staging_area_teleport_SpellScript::RelocateDest, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_darkmoon_staging_area_teleport_SpellScript();
    }
};

class item_darkmoon_faire_fireworks : public ItemScript
{
public:
    item_darkmoon_faire_fireworks() : ItemScript("item_darkmoon_faire_fireworks") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
    {
        AchievementEntry const* AchievFireworksAlliance = sAchievementStore.LookupEntry(6030);
        AchievementEntry const* AchievFireworksHorde = sAchievementStore.LookupEntry(6031);

        if (player->GetTeam() == ALLIANCE)
        {
            player->CompletedAchievement(AchievFireworksAlliance);
            player->CastSpell(player, 103740, false);
        }
        else
        {
            player->CompletedAchievement(AchievFireworksHorde);
            player->CastSpell(player, 103740, false);
        }

        return true;
    }
};

enum JESSICA_GOSSIP
{
    GOSSIP_BUTTON_1 = 13012,
    GOSSIP_BUTTON_1_ID = 0,
    GOSSIP_BUTTON_2 = 13012,
    GOSSIP_BUTTON_2_ID = 1,
    GOSSIP_BUTTON_3 = 13013,
    GOSSIP_BUTTON_3_ID = 0,
    
};

// 54485 - Jessica Rogers
class npc_jessica_rogers : public CreatureScript
{
public:
    npc_jessica_rogers() : CreatureScript("npc_jessica_rogers") { }

    struct npc_jessica_rogersAI : public ScriptedAI
    {
        npc_jessica_rogersAI(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            AddGossipItemFor(player, GOSSIP_BUTTON_1, GOSSIP_BUTTON_1_ID, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            SendGossipMenuFor(player, 18284, me->GetGUID());

            if (player->GetQuestStatus(QUEST_TARGET_TURTLE) == QUEST_STATUS_INCOMPLETE)
            {
                AddGossipItemFor(player, GOSSIP_BUTTON_2, GOSSIP_BUTTON_2_ID, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                SendGossipMenuFor(player, 53027, me->GetGUID());
            }

            player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                AddGossipItemFor(player, GOSSIP_BUTTON_3, GOSSIP_BUTTON_3_ID, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                if (player->HasItemCount(ITEM_DARKMOON_TOKEN))
                {
                    CloseGossipMenuFor(player);

                    player->DestroyItemCount(ITEM_DARKMOON_TOKEN, 1, true);
                    player->RemoveAurasByType(SPELL_AURA_MOUNTED);

                    player->AddAura(SPELL_RINGTOSS_ENABLE, player);
                    player->SetPower(POWER_ALTERNATE_POWER, 10);

                    return true;
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                AddGossipItemFor(player, GOSSIP_BUTTON_1, GOSSIP_BUTTON_1_ID, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                AddGossipItemFor(player, GOSSIP_BUTTON_2, GOSSIP_BUTTON_2_ID, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                break;
            }
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_jessica_rogersAI(creature);
    }
};

//
class spell_ring_toss : public SpellScriptLoader
{
public:
    spell_ring_toss() : SpellScriptLoader("spell_ring_toss") {}

    class spell_ring_toss_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ring_toss_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Player* player = GetCaster()->ToPlayer();

            WorldLocation* loc = GetHitDest();

            Creature* dubenko = caster->FindNearestCreature(54490, 100.0f, true);

            //dubenko->CastSpell(dubenko, 101737, false);
            if (dubenko && dubenko->IsWithinDist2d(loc, 1.2f))
            {
                if (dubenko->HasAura(SPELL_RINGTOSS_TURTLE_CIRCLE_1))
                {
                    if (dubenko->HasAura(SPELL_RINGTOSS_TURTLE_CIRCLE_2))
                        dubenko->CastSpell(dubenko, SPELL_RINGTOSS_TURTLE_CIRCLE_3, true);
                    else
                        dubenko->CastSpell(dubenko, SPELL_RINGTOSS_TURTLE_CIRCLE_2, true);
                }
                else
                    dubenko->CastSpell(dubenko, SPELL_RINGTOSS_TURTLE_CIRCLE_1, true);

                caster->CastSpell(dubenko, SPELL_RINGTOSS_HIT, false);
            }

            if (player)
            {
                if (player->GetReqKillOrCastCurrentCount(QUEST_TARGET_TURTLE, 54495) >= 3)
                    player->RemoveAurasDueToSpell(SPELL_RINGTOSS_ENABLE);
            }            
        }
                        

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ring_toss_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_ring_toss_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ring_toss_SpellScript();
    }
};

// at_target_turtle 7338
class at_target_turtle : public AreaTriggerScript
{
public:
    at_target_turtle() : AreaTriggerScript("at_target_turtle") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (!player->IsGameMaster())
            player->CastSpell(player, 109972, true);
        return true;
    }
};

// spells
class spell_gen_repair_damaged_tonk : public SpellScriptLoader
{
public:
    spell_gen_repair_damaged_tonk() : SpellScriptLoader("spell_gen_repair_damaged_tonk") {}

    class spell_gen_repair_damaged_tonk_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gen_repair_damaged_tonk_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* player = GetCaster()->ToPlayer();
            Creature* target = GetHitCreature();

            if (!target)
                return;

            player->KilledMonsterCredit(54504, ObjectGuid::Empty);

            Position myPos = target->GetPosition();
            target->SummonCreature(55356, myPos, TEMPSUMMON_TIMED_DESPAWN, 30000ms);
            target->DespawnOrUnsummon();
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gen_repair_damaged_tonk_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_gen_repair_damaged_tonk_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gen_repair_damaged_tonk_SpellScript();
    }
};

class spell_gen_shoe_baby : public SpellScriptLoader
{
public:
    spell_gen_shoe_baby() : SpellScriptLoader("spell_gen_shoe_baby") {}

    class spell_gen_shoe_baby_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gen_shoe_baby_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* player = GetCaster()->ToPlayer();
            player->KilledMonsterCredit(54510, ObjectGuid::Empty);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gen_shoe_baby_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_gen_shoe_baby_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gen_shoe_baby_SpellScript();
    }
};

class spell_cook_crunchy_frog : public SpellScriptLoader
{
public:
    spell_cook_crunchy_frog() : SpellScriptLoader("spell_cook_crunchy_frog") {}

    class spell_cook_crunchy_frog_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_cook_crunchy_frog_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* player = GetCaster()->ToPlayer();
            player->AddItem(72058, 1);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_cook_crunchy_frog_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_cook_crunchy_frog_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_cook_crunchy_frog_SpellScript();
    }
};

enum InjuriedCarnieYells
{
    SAY_GREETINGS_1 = 0,
    SAY_GREETINGS_2 = 1,
    SAY_GREETINGS_3 = 2,
    SAY_GREETINGS_4 = 3,
    SAY_GREETINGS_5 = 4,
};

class spell_heal_injuried_carnie : public SpellScriptLoader
{
public:
    spell_heal_injuried_carnie() : SpellScriptLoader("spell_heal_injuried_carnie") {}

    class spell_heal_injuried_carnie_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_heal_injuried_carnie_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleHealPct(SpellEffIndex /*effIndex*/)
        {
            Player* player = GetCaster()->ToPlayer();
            Creature* target = GetHitCreature();

            player->KilledMonsterCredit(54518, ObjectGuid::Empty);

            if (!target)
                return;

            switch (urand(0, 4))
            {
            case 0:
                target->AI()->Talk(SAY_GREETINGS_1);
                target->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                target->GetMotionMaster()->MoveRandom(30);
                target->DespawnOrUnsummon(8000ms);
                break;
            case 1:
                target->AI()->Talk(SAY_GREETINGS_2);
                target->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                target->GetMotionMaster()->MoveRandom(30);
                target->DespawnOrUnsummon(8000ms);
                break;
            case 2:
                target->AI()->Talk(SAY_GREETINGS_3);
                target->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                target->GetMotionMaster()->MoveRandom(30);
                target->DespawnOrUnsummon(8000ms);
                break;
            case 3:
                target->AI()->Talk(SAY_GREETINGS_4);
                target->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                target->GetMotionMaster()->MoveRandom(30);
                target->DespawnOrUnsummon(8000ms);
                break;
            case 4:
                target->AI()->Talk(SAY_GREETINGS_5);
                target->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                target->GetMotionMaster()->MoveRandom(30);
                target->DespawnOrUnsummon(8000ms);
                break;
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_heal_injuried_carnie_SpellScript::HandleHealPct, EFFECT_0, SPELL_EFFECT_HEAL_PCT);
            OnCheckCast += SpellCheckCastFn(spell_heal_injuried_carnie_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_heal_injuried_carnie_SpellScript();
    }
};

class spell_put_up_darkmoon_banner : public SpellScriptLoader
{
public:
    spell_put_up_darkmoon_banner() : SpellScriptLoader("spell_put_up_darkmoon_banner") {}

    class spell_put_up_darkmoon_banner_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_put_up_darkmoon_banner_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* player = GetCaster()->ToPlayer();
            player->KilledMonsterCredit(54545, ObjectGuid::Empty);

            if (Creature* loosestones = GetCaster()->FindNearestCreature(54545, 10.0f, true))
            {
                loosestones->SummonGameObject(179965, Position(loosestones->GetPositionX(), loosestones->GetPositionY(), loosestones->GetPositionZ(), loosestones->GetOrientation()), QuaternionData(), 0s);
                loosestones->DespawnOrUnsummon(30000ms);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_put_up_darkmoon_banner_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_put_up_darkmoon_banner_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_put_up_darkmoon_banner_SpellScript();
    }
};

class spell_darkmoon_deathmatch : public SpellScriptLoader
{
public:
    spell_darkmoon_deathmatch() : SpellScriptLoader("spell_darkmoon_deathmatch") {}

    class spell_darkmoon_deathmatch_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_darkmoon_deathmatch_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            if (caster->GetPositionY() <= 6400.0f)
                caster->CastSpell(caster, 108919, false);
            else
                caster->CastSpell(caster, 108923, false);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_darkmoon_deathmatch_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnCheckCast += SpellCheckCastFn(spell_darkmoon_deathmatch_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_darkmoon_deathmatch_SpellScript();
    }
};

enum HeShootsSpells
{
    SPELL_HESHOOTS_CRACKSHOT_ENABLE = 101871,
    SPELL_HESHOOTS_SHOOT = 101872,
    SPELL_HESHOOTS_TARGET_INDICATOR = 101010,
    SPELL_HESHOOTS_TARGET_INDICATOR_VISUAL = 43313,
    SPELL_HESHOOTS_KILL_CREDIT = 43300,
    SPELL_HESHOOTS_KILL_CREDIT_BONUS = 101012,
};

class npc_rinling_darkmoon : public CreatureScript
{
public:
    npc_rinling_darkmoon() : CreatureScript("npc_rinling_darkmoon") { }

    struct npc_rinling_darkmoonAI : public ScriptedAI
    {
        npc_rinling_darkmoonAI(Creature* creature) : ScriptedAI(creature)
        {
            Reset();
        }

        uint32 nextQuoteTimer;
        uint8 nextQuote;

        uint32 nextTargetChangeTimer;
        int8 targetIndex;
        ObjectGuid targetList[3];

        void Reset()
        {
            nextQuoteTimer = urand(1, 60) * 1000;
            nextQuote = 0;
            nextTargetChangeTimer = 0;
            targetIndex = -1;
        }

        void UpdateAI(const uint32 diff)
        {
            if (nextTargetChangeTimer <= diff)
            {
                if (targetIndex < 0 || targetIndex >= 3)
                {
                    std::list<Creature*> crList;
                    GetCreatureListWithEntryInGrid(crList, me, 24171, 100.0f);
                    int i = 0;
                    for (std::list<Creature*>::const_iterator itr = crList.begin(); itr != crList.end(); ++itr)
                    {
                        targetList[i++] = (*itr)->GetGUID();
                        if (i >= 3)
                            break;
                    }
                }

                int8 chosen = -1;
                do
                {
                    // randomly choose one of targets
                    chosen = urand(0, 2);
                } while (chosen == targetIndex && urand(0, 1) == 0); // the same target could be chosen with only 50% chance (+-)

                targetIndex = chosen;

                Creature* creature_bunny = ObjectAccessor::GetCreature(*me, targetList[chosen]);
                if (creature_bunny)
                    creature_bunny->CastSpell(creature_bunny, SPELL_HESHOOTS_TARGET_INDICATOR, true);

                nextTargetChangeTimer = 6500 + urand(0, 1000);
            }
            else
                nextTargetChangeTimer -= diff;
        }

        bool OnGossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            AddGossipItemFor(player, 6225, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            if (player->GetQuestStatus(QUEST_HE_SHOOTS_HE_SCORES) == QUEST_STATUS_INCOMPLETE)
                AddGossipItemFor(player, 6225, 2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

            player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*uiSender*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
                // Info
            case GOSSIP_ACTION_INFO_DEF + 1:
                    player->PlayerTalkClass->ClearMenus();
                    SendGossipMenuFor(player, 18353, me->GetGUID());
                    return OnGossipHello(player);
                break;
                // Ready to play
            case  GOSSIP_ACTION_INFO_DEF + 2:
                if (player->HasItemCount(ITEM_DARKMOON_TOKEN))
                {
                    CloseGossipMenuFor(player);

                    player->DestroyItemCount(ITEM_DARKMOON_TOKEN, 1, true);
                    player->CastSpell(player, SPELL_HESHOOTS_CRACKSHOT_ENABLE, true);

                    int16 progress = player->GetReqKillOrCastCurrentCount(QUEST_HE_SHOOTS_HE_SCORES, 54231);
                    if (progress > 0)
                        player->SetPower(POWER_ALTERNATE_POWER, progress);

                    return true;
                }
                break;
            }

            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rinling_darkmoonAI(creature);
    }
};

// spell - 101872
class spell_heshoots_shoot_hit : public SpellScriptLoader
{
public:
    spell_heshoots_shoot_hit() : SpellScriptLoader("spell_heshoots_shoot_hit") { }

    class spell_heshoots_shoot_hit_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_heshoots_shoot_hit_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster())
                return;

            Unit* target = GetHitUnit();

            if (!target)
                return;

            if (Aura* shootAura = target->GetAura(SPELL_HESHOOTS_TARGET_INDICATOR))
            {
                target->CastSpell(GetCaster(), SPELL_HESHOOTS_KILL_CREDIT, true);

                Player* pl = GetCaster()->ToPlayer();

                if (shootAura->GetMaxDuration() - shootAura->GetDuration() < 1000)
                {
                    target->CastSpell(GetCaster(), SPELL_HESHOOTS_KILL_CREDIT_BONUS, true);
                    AchievementEntry const* achiev = sAchievementStore.LookupEntry(6022);
                    if (pl)
                        pl->CompletedAchievement(achiev);
                }

                if (pl)
                {
                    if (pl->GetReqKillOrCastCurrentCount(QUEST_HE_SHOOTS_HE_SCORES, 54231) >= 25)
                        pl->RemoveAurasDueToSpell(SPELL_HESHOOTS_CRACKSHOT_ENABLE);
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_heshoots_shoot_hit_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_heshoots_shoot_hit_SpellScript();
    }
};

// spell - 101010
class spell_heshoots_indicator : public SpellScriptLoader
{
public:
    spell_heshoots_indicator() : SpellScriptLoader("spell_heshoots_indicator") { }

    class spell_heshoots_indicator_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_heshoots_indicator_AuraScript);

        void EffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*modes*/)
        {
            if (!GetUnitOwner())
                return;

            GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_HESHOOTS_TARGET_INDICATOR_VISUAL, true);
        }

        void EffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*modes*/)
        {
            if (!GetUnitOwner())
                return;

            GetUnitOwner()->RemoveAurasDueToSpell(SPELL_HESHOOTS_TARGET_INDICATOR_VISUAL);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_heshoots_indicator_AuraScript::EffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectApplyFn(spell_heshoots_indicator_AuraScript::EffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_heshoots_indicator_AuraScript();
    }
};

void AddSC_darkmoon_island()
{
    new npc_fire_juggler_darkmoon();

    new spell_darkmoon_carousel_whee();
    new spell_darkmoon_staging_area_teleport();

    new item_darkmoon_faire_fireworks();

    //ring toss
    new npc_jessica_rogers();
    new spell_ring_toss();
    new at_target_turtle();

    new spell_gen_repair_damaged_tonk();
    new spell_gen_shoe_baby();
    new spell_cook_crunchy_frog();
    new spell_heal_injuried_carnie();
    new spell_put_up_darkmoon_banner();
    new spell_darkmoon_deathmatch();

    //shoot gallery
    new npc_rinling_darkmoon();
    new spell_heshoots_shoot_hit();
    new spell_heshoots_indicator();
};
