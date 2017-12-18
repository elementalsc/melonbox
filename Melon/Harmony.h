#ifndef HARMONY_H
#define HARMONY_H

#include "MelonUtil.h"
#include "Modes.h"
#include "Substitutions.h"
#include "ConceptChord.h"

using namespace std;

typedef vector<ConceptChord> ProgressionType;

#define melonException int
#define VARIATION_FUNCTION_POINTER melonException (*)(ProgressionType&)
#define VARIATION_SUCCESS 1
#define VARIATION_FAILURE 0

vector<ProgressionType> hsuList =
{
    // Basic Harmonic Strucutal Unit

    // V-I
    {
        ConceptChord(5),
        ConceptChord(1)
    },

    // IV-I
    {
        ConceptChord(4),
        ConceptChord(1)
    },

    // II-V-I
    {
        ConceptChord(2),
        ConceptChord(5),
        ConceptChord(1)
    },

    // VI-V-I
    {
        ConceptChord(6),
        ConceptChord(5),
        ConceptChord(1)
    },

    // VI-II-V-I
    {
        ConceptChord(6),
        ConceptChord(2),
        ConceptChord(5),
        ConceptChord(1)
    },

    // III-II-V-I
    {
        ConceptChord(3),
        ConceptChord(2),
        ConceptChord(5),
        ConceptChord(1)
    }
};

//=====================================================================================================================
// BASIC HARMONIC STRUCTURAL UNIT VARIATIONS
//=====================================================================================================================

// Add tonic in front of the progression
int hsuBasicVariation_AddTonicAtBeggining(ProgressionType& oProgression)
{
	if(oProgression[0] != ConceptChord(1))
	{
		oProgression.insert(oProgression.begin(), ConceptChord(1));
		return VARIATION_SUCCESS;
	}
	
	return VARIATION_FAILURE;
}

// Substitute V-I resolution for V-(IV|VI)
int hsuBasicVariation_SubstituteFiveOneResolution(ProgressionType& oProgression)
{
	int wProgSizeMinusOne = oProgression.size() - 1;

	if(oProgression[wProgSizeMinusOne] == ConceptChord(1) &&
	   oProgression[wProgSizeMinusOne] == ConceptChord(5))
	{
		if (Probability(50))
		{
			oProgression[wProgSizeMinusOne] = ConceptChord(4);
			return VARIATION_SUCCESS;
		}
		else
		{
			oProgression[wProgSizeMinusOne] = ConceptChord(6);
			return VARIATION_SUCCESS;
		}
	}

	return VARIATION_FAILURE;
}

// Stop oProgression after V
int hsuBasicVariation_StopProgAfterDominant(ProgressionType& oProgression)
{
    // Starts iterating at one to avoid empty progression
    for(unsigned int i = 1; i < oProgression.size(); ++i)
    {
        if(oProgression[i] == ConceptChord(5))
        {
            oProgression.erase(oProgression.begin() + (++i), oProgression.end());
            return VARIATION_SUCCESS;
        }
    }

    return VARIATION_FAILURE;
}

//=====================================================================================================================
// GENERIC VARIATIONS
//=====================================================================================================================

// Substitute a chord
int hsuGenericVariation_Substitution(ProgressionType& oProgression)
{
    vector<int> wRemainingChords = generateListOfIndex(oProgression);
    int 	wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetConceptChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available substitutions
        if(Substitutions::genericSubstitutions[wTargetConceptChordDegree].size())
        {
            oProgression[wProgIndex] =                                                                  // Assign new degree value at index...
                    Substitutions::genericSubstitutions[wTargetConceptChordDegree]                      // ...in this degree's possible substitutions
                    [randVectorIndex(Substitutions::genericSubstitutions[wTargetConceptChordDegree])];  // ...a random possibile substitute
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
int hsuGenericVariation_Interpolation(ProgressionType& oProgression)
{
        vector<int> wRemainingChords = generateListOfIndex(oProgression);
    int 		wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetConceptChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available interpolations
        if(Substitutions::genericInterpolations[wTargetConceptChordDegree].size())
        {
            insertAtIndex(oProgression, wProgIndex,                                      			// Insert new concept chord at index...
                          Substitutions::genericInterpolations[wTargetConceptChordDegree]                       // ...in this degree's possible interpolations
                          [randVectorIndex(Substitutions::genericInterpolations[wTargetConceptChordDegree])]);  // ...a random possibile interpolated chord

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
int hsuGenericVariation_CircleOfFifthInsertion(ProgressionType& oProgression)
{
    // select two consecutive chords

    // compare if the correspond to a 3 chords sequence of the circle of 5th to insert a degree in between
    ProgressionType circleOfFifth = {ConceptChord(1),ConceptChord(4),ConceptChord(7),ConceptChord(3),ConceptChord(6),ConceptChord(2),ConceptChord(5)};

    //

}

//=====================================================================================================================
//	ALTERATIVE VARIATIONS
//=====================================================================================================================

// Insert a secondary fifth degree on a randomly selected chord that is not a tonic or leading
int hsuAlterativeVariation_AddSecondaryDominant(ProgressionType& oProgression)
{
    vector<int> wRemainingChords = generateListOfIndex(oProgression);
    int 		wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);

        // Attempt secondary dominant insertion
        if(!(oProgression[wProgIndex].mDegree == 1 || oProgression[wProgIndex].mDegree == 7 ))
        {
            // If the previous chord is not a secondary degree, or if it's the first of the progression
            if((wProgIndex > 0 && oProgression[wProgIndex - 1].mSecondaryDegree == NoSecondaryDegree))
            {
                insertAtIndex(oProgression, wProgIndex, ConceptChord(oProgression[wProgIndex].mDegree).SecondaryDegree(SecondaryDegree::V));
                return VARIATION_SUCCESS;
            }
        }
    }

    return VARIATION_FAILURE;
}

// Substitute a chord with a chord from another mode
int hsuAlterativeVariation_ModalMixture(ProgressionType& oProgression)
{

    vector<int>     wRemainingChordIndexes = generateListOfIndex(oProgression);
    int             wProgIndex;

    for(unsigned int i = 0; ( i < oProgression.size()); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChordIndexes);

        // VDMILLET :  ADD NUANCE FOR MAJOR/MINOR MODE           // "1" here is for "Major Mode chord substitutes"
        ProgressionType wSubstitutes = Substitutions::modalSubstitutions[1][oProgression[i].mDegree];

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

//=====================================================================================================================
// UTILS
//=====================================================================================================================

string ProgToString(ProgressionType& oProgression)
{
    string oString;

    for (ConceptChord conceptChord : oProgression)
    {
        oString.append(conceptChord.toString());
        oString.append(" - ");
    }

    return oString.substr(0, oString.size() - 3);
}



//
//	INSERTING MODE CHORDS
//
void applyModeTriads(vector<ConceptChord>& oProgression, Mode iMode, bool iNaturalOrHarmonic = true)
{
    for(int i = 0; i < oProgression.size(); ++i)
    {
        oProgression[i].mTriad = mNaturalTriads[((oProgression[i].mDegree - 1) + (iMode - 1)) % 7];
    }
}


//====================================================================================================================
// APPLY VARIATION TEMPLATE
//====================================================================================================================

// This function will attempt the available hsu variations on randomly selected chords of the progression
int applyVariation(ProgressionType& oProgression, int iVariationAmount, vector<VARIATION_FUNCTION_POINTER> iVariationFunctions)
{
    for(int wPass = 0; wPass < iVariationAmount; ++wPass)
    {
        vector<int> wRemainingVariations;

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
