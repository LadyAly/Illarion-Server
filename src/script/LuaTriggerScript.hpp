/*
 *  illarionserver - server for the game Illarion
 *  Copyright 2011 Illarion e.V.
 *
 *  This file is part of illarionserver.
 *
 *  illarionserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  illarionserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with illarionserver.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LUA_TRIGGER_SCRIPT_HPP
#define LUA_TRIGGER_SCRIPT_HPP

#include "Item.hpp"
#include "LuaScript.hpp"

class World;

class LuaTriggerScript : public LuaScript {
public:
    LuaTriggerScript();
    LuaTriggerScript(const std::string &filename, const position &pos);
    ~LuaTriggerScript() override = default;
    LuaTriggerScript(const LuaTriggerScript &) = delete;
    auto operator=(const LuaTriggerScript &) -> LuaTriggerScript & = delete;
    LuaTriggerScript(LuaTriggerScript &&) = default;
    auto operator=(LuaTriggerScript &&) -> LuaTriggerScript & = default;

    void CharacterOnField(Character *character);
    void MoveToField(Character *character);
    void MoveFromField(Character *character);
    void PutItemOnField(const ScriptItem &item, Character *character);
    void TakeItemFromField(const ScriptItem &item, Character *character);
    void ItemRotsOnField(const ScriptItem &oldItem, const ScriptItem &newItem);

private:
    position _pos{};
    void init_functions() const;
};

#endif
