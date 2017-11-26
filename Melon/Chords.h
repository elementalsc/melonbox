#pragma once


enum Triad
{
        NoDefinedTriad		= 0,
        MajorTriad,
        MinorTriad,
        DiminishedTriad,
        AugmentedTriad
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

