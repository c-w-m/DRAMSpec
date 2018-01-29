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



#include "TechnologyValues.h"

void
TechnologyValues::technologyValuesInitialize()
{
    techFileName = "";
    archFileName = "";

    technologyNode = 0*drs::nanometer;
    vpp = 0*si::volt;
    vdd = 0*si::volt;
    wireResistance = 0*drs::ohm_per_millimeter;
    wireCapacitance = 0*drs::femtofarad_per_millimeter;
    capacitancePerCell = 0*drs::femtofarads;
    resistancePerCell = 0*drs::kiloohm;
    cellWidth = 0*drs::micrometer;
    cellHeight = 0*drs::micrometer;
    capacitancePerBLCell = 0*drs::attofarads;
    resistancePerBLCell = 0*drs::ohm;
    capacitancePerWLCell = 0*drs::attofarads;
    resistancePerWLCell = 0*drs::ohm;
    BLSenseAmpHeight = 0*drs::micrometer;
    LWLDriverWidth = 0*drs::micrometer;
    LWLDriverResistance = 0*drs::ohm;
    rowDecoderWidth = 0*drs::micrometers;
    GWLDriverResistance = 0*si::ohm;
    Issa = 0*drs::microampere_per_bit;
    WRDriverResistance = 0*drs::ohm;
    colDecoderHeight = 0*drs::micrometers;
    CSLDriverResistance = 0*si::ohms;
    CSLLoadCapacitance = 0*drs::femtofarads;
    GDLDriverResistance = 0*si::ohms;
    DQDriverHeight = 0*drs::micrometers;
    DQtoTSVWireLength = 0*drs::micrometers;
    DQDriverResistance = 0*si::ohms;
    idd2nFreqSlope = 0*drs::milliamperes_per_megahertz_clock;
    idd2nTempAlpha = 0*drs::milliamperes;
    idd2nTempBeta = 0*drs::eergeds;
    idd2nRefTemp = 0*bu::celsius::degrees;
    idd2nOffset = 0*drs::milliamperes;
    IddOcdRcvSlope = 0*drs::microamperes_per_megahertz_clock;
    TSVHeight = 0*drs::micrometers;
    additionalLatencyTrl = 0*drs::clocks;
    driverEnableDelay = 0*drs::nanoseconds;
    inOutSSADelay = 0*drs::nanoseconds;
    cmdDecoderDelay = 0*drs::nanoseconds;
    IODelay = 0*drs::nanoseconds;
    SSAPrechargeDelay = 0*drs::nanoseconds;
    tWRMargin = 0*drs::nanoseconds;
    equalizerDelay = 0*drs::nanoseconds;

    dramType = "";
    is3D = false;
    isDLL = false;
    channelSize = 0*drs::gibibit;
    nBanks = 0;
    nHorizontalBanks = 0;
    nVerticalBanks = 0;
    cellsPerLWL = 0;
    cellsPerLWLRedundancy = 0;
    cellsPerLBL = 0;
    cellsPerLBLRedundancy = 0;
    interface = 0*drs::bit;
    prefetch = 0;
    dramFreq = 0*drs::megahertz_clock;
    dramCoreFreq = 0*drs::megahertz_clock;
    nTilesPerBank = 0;
    pageStorage = 0*drs::kibibyte;
    pageSpanningFactor = 0;
    BLArchitecture = "";
    subArrayToPageFactor = 0;
    retentionTime = 0*drs::millisecond;
    trefIBase = 0*drs::microsecond;
    refreshMode = 0;
    temperature = 0*bu::celsius::degrees;

    warning = "";
}

double
TechnologyValues::getJSONNumber(const rapidjson::Document& jsonDoc,
                                const char* memberName)
{
    if ( jsonDoc.HasMember( memberName ) == false )
    {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Could not find member \"");
        exceptionMsgThrown.append(memberName);
        exceptionMsgThrown.append("\" in JSON document ");
        exceptionMsgThrown.append(techFileName);
        exceptionMsgThrown.append("!\n");
        throw exceptionMsgThrown;
    }
    if ( jsonDoc[ memberName ].IsNumber() == false )
    {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Member \"");
        exceptionMsgThrown.append(memberName);
        exceptionMsgThrown.append("\" in JSON document ");
        exceptionMsgThrown.append(techFileName);
        exceptionMsgThrown.append(" is expected to be a number!\n");
        throw exceptionMsgThrown;
    }

    return jsonDoc[ memberName ].GetDouble();
}

