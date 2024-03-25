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

/*
 * Scripts for spells with SPELLFAMILY_MONK and SPELLFAMILY_GENERIC spells used by monk players.
 * Scriptnames of files in this file should be prefixed with "spell_monk_".
 */

#include "ScriptMgr.h"
#include "DB2Stores.h"
#include "Player.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "GridNotifiers.h"
#include "SpellHistory.h"
#include "SpellPackets.h"
#include "PhasingHandler.h"
#include "TemporarySummon.h"
#include "PetAI.h"
#include "DynamicObject.h"
#include "Containers.h"
#include "ObjectMgr.h"
#include <numeric>

enum MonkSpells
{
    SPELL_MONK_CALMING_COALESCENCE                      = 388220,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHANNEL         = 117952,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC        = 123333,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK       = 117962,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD    = 117953,
    SPELL_MONK_POWER_STRIKE_PROC                        = 129914,
    SPELL_MONK_POWER_STRIKE_ENERGIZE                    = 121283,
    SPELL_MONK_PROVOKE_SINGLE_TARGET                    = 116189,
    SPELL_MONK_PROVOKE_AOE                              = 118635,
    SPELL_MONK_NO_FEATHER_FALL                          = 79636,
    SPELL_MONK_OPEN_PALM_STRIKES_TALENT                 = 392970,
    SPELL_MONK_ROLL_BACKWARD                            = 109131,
    SPELL_MONK_ROLL_FORWARD                             = 107427,
    SPELL_MONK_SOOTHING_MIST                            = 115175,
    SPELL_MONK_STANCE_OF_THE_SPIRITED_CRANE             = 154436,
    SPELL_MONK_STAGGER_DAMAGE_AURA                      = 124255,
    SPELL_MONK_STAGGER_HEAVY                            = 124273,
    SPELL_MONK_STAGGER_LIGHT                            = 124275,
    SPELL_MONK_STAGGER_MODERATE                         = 124274,
    SPELL_MONK_SURGING_MIST_HEAL                        = 116995,
    SPELL_MONK_ZEN_PILGRIMAGE                           = 126892,
    SPELL_MONK_ZEN_PILGRIMAGE_RETURN                    = 126895,
    SPELL_MONK_ZEN_PILGRIMAGE_RETURN_AURA               = 126896,
    SPELL_MONK_POWER_STRIKES_AURA                       = 129914,
    SPELL_MONK_TOUCH_OF_DEATH                           = 322109,
    SPELL_MONK_TOUCH_OF_DEATH_DAMAGE                    = 322111,
    SPELL_MONK_TOUCH_OF_DEATH_AMPLIFIER                 = 271232,
    SPELL_MONK_DISABLE                                  = 116095,
    SPELL_MONK_DISABLE_ROOT                             = 116706,
    SPELL_MONK_RING_OF_PEACE_DISARM                     = 137461,
    SPELL_MONK_RING_OF_PEACE_SILENCE                    = 137460,
    SPELL_MONK_RING_OF_PEACE_KNOCKBACK                  = 142895,
    SPELL_MONK_SPEAR_HAND_STRIKE_SILENCE                = 116709,
    SPELL_MONK_TRANSCENDENCE_CLONE_TARGET               = 119051,
    SPELL_MONK_TRANSCENDENCE_VISUAL                     = 119053,
    SPELL_MONK_TRANSCENDENCE_TRANSFER                   = 119996,
    SPELL_MONK_TRANSCENDENCE_RANGE_CHECK                = 62388,
    SPELL_RISING_MIST_HEAL                              = 274912,
    SPELL_RISING_MIST                                   = 274909,
    SPELL_MONK_THUNDER_FOCUS_TEA                        = 116680,
    SPELL_MONK_RISING_THUNDER                           = 210804,
    SPELL_MONK_RENEWING_MIST_HOT                        = 119611,
    SPELL_MONK_MORTAL_WOUNDS                            = 115804,
    SPELL_MONK_ESSENCE_FONT_PERIODIC_HEAL               = 191840,
    SPELL_MONK_ENVELOPING_MIST                          = 124682,
    SPELL_MONK_FORTIFYING_BREW                          = 120954,
    SPELL_MONK_MODERATE_STAGGER                         = 124274,
    SPELL_MONK_LIGHT_STAGGER                            = 124275,
    SPELL_MONK_HEAVY_STAGGER                            = 124273,
    SPELL_MONK_DIZZYING_HAZE                            = 116330,
    SPELL_MONK_BREATH_OF_FIRE_DOT                       = 123725,
    SPELL_MONK_KEG_SMASH_AURA                           = 121253,
    SPELL_MONK_CLASH_RUSH                               = 324383,
    SPELL_MONK_CLASH_STUN                               = 324382,
    SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH           = 122281,
    SPELL_MONK_SONG_OF_CHI_JI_STUN                      = 198909,
    SPELL_MONK_CHI_WAVE_HEAL                            = 132463,
    SPELL_MONK_CHI_BURST_HEAL                           = 130654,
    SPELL_MONK_CHI_BURST_DAMAGE                         = 148135,
    SPELL_MONK_PURIFYING_BREW                           = 119582,
    MONK_NPC_JADE_SERPENT_STATUE                        = 60849,
};

#define MONK_TRANSCENDENCE_GUID "MONK_TRANSCENDENCE_GUID"

