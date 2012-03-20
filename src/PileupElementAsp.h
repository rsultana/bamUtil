/*
 *  Copyright (C) 2012  Regents of the University of Michigan
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//////////////////////////////////////////////////////////////////////////
// This file contains the processing for the executable option "stats"
// which generates some statistics for SAM/BAM files.

#ifndef __PILEUP_ELEMENT_ASP_H__
#define __PILEUP_ELEMENT_ASP_H__

#include "PileupElement.h"
#include "AspRecord.h"


class PileupElementAsp : public PileupElement
{
public:

    /// Set & open the output file.
    static void setOutputFile(const char* outputFile);

    /// Close the output file if it is open.
    static void closeOutputFile();

    /// Set the gap size threshold such that gaps smaller than this size are
    /// filled with empty records and gaps this size or larger are writen
    /// as new chromosome/position. 
    static void setGapSize(int gapSize);

    /// Set whether or not a deletion should be ignored.  Ignored deletions
    /// do not show up in the output. 
    /// If the deletion is not ignored (default), false, the deletion will be
    /// represented as a 'D' in the AspRecord for the base and 0 for the
    /// quality.
    static void setIgnoreDeletion(bool ignoreDeletion);

    static int getNumPosRecs() { return(ourNumPosRecs); }
    static int getNumEmptyRecs() { return(ourNumEmptyRecs); }
    static int getNumRefOnlyRecs() { return(ourNumRefOnlyRecs); }
    static int getNumDetailedRecs() { return(ourNumDetailedRecs); }

    // Print the output format, make sure you call after setSumStats
    // if you want summary statistics or your output file
    // will have the wrong header..
    static void printHeader();
    
    PileupElementAsp();

    virtual ~PileupElementAsp();

    // Add an entry to this pileup element.  
    virtual void addEntry(SamRecord& record);

    // Perform the analysis associated with this class.
    virtual void analyze();

    // Resets the entry, setting the new position associated with this element.
    virtual void reset(int32_t refPosition);

private:
    PileupElementAsp(const PileupElement& q);

    void initVars();

    static IFILE ourOutputFile;
    static int ourGapSize;
    static bool ourIgnoreDeletion;
    static bool ourReportOverMax;

    static int ourPrevPos;
    static int ourPrevChromID;

    static int ourNumPosRecs;
    static int ourNumEmptyRecs;
    static int ourNumRefOnlyRecs;
    static int ourNumDetailedRecs;

    String myOutputString;

    int myChromID;
    char myRefBase;
    bool myAllRef;
    int myOverMax;

    AspRecord myAspRecord;
};

#endif
