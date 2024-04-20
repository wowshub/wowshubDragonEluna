/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_UTIL_H
#define _ELUNA_UTIL_H

#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <memory>
#include "Common.h"
#include "SharedDefines.h"
#include "ObjectGuid.h"
#include "QueryResult.h"
#include "Log.h"

#define USING_BOOST
#define ELUNA_WINDOWS

typedef QueryResult ElunaQuery;
#define GET_GUID                GetGUID
#define HIGHGUID_PLAYER         HighGuid::Player
#define HIGHGUID_UNIT           HighGuid::Creature
#define HIGHGUID_ITEM           HighGuid::Item
#define HIGHGUID_GAMEOBJECT     HighGuid::GameObject
#define HIGHGUID_PET            HighGuid::Pet
#define HIGHGUID_TRANSPORT      HighGuid::Transport
#define HIGHGUID_VEHICLE        HighGuid::Vehicle
#define HIGHGUID_DYNAMICOBJECT  HighGuid::DynamicObject
#define HIGHGUID_CORPSE         HighGuid::Corpse
#define HIGHGUID_MO_TRANSPORT   HighGuid::Transport
#define HIGHGUID_GROUP          HighGuid::Party

#define ELUNA_LOG_INFO(message__, ...)     TC_LOG_INFO("eluna", message__, ##__VA_ARGS__);
#define ELUNA_LOG_ERROR(message__, ...)    TC_LOG_ERROR("eluna", message__, ## __VA_ARGS__);
#define ELUNA_LOG_DEBUG(message__, ...)    TC_LOG_DEBUG("eluna", message__, ##__VA_ARGS__);

#define MAKE_NEW_GUID(l, e, h)  ObjectGuid(h, e, l)

#define GUID_ENPART(guid)       ObjectGuid(guid).GetEntry()

#define GUID_LOPART(guid)       ObjectGuid(guid).GetCounter()

#define GUID_HIPART(guid)       ObjectGuid(guid).GetHigh()


typedef std::vector<uint8> BytecodeBuffer;

class Unit;
class WorldObject;
struct FactionTemplateEntry;

namespace ElunaUtil
{
    uint32 GetCurrTime();

    uint32 GetTimeDiff(uint32 oldMSTime);

    class ObjectGUIDCheck
    {
    public:
        ObjectGUIDCheck(ObjectGuid guid);
        bool operator()(WorldObject* object);

        ObjectGuid _guid;
    };

    // Binary predicate to sort WorldObjects based on the distance to a reference WorldObject
    class ObjectDistanceOrderPred
    {
    public:
        ObjectDistanceOrderPred(WorldObject const* pRefObj, bool ascending = true);
        bool operator()(WorldObject const* pLeft, WorldObject const* pRight) const;

        WorldObject const* m_refObj;
        const bool m_ascending;
    };

    // Doesn't get self
    class WorldObjectInRangeCheck
    {
    public:
        WorldObjectInRangeCheck(bool nearest, WorldObject const* obj, float range,
            uint16 typeMask = 0, uint32 entry = 0, uint32 hostile = 0, uint32 dead = 0);
        WorldObject const& GetFocusObject() const;
        bool operator()(WorldObject* u);

        WorldObject const* const i_obj;
        Unit const* i_obj_unit;
        FactionTemplateEntry const* i_obj_fact;
        uint32 const i_hostile; // 0 both, 1 hostile, 2 friendly
        uint32 const i_entry;
        float i_range;
        uint16 const i_typeMask;
        uint32 const i_dead; // 0 both, 1 alive, 2 dead
        bool const i_nearest;
    };

    /*
     * Encodes `data` in Base-64 and store the result in `output`.
     */
    void EncodeData(const unsigned char* data, size_t input_length, std::string& output);

    /*
     * Decodes `data` from Base-64 and returns a pointer to the result, or `NULL` on error.
     *
     * The returned result buffer must be `delete[]`ed by the caller.
     */
    unsigned char* DecodeData(const char* data, size_t *output_length);
};

#endif