// 117952 - Crackling Jade Lightning
class spell_monk_crackling_jade_lightning : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MONK_STANCE_OF_THE_SPIRITED_CRANE,
            SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC
        });
    }

    void OnTick(AuraEffect const* /*aurEff*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MONK_STANCE_OF_THE_SPIRITED_CRANE))
                caster->CastSpell(caster, SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_crackling_jade_lightning::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 117959 - Crackling Jade Lightning
class spell_monk_crackling_jade_lightning_knockback_proc_aura : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK,
            SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD
        });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (GetTarget()->HasAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD))
            return false;

        if (eventInfo.GetActor()->HasAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHANNEL, GetTarget()->GetGUID()))
            return false;

        Spell* currentChanneledSpell = GetTarget()->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
        if (!currentChanneledSpell || currentChanneledSpell->GetSpellInfo()->Id != SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHANNEL)
            return false;

        return true;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        GetTarget()->CastSpell(eventInfo.GetActor(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK, TRIGGERED_FULL_MASK);
        GetTarget()->CastSpell(GetTarget(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK_CD, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_monk_crackling_jade_lightning_knockback_proc_aura::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_monk_crackling_jade_lightning_knockback_proc_aura::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 116849 - Life Cocoon
class spell_monk_life_cocoon : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_CALMING_COALESCENCE });
    }

    void CalculateAbsorb(SpellEffIndex /*effIndex*/)
    {
        int32 absorb = GetCaster()->CountPctFromMaxHealth(GetEffectValue());
        if (Player* player = GetCaster()->ToPlayer())
            AddPct(absorb, player->GetRatingBonusValue(CR_VERSATILITY_HEALING_DONE));

        if (AuraEffect* calmingCoalescence = GetCaster()->GetAuraEffect(SPELL_MONK_CALMING_COALESCENCE, EFFECT_0, GetCaster()->GetGUID()))
        {
            AddPct(absorb, calmingCoalescence->GetAmount());
            calmingCoalescence->GetBase()->Remove();
        }

        GetSpell()->SetSpellValue(SPELLVALUE_BASE_POINT0, absorb);
    }

    void Register() override
    {
        OnEffectLaunch += SpellEffectFn(spell_monk_life_cocoon::CalculateAbsorb, EFFECT_2, SPELL_EFFECT_DUMMY);
    }
};

// 392972 - Open Palm Strikes
class spell_monk_open_palm_strikes : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellEffect({ { SPELL_MONK_OPEN_PALM_STRIKES_TALENT, EFFECT_1} });
    }

    bool CheckProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*procInfo*/)
    {
        AuraEffect const* talent = GetTarget()->GetAuraEffect(SPELL_MONK_OPEN_PALM_STRIKES_TALENT, EFFECT_1);
        return talent && roll_chance_i(talent->GetAmount());
    }

    void Register() override
    {
        DoCheckEffectProc += AuraCheckEffectProcFn(spell_monk_open_palm_strikes::CheckProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 121817 - Power Strike
class spell_monk_power_strike_periodic : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_POWER_STRIKE_PROC });
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        GetTarget()->CastSpell(GetTarget(), SPELL_MONK_POWER_STRIKE_PROC, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_power_strike_periodic::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 129914 - Power Strike Proc
class spell_monk_power_strike_proc : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_POWER_STRIKE_ENERGIZE });
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        GetTarget()->CastSpell(GetTarget(), SPELL_MONK_POWER_STRIKE_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_monk_power_strike_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 115546 - Provoke
class spell_monk_provoke : public SpellScript
{
    static uint32 const BlackOxStatusEntry = 61146;

    bool Validate(SpellInfo const* spellInfo) override
    {
        if (!(spellInfo->GetExplicitTargetMask() & TARGET_FLAG_UNIT_MASK)) // ensure GetExplTargetUnit() will return something meaningful during CheckCast
            return false;
        return ValidateSpellInfo(
        {
            SPELL_MONK_PROVOKE_SINGLE_TARGET,
            SPELL_MONK_PROVOKE_AOE
        });
    }

    SpellCastResult CheckExplicitTarget()
    {
        if (GetExplTargetUnit()->GetEntry() != BlackOxStatusEntry)
        {
            SpellInfo const* singleTarget = sSpellMgr->AssertSpellInfo(SPELL_MONK_PROVOKE_SINGLE_TARGET, GetCastDifficulty());
            SpellCastResult singleTargetExplicitResult = singleTarget->CheckExplicitTarget(GetCaster(), GetExplTargetUnit());
            if (singleTargetExplicitResult != SPELL_CAST_OK)
                return singleTargetExplicitResult;
        }
        else if (GetExplTargetUnit()->GetOwnerGUID() != GetCaster()->GetGUID())
            return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void HandleDummy(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
        if (GetHitUnit()->GetEntry() != BlackOxStatusEntry)
            GetCaster()->CastSpell(GetHitUnit(), SPELL_MONK_PROVOKE_SINGLE_TARGET, true);
        else
            GetCaster()->CastSpell(GetHitUnit(), SPELL_MONK_PROVOKE_AOE, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_monk_provoke::CheckExplicitTarget);
        OnEffectHitTarget += SpellEffectFn(spell_monk_provoke::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 109132 - Roll
class spell_monk_roll : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_ROLL_BACKWARD, SPELL_MONK_ROLL_FORWARD, SPELL_MONK_NO_FEATHER_FALL });
    }

    SpellCastResult CheckCast()
    {
        if (GetCaster()->HasUnitState(UNIT_STATE_ROOT))
            return SPELL_FAILED_ROOTED;
        return SPELL_CAST_OK;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), GetCaster()->HasUnitMovementFlag(MOVEMENTFLAG_BACKWARD) ? SPELL_MONK_ROLL_BACKWARD : SPELL_MONK_ROLL_FORWARD,
            TRIGGERED_IGNORE_CAST_IN_PROGRESS);
        GetCaster()->CastSpell(GetCaster(), SPELL_MONK_NO_FEATHER_FALL, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_monk_roll::CheckCast);
        OnEffectHitTarget += SpellEffectFn(spell_monk_roll::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 107427 - Roll
// 109131 - Roll (backward)
class spell_monk_roll_aura : public AuraScript
{
    void CalcMovementAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount += 100;
    }

    void CalcImmunityAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount -= 100;
    }

    void ChangeRunBackSpeed(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->SetSpeed(MOVE_RUN_BACK, GetTarget()->GetSpeed(MOVE_RUN));
    }

    void RestoreRunBackSpeed(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->UpdateSpeed(MOVE_RUN_BACK);
    }

    void Register() override
    {
        // Values need manual correction
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_roll_aura::CalcMovementAmount, EFFECT_0, SPELL_AURA_MOD_SPEED_NO_CONTROL);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_roll_aura::CalcMovementAmount, EFFECT_2, SPELL_AURA_MOD_MINIMUM_SPEED);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_roll_aura::CalcImmunityAmount, EFFECT_5, SPELL_AURA_MECHANIC_IMMUNITY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_roll_aura::CalcImmunityAmount, EFFECT_6, SPELL_AURA_MECHANIC_IMMUNITY);

        // This is a special aura that sets backward run speed equal to forward speed
        AfterEffectApply += AuraEffectApplyFn(spell_monk_roll_aura::ChangeRunBackSpeed, EFFECT_4, SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectApplyFn(spell_monk_roll_aura::RestoreRunBackSpeed, EFFECT_4, SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};

// Utility for stagger scripts
Aura* FindExistingStaggerEffect(Unit* unit)
{
    if (Aura* auraLight = unit->GetAura(SPELL_MONK_STAGGER_LIGHT))
        return auraLight;

    if (Aura* auraModerate = unit->GetAura(SPELL_MONK_STAGGER_MODERATE))
        return auraModerate;

    if (Aura* auraHeavy = unit->GetAura(SPELL_MONK_STAGGER_HEAVY))
        return auraHeavy;

    return nullptr;
}

static constexpr SpellEffIndex AuraStaggerEffectTick = EFFECT_0;
static constexpr SpellEffIndex AuraStaggerEffectTotal = EFFECT_1;

// 115069 - Stagger
class spell_monk_stagger : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_STAGGER_LIGHT, SPELL_MONK_STAGGER_MODERATE, SPELL_MONK_STAGGER_HEAVY });
    }

    void AbsorbNormal(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
    {
        Absorb(dmgInfo, 1.0f);
    }

    void AbsorbMagic(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
    {
        AuraEffect const* effect = GetEffect(EFFECT_4);
        if (!effect)
            return;

        Absorb(dmgInfo, float(effect->GetAmount()) / 100.0f);
    }

    void Absorb(DamageInfo& dmgInfo, float multiplier)
    {
        // Prevent default action (which would remove the aura)
        PreventDefaultAction();

        // make sure damage doesn't come from stagger damage spell SPELL_MONK_STAGGER_DAMAGE_AURA
        if (SpellInfo const* dmgSpellInfo = dmgInfo.GetSpellInfo())
            if (dmgSpellInfo->Id == SPELL_MONK_STAGGER_DAMAGE_AURA)
                return;

        AuraEffect const* effect = GetEffect(AuraStaggerEffectTick);
        if (!effect)
            return;

        Unit* target = GetTarget();
        float agility = target->GetStat(STAT_AGILITY);
        float base = CalculatePct(agility, float(effect->GetAmount()));
        float K = sDB2Manager.EvaluateExpectedStat(ExpectedStatType::ArmorConstant, target->GetLevel(), -2, 0, Classes(target->GetClass()), 0);

        float newAmount = (base / (base + K));
        newAmount *= multiplier;

        // Absorb X percentage of the damage
        float absorbAmount = float(dmgInfo.GetDamage()) * newAmount;
        if (absorbAmount > 0)
        {
            dmgInfo.AbsorbDamage(absorbAmount);

            // Cast stagger and make it tick on each tick
            AddAndRefreshStagger(absorbAmount);
        }
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_monk_stagger::AbsorbNormal, EFFECT_1);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_monk_stagger::AbsorbMagic, EFFECT_2);
    }

