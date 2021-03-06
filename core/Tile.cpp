/*
 * Copyright (c) 2017, University of Kaiserslautern
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Omar Naji,
 *          Matthias Jung,
 *          Christian Weis,
 *          Kamal Haddad,
 *          Andre Lucas Chinazzo
 */



#include "Tile.h"

void
Tile::tileInitialize()
{
    tileStorage = 0*drs::bits;
    tileWidth = 0*drs::micrometers;
    tileHeight = 0*drs::micrometers;

    nSubArraysPerArrayBlock = 0;
    nArrayBlocksPerTile = 0;

}

void
Tile::tileStorageCalc()
{
    bu::quantity<drs::bit_unit> bankStorage(channelSize/nBanks);

    tileStorage = bankStorage/nTilesPerBank;

}

void
Tile::checkTileDataConsistency()
{
    // Check input consistency with respect to tilesPerBank & pageSpanningFactor
    if ( nTilesPerBank == 1.0 ) {
        if (   pageSpanningFactor != 1.0 )
        {
            std::string exceptionMsgThrown("[ERROR] ");
            exceptionMsgThrown.append("If architecture has ");
            exceptionMsgThrown.append("1 tile per bank, ");
            exceptionMsgThrown.append("the page spanning factor ");
            exceptionMsgThrown.append("across the tile must be 1.");
            throw exceptionMsgThrown;
        }
    }

    else if ( nTilesPerBank == 2.0 ) {
        if (   pageSpanningFactor != 1.0
               && pageSpanningFactor != 0.5
               )
        {
            std::string exceptionMsgThrown("[ERROR] ");
            exceptionMsgThrown.append("If architecture has ");
            exceptionMsgThrown.append("2 tile per bank, ");
            exceptionMsgThrown.append("the page spanning factor ");
            exceptionMsgThrown.append("across the tile must be 1 or 0.5.");
            throw exceptionMsgThrown;
        }
    }

    else if ( nTilesPerBank == 4.0 ) {
        if (   pageSpanningFactor != 1
            && pageSpanningFactor != 0.5
            && pageSpanningFactor != 0.25 )
        {
            std::string exceptionMsgThrown("[ERROR] ");
            exceptionMsgThrown.append("If architecture has ");
            exceptionMsgThrown.append("4 tile per bank, ");
            exceptionMsgThrown.append("the page spanning factor ");
            exceptionMsgThrown.append("across the tile must be 1, 0.5 or 0.25.");
            throw exceptionMsgThrown;
        }
    }

    else {
        std::string exceptionMsgThrown("[ERROR] ");
        exceptionMsgThrown.append("Architecture must have ");
        exceptionMsgThrown.append("1, 2 or 4 tile per bank.");
        throw exceptionMsgThrown;
    }
}

void
Tile::tileLenghtCalc()
{
    nSubArraysPerArrayBlock = ceil(
                                    SCALE_QUANTITY(pageStorage, drs::bit_unit)
                                    * pageSpanningFactor
                                    * subArrayToPageFactor
                                    / subArrayRowStorage
                                  );

    tileWidth = nSubArraysPerArrayBlock * subArrayWidth
                + 1.0 * LWLDriverWidth;


    if ( BLArchitecture == "OPEN" ) {
        nArrayBlocksPerTile = ceil(tileStorage
                                   / subArrayStorage
                                   / nSubArraysPerArrayBlock
                                   + 1  // Dummy row of subarrays
                                        //  for BL capacitance matching
                                  );

        tileHeight = nArrayBlocksPerTile * subArrayHeight
                     - 1.0 * BLSenseAmpHeight
                     + 1.0 * colDecoderHeight;

    }

    else if ( BLArchitecture == "FOLDED" ) {
        nArrayBlocksPerTile = ceil(tileStorage
                                   / subArrayStorage
                                   / nSubArraysPerArrayBlock
                                  );

        tileHeight = nArrayBlocksPerTile * subArrayHeight
                     + 1.0 * BLSenseAmpHeight
                     + 1.0 * colDecoderHeight;
    }

    else {
        std::string exceptionMsgThrown("[ERROR] ");
        exceptionMsgThrown.append("Bitline architecture must be ");
        exceptionMsgThrown.append("either \'OPEN\' or \'FOLDED\'.");
        throw exceptionMsgThrown;
    }

}

void
Tile::tileCompute()
{
    tileStorageCalc();

    try {
        checkTileDataConsistency();
        tileLenghtCalc();
    }catch (std::string exceptionMsgThrown){
        throw exceptionMsgThrown;
    }

}

