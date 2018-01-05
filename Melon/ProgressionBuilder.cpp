#include "ProgressionBuilder.h"




//=====================================================================================================================
// GENERATE PROGRESSION
//=====================================================================================================================

Progression
ProgressionBuilder::generate()
{
    Progression oProgression({},mScale,mMode,mModeType);

    logger->log("Generating progression... ------------------------------------------------");

    // Recuperate random Harmonic Structural Unit
    oProgression.setChords(hsuList[randomInt(0, hsuList.size()-1)]);

    logger->logProgression(oProgression, "Basic HSU\t");

    // Apply random variations
    // TODO: add a variation memento, at least to look back if certain modifications are made
    applyVariation(oProgression,mVariationAmount,basicVariationFunctions);

    // Apply modal mixture
    //applyModalVariation(oProgression,mVariationAmount,modalVariationFunctions);

    // Apply mode
    applyModeTriads(oProgression, mMode, mModeType);

    // Apply notes

    logger->log("-------------------------------------------------...progression completed!");
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
                logger->log("Variations applied", Trace);
                break;
            }
            else
            {
                removeEraseValue(wRemainingVariations,wCase);
                if (!wRemainingVariations.size())
                {
                    logger->log("Variation failure", Warning);
                    return VARIATION_FAILURE;
                }
            }
        }
    }

    logger->log("Completed basic variations", Trace);
    return VARIATION_SUCCESS;
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
        logger->logProgression(oProgression, "Added tonic at beginning : ");
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

            logger->logProgression(oProgression, "Substituted V-I for IV-I : ");
            return VARIATION_SUCCESS;
        }
        else
        {
            oProgression[wProgSizeMinusOne] = Chord(6);
            logger->logProgression(oProgression, "Substituted V-I for VI-I : ");
            return VARIATION_SUCCESS;
        }
    }

    return VARIATION_FAILURE;
}