private:
    void AddAndRefreshStagger(float amount)
    {
        Unit* target = GetTarget();
        if (Aura* auraStagger = FindExistingStaggerEffect(target))
        {
            AuraEffect* effStaggerRemaining = auraStagger->GetEffect(AuraStaggerEffectTotal);
            if (!effStaggerRemaining)
                return;

            float newAmount = effStaggerRemaining->GetAmount() + amount;
            uint32 spellId = GetStaggerSpellId(target, newAmount);
            if (spellId == effStaggerRemaining->GetSpellInfo()->Id)
            {
                auraStagger->RefreshDuration();
                effStaggerRemaining->ChangeAmount(newAmount, false, true /* reapply */);
            }
            else
            {
                // amount changed the stagger type so we need to change the stagger amount (e.g. from medium to light)
                GetTarget()->RemoveAura(auraStagger);
                AddNewStagger(target, spellId, newAmount);
            }
        }
        else
            AddNewStagger(target, GetStaggerSpellId(target, amount), amount);
    }

    uint32 GetStaggerSpellId(Unit* unit, float amount)
    {
        const float StaggerHeavy = 0.6f;
        const float StaggerModerate = 0.3f;

        float staggerPct = amount / float(unit->GetMaxHealth());
        return (staggerPct >= StaggerHeavy) ? SPELL_MONK_STAGGER_HEAVY :
            (staggerPct >= StaggerModerate) ? SPELL_MONK_STAGGER_MODERATE :
            SPELL_MONK_STAGGER_LIGHT;
    }

    void AddNewStagger(Unit* unit, uint32 staggerSpellId, float staggerAmount)
    {
        // We only set the total stagger amount. The amount per tick will be set by the stagger spell script
        unit->CastSpell(unit, staggerSpellId, CastSpellExtraArgs(SPELLVALUE_BASE_POINT1, staggerAmount).SetTriggerFlags(TRIGGERED_FULL_MASK));
    }
};

// 124255 - Stagger - SPELL_MONK_STAGGER_DAMAGE_AURA
class spell_monk_stagger_damage_aura : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_STAGGER_LIGHT, SPELL_MONK_STAGGER_MODERATE, SPELL_MONK_STAGGER_HEAVY });
    }

    void OnPeriodicDamage(AuraEffect const* aurEff)
    {
        // Update our light/medium/heavy stagger with the correct stagger amount left
        if (Aura* auraStagger = FindExistingStaggerEffect(GetTarget()))
        {
            if (AuraEffect* auraEff = auraStagger->GetEffect(AuraStaggerEffectTotal))
            {
                float total = float(auraEff->GetAmount());
                float tickDamage = float(aurEff->GetAmount());
                auraEff->ChangeAmount(total - tickDamage);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_stagger_damage_aura::OnPeriodicDamage, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 124273, 124274, 124275 - Light/Moderate/Heavy Stagger - SPELL_MONK_STAGGER_LIGHT / SPELL_MONK_STAGGER_MODERATE / SPELL_MONK_STAGGER_HEAVY
class spell_monk_stagger_debuff_aura : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_STAGGER_DAMAGE_AURA })
            && ValidateSpellEffect({ { SPELL_MONK_STAGGER_DAMAGE_AURA, EFFECT_0 } });
    }

    bool Load() override
    {
        _period = float(sSpellMgr->AssertSpellInfo(SPELL_MONK_STAGGER_DAMAGE_AURA, GetCastDifficulty())->GetEffect(EFFECT_0).ApplyAuraPeriod);
        return true;
    }

    void OnReapply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        // Calculate damage per tick
        float total = float(aurEff->GetAmount());
        float perTick = total * _period / float(GetDuration()); // should be same as GetMaxDuration() TODO: verify

        // Set amount on effect for tooltip
        AuraEffect* effInfo = GetAura()->GetEffect(AuraStaggerEffectTick);
        if (effInfo)
            effInfo->ChangeAmount(perTick);

        // Set amount on damage aura (or cast it if needed)
        CastOrChangeTickDamage(perTick);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        if (mode != AURA_EFFECT_HANDLE_REAL)
            return;

        // Remove damage aura
        GetTarget()->RemoveAura(SPELL_MONK_STAGGER_DAMAGE_AURA);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectRemoveFn(spell_monk_stagger_debuff_aura::OnReapply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(spell_monk_stagger_debuff_aura::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }

private:
    float _period = 0.0f;

    void CastOrChangeTickDamage(float tickDamage)
    {
        Unit* unit = GetTarget();
        Aura* auraDamage = unit->GetAura(SPELL_MONK_STAGGER_DAMAGE_AURA);
        if (!auraDamage)
        {
            unit->CastSpell(unit, SPELL_MONK_STAGGER_DAMAGE_AURA, true);
            auraDamage = unit->GetAura(SPELL_MONK_STAGGER_DAMAGE_AURA);
        }

        if (auraDamage)
            if (AuraEffect* eff = auraDamage->GetEffect(AuraStaggerEffectTick))
                eff->ChangeAmount(tickDamage);
    }
};