string
TechnologyValues::getJSONString(const rapidjson::Document& jsonDoc,
                                const char* memberName)
{
    if ( jsonDoc.HasMember( memberName ) == false )
    {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Could not find member \"");
        exceptionMsgThrown.append(memberName);
        exceptionMsgThrown.append("\" in JSON document ");
        exceptionMsgThrown.append(techFileName);
        exceptionMsgThrown.append("!\n");
        throw exceptionMsgThrown;
    }
    if ( jsonDoc[ memberName ].IsString() == false )
    {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Member \"");
        exceptionMsgThrown.append(memberName);
        exceptionMsgThrown.append("\" in JSON document ");
        exceptionMsgThrown.append(techFileName);
        exceptionMsgThrown.append(" is expected to be a string!\n");
        throw exceptionMsgThrown;
    }

    return jsonDoc[ memberName ].GetString();
}

void 
TechnologyValues::readjson(const string& t,const string& p)
{
    techFileName = t;
    archFileName = p;

    // Try to open technology file given by the user
    ifstream techFile(techFileName);
    // Test if file was (and still is) opened
    if ( techFile.is_open() == false ) {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Could not open technology file: ");
        exceptionMsgThrown.append(techFileName);
        exceptionMsgThrown.append("!\n");
        throw exceptionMsgThrown;
    }

    // Find length of the file
    int techFileLength;
    techFile.seekg(0, ios::end);
    techFileLength = techFile.tellg();
    techFile.seekg(0, ios::beg);

    // Create an internal copy as a C-style string
    char* techFileText = new char[techFileLength + 1];
    techFile.read(techFileText, techFileLength);
    techFileText[ techFileLength ] = '\0';

    // Close the file
    techFile.close();

    // Parse the file as a JSON Document
    rapidjson::Document techDocument;
    techDocument.Parse(techFileText);
    if ( techDocument.HasParseError() ) {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Could not parse ");
        exceptionMsgThrown.append(techFileName);
        exceptionMsgThrown.append(" as a JSON document.\n");
        throw exceptionMsgThrown;
    }

    try {
        //Technology node in nm
        technologyNode = getJSONNumber(techDocument, "TechnologyNode[nm]")
                         * drs::nanometer;

        //voltage vpp
        vpp = getJSONNumber(techDocument, "Vpp[V]")
              * si::volt;
        //voltage vdd
        vdd = getJSONNumber(techDocument, "Vdd[V]")
              * si::volt;

        //wire resistance in ohm/mm
        wireResistance = getJSONNumber(techDocument, "WireResistance[Ohm/mm]")
                         * drs::ohm_per_millimeter;

        //wire capa in ff/mm
        wireCapacitance = getJSONNumber(techDocument, "WireCapacitance[fF/mm]")
                          * drs::femtofarad_per_millimeter;

        //cell capa
        capacitancePerCell = getJSONNumber(techDocument, "CellCapacitance[fF]")
                             * drs::femtofarads;

        //cell resistance
        resistancePerCell = getJSONNumber(techDocument, "CellResistance[KOhm]")
                            * drs::kiloohm;

        //cell width
        cellWidth = getJSONNumber(techDocument, "CellWidth[um]")
                    * drs::micrometers;

        //cell height
        cellHeight = getJSONNumber(techDocument, "CellHeight[um]")
                     * drs::micrometers;

        //Bitline per cell capa
        capacitancePerBLCell = getJSONNumber(techDocument, "BitlineCapacitancePerCell[aF]")
                               * drs::attofarads;

        //Bitline per cell resistance
        resistancePerBLCell = getJSONNumber(techDocument, "BitlineResistancePerCell[Ohm]")
                              * drs::ohm;

        //Wordline per cell capa
        capacitancePerWLCell = getJSONNumber(techDocument, "WordlineCapacitancePerCell[aF]")
                               * drs::attofarads;

        //Wordline per cell resistance
        resistancePerWLCell = getJSONNumber(techDocument, "WordlineResistancePerCell[Ohm]")
                              * drs::ohm;

        //Sense amp height
        BLSenseAmpHeight = getJSONNumber(techDocument, "PrimarySenseAmpHeight[um]")
                           * drs::micrometer;

        //Local wordline driver width
        LWLDriverWidth = getJSONNumber(techDocument, "LocalWordlineDriverWitdh[um]")
                        * drs::micrometer;

        //Local wordline driver resistance in ohm
        LWLDriverResistance = getJSONNumber(techDocument, "LocalWordlineDriverResistance[Ohm]")
                              * drs::ohm;

        //Row decoder (between tiles) width
        rowDecoderWidth = getJSONNumber(techDocument, "RowDecoderWidth[um]")
                          * drs::micrometer;

        //Global wordline driver resistance in ohm
        GWLDriverResistance = getJSONNumber(techDocument, "GlobalWordlineDriverResistance[Ohm]")
                              * si::ohm;

        //current of SSA in milliamperes
        Issa = getJSONNumber(techDocument, "SecondarySenseAmpCurrent[uA]")
               * drs::microampere_per_bit;

        // Write Restore Driver resistance
        WRDriverResistance = getJSONNumber(techDocument, "WriteDriverResistance[Ohm]")
                       * drs::ohm;

        //Column decoder (between tiles) height
        colDecoderHeight = getJSONNumber(techDocument, "ColumnDecoderHeight[um]")
                           * drs::micrometer;

        //CSL driver resistance in ohm
        CSLDriverResistance = getJSONNumber(techDocument, "CSLDriverResistance[Ohm]")
                              * si::ohm;

        //CSL load capacitance
        CSLLoadCapacitance = getJSONNumber(techDocument, "CSLLoadCapacitance[fF]")
                         * drs::femtofarads;

        //GDL driver resistance in ohm
        GDLDriverResistance = getJSONNumber(techDocument, "GlobalDataLineDriverResistance[Ohm]")
                              * si::ohm;

        //DQ driver (between banks) height
        DQDriverHeight = getJSONNumber(techDocument, "DQDriverHeight[um]")
                         * drs::micrometer;

        //Length of the wire going from the DQ main wiring to the TSV
        DQtoTSVWireLength = getJSONNumber(techDocument, "DQtoTSVWireLength[um]")
                             * drs::micrometers;

        //DQ driver resistance in ohm
        DQDriverResistance = getJSONNumber(techDocument, "DQDriverResistance[Ohm]")
                             * si::ohm;

        //Background current slope with frequency
        idd2nFreqSlope = getJSONNumber(techDocument, "IDD2NFreqSlope[mA/MHz]")
                                 * drs::milliamperes_per_megahertz_clock;

        //Background current alpha coefficient (models temperature dependency)
        idd2nTempAlpha = getJSONNumber(techDocument, "IDD2NTempAlpha[mA]")
                                 * drs::milliamperes;

        //Background current beta coefficient (models temperature dependency)
        idd2nTempBeta = getJSONNumber(techDocument, "IDD2NTempBeta[C^-1]")
                                 * drs::eergeds;

        //Background current reference temperature (models temperature dependency)
        idd2nRefTemp = getJSONNumber(techDocument, "IDD2NRefTemp[C]")
                                 * bu::celsius::degrees;

        //Background current offset (current at ref temp and 0 MHz)
        idd2nOffset = getJSONNumber(techDocument, "IDD2NOffset[mA]")
                                  * drs::milliamperes;

        //Current slope per IO pin (Off Channel Driver)
        IddOcdRcvSlope = getJSONNumber(techDocument, "OCDCurrentSlope[uA/MHz]")
                                    * drs::microamperes_per_megahertz_clock;


        //Height of the TSV area needed for each bank I/O
        TSVHeight = getJSONNumber(techDocument, "TSVHeight[um]")
                    * drs::micrometer;

        //Additional latency required for trl calculation
        additionalLatencyTrl = getJSONNumber(techDocument, "AdditionalTRLLatency[cc]")
                         * drs::clock;

        //Driver enabling delay
        driverEnableDelay = getJSONNumber(techDocument, "DriverEnableDelay[ns]")
                         * drs::nanoseconds;

        //Signal delay from input to output of SSA
        inOutSSADelay = getJSONNumber(techDocument, "InOutSSADelay[ns]")
                         * drs::nanoseconds;

        //Command decoder delay - clock wave pipeline delay
        cmdDecoderDelay = getJSONNumber(techDocument, "CommandDecoderDelay[ns]")
                         * drs::nanoseconds;

        //I/O interface delay
        IODelay = getJSONNumber(techDocument, "IODelay[ns]")
                         * drs::nanoseconds;

        //Delay for SSA precharging
        SSAPrechargeDelay = getJSONNumber(techDocument, "SSAPrechargeDelay[ns]")
                         * drs::nanoseconds;

        // Security margin for Write Recovery
        tWRMargin = getJSONNumber(techDocument, "tWRMargin[ns]")
                         * drs::nanoseconds;

        //Equalizer circuit enabling delay
        equalizerDelay = getJSONNumber(techDocument, "EqualizerDelay[ns]")
                         * drs::nanoseconds;

    } catch(string exceptionMsgThrown) {
        throw exceptionMsgThrown;
    }




    // Try to open architecture file given by the user
    ifstream archFile(archFileName);
    // Test if file was (and still is) opened
    if ( archFile.is_open() == false ) {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Could not open architecture file: ");
        exceptionMsgThrown.append(archFileName);
        exceptionMsgThrown.append("!\n");
        throw exceptionMsgThrown;
    }

    // Find length of the file
    int archFileLength;
    archFile.seekg(0, ios::end);
    archFileLength = archFile.tellg();
    archFile.seekg(0, ios::beg);

    // Create an internal copy as a C-style string
    char* archFileText = new char[archFileLength + 1];
    archFile.read(archFileText, archFileLength);
    archFileText[ archFileLength ] = '\0';

    // Close the file
    archFile.close();

    // Parse the file as a JSON Document
    rapidjson::Document archDocument;
    archDocument.Parse(archFileText);
    if ( archDocument.HasParseError() ) {
        string exceptionMsgThrown;
        exceptionMsgThrown.append("[ERROR] ");
        exceptionMsgThrown.append("Could not parse ");
        exceptionMsgThrown.append(archFileName);
        exceptionMsgThrown.append(" as a JSON document.\n");
        throw exceptionMsgThrown;
    }

    try {
        //DRAM Type
        dramType = getJSONString(archDocument, "DRAMType[-]");

        //3D ON/OFF Feature
        //set 3D on for HMC/WideIO
        is3D = ( getJSONString(archDocument, "3D[-]") == "ON" );

        // DLL ON/OFF Feature
        isDLL = ( getJSONString(archDocument, "DLL[-]") == "ON" );

        //size of DRAM Channel
        channelSize = getJSONNumber(archDocument, "ChannelSize[Gb]")
                      * drs::gibibits;

        //# of banks
        nBanks = getJSONNumber(archDocument, "NumberOfBanksPerChannel[]");

        //# of banks in the row direction
        nHorizontalBanks = getJSONNumber(archDocument, "NumberOfHorizontalBanksPerChannel[]");

        //# of banks in the column direction
        nVerticalBanks = getJSONNumber(archDocument, "NumberOfVerticalBanksPerChannel[]");

        //cells per subarray row
        cellsPerLWL = getJSONNumber(archDocument, "CellsPerSubarrayRow[]");

        //cells per subarray row redundancy
        cellsPerLWLRedundancy = getJSONNumber(archDocument, "RedundantCellsPerSubarrayRow[]");

        //cells per subarray column
        cellsPerLBL = getJSONNumber(archDocument, "CellsPerSubarrayColumn[]");

        //cells per subarray column redundancy
        cellsPerLBLRedundancy = getJSONNumber(archDocument, "RedundantCellsPerSubarrayColumn[]");

        //Interface (channel-wise)
        interface = getJSONNumber(archDocument, "Interface[bit]")
                    * drs::bits;

        //Number of prefetched words (interface wide) per CAS
        prefetch = getJSONNumber(archDocument, "Prefetch[]");

        //DRAM Frequency
        dramFreq = getJSONNumber(archDocument, "Frequency[MHz]")
                         * drs::megahertz_clock;

        //DRAM Core Frequency
        dramCoreFreq = getJSONNumber(archDocument, "CoreFrequency[MHz]")
                         * drs::megahertz_clock;

        // Number of tiles per bank
        nTilesPerBank = getJSONNumber(archDocument, "TilesPerBank[]");

        // Page size - number of local sense amp. activated in a row access
        pageStorage = getJSONNumber(archDocument, "PageSize[KB]")
                         * drs::kibibyte;

        // Spanning factor of pages across tiles
        pageSpanningFactor = getJSONNumber(archDocument, "PageSpanningFactor[]");

        // Subarray to page factor (inverse percentage bitlines that are sensed per row access)
        subArrayToPageFactor = getJSONNumber(archDocument, "SubarrayToPageFactor[]");

        // DRAM Bitline Architecture: OPEN or FOLDED bitline
        BLArchitecture = getJSONString(archDocument, "BitlineArchitecture[-]");

        // Retention time
        retentionTime = getJSONNumber(archDocument, "RetentionTime[ms]")
                         * drs::millisecond;

        // Normal mode and temp. average interval between AR commands
        trefIBase = getJSONNumber(archDocument, "tREFI(base)[us]")
                         * drs::microsecond;

        // Refresh mode according to JEDEC (eg., JESD79-4B)
        refreshMode = getJSONNumber(archDocument, "RefreshMode[]");

        // Temperature used for timings and currents calculations
        temperature = getJSONNumber(archDocument, "Temperature[C]")
                         * bu::celsius::degrees;

    } catch(string exceptionMsgThrown) {
        throw exceptionMsgThrown;
    }

}
