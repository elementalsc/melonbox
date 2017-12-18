#ifndef SUBSTITUTIONS_H
#define SUBSTITUTIONS_H

#include "Chord.h"
#include "Progression.h"
using namespace std;

namespace Substitutions
{
    vector<Progression> genericSubstitutions =
    {
        Progression(),	// index 0 empty for readability

        // 1st degree
        Progression({
            Chord(1, Inversion::Six),
            Chord(6),
            Chord(6, Inversion::Six),
            Chord(3)
        }),

        // 2nd degree
        Progression({
            Chord(2, Inversion::Six),
            Chord(4)
        }),

        // 3rd degree
        Progression(),

        // 4th degree
        Progression({
            Chord(2),
            Chord(2, Inversion::Six),
            Chord(6, Inversion::Six)
        }),

        // 5th degree
        Progression({
            Chord(5, Inversion::Six),
            Chord(1, Inversion::SixFour),
            Chord(3, Inversion::Six)
        }),

        // 6th degree
        Progression(),

        // 7th degree
        Progression()
    };

    vector<Progression> genericInterpolations =
    {
        {},	// index 0 empty for readability

        // 1st degree
        Progression(),

        // 2nd degree
        Progression({
            Chord(4),
        }),

        // 3rd degree
        Progression(),

        // 4th degree
        Progression({
            Chord(2),
        }),

        // 5th degree
        Progression({
            Chord(1, Inversion::SixFour)
        }),

        // 6th degree
        Progression(),

        // 7th degree
        Progression(),
    };

    // créer un algorithme qui donne des accords de substitution selon la gamme et le mode utiliser
    // utiliser des critères comme...
    //      "pas plus d'une ou deux notes hors gamme"
    //      "interdiction de modifier tonique ou dominante"
    vector<vector<Progression>> modalSubstitutions =
    {
        // index 0 empty for readability
        {},

        //
        // Major modes substitutions
        //
        {
            // index 0 empty for readability
            Progression(),

            // 1st degree : Parallel minor
            Progression({
                Chord(1, Triad::MinorTriad)
            }),

            // 2nd degree : Parallel minor, V/II
            Progression({
                Chord(2, Triad::MajorTriad)
            }),

            // 3rd degree : Parallel minor, V/III
            Progression({
                Chord(3, Triad::MajorTriad)
            }),

            // 4th degree : Parallel minor, Neapolitan sixth
            Progression({
                Chord(2, Triad::MajorTriad, Inversion::Six, Alteration::Flat)
            }),

            // 5th degree : Parallel minor, V/V
            Progression({
                Chord(5, Triad::MinorTriad)
            }),

            // 6th degree : Parallel minor, V/VI
            Progression({
                Chord(6, Triad::MajorTriad)
            }),

            // 7th degree : Flat major 7th
            Progression({
                Chord(7, Triad::MajorTriad, Alteration::Flat)
            })
        },

        //
        // Minor modes substitutions
        //
        {
        }
    };
}

#endif // SUBSTITUTIONS_H
