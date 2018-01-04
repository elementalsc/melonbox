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
    switch(oProgression.getMode())
    {
    // Major modes can switch minor chords to major (II, III, VI, VII)
    case Ionian :
    case Lydian :
    case Mixolydian :
        wCandidateDegrees = {2,3,6,7};
        wMajorMode = true;
        break;
    // Minor modes can switch fewer major chords to minor (III)
    case Dorian :
    case Phrygian :
    case Aeolian :
    case Locrian :
        wCandidateDegrees = {3};
        wMajorMode = false;
        break;
    default:
        logger->log("Unable to evaluate Progression mode in MajorMinorMixing",Error);
        return VARIATION_FAILURE;
        break;
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

    logger->logProgression(oProgression, "MajorMinorMix : ");
    return VARIATION_SUCCESS;
}

// Substitute a chord with a chord from another mode
int
ProgressionBuilder::hsuAlterativeVariation_AnyModalMixture(Progression& oProgression)
{

    // Mode mixte (changer un accord majeur en mineur, et inversement)
    // Ne pas utiliser deux accords mixte de manière consécutive
    // Fait pour se substituer à un accord STANDARD
    // II substitué pour N (IIb6), ou IV dans le contexte IV - I

    // En majeur....
    // Interpolation entre des accords "synonymes" pour accroître la tension
        // II - V -> II - IImm - V
        // IV - V -> IV - IVmm - V
        // IV - V -> IV - IImm - V
    // Emprunt de III, VI, VII mineur

    // En mineur...
    // Majorisation de I ou de VI à la fin de la progression
    // Emprunt du III majeur


    // comparer à un mode et voir si on a pas trop de notes différentes de la gamme initiale
    // conserver une mémoire des notes étrangères déjà utilisées

    std::vector<int> wRemainingChordIndexes = oProgression.indexList();
    int              wProgIndex;

    for(unsigned int i = 0; ( i < oProgression.size()); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChordIndexes);

        // VDMILLET :  ADD NUANCE FOR MAJOR/MINOR MODE           // "1" here is for "Major Mode chord substitutes"
        Progression wSubstitutes = modalSubstitutions[1][oProgression[i].getDegree()];

        // if this chord has modal substitutes
        if(wSubstitutes.size() >= 1 && oProgression[wProgIndex].getSecondaryDegree() == NoSecondaryDegree)
        {
            // if the previous chord is not a secondary degree, or if it's the first of the progression
            if ( (wProgIndex > 0 && oProgression[wProgIndex - 1].getSecondaryDegree() == NoSecondaryDegree))
            {
                oProgression[wProgIndex] = wSubstitutes[randomInt(0, wSubstitutes.size() - 1)];
                return VARIATION_SUCCESS;
            }
        }
    }

    return VARIATION_FAILURE;
}


