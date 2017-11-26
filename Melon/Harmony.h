#pragma once
#include "Modes.h"
#include "Substitutions.h"
#include "ConceptChord.cpp"

typedef vector<ConceptChord> Progression;

#define melonException int
#define VARIATION_FUNCTION_POINTER melonException (*)(Progression&)
#define VARIATION_SUCCESS 1
#define VARIATION_FAILURE 0
vector<Progression> hsuList =
{
    // Basic Harmonic Strucutal Unit families

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

//
// BASINC HARMONIC STRUCTURAL UNIT VARIATIONS
//

// Add tonic in front of the progression
int hsuBasicVariation_AddTonicAtBeggining(Progression& oProgression)
{
  if (oProgression[0] != ConceptChord(1))
  {
     oProgression.insert(oProgression.begin(), ConceptChord(1));
     return VARIATION_SUCCESS;
  }
  return VARIATION_FAILURE;
}

// Substitute V-I resolution for V-(IV|VI)
int hsuBasicVariation_SubstituteFiveOneResolution(Progression& oProgression)
{
  int wProgSize = oProgression.size();
  if ( oProgression[wProgSize - 1] == ConceptChord(1) &&
       oProgression[wProgSize - 1] == ConceptChord(5) )
  {
     if (Probability(50))
     {
       oProgression[wProgSize - 1] = ConceptChord(4);
       return VARIATION_SUCCESS;
     }
     else
     {
       oProgression[wProgSize - 1] = ConceptChord(6);
       return VARIATION_SUCCESS;
     }
  }
  return VARIATION_FAILURE;
}

// Stop oProgression after V
int hsuBasicVariation_StopProgAfterDominant(Progression& oProgression)
{
      for (unsigned int i = 1; i < oProgression.size(); ++i)
      {
             if (oProgression[i] == ConceptChord(5))
             {
                   oProgression.erase(oProgression.begin() + (++i), oProgression.end());
                   return VARIATION_SUCCESS;
             }
      }
      return VARIATION_FAILURE;
}

// HSU variations functions list
vector<VARIATION_FUNCTION_POINTER> hsuBasicVariationFunctions =
{
      hsuBasicVariation_AddTonicAtBeggining,
      hsuBasicVariation_SubstituteFiveOneResolution,
      hsuBasicVariation_StopProgAfterDominant
};



//
// GENERIC VARIATIONS
//

// Substitute a chord
// This function will randomly attempt substitution on chords of the progression, until it succeeds
// or fails after trying every chord of the progression.
int hsuGenericVariation_Substitution(Progression& oProgression)
{
    vector<int> wRemainingChords;
    for(int i = 0; i < oProgression.size(); ++i)
    {
        wRemainingChords.push_back(i);
    }

    int wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetConceptChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available substitutions
        if(Substitutions::genericSubstitutions[wTargetConceptChordDegree].size())
        {
            oProgression[wProgIndex] =                                                                  // assign new degree value at index...
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

//  Interpolate
int hsuGenericVariation_Interpolation(Progression& oProgression)
{
    vector<int> wRemainingChords;
    for(int i = 0; i < oProgression.size(); ++i)
    {
        wRemainingChords.push_back(i);
    }

    int wProgIndex;

    for(int i = 0; i < oProgression.size(); ++i)
    {
        wProgIndex = randVectorIndex(wRemainingChords);
        int wTargetConceptChordDegree = oProgression[wProgIndex].mDegree;

        // If the targeted degree has available interpolations
        if(Substitutions::genericInterpolations[wTargetConceptChordDegree].size())
        {
            oProgression.insert(oProgression.begin() + wProgIndex,                                      // insert new concept chord at index...
                    Substitutions::genericInterpolations[wTargetConceptChordDegree]                     // ...in this degree's possible interpolations
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

// HSU variations functions list
vector<VARIATION_FUNCTION_POINTER> hsuGenericVariationFunctions =
{
      hsuGenericVariation_Substitution,
      hsuGenericVariation_Interpolation
};


//
// This function will randomly attempt the available hsu variations
//
bool variation(Progression& oProgression, int iVariationAmount, vector<VARIATION_FUNCTION_POINTER> iVariationFunctions)
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
                return true;
            }
            else
            {
                removeEraseValue(wRemainingVariations,wCase);
            }
        }
    }
    return false;
}


//
//	INSERTING MODE CHORDS
//
void applyModeTriads(vector<ConceptChord>& oProgression, Mode mode)
{
    Triad majorTriads[7] =
    {
        Triad::MajorTriad,
        Triad::MinorTriad,
        Triad::MinorTriad,
        Triad::MajorTriad,
        Triad::MajorTriad,
        Triad::MinorTriad,
        Triad::DiminishedTriad
    };

    for (int i = 0; i < oProgression.size(); ++i)
    {
        oProgression[i].mTriad = majorTriads[((oProgression[i].mDegree - 1) + (mode - 1)) % 7];
    }
}


//
//	SECONDARY DOMINANTS
//
void addSecondaryDominant(Progression& progression, int maxInterpolationCount)
{
    int interpolationCount = 0;

    for (unsigned int i = 0; i < progression.size(); ++i)
    {
        // Attempt interpolation
        if ( !(progression[i].mDegree == 1 || progression[i].mDegree == 7 ) && interpolationCount < maxInterpolationCount )
        {
            if ((i > 0 && progression[i - 1].mSecondaryDegree == NoSecondaryDegree) || !i)
            {
                if ( Probability(probSecondaryDominant) )
                {
                    progression.insert(progression.begin() + i, ConceptChord(progression[i].mDegree).SecondaryDegree(SecondaryDegree::V));
                    ++interpolationCount;
                }
            }
        }
    }
}



//
// MODAL MIXTURE
//
void modalMixture(Progression& progression, Mode mode, int maxSubstitutionsCount)
{
    // attempt mode-specific substitions (modal mixture & secondary degrees)
    if (maxSubstitutionsCount <= 0)	return;

    int substitutionCount = 0;

    for (unsigned int i = 0; ( i < progression.size() && substitutionCount < maxSubstitutionsCount ); ++i)
    {
        Progression wSubstitutes = Substitutions::modalSubstitutions[mode][progression[i].mDegree];

        if (wSubstitutes.size() >= 1 &&
            progression[i].mSecondaryDegree == NoSecondaryDegree && substitutionCount < maxSubstitutionsCount)
        {
            if ( (i > 0 && progression[i - 1].mSecondaryDegree == NoSecondaryDegree) || !i)
            {

                if ( Probability(probModalMixture) ) // Attempt substitution
                {
                    ConceptChord randomCandidate = wSubstitutes[randomInt(0, wSubstitutes.size() - 1)];
                    if( (i > 0 && progression[i - 1] != randomCandidate) || !i)
                    {
                        progression[i] = randomCandidate;
                        ++substitutionCount;
                    }
                }
            }
        }
    }
}






//
// CORRECTIONS
//
void removeDuplicates(Progression& oProgression)
{

}

void checkCadence(Progression& oProgression, Progression& cadence)
{

    // validate presence of a cadence structure

}


// UTILS

string ProgToString(Progression& progression)
{
    string oString;

    for (ConceptChord conceptChord : progression)
    {
        oString.append(conceptChord.toString());
        oString.append(" - ");
    }

    return oString.substr(0, oString.size() - 3);
}