// Zen Pilgrimage - 126892, Zen Pilgrimage - 194011
class spell_monk_zen_pilgrimage : public SpellScriptLoader
{
public:
    spell_monk_zen_pilgrimage() : SpellScriptLoader("spell_monk_zen_pilgrimage") { }

    class spell_monk_zen_pilgrimage_SpellScript : public SpellScript
    {
        SpellCastResult CheckDist()
        {
            if (GetSpellInfo()->Id == 194011)
                return SPELL_CAST_OK;

            if (Unit* caster = GetCaster())
                if (Player* _player = caster->ToPlayer())
                    if (_player->IsQuestRewarded(40236)) // Check quest for port to oplot
                    {
                        caster->CastSpell(caster, 194011, false);
                        return SPELL_FAILED_DONT_REPORT;
                    }

            return SPELL_CAST_OK;
        }

        void HandleOnCast()
        {
            if (Unit* caster = GetCaster())
                if (Player* _player = caster->ToPlayer())
                {
                    if (GetSpellInfo()->Id == SPELL_MONK_ZEN_PILGRIMAGE)
                    {
                        _player->SaveManualRecallPosition();
                        _player->CastSpell(_player, SPELL_MONK_ZEN_PILGRIMAGE_RETURN_AURA, true);
                    }

                }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_monk_zen_pilgrimage_SpellScript::HandleOnCast);
            OnCheckCast += SpellCheckCastFn(spell_monk_zen_pilgrimage_SpellScript::CheckDist);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_zen_pilgrimage_SpellScript();
    }
};

// Zen Pilgrimage : Return - 126895
class spell_monk_zen_pilgrimage_return : public SpellScriptLoader
{
public:
    spell_monk_zen_pilgrimage_return() : SpellScriptLoader("spell_monk_zen_pilgrimage_return") { }

    class spell_monk_zen_pilgrimage_return_SpellScript : public SpellScript
    {
        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* _player = caster->ToPlayer())
                {
                    if (GetSpellInfo()->Id == SPELL_MONK_ZEN_PILGRIMAGE_RETURN)
                    {
                        _player->ManualRecall();
                        _player->RemoveAura(SPELL_MONK_ZEN_PILGRIMAGE_RETURN_AURA);
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_zen_pilgrimage_return_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_zen_pilgrimage_return_SpellScript();
    }
};

// 100780 - Tiger Palm
class spell_monk_tiger_palm : public SpellScript
{
    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (Aura* powerStrikes = GetCaster()->GetAura(SPELL_MONK_POWER_STRIKES_AURA))
        {
            SetEffectValue(GetEffectValue() + powerStrikes->GetEffect(EFFECT_0)->GetBaseAmount());
            powerStrikes->Remove();
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_tiger_palm::HandleHit, EFFECT_1, SPELL_EFFECT_ENERGIZE);
    }
};

// Zen Flight - 125883
class spell_monk_zen_flight_check : public SpellScriptLoader
{
public:
    spell_monk_zen_flight_check() : SpellScriptLoader("spell_monk_zen_flight_check") { }

    class spell_monk_zen_flight_check_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_zen_flight_check_SpellScript);

        SpellCastResult CheckTarget()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (_player->GetMap()->IsBattlegroundOrArena())
                    return SPELL_FAILED_NOT_IN_BATTLEGROUND;

                // In Kalimdor or Eastern Kingdom with Flight Master's License
                if (!_player->HasSpell(90267) && (_player->GetMapId() == 1 || _player->GetMapId() == 0))
                    return SPELL_FAILED_NOT_HERE;

                // In Pandaria with Wisdom of the Four Winds
                if (!_player->HasSpell(115913) && (_player->GetMapId() == 870))
                    return SPELL_FAILED_NOT_HERE;

                // Legion, Broken Isles
                if (_player->GetMapId() == 1220)
                    return SPELL_FAILED_NOT_HERE;

                // In BfA Content not yet
                if (_player->GetMapId() == 1642 || _player->GetMapId() == 1643)
                    return SPELL_FAILED_NOT_HERE;
            }

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_monk_zen_flight_check_SpellScript::CheckTarget);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_zen_flight_check_SpellScript();
    }

    class spell_monk_zen_flight_check_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_zen_flight_check_AuraScript);

        bool Load() override
        {
            return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (!GetCaster())
                return;

            if (Player* caster = GetCaster()->ToPlayer())
                if (caster->GetSkillValue(SKILL_RIDING) >= 375)
                    amount = 310;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_zen_flight_check_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_zen_flight_check_AuraScript();
    }
};

