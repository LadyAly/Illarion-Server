//  illarionserver - server for the game Illarion
//  Copyright 2011 Illarion e.V.
//
//  This file is part of illarionserver.
//
//  illarionserver is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  illarionserver is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with illarionserver.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include "InitialConnection.hpp"
#include "thread_safe_vector.hpp"

#include <memory>
#include <mutex>
#include <thread>

class Player;

class PlayerManager {
public:
    static auto get() -> PlayerManager &;

    void activate();
    void stop();

    [[nodiscard]] auto threadOK() const -> bool { return threadOk; }

    [[nodiscard]] auto findPlayer(const std::string &name) const -> bool;

    static void setLoginLogout(bool val);

    using TPLAYERVECTOR = thread_safe_vector<Player *>;

    auto getLogOutPlayers() -> TPLAYERVECTOR & { return loggedOutPlayers; }
    auto getLogInPlayers() -> TPLAYERVECTOR & { return loggedInPlayers; }

private:
    static std::unique_ptr<PlayerManager> instance;

    /**
     * loop which is threaded to get new connections
     * create players, or storing data and deleting old connections
     */
    static void loginLoop(PlayerManager *pmanager);
    static void playerSaveLoop(PlayerManager *pmanager);
    static std::mutex mut;

    // Mutex der gesetzt wird beim reloaden. (Als multi read single write lock)
    static std::mutex reloadmutex;

    /**
     * true if the thread is running
     */
    volatile bool running = false;

    /**
     * if false the thread was exited correctly
     */
    volatile bool threadOk = false;

    /**
     * logged out players which connection wherent shutted down
     */
    // CInitialConnection::TVECTORPLAYER shutdownConnections;

    /**
     * player which are not on the main map anymore
     */
    TPLAYERVECTOR loggedOutPlayers;

    /**
     * players which are logged in and correctly loaded
     */
    TPLAYERVECTOR loggedInPlayers;

    /**
     * initial connection to get the new connections
     */
    std::shared_ptr<InitialConnection> incon = InitialConnection::create();

    std::unique_ptr<std::thread> login_thread = nullptr;
    std::unique_ptr<std::thread> save_thread = nullptr;
};

#endif
