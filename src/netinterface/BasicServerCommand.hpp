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

#ifndef CBASICSERVERCOMMAND_HPP
#define CBASICSERVERCOMMAND_HPP

#include "netinterface/BasicCommand.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <types.hpp>
#include <vector>

class BasicServerCommand;
using ServerCommandPointer = std::shared_ptr<BasicServerCommand>;

/**
 *@ingroup Netinterface
 *Class which represents a basic command that is sent from the
 *server to the client. Each constructor prepares a 6 byte header as follows:
 *- Byte 0: Unique command id
 *- Byte 1: Byte 1 xor 0xFF (complement)
 *- Byte 2+3: Length of the following data segment
 *- Byte 4+5: Checksum consisting of the sum of all data bytes mod 0xFFFF
 *
 *Once all data has been added to the command, the header needs to be finalized with addHeader()
 */
class BasicServerCommand : public BasicCommand {
public:
    /**
     * Constructor which creates the server command.
     * In this case the internal data buffer is 1000 bytes large.
     * @param defByte The id of this command
     */
    explicit BasicServerCommand(unsigned char defByte);

    /**
     * Constructor which creates the server command.
     * @param defByte The id of this command
     * @param bsize The initial buffer size of this command
     */
    BasicServerCommand(unsigned char defByte, uint16_t bsize);

    auto operator=(const BasicServerCommand &) -> BasicServerCommand & = delete;
    BasicServerCommand(const BasicServerCommand &) = delete;
    BasicServerCommand(BasicServerCommand &&) = default;
    auto operator=(BasicServerCommand &&) -> BasicServerCommand & = default;
    ~BasicServerCommand() = default;

    /**
     * Function which returns the data buffer of the command.
     * @return The data buffer of the command
     */
    [[nodiscard]] auto cmdData() const -> const std::vector<char> &;

    /**
     * Returns the length of the command in bytes
     * @return The length of the command
     */
    [[nodiscard]] auto getLength() const -> int;

    void addStringToBuffer(const std::string &data);
    void addIntToBuffer(int data);
    void addShortIntToBuffer(short int data);
    void addUnsignedCharToBuffer(unsigned char data);
    void addColourToBuffer(const Colour &c);

    /**
     * Adds all the header information to the top of the buffer
     * which depends on the commands data, like length and checksum
     */
    void addHeader();
    void initHeader();

private:
    static constexpr uint16_t headerSize = 6;
    static constexpr uint16_t lengthPosition = 2;
    static constexpr uint16_t crcPosition = 4;
    static constexpr uint16_t defaultBufferSize = 1000;
    uint16_t baseBufferSize = defaultBufferSize;

    std::vector<char> buffer;
    uint32_t checkSum = 0;

    uint16_t bufferPos = 0;     // stores the current buffer position and the size of the used buffer
    uint16_t bufferSizeMod = 1; // bufferSizeMod * baseBufferSize = current buffer size

    // if there is a buffer overflow this function doubles buffer size
    void resizeBuffer();
};

#endif