// Touch of Death - 322109
class spell_monk_touch_of_death : public AuraScript
{
    PrepareAuraScript(spell_monk_touch_of_death);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = true;
        if (Unit* caster = GetCaster())
            if (int32 effInfo = GetAura()->GetSpellInfo()->GetEffect(EFFECT_1).CalcValue())
            {
                amount = int32(caster->CountPctFromMaxHealth(effInfo));
                const_cast<AuraEffect*>(aurEff)->SetAmount(amount);
            }
    }

    void OnTick(AuraEffect const* aurEff)
    {
        if (Unit* caster = GetCaster())
        {
            int32 damage = aurEff->GetAmount();

            // Damage reduced to Players, need to check reduction value
            if (GetTarget()->GetTypeId() == TYPEID_PLAYER)
                damage /= 2;

            caster->CastSpell(GetTarget(), SPELL_MONK_TOUCH_OF_DEATH_DAMAGE, CastSpellExtraArgs().AddSpellBP0(damage));
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_touch_of_death::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_touch_of_death::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 271232 - Touch of Death Amplifier - Triggers: 271233 on ToD Cast via proc
class spell_monk_touch_of_death_passive : public AuraScript
{
    PrepareAuraScript(spell_monk_touch_of_death_passive);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_MONK_TOUCH_OF_DEATH
            });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo()->Id != SPELL_MONK_TOUCH_OF_DEATH)
            return false;
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_monk_touch_of_death_passive::CheckProc);
    }
};

// 322113 - Amplifier (Applied with ToD)
class spell_monk_touch_of_death_amplifier : public AuraScript
{
    PrepareAuraScript(spell_monk_touch_of_death_amplifier);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_MONK_TOUCH_OF_DEATH,
                SPELL_MONK_TOUCH_OF_DEATH_AMPLIFIER
            });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        if (AuraEffect* aurEff = GetTarget()->GetAuraEffect(SPELL_MONK_TOUCH_OF_DEATH, EFFECT_0))
            if (AuraEffect* aurEffAmplifier = eventInfo.GetActor()->GetAuraEffect(SPELL_MONK_TOUCH_OF_DEATH_AMPLIFIER, EFFECT_0))
            {
                int32 damage = aurEff->GetAmount() + CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEffAmplifier->GetAmount());
                aurEff->SetAmount(damage);
            }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_monk_touch_of_death_amplifier::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_monk_touch_of_death_amplifier::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Disable - 116095
class spell_monk_disable : public SpellScript
{
    PrepareSpellScript(spell_monk_disable);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MONK_DISABLE, SPELL_MONK_DISABLE_ROOT });
    }

    void HandleOnEffectHitTarget(SpellEffIndex /*effectIndex*/)
    {
        if (Unit* target = GetExplTargetUnit())
            if (target->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED))
                GetCaster()->CastSpell(target, SPELL_MONK_DISABLE_ROOT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_disable::HandleOnEffectHitTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

// Disable - 116095
class aura_monk_disable : public AuraScript
{
    PrepareAuraScript(aura_monk_disable);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
        {
            if ((damageInfo->GetAttackType() == BASE_ATTACK ||
                damageInfo->GetAttackType() == OFF_ATTACK) &&
                damageInfo->GetAttacker() == GetCaster())
            {
                GetAura()->RefreshDuration();
                return true;
            }
        }
        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(aura_monk_disable::CheckProc);
    }
};

// Spear Hand Strike - 116705
class spell_monk_spear_hand_strike : public SpellScriptLoader
{
public:
    spell_monk_spear_hand_strike() : SpellScriptLoader("spell_monk_spear_hand_strike") { }

    class spell_monk_spear_hand_strike_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_spear_hand_strike_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->isInFront(_player))
                    {
                        _player->CastSpell(target, SPELL_MONK_SPEAR_HAND_STRIKE_SILENCE, true);
                        _player->GetSpellHistory()->AddCooldown(116705, 0, std::chrono::seconds(15));
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_monk_spear_hand_strike_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_spear_hand_strike_SpellScript();
    }
};

// 101643
class spell_monk_transcendence : public SpellScript
{
public:
    PrepareSpellScript(spell_monk_transcendence);

    void HandleSummon(Creature* creature)
    {
        DespawnSpirit(GetCaster());
        GetCaster()->CastSpell(creature, SPELL_MONK_TRANSCENDENCE_CLONE_TARGET, true);
        creature->CastSpell(creature, SPELL_MONK_TRANSCENDENCE_VISUAL, true);
        creature->SetAIAnimKitId(2223); // Sniff Data
        creature->SetDisableGravity(true);
        creature->SetControlled(true, UNIT_STATE_ROOT);
        GetCaster()->VariableStorage.Set(MONK_TRANSCENDENCE_GUID, creature->GetGUID());
    }

    static Creature* GetSpirit(Unit* caster)
    {
        ObjectGuid spiritGuid = caster->VariableStorage.GetValue<ObjectGuid>(MONK_TRANSCENDENCE_GUID, ObjectGuid());

        if (spiritGuid.IsEmpty())
            return nullptr;

        return ObjectAccessor::GetCreature(*caster, spiritGuid);
    }

    static void DespawnSpirit(Unit* caster)
    {
        // Remove previous one if any
        if (Creature* spirit = GetSpirit(caster))
            spirit->DespawnOrUnsummon();

        caster->VariableStorage.Remove(MONK_TRANSCENDENCE_GUID);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_monk_transcendence::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
    }
};

// 101643
class aura_monk_transcendence : public AuraScript
{
    PrepareAuraScript(aura_monk_transcendence);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        spell_monk_transcendence::DespawnSpirit(GetTarget());

