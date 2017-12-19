#ifndef PROGRESSIONBUILDER_H
#define PROGRESSIONBUILDER_H
#include "Chord.h"
#include "Modes.h"
#include "Progression.h"
#include "Substitutions.h"
#include "MelonUtil.h"

#define melonException int
#define VARIATION_FUNCTION_POINTER melonException (*)(Progression&)
#define VARIATION_SUCCESS 1
#define VARIATION_FAILURE 0


class ProgressionBuilder
{
public:
    ProgressionBuilder();

    int     mNumberOfChords;
    Note    mScale;
    Mode    mMode;

    Progression generate();

private:

    // This function will RANDOMLY attempt the available hsu variations on RANDOMLY selected chords of the progression
    int applyVariation(Progression& oProgression, int iVariationAmount, vector<VARIATION_FUNCTION_POINTER> iVariationFunctions);

    // Basic Harmonic Strucutal Unit
    std::vector<Progression> hsuList =
    {
        // V-I
        Progression({Chord(5), Chord(1)}),

        // IV-I
        Progression({Chord(4), Chord(1)}),

        // II-V-I
        Progression({Chord(2), Chord(5), Chord(1)}),

        // VI-V-I
        Progression({Chord(6), Chord(5), Chord(1)}),

        // VI-II-V-I
        Progression({Chord(6), Chord(2), Chord(5), Chord(1)
        }),

        // III-II-V-I
        Progression({Chord(3), Chord(2), Chord(5), Chord(1)})
    };

    //=====================================================================================================================
    // BASIC HARMONIC STRUCTURAL UNIT VARIATIONS
    //=====================================================================================================================

    // Add tonic in front of the progression
    int hsuBasicVariation_AddTonicAtBeggining(Progression& oProgression);

    // Substitute V-I resolution for V-(IV|VI)
    int hsuBasicVariation_SubstituteFiveOneResolution(Progression& oProgression);

    // Stop oProgression after V
    int hsuBasicVariation_StopProgAfterDominant(Progression& oProgression);

    //=====================================================================================================================
    // GENERIC VARIATIONS
    //=====================================================================================================================

    // Substitute a chord
    int hsuGenericVariation_Substitution(Progression& oProgression);

    //  Insert a chord before another one
    int hsuGenericVariation_Interpolation(Progression& oProgression);

    //=====================================================================================================================
    //	ALTERATIVE VARIATIONS
    //=====================================================================================================================

    // Insert a secondary fifth degree on a randomly selected chord that is not a tonic or leading
    int hsuAlterativeVariation_AddSecondaryDominant(Progression& oProgression);

    // Substitute a chord with a chord from another mode
    int hsuAlterativeVariation_ModalMixture(Progression& oProgression);
    //=====================================================================================================================
    // HSU VARIATION FUNCTIONS LIST
    //=====================================================================================================================

    std::vector<VARIATION_FUNCTION_POINTER> hsuBasicVariationFunctions =
    {
        ProgressionBuilder::hsuBasicVariation_AddTonicAtBeggining,
        ProgressionBuilder::hsuBasicVariation_SubstituteFiveOneResolution,
        ProgressionBuilder::hsuBasicVariation_StopProgAfterDominant
    };

    std::vector<VARIATION_FUNCTION_POINTER> hsuGenericVariationFunctions =
    {
        hsuGenericVariation_Substitution,
        hsuGenericVariation_Interpolation
    };

    std::vector<VARIATION_FUNCTION_POINTER> hsuAlterativeVariationFunctions =
    {
        hsuAlterativeVariation_AddSecondaryDominant,
        hsuAlterativeVariation_ModalMixture
    };

    std::vector<VARIATION_FUNCTION_POINTER> allVariationFunctions =
    {
        hsuBasicVariation_AddTonicAtBeggining,
        hsuBasicVariation_SubstituteFiveOneResolution,
        hsuBasicVariation_StopProgAfterDominant,
        hsuGenericVariation_Substitution,
        hsuGenericVariation_Interpolation,
        hsuAlterativeVariation_AddSecondaryDominant/*,
        hsuAlterativeVariation_ModalMixture*/
    };

};




#endif // PROGRESSIONBUILDER_H