// Stop progression after V
int
ProgressionBuilder::hsuBasicVariation_StopProgAfterDominant(Progression& oProgression)
{
    // Starts iterating at one to avoid empty progression
    for(unsigned int i = 1; i < oProgression.size(); ++i)
    {
        if(oProgression[i] == Chord(5))
        {
            oProgression.removeChord(++i);
            logger->logProgression(oProgression, "Ended progression after V : ");
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
        int wTargetChordDegree = oProgression[wProgIndex].getDegree();

        // If the targeted degree has available substitutions
        if(genericSubstitutions[wTargetChordDegree].size())
        {
            oProgression[wProgIndex] =                                                           // Assign new degree value at index...
                    genericSubstitutions[wTargetChordDegree]                      // ...in this degree's possible substitutions
                    [randVectorIndex(genericSubstitutions[wTargetChordDegree].getChords())];  // ...a random possibile substitute

            logger->logProgression(oProgression, "Substituted a chord : ");
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
        int wTargetChordDegree = oProgression[wProgIndex].getDegree();

        // If the targeted degree has available interpolations
        if(genericInterpolations[wTargetChordDegree].size())
        {
            oProgression.insertChord(genericInterpolations[wTargetChordDegree][randVectorIndex(genericInterpolations[wTargetChordDegree].getChords())],wProgIndex);

            logger->logProgression(oProgression, "Inserted chord by interpolation : ");
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
        if(!(oProgression[wProgIndex].getDegree() == 1 || oProgression[wProgIndex].getDegree()== 7 ))
        {
            // If the previous chord is not a secondary degree, or if it's the first of the progression
            if((wProgIndex > 0 && oProgression[wProgIndex - 1].getSecondaryDegree() == NoSecondaryDegree))
            {
                oProgression.insertChord(Chord(oProgression[wProgIndex].getDegree()).setSecondaryDegree(SecondaryDegree::V),wProgIndex);

                logger->logProgression(oProgression, "Inserted secondary fifth : ");
                return VARIATION_SUCCESS;
            }
        }
    }

    return VARIATION_FAILURE;
}

int
ProgressionBuilder::hsuAlterativeVariation_MajorMinorSubstitution(Progression& oProgression)
{
    std::vector<int>    wCandidateDegrees;
    bool                wMajorMode;

    // According to mode, determine what degrees might be mixed
    if(isMajorMode(oProgression.getMode()))
    {
        wCandidateDegrees = {2,3,6,7};
        wMajorMode = true;
    }
    else
    {
        wCandidateDegrees = {3};
        wMajorMode = false;
    }

    // Build vector of chord indexes candidate to mode mixing
    std::vector<int> wProgressionCandidates;

    for(int wCandidateDegreeIndex = 0; wCandidateDegreeIndex < wCandidateDegrees.size();++wCandidateDegreeIndex)
    {
        for(int wProgChordIndex = 0; wProgChordIndex < oProgression.size(); ++wProgChordIndex)
        {
            if(oProgression[wProgChordIndex].getDegree() == wCandidateDegrees[wCandidateDegreeIndex])
            {
                wProgressionCandidates.push_back(wProgChordIndex);
            }
        }
    }

    if(!wProgressionCandidates.size())
    {
        logger->log("No available candidate for MajorMinorMixing in progression",Warning);
        return VARIATION_FAILURE;
    }

    if(wMajorMode)
    {
        oProgression[randVectorIndex(wProgressionCandidates)].setTriad(MinorTriad);
    }
    else
    {
        oProgression[randVectorIndex(wProgressionCandidates)].setTriad(MajorTriad);
    }

    logger->logProgression(oProgression, "Major<->Minor substitution : ");
    return VARIATION_SUCCESS;
}
int
ProgressionBuilder::hsuAlterativeVariation_MajorMinorInterpolation(Progression& oProgression)
{
    // Major mode possible interpolation
    // II - V -> II - [II | IV]mm - V
    // IV - V -> II - [II | IV]mm - V

    if(!isMajorMode(oProgression.getMode()))
    {
        logger->log("Can't use MajorMinorInterpolation with minor mode",Warning);
        return VARIATION_FAILURE;
    }

    // Build vector of chord indexes candidate to mode mixing
    std::vector<int> wProgressionCandidates;

    for(int wProgChordIndex = 0; wProgChordIndex < oProgression.size(); ++wProgChordIndex)
    {
        if((oProgression[wProgChordIndex].getDegree() == 2 || oProgression[wProgChordIndex].getDegree() == 4)
          // TODO :  add overflow protection here
          && oProgression[wProgChordIndex + 1].getDegree() == 5 )
        {
            wProgressionCandidates.push_back(wProgChordIndex);
        }
    }

    if(!wProgressionCandidates.size())
    {
        logger->log("No available candidate for MajorMinorInterpolation in progression",Warning);
        return VARIATION_FAILURE;
    }

    // Insert II or IV, keep inversion
    if(probability(50))
    {
        int wProgressionIndex = randVectorIndex(wProgressionCandidates);
        oProgression.insertChord(Chord(2).setTriad(MajorTriad).setInversion(oProgression[wProgressionIndex].getInversion()), wProgressionIndex + 1);
    }
    else
    {
        int wProgressionIndex = randVectorIndex(wProgressionCandidates);
        oProgression.insertChord(Chord(4).setTriad(MinorTriad).setInversion(oProgression[wProgressionIndex].getInversion()), wProgressionIndex + 1);
    }

    logger->logProgression(oProgression, "Major<->Minor interpolation : ");
    return VARIATION_SUCCESS;
}

int
ProgressionBuilder::hsuAlterativeVariation_NeapolitanSixth(Progression& oProgression)
{
    // Build vector of chord indexes candidate to mode mixing
    std::vector<int> wProgressionCandidates;

    for(int wProgChordIndex = 0; wProgChordIndex < oProgression.size(); ++wProgChordIndex)
    {
        if(oProgression[wProgChordIndex].getDegree() == 2         // TODO : add overflow protection here
           || (oProgression[wProgChordIndex].getDegree() == 4 && oProgression[wProgChordIndex + 1].getDegree() == 5))
        {
            wProgressionCandidates.push_back(wProgChordIndex);
        }
    }

    if(!wProgressionCandidates.size())
    {
        logger->log("No available candidate for NeapolitanSixth in progression",Warning);
        return VARIATION_FAILURE;
    }

    oProgression[randVectorIndex(wProgressionCandidates)] = Chord(2,MajorTriad,Six,Flat);
    logger->logProgression(oProgression, "Neopolitan sixth : ");
    return VARIATION_SUCCESS;
}

// Substitute a chord with a chord from another mode
int
ProgressionBuilder::hsuAlterativeVariation_AnyModalMixture(Progression& oProgression, int iStrangerNotesAllowed)
{

    std::vector<int> wRemainingChordIndexes = oProgression.indexList();

    // No modal mixture on 1st chord to stabilize progression root
    removeEraseValue(wRemainingChordIndexes, 0);

    int         wProgIndex;
    Mode        wMode = oProgression.getMode();
    ModeType    wModeType = oProgression.getModeType();

    for(int i = 0; i < oProgression.size(); ++i)
    {

        // take a degree of the progression
        wProgIndex = randVectorIndex(wRemainingChordIndexes);

        // establish degrees note according to mode
        std::vector<int> wSourceChordNotes = getChordNotes(oProgression[wProgIndex]);


        // Remove current mode from candidates
        std::vector<Mode> wRemainingModes = {Ionian, Dorian, Phrygian, Lydian, Mixolydian, Aeolian, Locrian};

        removeEraseValue(wRemainingModes, wMode);

        // Attempt substitution for other mode
        Chord wModeChord;
        Mode wModeAttempted;
        for(int j = 0; j < wRemainingModes.size(); ++j)
        {
            wModeAttempted = wRemainingModes[randVectorIndex(wRemainingModes)];
            wModeChord = oProgression[wProgIndex];

            // Find other mode chord notes
            std::vector<int> wModeChordNotes = getChordNotes(wModeChord.setMode(wModeAttempted));

            for(int k = 0; k < wModeChordNotes.size(); ++k)
            {
                wModeChordNotes[k] =- wSourceChordNotes[k];
            }

            // Count in wModeChordNotes how many notes were different
            if(std::count_if(wModeChordNotes.begin(), wModeChordNotes.end(), [](int i){return i == 0;}) <= iStrangerNotesAllowed)
            {
                oProgression[wProgIndex].setMode(wModeAttempted);
                logger->logProgression(oProgression, "Modal mixture : ");
                return VARIATION_SUCCESS;
            }

        }

        // Try other degree of progression if no success
        removeEraseValue(wRemainingChordIndexes, wProgIndex);
    }

    logger ->log("Unable to realize modal mixture on chord", Warning);
    return VARIATION_FAILURE;
}

std::vector<int>
ProgressionBuilder::getChordNotes(Chord iChord)
{
    // If iChord already has notes
    if(iChord.getNotes().size())
    {
        return iChord.getNotes();
    }

    // TODO : improve this (generate chord notes at initialization? check all chord parameters?...)

    std::vector<int> oNotes;
    std::vector<int> wScale = getModeScale(iChord.getMode(), iChord.getModeType());

    // Get first chord note on scale
    oNotes.push_back(wScale[iChord.getDegree()]);

    // Get 2nd note
    if(oNotes[0] <= 5)
    {
        oNotes.push_back(wScale[iChord.getDegree() + 2]);
    }
    else
    {
        oNotes.push_back(wScale[iChord.getDegree() - 5]);
    }

    // Get 3nd note
    if(oNotes[1] <= 5)
    {
        oNotes.push_back(wScale[iChord.getDegree() + 2]);
    }
    else
    {
        oNotes.push_back(wScale[iChord.getDegree() - 5]);
    }

    return oNotes;
}
