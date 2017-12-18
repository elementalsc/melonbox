#ifndef HARMONY_H
#define HARMONY_H

#include "MelonUtil.h"
#include "Modes.h"
#include "Substitutions.h"
#include "Chord.h"
#include "Progression.h"

//typedef vector<Chord> Progression;

#define melonException int
#define VARIATION_FUNCTION_POINTER melonException (*)(Progression&)
#define VARIATION_SUCCESS 1
#define VARIATION_FAILURE 0

Progression progression_V_I;

vector<Progression> hsuList =
{
    // Basic Harmonic Strucutal Unit

    progression_V_I
    /*
    // V-I
    {
        Chord(5),
        Chord(1)
    },

    // IV-I
    {
        Chord(4),
        Chord(1)
    },

    // II-V-I
    {
        Chord(2),
        Chord(5),
        Chord(1)
    },

    // VI-V-I
    {
        Chord(6),
        Chord(5),
        Chord(1)
    },

    // VI-II-V-I
    {
        Chord(6),
        Chord(2),
        Chord(5),
        Chord(1)
    },

    // III-II-V-I
    {
        Chord(3),
        Chord(2),
        Chord(5),
        Chord(1)
    }*/
};

//=====================================================================================================================
// BASIC HARMONIC STRUCTURAL UNIT VARIATIONS
//=====================================================================================================================

// Add tonic in front of the progression
int hsuBasicVariation_AddTonicAtBeggining(Progression& oProgression)
{
    if(oProgression[0] != Chord(1))
	{
        oProgression.insertChord(Chord(1),0);
		return VARIATION_SUCCESS;
	}
	
	return VARIATION_FAILURE;
}

// Substitute V-I resolution for V-(IV|VI)
int hsuBasicVariation_SubstituteFiveOneResolution(Progression& oProgression)
{
	int wProgSizeMinusOne = oProgression.size() - 1;

        if(oProgression[wProgSizeMinusOne] == Chord(1) &&
           oProgression[wProgSizeMinusOne] == Chord(5))
	{
		if (Probability(50))
		{
                        oProgression[wProgSizeMinusOne] = Chord(4);
			return VARIATION_SUCCESS;
		}
		else
		{
                        oProgression[wProgSizeMinusOne] = Chord(6);
			return VARIATION_SUCCESS;
		}
	}

	return VARIATION_FAILURE;
}

// Stop oProgression after V
int hsuBasicVariation_StopProgAfterDominant(Progression& oProgression)
{
    // Starts iterating at one to avoid empty progression
    for(unsigned int i = 1; i < oProgression.size(); ++i)
    {
        if(oProgression[i] == Chord(5))
        {
            oProgression.removeChord(++i);
            return VARIATION_SUCCESS;
        }
    }

    return VARIATION_FAILURE;
}

//=====================================================================================================================
// GENERIC VARIATIONS
//=====================================================================================================================

// Substitute a chord
int hsuGenericVariation_Substitution(Progression& oProgression)
{
    std::vector<int> wRemainingChords = oProgression.indexList();
    int 	wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available substitutions
        if(Substitutions::genericSubstitutions[wTargetChordDegree].size())
        {
            oProgression[wProgIndex] =                                                           // Assign new degree value at index...
                    Substitutions::genericSubstitutions[wTargetChordDegree]                      // ...in this degree's possible substitutions
                    [randVectorIndex(Substitutions::genericSubstitutions[wTargetChordDegree])];  // ...a random possibile substitute
            return VARIATION_SUCCESS;
        }
        else
        {
            removeEraseValue(wRemainingChords,wProgIndex);
        }
    }

    return VARIATION_FAILURE;
}

//  Insert a chord before another one
int hsuGenericVariation_Interpolation(Progression& oProgression)
{
    std::vector<int> wRemainingChords = oProgression.indexList();
    int              wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available interpolations
        if(Substitutions::genericInterpolations[wTargetChordDegree].size())
        {
            oProgression.insertChord(Substitutions::genericInterpolations[wTargetChordDegree][randVectorIndex(Substitutions::genericInterpolations[wTargetChordDegree])],wProgIndex);
            /*
            insertAtIndex(oProgression, wProgIndex,                                      			// Insert new concept chord at index...
                          Substitutions::genericInterpolations[wTargetChordDegree]                       // ...in this degree's possible interpolations
                          [randVectorIndex(Substitutions::genericInterpolations[wTargetChordDegree])]);  // ...a random possibile interpolated chord
                          */

            return VARIATION_SUCCESS;
        }
        else
        {
            removeEraseValue(wRemainingChords,wProgIndex);
        }
    }

    return VARIATION_FAILURE;
}

// Circle of fifths
// Between two concept chords,
int hsuGenericVariation_CircleOfFifthInsertion(Progression& oProgression)
{
    // select two consecutive chords

    // compare if the correspond to a 3 chords sequence of the circle of 5th to insert a degree in between
    Progression circleOfFifth = {Chord(1),Chord(4),Chord(7),Chord(3),Chord(6),Chord(2),Chord(5)};

    //

}

