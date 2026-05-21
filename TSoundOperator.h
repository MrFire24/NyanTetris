#pragma once
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <iostream>

struct soundParams {
    int freq;
    int duration;
    int velocity;
    int instrument;
    float tempo = 1.0;
};

class TSoundOperator {
private:
    HMIDIOUT _device; // MIDI output device handle
    void _playSound(soundParams params);
public:
    TSoundOperator();
    ~TSoundOperator();
    void playSound(int freq, int duration, int velocity, int instrument, float tempo = 1.0);
};

extern TSoundOperator SoundOperator;

namespace instruments {
    enum {
        AcousticGrandPiano = 0, // Acoustic grand piano: classic grand piano sound
        BrightAcousticPiano,    // Bright acoustic piano: similar to grand piano but with a brighter tone
        ElectricGrandPiano,     // Electric grand piano: electric version of the grand piano with a bright sound
        HonkyTonkPiano,         // Honky-tonk piano: imitation of an old worn-out piano with a characteristic sound
        ElectricPiano1,         // Electric piano 1: classic electric piano
        ElectricPiano2,         // Electric piano 2: second variant of the electric piano
        Harpsichord,            // Celesta: instrument with a sound similar to a celesta
        Clavi,                  // Clavi: electronic instrument with a sharp sound
        Celesta,                // Celesta: instrument with a crystal-clear sound
        Glockenspiel,           // Glockenspiel: bright, ringing and pure sound
        MusicBox,               // Music box: music box sound with a melody
        Vibraphone,             // Vibraphone: soft, vibrating sound, similar to a xylophone
        Marimba,                // Marimba: instrument with a rich, melodic sound
        Xylophone,              // Xylophone: bright and pure sound, similar to a glockenspiel
        TubularBells,           // Tubular bells: deep and soft sound, similar to a glockenspiel
        Dulcimer,               // Dulcimer: warm and pleasant sound
        DrawbarOrgan,           // Organ: classic organ sound
        PercussiveOrgan,        // Percussive organ: organ with a brighter and more distinct sound
        RockOrgan,              // Rock organ: organ with a bright and aggressive sound
        ChurchOrgan,            // Church organ: powerful and deep organ sound
        ReedOrgan,              // Reed organ: organ sound with a softer tone
        Accordion,              // Accordion: bright and dynamic accordion sound
        Harmonica,              // Harmonica: harmonica sound with a melodic tone
        TangoAccordion,         // Tango accordion: bright and exotic accordion sound
        AcousticGuitarNylon,    // Acoustic guitar (nylon strings): soft and pleasant guitar sound
        AcousticGuitarSteel,    // Acoustic guitar (steel strings): brighter and sharper guitar sound
        ElectricGuitarJazz,     // Electric guitar (jazz): soft and pleasant electric guitar sound
        ElectricGuitarClean,    // Electric guitar (clean): clean and bright electric guitar sound
        ElectricGuitarMuted,    // Electric guitar (muted): guitar sound with muted notes
        OverdrivenGuitar,       // Overdriven guitar: guitar with an overdriven sound
        DistortionGuitar,       // Distortion guitar: guitar with a distorted sound
        GuitarHarmonics,        // Guitar harmonics: guitar sound with harmonics
        AcousticBass,           // Acoustic bass: soft and deep bass guitar sound
        ElectricBassFinger,     // Electric bass (fingered): electric bass guitar sound
        ElectricBassPick,       // Electric bass (picked): electric bass guitar sound
        FretlessBass,           // Fretless bass: soft and smooth fretless bass guitar sound
        SlapBass1,              // Slap bass 1: bass guitar with a characteristic slap bass sound
        SlapBass2,              // Slap bass 2: second variant of the bass guitar with a characteristic slap bass sound
        SynthBass1,             // Synth bass 1: synthesized bass sound
        SynthBass2,             // Synth bass 2: second variant of the synthesized bass sound
        Violin,                 // Violin: melodic and emotional violin sound
        Viola,                  // Viola: deeper and softer viola sound
        Cello,                  // Cello: deep and emotional cello sound
        Contrabass,             // Contrabass: powerful and deep double bass sound
        TremoloStrings,         // Tremolo strings: string sound with a trembling effect
        PizzicatoStrings,       // Pizzicato strings: string sound with a pizzicato effect
        OrchestralHarp,         // Orchestral harp: soft and crystal-clear harp sound
        Timpani,                // Timpani: powerful and deep timpani sound
        StringEnsemble1,        // String ensemble 1: ensemble of string instruments sound
        StringEnsemble2,        // String ensemble 2: second variant of the string ensemble sound
        SynthStrings1,          // Synth strings 1: synthesized string instruments sound
        SynthStrings2,          // Synth strings 2: second variant of the synthesized string sound


        ChoirAahs,              // Choir: choir "aah" sound
        VoiceOohs,              // Voices: "ooh" sound
        SynthVoice,             // Synth voice: synthesized voice sound


