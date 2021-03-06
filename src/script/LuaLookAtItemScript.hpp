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

#ifndef LUA_LOOK_AT_ITEM_SCRIPT_HPP
#define LUA_LOOK_AT_ITEM_SCRIPT_HPP

#include "ItemLookAt.hpp"
#include "LuaScript.hpp"

class Character;
class ScriptItem;

class LuaLookAtItemScript : public LuaScript {
public:
    explicit LuaLookAtItemScript(const std::string &filename);
    ~LuaLookAtItemScript() override = default;
    LuaLookAtItemScript(const LuaLookAtItemScript &) = delete;
    auto operator=(const LuaLookAtItemScript &) -> LuaLookAtItemScript & = delete;
    LuaLookAtItemScript(LuaLookAtItemScript &&) = default;
    auto operator=(LuaLookAtItemScript &&) -> LuaLookAtItemScript & = default;

    auto lookAtItem(Character *character, const ScriptItem &item) -> ItemLookAt;
};

#endif