        if (GetTarget()->HasAura(SPELL_MONK_TRANSCENDENCE_RANGE_CHECK))
        {
            GetTarget()->RemoveAura(SPELL_MONK_TRANSCENDENCE_RANGE_CHECK);
        }
    }

    void HandleDummyTick(AuraEffect const* /*aurEff*/)
    {
        SpellInfo const* spellInfo = sSpellMgr->AssertSpellInfo(SPELL_MONK_TRANSCENDENCE_TRANSFER, GetCastDifficulty());

        Unit* spirit = spell_monk_transcendence::GetSpirit(GetTarget());
        if (spirit && GetTarget()->IsWithinDist(spirit, spellInfo->GetMaxRange(true)))
        {
            if (!GetTarget()->HasAura(SPELL_MONK_TRANSCENDENCE_RANGE_CHECK))
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_MONK_TRANSCENDENCE_RANGE_CHECK, true);
            }
        }
        else
        {
            if (GetTarget()->HasAura(SPELL_MONK_TRANSCENDENCE_RANGE_CHECK))
            {
                GetTarget()->RemoveAura(SPELL_MONK_TRANSCENDENCE_RANGE_CHECK);
            }
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(aura_monk_transcendence::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_monk_transcendence::HandleDummyTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 119996 - Transcendence: Transfer
class spell_monk_transcendence_transfer : public SpellScript
{
    PrepareSpellScript(spell_monk_transcendence_transfer);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();

        if (!caster)
            return SPELL_FAILED_ERROR;

        Unit* spirit = spell_monk_transcendence::GetSpirit(caster);
        if (!spirit)
        {
            SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_YOU_HAVE_NO_SPIRIT_ACTIVE);
            return SPELL_FAILED_CUSTOM_ERROR;
        }

        if (!spirit->IsWithinDist(caster, GetSpellInfo()->GetMaxRange(true, caster, GetSpell())))
            return SPELL_FAILED_OUT_OF_RANGE;

        return SPELL_CAST_OK;
    }

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Unit* spirit = spell_monk_transcendence::GetSpirit(caster);
        if (!spirit)
            return;

        caster->NearTeleportTo(*spirit, true);
        spirit->NearTeleportTo(*caster, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_monk_transcendence_transfer::CheckCast);
        OnCast += SpellCastFn(spell_monk_transcendence_transfer::HandleOnCast);
    }
};

// Rising Sun Kick - 107428
class spell_monk_rising_sun_kick : public SpellScript
{
    PrepareSpellScript(spell_monk_rising_sun_kick);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster()->ToPlayer();
        Unit* target = GetHitUnit();
        if (!target || !caster)
            return;

        if (caster->HasAura(SPELL_MONK_RISING_THUNDER))
            caster->ToPlayer()->GetSpellHistory()->ResetCooldown(SPELL_MONK_THUNDER_FOCUS_TEA, true);

        if (caster->GetPrimarySpecialization() == ChrSpecialization::MonkBrewmaster)
            caster->CastSpell(target, SPELL_MONK_MORTAL_WOUNDS, true);

        if (caster->GetPrimarySpecialization() == ChrSpecialization::MonkMistweaver && caster->HasAura(SPELL_RISING_MIST))
        {
            caster->CastSpell(nullptr, SPELL_RISING_MIST_HEAL, true);

            if (Aura* reneWingMist = caster->GetAura(SPELL_MONK_RENEWING_MIST_HOT))
                reneWingMist->RefreshDuration(true);

            if (Aura* envelopingMist = caster->GetAura(SPELL_MONK_ENVELOPING_MIST))
                envelopingMist->RefreshDuration(true);

            if (Aura* essenceFont = caster->GetAura(SPELL_MONK_ESSENCE_FONT_PERIODIC_HEAL))
                essenceFont->RefreshDuration(true);
        }
        std::list<Unit*> u_li;
        caster->GetFriendlyUnitListInRange(u_li, 100.0f);
        for (auto& targets : u_li)
        {
            if (Aura* relatedAuras = targets->GetAura(SPELL_MONK_RENEWING_MIST_HOT || targets->GetAura(SPELL_MONK_ENVELOPING_MIST || targets->GetAura(SPELL_MONK_ESSENCE_FONT_PERIODIC_HEAL))))
                relatedAuras->RefreshDuration(true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_rising_sun_kick::HandleOnHit, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

// Fortifying brew - 115203
class spell_monk_fortifying_brew : public SpellScriptLoader
{
public:
    spell_monk_fortifying_brew() : SpellScriptLoader("spell_monk_fortifying_brew") { }

    class spell_monk_fortifying_brew_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_fortifying_brew_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (caster && caster->GetTypeId() == TYPEID_PLAYER)
                caster->CastSpell(caster, SPELL_MONK_FORTIFYING_BREW, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_fortifying_brew_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_fortifying_brew_SpellScript();
    }
};

// Purifying Brew - 119582
class spell_monk_purifying_brew : public SpellScriptLoader
{
public:
    spell_monk_purifying_brew() : SpellScriptLoader("spell_monk_purifying_brew") { }

    class spell_monk_purifying_brew_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_purifying_brew_SpellScript);

        void HandleOnHit()
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* _player = caster->ToPlayer())
                {
                    Aura* staggerAmount = _player->GetAura(SPELL_MONK_LIGHT_STAGGER);

                    if (!staggerAmount)
                        staggerAmount = _player->GetAura(SPELL_MONK_MODERATE_STAGGER);
                    if (!staggerAmount)
                        staggerAmount = _player->GetAura(SPELL_MONK_HEAVY_STAGGER);

                    if (staggerAmount)
                    {
                        int32 newStagger = staggerAmount->GetEffect(EFFECT_1)->GetAmount();
                        newStagger = newStagger * 0.5;
                        staggerAmount->GetEffect(EFFECT_1)->ChangeAmount(newStagger);
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_monk_purifying_brew_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_purifying_brew_SpellScript();
    }
};

// 115181 - Breath of Fire
class spell_monk_breath_of_fire : public SpellScriptLoader
{
public:
    spell_monk_breath_of_fire() : SpellScriptLoader("spell_monk_breath_of_fire") { }

    class spell_monk_breath_of_fire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_breath_of_fire_SpellScript);

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* _player = caster->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // if Dizzying Haze is on the target, they will burn for an additionnal damage over 8s
                        if (target->HasAura(SPELL_MONK_DIZZYING_HAZE))
                            _player->CastSpell(target, SPELL_MONK_BREATH_OF_FIRE_DOT, true);
                        if (target->HasAura(SPELL_MONK_KEG_SMASH_AURA))
                            _player->CastSpell(target, SPELL_MONK_BREATH_OF_FIRE_DOT, true);
                    }
                }
            }
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_monk_breath_of_fire_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_breath_of_fire_SpellScript();
    }
};

// Dampen Harm - 122278
class spell_monk_dampen_harm : public SpellScriptLoader
{
public:
    spell_monk_dampen_harm() : SpellScriptLoader("spell_monk_dampen_harm") { }
    class spell_monk_dampen_harm_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_dampen_harm_AuraScript);
        int32 healthPct;

        bool Load() override
        {
            healthPct = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(GetCaster());
            return GetUnitOwner()->ToPlayer();
        }

        void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void Absorb(AuraEffect* auraEffect, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            Unit* target = GetTarget();
            uint32 health = target->CountPctFromMaxHealth(healthPct);
            if (dmgInfo.GetDamage() < health)
                return;

            absorbAmount = dmgInfo.GetDamage() * (GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(GetCaster()) / 100);
            auraEffect->GetBase()->DropCharge();
        }
        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_dampen_harm_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_monk_dampen_harm_AuraScript::Absorb, EFFECT_0);
        }
    };
    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_dampen_harm_AuraScript();
    }
};

