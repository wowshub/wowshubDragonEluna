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

#include "Containers.h"
#include "DB2Stores.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include <MovementPackets.h>
#include <G3D/g3dmath.h>
#include "MotionMaster.h"
#include "ScriptedCreature.h"

enum ToySpells
{
    SPELL_NECRONOM_I_NOM_JUMP               = 340184,
    SPELL_NECRONOM_I_NOM_MORPH              = 340118,
    SPELL_NECRONOM_I_NOM_SCALE              = 340161,
    SPELL_NECRONOM_I_NOM_FILTER             = 341640,
    SPELL_BOWL_OF_GLOWING_PUFFERFISH_TAKE   = 291106,

};

// itemid - 182732
// spellid - 340110
class spell_necronom_i_nom : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_NECRONOM_I_NOM_JUMP,
                SPELL_NECRONOM_I_NOM_MORPH,
                SPELL_NECRONOM_I_NOM_SCALE,
                SPELL_NECRONOM_I_NOM_FILTER
            });
    }

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        uint32 RandomEffects = urand(0, 3);

        switch (RandomEffects)
        {
        case 0:
            //jump
            caster->CastSpell(caster, SPELL_NECRONOM_I_NOM_JUMP, true);
            break;
        case 1:
            //morph
            caster->CastSpell(caster, SPELL_NECRONOM_I_NOM_MORPH, true);
            break;
        case 2:
            //scale
            caster->CastSpell(caster, SPELL_NECRONOM_I_NOM_SCALE, true);
            break;
        case 3:
            //filter
            caster->CastSpell(caster, SPELL_NECRONOM_I_NOM_FILTER, true);
            break;
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_necronom_i_nom::HandleOnCast);
    }
};

enum ItemIds
{
    YELLOW = 163521,
    PURPLE = 163518,
    GREEN = 163172,
    RED = 163517,
    ORANGE = 163520,
    BLUE = 163516,
    MAX_ITEM_ID
};

// itemid - 166704
// spellid - 291106
class spell_bowl_of_glowing_pufferfish : public SpellScript
{

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        assert(caster);

        if (Player* player = caster->ToPlayer())
        {
            uint32 randomIndex = urand(0, MAX_ITEM_ID - 1);

            uint32 itemId = 0;
            switch (randomIndex)
            {
            case 0:
                itemId = YELLOW;
                break;
            case 1:
                itemId = PURPLE;
                break;
            case 2:
                itemId = GREEN;
                break;
            case 3:
                itemId = RED;
                break;
            case 4:
                itemId = ORANGE;
                break;
            case 5:
                itemId = BLUE;
                break;
            }
            player->AddItem(itemId, 1);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_bowl_of_glowing_pufferfish::HandleOnCast);
    }
};

class item_darkmoon_faire_fireworks2 : public ItemScript
{
public:
    item_darkmoon_faire_fireworks2() : ItemScript("item_darkmoon_faire_fireworks2") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
    {
        player->CastSpell(player, 103740, false);

        return true;
    }
};

void AddSC_toy_spell_scripts()
{
    RegisterSpellScript(spell_necronom_i_nom);
    RegisterSpellScript(spell_bowl_of_glowing_pufferfish);
    new item_darkmoon_faire_fireworks2();
}
