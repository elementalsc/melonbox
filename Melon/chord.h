#ifndef CHORD_H
#define CHORD_H

#include "Modes.h"

enum Note
{
    C   = 0,
    Cs  = 1,
    Db  = 1,
    D   = 2,
    Ds  = 3,
    Eb  = 3,
    E   = 4,
    F   = 5,
    Fs  = 6,
    Gb  = 6,
    G   = 7,
    Gs  = 8,
    Ab  = 8,
    A   = 9,
    As  = 10,
    Bb  = 10,
    B   = 11
};

enum Triad
{
    NoDefinedTriad		= 0,
    MajorTriad,
    MinorTriad,
    DiminishedTriad,
    AugmentedTriad
};

static Triad mNaturalTriads[7] = // Natural triads
{
    Triad::MajorTriad,
    Triad::MinorTriad,
    Triad::MinorTriad,
    Triad::MajorTriad,
    Triad::MajorTriad,
    Triad::MinorTriad,
    Triad::DiminishedTriad
};

static Triad mHarmonicTriads[7] = // Harmonic triads
{
    Triad::AugmentedTriad,
    Triad::MinorTriad,
    Triad::MajorTriad,
    Triad::MajorTriad,
    Triad::DiminishedTriad,
    Triad::MinorTriad,
    Triad::DiminishedTriad
};
enum Seventh
{
    NoSeventh			= 0,
    MajorSeventh,
    MinorSeventh,
    DiminishedSeventh
};

enum AddedDegree
{
    NoAddedDegree		= 0,
    Add6				= 6,
    Add9				= 9,
    Add11				= 11,
    Add13				= 13
};

enum SuspendedDegree
{
    NoSuspendedDegree	= 0,
    Sus2				= 2,
    Sus4				= 4
};

enum Alteration
{
    NoAlteration		= 0,
    Flat				=-1,
    Sharp				= 1
};

enum Inversion
{
    Root				= 0,
    First				= 1,
    Six					= 1,
    Second				= 2,
    SixFour				= 2,
    Third				= 3
};

enum SecondaryDegree
{
    NoSecondaryDegree	= 0,
    IV					= 4,
    V					= 5,
    VII					= 7
};




class Chord
{


};



#endif // CHORD_H
