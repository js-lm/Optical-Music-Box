#pragma once

#include <cstdint>
#include <span>

#include "chord.hpp"

class MidiManager{
public:
    // default
    enum class Instrument : uint8_t{
        // piano
        Grand_Piano_1           = 0,
        Bright_Piano_2          = 1,
        Electric_Grand_Piano_3  = 2,
        Honky_Tonk_Piano        = 3,
        Electric_Piano_1        = 4,
        Electric_Piano_2        = 5,
        Harpsichord             = 6,
        Clavi                   = 7,

        // chromatic percussion
        Celesta                 = 8,
        Glockenspiel            = 9,
        Music_Box               = 10,
        Vibraphone              = 11,
        Marimba                 = 12,
        Xylophone               = 13,
        Tubular_Bells           = 14,
        Santur                  = 15,

        // organ
        Drawbar_Organ           = 16,
        Percussive_Organ        = 17,
        Rock_Organ              = 18,
        Church_Organ            = 19,
        Reed_Organ              = 20,
        Accordion_French        = 21,
        Harmonica               = 22,
        Tango_Accordion         = 23,

        // guitar
        Acoustic_Guitar_Nylon   = 24,
        Acoustic_Guitar_Steel   = 25,
        Electric_Guitar_Jazz    = 26,
        Electric_Guitar_Clean   = 27,
        Electric_Guitar_Muted   = 28,
        Overdriven_Guitar       = 29,
        Distortion_Guitar       = 30,
        Guitar_Harmonics        = 31,

        // bass
        Acoustic_Bass           = 32,
        Finger_Bass             = 33,
        Picked_Bass             = 34,
        Fretless_Bass           = 35,
        Slap_Bass_1             = 36,
        Slap_Bass_2             = 37,
        Synthesizer_Bass_1      = 38,
        Synthesizer_Bass_2      = 39,

        // string
        Violin                  = 40,
        Viola                   = 41,
        Cello                   = 42,
        Contrabass              = 43,
        Tremolo_Strings         = 44,
        Pizzicato_Strings       = 45,
        Orchestral_Harp         = 46,
        Timpani                 = 47,

        // ensemble
        String_Ensemble_1       = 48,
        String_Ensemble_2       = 49,
        Synthesizer_Strings_1   = 50,
        Synthesizer_Strings_2   = 51,
        Choir_Aahs              = 52,
        Voice_Oohs              = 53,
        Synthesizer_Voice       = 54,
        Orchestra_Hit           = 55,

        // brass
        Trumpet                 = 56,
        Trombone                = 57,
        Tuba                    = 58,
        Muted_Trumpet           = 59,
        French_Horn             = 60,
        Brass_Section           = 61,
        Synthesizer_Brass_1     = 62,
        Synthesizer_Brass_2     = 63,

        // reed
        Soprano_Sax             = 64,
        Alto_Sax                = 65,
        Tenor_Sax               = 66,
        Baritone_Sax            = 67,
        Oboe                    = 68,
        English_Horn            = 69,
        Bassoon                 = 70,
        Clarinet                = 71,

        // pipe
        Piccolo                 = 72,
        Flute                   = 73,
        Recorder                = 74,
        Pan_Flute               = 75,
        Blown_Bottle            = 76,
        Shakuhachi              = 77,
        Whistle                 = 78,
        Ocarina                 = 79,

        // synth lead
        Lead_1_Square           = 80,
        Lead_2_Sawtooth         = 81,
        Lead_3_Calliope         = 82,
        Lead_4_Chiff            = 83,
        Lead_5_Charang          = 84,
        Lead_6_Voice            = 85,
        Lead_7_Fifths           = 86,
        Lead_8_Bass_Lead        = 87,

        // synth pad
        Pad_1_Fantasia          = 88,
        Pad_2_Warm              = 89,
        Pad_3_Polysynth         = 90,
        Pad_4_Choir             = 91,
        Pad_5_Bowed             = 92,
        Pad_6_Metallic          = 93,
        Pad_7_Halo              = 94,
        Pad_8_Sweep             = 95,

        // synth effects
        Effects_1_Rain          = 96,
        Effects_2_Soundtrack    = 97,
        Effects_3_Crystal       = 98,
        Effects_4_Atmosphere    = 99,
        Effects_5_Brightness    = 100,
        Effects_6_Goblins       = 101,
        Effects_7_Echoes        = 102,
        Effects_8_Sci_Fi        = 103,

        // ethnic
        Sitar                   = 104,
        Banjo                   = 105,
        Shamisen                = 106,
        Koto                    = 107,
        Kalimba                 = 108,
        Bag_Pipe                = 109,
        Fiddle                  = 110,
        Shanai                  = 111,

        // percussive
        Tinkle_Bell             = 112,
        Agogo                   = 113,
        Steel_Drums             = 114,
        Woodblock               = 115,
        Taiko_Drum              = 116,
        Melodic_Tom             = 117,
        Synthesizer_Drum        = 118,
        Reverse_Cymbal          = 119,

        // sound effects
        Guitar_Fret_Noise       = 120,
        Breath_Noise            = 121,
        Seashore                = 122,
        Bird_Tweet              = 123,
        Telephone_Ring          = 124,
        Helicopter              = 125,
        Applause                = 126,
        Gunshot                 = 127
    };

    using Channel   = uint8_t;
    using Octave    = int8_t;
    using Velocity  = uint8_t;
    using Note      = uint8_t;

    enum class Style{

    };

    using BPM = uint16_t;

public:
    MidiManager() = default;
    ~MidiManager() = default;

    void initialization();

public:
    void noteOn(Channel channel, Note note, Velocity velocity);
    void noteOff(Channel channel, Note note);

    void playChord(Channel channel, Chord chord, Style style, BPM bpm);
    void stopChord(Channel channel);

    void silence(Channel channel);

public:
    void setBank(Channel channel, bool useAlternativeBank);
    void setInstrument(Channel channel, Instrument instrument);

};