        OrchestraHit,           // Orchestra hit: powerful orchestral hit sound
        Trumpet,                // Trumpet: bright and piercing trumpet sound
        Trombone,               // Trombone: soft and deep trombone sound
        Tuba,                   // Tuba: powerful and deep tuba sound
        MutedTrumpet,           // Muted trumpet: trumpet sound with a mute effect
        FrenchHorn,             // French horn: beautiful and emotional French horn sound
        BrassSection,           // Brass section: brass orchestra sound
        SynthBrass1,            // Synth brass 1: synthesized brass instruments sound
        SynthBrass2,            // Synth brass 2: second variant of the synthesized brass sound
        SopranoSax,             // Soprano saxophone: bright and piercing soprano saxophone sound
        AltoSax,                // Alto saxophone: deep and soft alto saxophone sound
        TenorSax,               // Tenor saxophone: soft and emotional tenor saxophone sound
        BaritoneSax,            // Baritone saxophone: deep and warm baritone saxophone sound
        Oboe,                   // Oboe: bright and melodic oboe sound
        EnglishHorn,            // English horn: soft and deep English horn sound
        Bassoon,                // Bassoon: deep and dark bassoon sound
        Clarinet,               // Clarinet: soft and melodic clarinet sound
        Piccolo,                // Piccolo: bright and piercing piccolo sound
        Flute,                  // Flute: pure and transparent flute sound
        Recorder,               // Recorder: soft and pleasant recorder sound
        PanFlute,               // Pan flute: exotic and melodic pan flute sound
        BlownBottle,            // Blown bottle: whistling sound through a bottle
        Shakuhachi,             // Shakuhachi: traditional Japanese instrument with a melodic sound
        Whistle,                // Whistle: ordinary whistle
        Ocarina,                // Ocarina: soft and pleasant ocarina sound


        Lead1Square,            // Lead 1: square wave, bright and synthesized sound
        Lead2Sawtooth,          // Lead 2: sawtooth wave, sharp and cutting sound
        Lead3Calliope,          // Lead 3: bright and exotic synthesizer sound
        Lead4Chiff,             // Lead 4: sound with emphasized high frequencies
        Lead5Charang,           // Lead 5: soft and pleasant sound with a characteristic effect
        Lead6Voice,             // Lead 6: sound with emphasized low frequencies
        Lead7Fifths,            // Lead 7: sound with fifth chords
        Lead8BassLead,          // Lead 8: sound with a characteristic bass


        Pad1NewAge,             // Pad 1: new age sound
        Pad2Warm,               // Pad 2: soft and warm pad sound
        Pad3Polysynth,          // Pad 3: polysynth pad sound
        Pad4Choir,              // Pad 4: pad sound similar to a choir
        Pad5Bowed,              // Pad 5: pad sound similar to bowed instruments
        Pad6Metallic,           // Pad 6: metallic pad sound
        Pad7Halo,               // Pad 7: pad sound with a halo effect
        Pad8Sweep,              // Pad 8: pad sound with a sweep effect


        FX1Rain,                // FX 1: rain sound
        FX2Soundtrack,          // FX 2: soundtrack sound
        FX3Crystal,             // FX 3: crystal sound
        FX4Atmosphere,          // FX 4: atmosphere sound
        FX5Brightness,          // FX 5: bright sound
        FX6Goblins,             // FX 6: goblin sound
        FX7Echoes,              // FX 7: echo
        FX8SciFi,               // FX 8: sci-fi sound


        Sitar,                  // Sitar: bright and exotic sitar sound
        Banjo,                  // Banjo: banjo sound with a characteristic timbre
        Shamisen,               // Shamisen: Japanese string instrument with a melodic sound
        Koto,                   // Koto: traditional Japanese instrument with a soft sound
        Kalimba,                // Kalimba: African instrument with a melodic sound
        Bagpipe,                // Bagpipe: rough and powerful bagpipe sound
        Fiddle,                 // Fiddle (folk violin): bright and dynamic violin sound
        Shanai,                 // Shanai: traditional Indian instrument with a bright sound
        TinkleBell,             // Tinkle bell: small bell sound
        Agogo,                  // Agogo: agogo sound with a characteristic rhythm
        SteelDrums,             // Steel drums: bright and cheerful steel drum sound
        Woodblock,              // Woodblock: wooden block sound with a rhythmic effect
        TaikoDrum,              // Taiko drum: powerful and deep taiko drum sound
        MelodicTom,             // Melodic tom: soft and pleasant tom sound
        SynthDrum,              // Synth drum: synthesized drum sound


        ReverseCymbal,          // Reverse cymbal: cymbal sound played in reverse
        GuitarFretNoise,        // Guitar fret noise: noise from strumming guitar strings


        BreathNoise,            // Breath noise: breathing noise
        Seashore,               // Seashore: ocean surf sound
        BirdTweet,              // Bird tweet: bird singing sound
        TelephoneRing,          // Telephone ring: telephone ringing sound
        Helicopter,             // Helicopter: helicopter sound
        Applause,               // Applause: audience applause
        Gunshot                 // Gunshot: pistol shot sound
    };
}