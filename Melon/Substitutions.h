#ifndef SUBSTITUTIONS_H
#define SUBSTITUTIONS_H

#include "Chord.h"
using namespace std;

namespace Substitutions
{
    vector<vector<Chord>> genericSubstitutions =
    {
        {},	// index 0 empty for readability


        // COMPLETE ACCORDING TO CIRCLE OF 5THs


            // 1st degree
        {
            Chord(1, Inversion::Six),
            Chord(6),
            Chord(6, Inversion::Six),
            Chord(3)
        },

        // 2nd degree
        {
            Chord(2, Inversion::Six),
            Chord(4)
        },

        // 3rd degree
        {

        },

        // 4th degree
        {
            Chord(2),
            Chord(2, Inversion::Six),
            Chord(6, Inversion::Six)
        },

        // 5th degree
        {
            Chord(5, Inversion::Six),
            Chord(1, Inversion::SixFour),
            Chord(3, Inversion::Six)
        },

        // 6th degree
        {

        },

        // 7th degree
        {

        }
    };

    vector<vector<Chord>> genericInterpolations =
    {
        {},	// index 0 empty for readability

            // 1st degree
        {
        },

        // 2nd degree
        {
            Chord(4),
        },

        // 3rd degree
        {

        },

        // 4th degree
        {
            Chord(2),
        },

        // 5th degree
        {
            Chord(1, Inversion::SixFour)
        },

        // 6th degree
        {

        },

        // 7th degree
        {

        }
    };

    // créer un algorithme qui donne des accords de substitution selon la gamme et le mode utiliser
    // utiliser des critères comme...
    //      "pas plus d'une ou deux notes hors gamme"
    //      "interdiction de modifier tonique ou dominante"
    vector<vector<vector<Chord>>> modalSubstitutions =
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
                Chord(1, Triad::MinorTriad)
            },

            // 2nd degree : Parallel minor, V/II
            {
                Chord(2, Triad::MajorTriad)
            },

            // 3rd degree : Parallel minor, V/III
            {
                Chord(3, Triad::MajorTriad)
            },

            // 4th degree : Parallel minor, Neapolitan sixth
            {
                Chord(2, Triad::MajorTriad, Inversion::Six, Alteration::Flat)
            },

            // 5th degree : Parallel minor, V/V
            {
                Chord(5, Triad::MinorTriad)
            },

            // 6th degree : Parallel minor, V/VI
            {
                Chord(6, Triad::MajorTriad)
            },

            // 7th degree : Flat major 7th
            {
                Chord(7, Triad::MajorTriad, Alteration::Flat)
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

#endif // SUBSTITUTIONS_H