//=====================================================================================================================
//	ALTERATIVE VARIATIONS
//=====================================================================================================================

// Insert a secondary fifth degree on a randomly selected chord that is not a tonic or leading
int hsuAlterativeVariation_AddSecondaryDominant(Progression& oProgression)
{
    std::vector<int> wRemainingChords = oProgression.indexList();
    int              wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);

        // Attempt secondary dominant insertion
        if(!(oProgression[wProgIndex].mDegree == 1 || oProgression[wProgIndex].mDegree == 7 ))
        {
            // If the previous chord is not a secondary degree, or if it's the first of the progression
            if((wProgIndex > 0 && oProgression[wProgIndex - 1].mSecondaryDegree == NoSecondaryDegree))
            {
                oProgression.insertChord(Chord(oProgression[wProgIndex].mDegree).SecondaryDegree(SecondaryDegree::V),wProgIndex);
                /*
                insertAtIndex(oProgression, wProgIndex, Chord(oProgression[wProgIndex].mDegree).SecondaryDegree(SecondaryDegree::V));
                return VARIATION_SUCCESS;
                */
            }
        }
    }

    return VARIATION_FAILURE;
}

// Substitute a chord with a chord from another mode
int hsuAlterativeVariation_ModalMixture(Progression& oProgression)
{
/*
    std::vector<int> wRemainingChordIndexes = oProgression.indexList();
    int              wProgIndex;

    for(unsigned int i = 0; ( i < oProgression.size()); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChordIndexes);

        // VDMILLET :  ADD NUANCE FOR MAJOR/MINOR MODE           // "1" here is for "Major Mode chord substitutes"
        Progression wSubstitutes = Substitutions::modalSubstitutions[1][oProgression[i].mDegree];

        // if this chord has modal substitutes
        if(wSubstitutes.size() >= 1 && oProgression[wProgIndex].mSecondaryDegree == NoSecondaryDegree)
        {
            // if the previous chord is not a secondary degree, or if it's the first of the progression
            if ( (wProgIndex > 0 && oProgression[wProgIndex - 1].mSecondaryDegree == NoSecondaryDegree))
            {
                oProgression[wProgIndex] = wSubstitutes[randomInt(0, wSubstitutes.size() - 1)];
                return VARIATION_SUCCESS;
            }
        }
    }
*/
    return VARIATION_FAILURE;
}

//=====================================================================================================================
// HSU VARIATION FUNCTIONS LIST
//=====================================================================================================================

vector<VARIATION_FUNCTION_POINTER> hsuBasicVariationFunctions =
{
    hsuBasicVariation_AddTonicAtBeggining,
    hsuBasicVariation_SubstituteFiveOneResolution,
    hsuBasicVariation_StopProgAfterDominant
};

vector<VARIATION_FUNCTION_POINTER> hsuGenericVariationFunctions =
{
    hsuGenericVariation_Substitution,
    hsuGenericVariation_Interpolation
};

vector<VARIATION_FUNCTION_POINTER> hsuAlterativeVariationFunctions =
{
    hsuAlterativeVariation_AddSecondaryDominant,
    hsuAlterativeVariation_ModalMixture
};

vector<VARIATION_FUNCTION_POINTER> allVariationFunctions =
{
    hsuBasicVariation_AddTonicAtBeggining,
    hsuBasicVariation_SubstituteFiveOneResolution,
    hsuBasicVariation_StopProgAfterDominant,
    hsuGenericVariation_Substitution,
    hsuGenericVariation_Interpolation,
    hsuAlterativeVariation_AddSecondaryDominant/*,
    hsuAlterativeVariation_ModalMixture*/
};



//====================================================================================================================
// APPLY VARIATION TEMPLATE
//====================================================================================================================

// This function will attempt the available hsu variations on randomly selected chords of the progression
int applyVariation(Progression& oProgression, int iVariationAmount, vector<VARIATION_FUNCTION_POINTER> iVariationFunctions)
{
    for(int wPass = 0; wPass < iVariationAmount; ++wPass)
    {
        std::vector<int> wRemainingVariations;

        // Create a vector containing a  continous list of int (0,1,2,3...) for all the variationFunctions
        // vector possible indexes. Each attempted index will be removed from the vector, so it is not attempted
        // more than once.
        for(int i = 0; i < iVariationFunctions.size(); ++i)
        {
            wRemainingVariations.push_back(i);
        }

        int wCase;
        for(int i = 0; i < iVariationFunctions.size(); ++i)
        {
            // among the 3 possibilities, if one fails for incompatibility,
            // remove it from switch case possible inputs
            wCase = randVectorIndex(wRemainingVariations);

            if(iVariationFunctions[wCase](oProgression))
            {
                return VARIATION_SUCCESS;
            }
            else
            {
                removeEraseValue(wRemainingVariations,wCase);
            }
        }
    }
	
    return VARIATION_FAILURE;
}


#endif // HARMONY_H
