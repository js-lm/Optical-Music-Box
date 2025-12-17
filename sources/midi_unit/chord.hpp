#pragma once

#include <cstdint>

struct Chord{
    enum class Root : uint8_t{ C, D, E, F, G, A, B} root;
    enum class Accidental : uint8_t{ Natural, Sharp, Flat} accidental;
    enum class Triad : uint8_t{
        Major, Minor, Diminished, Augmented
    } triad;
    enum class Extension : uint8_t{
        None        = 0,
        Minor7      = 1 << 0,
        Major7      = 1 << 1,
        Ninth       = 1 << 2,
        Eleventh    = 1 << 3,
        Thirteenth  = 1 << 4,
    } extension;

    struct Duration{
        uint8_t numerator;
        uint8_t denominator;
    } duration;

    using Octave = int8_t;
    Octave octave;
    
};

constexpr Chord::Extension operator|(Chord::Extension left, Chord::Extension right){
    using Extension = Chord::Extension;

    const auto extension{static_cast<Extension>(
        static_cast<uint8_t>(left) | static_cast<uint8_t>(right)
    )};

    const auto conflictMask{
        static_cast<Extension>(Extension::Minor7) 
      | static_cast<Extension>(Extension::Major7)
    };
    
    if(extension == conflictMask) return Chord::Extension::None; 
    
    return extension;
}

// TODO: This is not the way to do it. Too complicated, I don't need such precision. 
// I should replace triad and extension with just quality or just copy what Lovely Composer did