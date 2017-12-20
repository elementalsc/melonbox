#include "ProgressionBuilder.h"




//=====================================================================================================================
// GENERATE PROGRESSION
//=====================================================================================================================

Progression
ProgressionBuilder::generate()
{
    Progression oProgression;

    // Recuperate random Harmonic Structural Unit
    oProgression = hsuList[randomInt(0, hsuList.size()-1)];

    // Apply random variations
    applyVariation(oProgression,mVariationAmount,allVariationFunctions);

    // Apply modal mixture

    // Apply mode
    applyModeTriads(oProgression, mMode, true);

    // Apply notes


    return oProgression;
}


//=====================================================================================================================
//	APPLY VARIATION
//=====================================================================================================================

// This function will RANDOMLY attempt the available hsu variations on RANDOMLY selected chords of the progression
int
ProgressionBuilder::applyVariation(Progression& oProgression, int iVariationAmount, std::vector<VARIATION_FUNCTION_POINTER> iVariationFunctions)
{
    for(int wPass = 0; wPass < iVariationAmount; ++wPass)
    {
        std::vector<int> wRemainingVariations = generateListOfIndex(iVariationFunctions);

        int wCase;

        for(int i = 0; i < iVariationFunctions.size(); ++i)
        {
            // among the possibilities, if one fails for incompatibility,
            // remove it from possible inputs
            wCase = randVectorIndex(wRemainingVariations);

            if((this->*iVariationFunctions[wCase])(oProgression))
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


//=====================================================================================================================
// BASIC VARIATIONS
//=====================================================================================================================

// Add tonic in front of the progression
int
ProgressionBuilder::hsuBasicVariation_AddTonicAtBeggining(Progression& oProgression)
{
    if(oProgression[0] != Chord(1))
    {
        oProgression.insertChord(Chord(1),0);
        return VARIATION_SUCCESS;
    }

    return VARIATION_FAILURE;
}

// Substitute V-I resolution for V-(IV|VI)
int
ProgressionBuilder::hsuBasicVariation_SubstituteFiveOneResolution(Progression& oProgression)
{
    int wProgSizeMinusOne = oProgression.size() - 1;

        if(oProgression[wProgSizeMinusOne] == Chord(1) &&
           oProgression[wProgSizeMinusOne] == Chord(5))
    {
        if (probability(50))
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
int
ProgressionBuilder::hsuBasicVariation_StopProgAfterDominant(Progression& oProgression)
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
int
ProgressionBuilder::hsuGenericVariation_Substitution(Progression& oProgression)
{
    std::vector<int> wRemainingChords = oProgression.indexList();
    int 	wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available substitutions
        if(genericSubstitutions[wTargetChordDegree].size())
        {
            oProgression[wProgIndex] =                                                           // Assign new degree value at index...
                    genericSubstitutions[wTargetChordDegree]                      // ...in this degree's possible substitutions
                    [randVectorIndex(genericSubstitutions[wTargetChordDegree].mChords)];  // ...a random possibile substitute
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
int
ProgressionBuilder::hsuGenericVariation_Interpolation(Progression& oProgression)
{
    std::vector<int> wRemainingChords = oProgression.indexList();
    int              wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available interpolations
        if(genericInterpolations[wTargetChordDegree].size())
        {
            oProgression.insertChord(genericInterpolations[wTargetChordDegree][randVectorIndex(genericInterpolations[wTargetChordDegree].mChords)],wProgIndex);
            return VARIATION_SUCCESS;
        }
        else
        {
            removeEraseValue(wRemainingChords,wProgIndex);
        }
    }

    return VARIATION_FAILURE;
}

//=====================================================================================================================
//	ALTERATIVE VARIATIONS
//=====================================================================================================================

// Insert a secondary fifth degree on a randomly selected chord that is not a tonic or leading
int
ProgressionBuilder::hsuAlterativeVariation_AddSecondaryDominant(Progression& oProgression)
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
            }
        }
    }

    return VARIATION_FAILURE;
}

// Substitute a chord with a chord from another mode
int
ProgressionBuilder::hsuAlterativeVariation_ModalMixture(Progression& oProgression)
{

    std::vector<int> wRemainingChordIndexes = oProgression.indexList();
    int              wProgIndex;

    for(unsigned int i = 0; ( i < oProgression.size()); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChordIndexes);

        // VDMILLET :  ADD NUANCE FOR MAJOR/MINOR MODE           // "1" here is for "Major Mode chord substitutes"
        Progression wSubstitutes = modalSubstitutions[1][oProgression[i].mDegree];

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


