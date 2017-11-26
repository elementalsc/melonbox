#pragma once
#include "MelonUtil.h"
#include "Modes.h"
#include "Substitutions.h"
#include "ConceptChord.cpp"

typedef vector<ConceptChord> Progression;

#define melonException int
#define VARIATION_FUNCTION_POINTER melonException (*)(Progression&)

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
int hsuVariation1(Progression& oProgression)
{
  if (oProgression[0] != ConceptChord(1))
  {
     oProgression.insert(oProgression.begin(), ConceptChord(1));
     return 1;
  }
  return 0;
}

// Substitute V-I resolution for V-(IV|VI)
int hsuVariation2(Progression& oProgression)
{
  int wProgSize = oProgression.size();
  if ( oProgression[wProgSize - 1] == ConceptChord(1) &&
       oProgression[wProgSize - 1] == ConceptChord(5) )
  {
     if ( YesOrNo() )
     {
       oProgression[wProgSize - 1] = ConceptChord(4);
       return 1;
     }
     else
     {
       oProgression[wProgSize - 1] = ConceptChord(6);
       return 1;
     }
  }

  return 0;
}

// Stop oProgression after V
int hsuVariation3(Progression& oProgression)
{
      for (unsigned int i = 1; i < oProgression.size(); ++i)
      {
             if (oProgression[i] == ConceptChord(5))
             {
                   oProgression.erase(oProgression.begin() + (++i), oProgression.end());
                   return 1;
             }
      }
      return 0;
}

// HSU variations functions list
vector<VARIATION_FUNCTION_POINTER> hsuVariationFunctions =
{
      hsuVariation1,
      hsuVariation2,
      hsuVariation3
};



//
// VARIATIONS ON HARMONIC STRUCTURAL UNITS
//

void hsuVariation(Progression& oProgression, int iVariationAmount)
{
    bool wAttemptSuccessful = false;

    for(int wPass = 0; wPass < iVariationAmount; ++wPass)
    {
        vector<int> wAvailableVariations;

        // Create a vector containing a  continous list of int (0,1,2,3...) for all the variationFunctions
        // vector possible indexes. Each attempted index will be removed from the vector, so it is not attempted
        // more than once.
        for(int i = 0; i < hsuVariationFunctions.size(); ++i) wAvailableVariations.push_back(i);

        wAttemptSuccessful = false;
        int wCase;
        while(!wAttemptSuccessful)
        {
            // among the 3 possibilities, if one fails for incompatibility,
            // remove it from switch case possible inputs
            wCase = randVectorIndex(wAvailableVariations);

            if(hsuVariationFunctions[wCase](oProgression))
            {
                wAttemptSuccessful = true;
            }
            else
            {
                wAttemptSuccessful = false;
                removeEraseValue(wAvailableVariations,wCase);
                /*
                wAvailableVariations.erase(std::remove(wAvailableVariations.begin(),
                                                       wAvailableVariations.end(),
                                                       wCase), wAvailableVariations.end());*/
            }
        }
    }
}



//
// GENERIC SUBSTITUTIONS
//
void hsuGenericSubstitutions(Progression& progression, int maxSubstitutionsCount, int maxInterpolationCount)
{
    int substitutionCount = 0;
    int interpolationCount = 0;

    for (unsigned int i = 0; i < progression.size(); ++i)
    {

        // Attempt substitution

        vector<ConceptChord> wSubstitution	= Substitutions::genericSubstitutions[progression[i].mDegree];

        if (wSubstitution.size() >= 1)
        {
            if ( Probability(probGenericSubstitutions) && substitutionCount < maxSubstitutionsCount)
            {
                progression[i] = wSubstitution[randomInt(0, wSubstitution.size() - 1)];
                ++substitutionCount;
            }
        }


        // Attempt interpolation

        vector<ConceptChord> wInterpolation = Substitutions::genericInterpolations[progression[i].mDegree];

        if (wInterpolation.size() >= 1)
        {
            if ( Probability(probGenericSubstitutions) && interpolationCount < maxInterpolationCount)
            {
                progression.insert(progression.begin() + i,wInterpolation[ randomInt(0, wInterpolation.size()-1)]);
                ++interpolationCount;
            }
        }
    }
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
