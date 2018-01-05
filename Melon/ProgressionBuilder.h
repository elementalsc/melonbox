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

struct ModalMixtureParameters
{
    bool mSecondaryDominant;
    bool mNeopolitanSixth;
    bool mMajorMinor;
    bool mModalMixture;
};

static ModalMixtureParameters defaultModalMixtureParameters = {false, false, false,false};

class ProgressionBuilder
{

private:

    int          mVariationAmount;
    Note         mScale;
    Mode         mMode;
    ModeType     mModeType;
    ModalMixtureParameters mModalMixtureParameters;
    MelonLogger* logger             = logger->getInstance();

public:

//=====================================================================================================================
// CONSTRUCTORS
//=====================================================================================================================

    ProgressionBuilder() = delete;

    ProgressionBuilder(int iVariationAmount = 1, Note iScale = C, Mode iMode = Ionian, ModeType iModeType = NaturalMode, ModalMixtureParameters iModalMixtureParemeters = defaultModalMixtureParameters) :
        mVariationAmount(iVariationAmount),
        mScale(iScale),
        mMode(iMode),
        mModeType(iModeType),
        mModalMixtureParameters(iModalMixtureParemeters)
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
    int applyVariation(Progression& oProgression, int iVariationAmount, std::vector<VARIATION_FUNCTION_POINTER> iVariationFunctions);// This function will RANDOMLY attempt the available hsu variations on RANDOMLY selected chords of the progression

    std::vector<int> getChordNotes(Chord iChord);

//=====================================================================================================================
// BASIC HARMONIC STRUCTURAL UNIT
//=====================================================================================================================
    std::vector<std::vector<Chord>> hsuList =
    {
        // V-I
        {Chord(5), Chord(1)},

        // IV-I
        {Chord(4), Chord(1)},

        // II-V-I
        {Chord(2), Chord(5), Chord(1)},

        // VI-V-I
        {Chord(6), Chord(5), Chord(1)},

        // VI-II-V-I
        {Chord(6), Chord(2), Chord(5), Chord(1)},

        // III-II-V-I
        {Chord(3), Chord(2), Chord(5), Chord(1)}
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

    // Change III, VI or VII from minor to major or III from major to minor
    int hsuAlterativeVariation_MajorMinorSubstitution(Progression& oProgression);

    // Insert mixed II or IV chord in II - V or IV - V progression
    int hsuAlterativeVariation_MajorMinorInterpolation(Progression& oProgression);

    // Substitute II or IV (in IV - V context) for IIb6
    int hsuAlterativeVariation_NeapolitanSixth(Progression& oProgression);

    // Substitute a chord with a chord from another mode
    int hsuAlterativeVariation_AnyModalMixture(Progression& oProgression, int iStrangerNotesAllowed);
    int hsuAlterativeVariation_ModalMixtureOneStranger(Progression& oProgression);
    int hsuAlterativeVariation_ModalMixtureTwoStranger(Progression& oProgression);

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
        hsuAlterativeVariation_AddSecondaryDominant,
        hsuAlterativeVariation_AddSecondaryDominant,
        hsuAlterativeVariation_MajorMinorSubstitution,
        hsuAlterativeVariation_MajorMinorInterpolation,
        hsuAlterativeVariation_NeapolitanSixth/*,
        hsuAlterativeVariation_ModalMixtureOneStranger,
        hsuAlterativeVariation_ModalMixtureTwoStranger*/
    };

    std::vector<VARIATION_FUNCTION_POINTER> basicVariationFunctions =
    {
        hsuBasicVariation_AddTonicAtBeggining,
        hsuBasicVariation_SubstituteFiveOneResolution,
        hsuBasicVariation_StopProgAfterDominant,
        hsuGenericVariation_Substitution,
        hsuGenericVariation_Interpolation
    };

    std::vector<VARIATION_FUNCTION_POINTER> modalVariationFunctions =
    {
        hsuAlterativeVariation_AddSecondaryDominant,
        hsuAlterativeVariation_MajorMinorSubstitution,
        hsuAlterativeVariation_MajorMinorInterpolation,
        hsuAlterativeVariation_NeapolitanSixth,
        hsuAlterativeVariation_ModalMixtureOneStranger,
        hsuAlterativeVariation_ModalMixtureTwoStranger

    };


}; // class ProgressionBuilder

#endif // PROGRESSIONBUILDER_H
