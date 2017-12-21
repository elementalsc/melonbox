#ifndef PROGRESSIONBUILDER_H
#define PROGRESSIONBUILDER_H

#include "Progression.h"
#include "MelonLogger.h"
#include "MelonUtil.h"

#define melonException int
// Method pointer to list variation functions
#define VARIATION_FUNCTION_POINTER melonException (ProgressionBuilder::*)(Progression&)
#define VARIATION_SUCCESS 1
#define VARIATION_FAILURE 0

class ProgressionBuilder
{

public:

    int          mVariationAmount   = 3;
    Note         mScale             = C;
    Mode         mMode              = Ionian;
    ModeType     mModeType          = NaturalMode;
    MelonLogger* logger             = logger->getInstance();

//=====================================================================================================================
// CONSTRUCTORS
//=====================================================================================================================

    ProgressionBuilder()
    {}

    ProgressionBuilder(int iVariationAmount, Note iScale, Mode iMode) :
        mVariationAmount(iVariationAmount),
        mScale(iScale),
        mMode(iMode)
    {}


//=====================================================================================================================
// PUBLIC METHODS
//=====================================================================================================================

    // Logic generating the progression
    Progression generate();

private:

//=====================================================================================================================
// PRIVATE METHODS
//=====================================================================================================================

    // This function will RANDOMLY attempt the available hsu variations on RANDOMLY selected chords of the progression
    int applyVariation(Progression& oProgression, int iVariationAmount, std::vector<VARIATION_FUNCTION_POINTER> iVariationFunctions);


//=====================================================================================================================
// BASIC HARMONIC STRUCTURAL UNIT
//=====================================================================================================================
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
        Progression({Chord(6), Chord(2), Chord(5), Chord(1)}),

        // III-II-V-I
        Progression({Chord(3), Chord(2), Chord(5), Chord(1)})
    };

//=====================================================================================================================
// GENERIC SUBSTITUTIONS AND INTERPOLATIONS LISTS
//=====================================================================================================================
    std::vector<Progression> genericSubstitutions =
    {
        {},	// index 0 empty for readability

        // 1st degree
        Progression({Chord(1, Inversion::Six), Chord(6), Chord(6, Inversion::Six), Chord(3)}),

        // 2nd degree
        Progression({Chord(2, Inversion::Six), Chord(4)}),

        // 3rd degree
        {},

        // 4th degree
        Progression({Chord(2), Chord(2, Inversion::Six), Chord(6, Inversion::Six)}),

        // 5th degree
        Progression({Chord(5, Inversion::Six), Chord(1, Inversion::SixFour), Chord(3, Inversion::Six)}),

        // 6th degree
        {},

        // 7th degree
        {}
    };

    std::vector<Progression> genericInterpolations =
    {
        {},	// index 0 empty for readability

        // 1st degree
        {},

        // 2nd degree
        Progression({Chord(4)}),

        // 3rd degree
        {},

        // 4th degree
        Progression({Chord(2)}),

        // 5th degree
        Progression({Chord(1, Inversion::SixFour)}),

        // 6th degree
        {},

        // 7th degree
        {},
    };

    // créer un algorithme qui donne des accords de substitution selon la gamme et le mode utiliser
    // utiliser des critères comme...
    //      "pas plus d'une ou deux notes hors gamme"
    //      "interdiction de modifier tonique ou dominante"
    std::vector<std::vector<Progression>> modalSubstitutions =
    {
        // index 0 empty for readability
        {},
        {
            // index 0 empty for readability
            {},

            // 1st degree : Parallel minor
            Progression({Chord(1, Triad::MinorTriad)}),

            // 2nd degree : Parallel minor, V/II
            Progression({Chord(2, Triad::MajorTriad)}),

            // 3rd degree : Parallel minor, V/III
            Progression({Chord(3, Triad::MajorTriad)}),

            // 4th degree : Parallel minor, Neapolitan sixth
            Progression({Chord(2, Triad::MajorTriad, Inversion::Six, Alteration::Flat)}),

            // 5th degree : Parallel minor, V/V
            Progression({Chord(5, Triad::MinorTriad)}),

            // 6th degree : Parallel minor, V/VI
            Progression({Chord(6, Triad::MajorTriad)}),

            // 7th degree : Flat major 7th
            Progression({Chord(7, Triad::MajorTriad, Alteration::Flat)})
        }
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

}; // class ProgressionBuilder

#endif // PROGRESSIONBUILDER_H