// 324312 - Clash
class spell_monk_clash : public SpellScript
{
    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = caster->ToPlayer()->GetSelectedUnit();
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_MONK_CLASH_RUSH, true);
        caster->CastSpell(target, SPELL_MONK_CLASH_STUN, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_monk_clash::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

//122280
class spell_monk_healing_elixirs_aura : public SpellScriptLoader
{
public:
    spell_monk_healing_elixirs_aura() : SpellScriptLoader("spell_monk_healing_elixirs_aura") { }
    class spell_monk_healing_elixirs_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_healing_elixirs_aura_AuraScript);
        void OnProc(AuraEffect* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            if (!GetCaster())
                return;
            if (!eventInfo.GetDamageInfo())
                return;
            if (!eventInfo.GetDamageInfo()->GetDamage())
                return;
            if (Unit* caster = GetCaster())
            {
                if (caster->HealthBelowPctDamaged(35, eventInfo.GetDamageInfo()->GetDamage()))
                {
                    caster->CastSpell(caster, SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH, true);
                    caster->GetSpellHistory()->ConsumeCharge(SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH);
                }
            }
        }
        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_monk_healing_elixirs_aura_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };
    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_healing_elixirs_aura_AuraScript();
    }
};

class spell_monk_ring_of_peace_dummy : public SpellScriptLoader
{
public:
    spell_monk_ring_of_peace_dummy() : SpellScriptLoader("spell_monk_ring_of_peace_dummy") {}

    class spell_monk_ring_of_peace_dummy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_ring_of_peace_dummy_AuraScript);

        void HandleDummyProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetTarget())
                {
                    caster->CastSpell(target, SPELL_MONK_RING_OF_PEACE_SILENCE, true);
                    caster->CastSpell(target, SPELL_MONK_RING_OF_PEACE_DISARM, true);
                }
            }
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_monk_ring_of_peace_dummy_AuraScript::HandleDummyProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_ring_of_peace_dummy_AuraScript();
    }
};

//3983
struct at_monk_ring_of_peace : AreaTriggerAI
{
    at_monk_ring_of_peace(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* target) override
    {
        if (at->GetCaster())
            if (at->GetCaster()->IsValidAttackTarget(target))
                target->CastSpell(target, SPELL_MONK_RING_OF_PEACE_KNOCKBACK, true);
    }
};

// Song of Chi-Ji - 198898
// AreaTriggerID - 5484
struct at_monk_song_of_chi_ji : AreaTriggerAI
{
    at_monk_song_of_chi_ji(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnUnitEnter(Unit* target) override
    {
        if (at->GetCaster())
            if (at->GetCaster()->IsValidAttackTarget(target))
                target->CastSpell(target, SPELL_MONK_SONG_OF_CHI_JI_STUN, true);
    }
};

// 115098 - Chi Wave
class spell_monk_chi_wave : public SpellScriptLoader
{
public:
    spell_monk_chi_wave() : SpellScriptLoader("spell_monk_chi_wave") {}

    class spell_monk_chi_wave_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_chi_wave_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!target)
                return;

            if (caster->IsFriendlyTo(target))
                caster->CastSpell(target, 132464, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_BASE_POINT1, GetEffectValue()));
            else if (caster->IsValidAttackTarget(target))
                caster->CastSpell(target, 132467, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_BASE_POINT1, GetEffectValue()));
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_chi_wave_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_chi_wave_SpellScript();
    }
};

// Chi Wave (healing bolt) - 132464
class spell_monk_chi_wave_healing_bolt : public SpellScriptLoader
{
public:
    spell_monk_chi_wave_healing_bolt() : SpellScriptLoader("spell_monk_chi_wave_healing_bolt") { }

    class spell_monk_chi_wave_healing_bolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_chi_wave_healing_bolt_SpellScript);

        void HandleOnHit()
        {
            if (!GetOriginalCaster())
                return;

            if (Player* _player = GetOriginalCaster()->ToPlayer())
                if (Unit* target = GetHitUnit())
                    _player->CastSpell(target, SPELL_MONK_CHI_WAVE_HEAL, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_monk_chi_wave_healing_bolt_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_chi_wave_healing_bolt_SpellScript();
    }
};

// 132464 - Chi Wave (heal missile)
class spell_monk_chi_wave_heal_missile : public SpellScriptLoader
{
public:
    spell_monk_chi_wave_heal_missile() : SpellScriptLoader("spell_monk_chi_wave_heal_missile") {}

    class spell_monk_chi_wave_heal_missile_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_chi_wave_heal_missile_AuraScript);

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!target || !caster)
                return;

            caster->CastSpell(target, 132463, true);
            // rerun target selector
            caster->CastSpell(target, 132466, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_BASE_POINT1, aurEff->GetAmount() - 1).SetTriggeringAura(aurEff));
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_monk_chi_wave_heal_missile_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_chi_wave_heal_missile_AuraScript();
    }
};

// 132467 - Chi Wave (damage missile)
class spell_monk_chi_wave_damage_missile : public SpellScriptLoader
{
public:
    spell_monk_chi_wave_damage_missile() : SpellScriptLoader("spell_monk_chi_wave_damage_missile") {}

    class spell_monk_chi_wave_damage_missile_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_chi_wave_damage_missile_AuraScript);

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!target || !caster)
                return;

            // rerun target selector
            caster->CastSpell(target, 132466, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_BASE_POINT1, aurEff->GetAmount() - 1).SetTriggeringAura(aurEff));
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_monk_chi_wave_damage_missile_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_chi_wave_damage_missile_AuraScript();
    }
};

//123986, 5300
struct at_monk_chi_burst : AreaTriggerAI
{
    at_monk_chi_burst(AreaTrigger* at) : AreaTriggerAI(at) { }

