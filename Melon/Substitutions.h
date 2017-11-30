#pragma once


#include "ConceptChord.cpp"

namespace Substitutions
{
    vector<vector<ConceptChord>> genericSubstitutions =
    {
        {},	// index 0 empty for readability


        // COMPLETE ACCORDING TO CIRCLE OF 5THs


            // 1st degree
        {
            ConceptChord(1, Inversion::Six),
            ConceptChord(6),
            ConceptChord(6,	Inversion::Six),
            ConceptChord(3)
        },

        // 2nd degree
        {
            ConceptChord(2, Inversion::Six),
            ConceptChord(4)
        },

        // 3rd degree
        {

        },

        // 4th degree
        {
            ConceptChord(2),
            ConceptChord(2, Inversion::Six),
            ConceptChord(6,	Inversion::Six)
        },

        // 5th degree
        {
            ConceptChord(5, Inversion::Six),
            ConceptChord(1,	Inversion::SixFour),
            ConceptChord(3,	Inversion::Six)
        },

        // 6th degree
        {

        },

        // 7th degree
        {

        }
    };

    vector<vector<ConceptChord>> genericInterpolations =
    {
        {},	// index 0 empty for readability

            // 1st degree
        {
        },

        // 2nd degree
        {
            ConceptChord(4),
        },

        // 3rd degree
        {

        },

        // 4th degree
        {
            ConceptChord(2),
        },

        // 5th degree
        {
            ConceptChord(1,	Inversion::SixFour)
        },

        // 6th degree
        {

        },

        // 7th degree
        {

        }
    };

    vector<vector<vector<ConceptChord>>> modalSubstitutions =
    {
        // index 0 empty for readability
        {},

        //
        // Major modes substitutions
        //
        {
            // index 0 empty for readability
            {},

            // 1st degree : Parallel minor
            {
                ConceptChord(1,	Triad::MinorTriad)
            },

            // 2nd degree : Parallel minor, V/II
            {
                ConceptChord(2,	Triad::MajorTriad)
            },

            // 3rd degree : Parallel minor, V/III
            {
                ConceptChord(3,	Triad::MajorTriad)
            },

            // 4th degree : Parallel minor, Neapolitan sixth
            {
                ConceptChord(2,	Triad::MajorTriad, Inversion::Six, Alteration::Flat)
            },

            // 5th degree : Parallel minor, V/V
            {
                ConceptChord(5,	Triad::MinorTriad)
            },

            // 6th degree : Parallel minor, V/VI
            {
                ConceptChord(6,	Triad::MajorTriad)
            },

            // 7th degree : Flat major 7th
            {
                ConceptChord(7,	Triad::MajorTriad, Alteration::Flat)
            }
        },

        //
        // Minor modes substitutions
        //
        {
            // index 0 empty for readability
            {},

            // 1st degree :
            {
            },

            // 2nd degree :
            {
            },

            // 3rd degree :
            {
            },

            // 4th degree :
            {
            },

            // 5th degree :
            {
            },

            // 6th degree :
            {
            },

            // 7th degree :
            {
            }
        },
    };
}