    void OnUnitEnter(Unit* target) override
    {
        if (!at->GetCaster())
            return;

        if (at->GetCaster()->IsValidAssistTarget(target))
            at->GetCaster()->CastSpell(target, SPELL_MONK_CHI_BURST_HEAL, true);

        if (at->GetCaster()->IsValidAttackTarget(target))
            at->GetCaster()->CastSpell(target, SPELL_MONK_CHI_BURST_DAMAGE, true);
    }
};

// Chi Burst heal - 130654 - POSSIBLE CRASH
class spell_monk_chi_burst_heal : public SpellScriptLoader
{
public:
    spell_monk_chi_burst_heal() : SpellScriptLoader("spell_monk_chi_burst_heal") { }

    class spell_monk_chi_burst_heal_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_chi_burst_heal_SpellScript);

        void HandleHeal(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* unit = GetHitUnit();
            if (!caster || !unit)
                return;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_MONK_CHI_BURST_HEAL, DIFFICULTY_NONE);
            if (!spellInfo)
                return;

            int32 damage = (float)caster->GetTotalAttackPowerValue(BASE_ATTACK) * 4.125f;
            damage = caster->SpellDamageBonusDone(unit, spellInfo, damage, HEAL, spellInfo->GetEffect(EFFECT_0));
            damage = unit->SpellDamageBonusTaken(caster, spellInfo, damage, HEAL);

            SetHitHeal(damage);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_chi_burst_heal_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_chi_burst_heal_SpellScript();
    }
};

//115399
class spell_monk_black_ox_brew : public SpellScriptLoader
{
public:
    spell_monk_black_ox_brew() : SpellScriptLoader("spell_monk_black_ox_brew") { }

    class spell_monk_black_ox_brew_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_black_ox_brew_SpellScript);

        void HandleHit(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->GetSpellHistory()->ResetCharges(sSpellMgr->GetSpellInfo(SPELL_MONK_PURIFYING_BREW, DIFFICULTY_NONE)->ChargeCategoryId);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_black_ox_brew_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_ENERGIZE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_black_ox_brew_SpellScript();
    }
};

//115313 - Summon Jade Serpent Statue
class spell_monk_jade_serpent_statue : public SpellScriptLoader
{
public:
    spell_monk_jade_serpent_statue() : SpellScriptLoader("spell_monk_jade_serpent_statue") { }

    class spell_monk_jade_serpent_statue_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_jade_serpent_statue_SpellScript);

        void HandleSummon()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Player* player = caster->ToPlayer();
            if (!player)
                return;

            std::list<Creature*> serpentStatueList;
            player->GetCreatureListWithEntryInGrid(serpentStatueList, MONK_NPC_JADE_SERPENT_STATUE, 500.0f);

            for (std::list<Creature*>::iterator i = serpentStatueList.begin(); i != serpentStatueList.end(); ++i)
            {
                Unit* owner = (*i)->GetOwner();

                if (owner && owner == player && (*i)->IsSummon())
                    continue;

                i = serpentStatueList.erase(i);
            }

            if ((int32)serpentStatueList.size() >= 1)
                serpentStatueList.back()->ToTempSummon()->UnSummon();
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_monk_jade_serpent_statue_SpellScript::HandleSummon);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_jade_serpent_statue_SpellScript();
    }
};

//60849
struct npc_monk_jade_serpent_statue : public ScriptedAI
{
    npc_monk_jade_serpent_statue(Creature* c) : ScriptedAI(c) { }

    void UpdateAI(uint32 diff) override
    {
        if (Unit* owner = me->GetOwner())
        {
            if (Player* player = owner->ToPlayer())
            {
                if (player->GetClass() != CLASS_MONK)
                    return;
                else
                {
                    if (player->GetPrimarySpecialization() != ChrSpecialization::MonkMistweaver && me->IsInWorld())
                        me->DespawnOrUnsummon();
                }
            }
        }
    }
};

// 227291 Niuzao's


void AddSC_monk_spell_scripts()
{
    RegisterSpellScript(spell_monk_crackling_jade_lightning);
    RegisterSpellScript(spell_monk_crackling_jade_lightning_knockback_proc_aura);
    RegisterSpellScript(spell_monk_life_cocoon);
    RegisterSpellScript(spell_monk_open_palm_strikes);
    RegisterSpellScript(spell_monk_power_strike_periodic);
    RegisterSpellScript(spell_monk_power_strike_proc);
    RegisterSpellScript(spell_monk_provoke);
    RegisterSpellScript(spell_monk_roll);
    RegisterSpellScript(spell_monk_roll_aura);
    RegisterSpellScript(spell_monk_stagger);
    RegisterSpellScript(spell_monk_stagger_damage_aura);
    RegisterSpellScript(spell_monk_stagger_debuff_aura);

    //new
    new spell_monk_zen_pilgrimage();
    new spell_monk_zen_pilgrimage_return();
    RegisterSpellScript(spell_monk_tiger_palm);
    new spell_monk_zen_flight_check();
    RegisterSpellScript(spell_monk_touch_of_death);
    RegisterSpellScript(spell_monk_touch_of_death_amplifier);
    RegisterSpellScript(spell_monk_touch_of_death_passive);
    RegisterSpellAndAuraScriptPair(spell_monk_disable, aura_monk_disable);
    new spell_monk_spear_hand_strike();
    RegisterSpellScript(spell_monk_transcendence);
    RegisterSpellScript(aura_monk_transcendence);
    RegisterSpellScript(spell_monk_transcendence_transfer);
    RegisterSpellScript(spell_monk_rising_sun_kick);
    new spell_monk_fortifying_brew();
    new spell_monk_purifying_brew();
    new spell_monk_breath_of_fire();
    new spell_monk_dampen_harm();
    RegisterSpellScript(spell_monk_clash);
    new spell_monk_healing_elixirs_aura();
    new spell_monk_ring_of_peace_dummy();
    RegisterAreaTriggerAI(at_monk_ring_of_peace);
    RegisterAreaTriggerAI(at_monk_song_of_chi_ji);
    new spell_monk_chi_wave();
    new spell_monk_chi_wave_damage_missile();
    new spell_monk_chi_wave_heal_missile();
    new spell_monk_chi_wave_healing_bolt();
    RegisterAreaTriggerAI(at_monk_chi_burst);
    new spell_monk_chi_burst_heal();
    new spell_monk_black_ox_brew();
    new spell_monk_jade_serpent_statue();
    RegisterCreatureAI(npc_monk_jade_serpent_statue);
}
