#include "TSoundOperator.h"
#include <thread>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

using namespace std;

TSoundOperator SoundOperator;

TSoundOperator::TSoundOperator() {
    midiOutOpen(&(this->_device), (UINT)-1, 0, 0, CALLBACK_NULL);
}

TSoundOperator::~TSoundOperator() {
    midiOutClose(this->_device);
}

void TSoundOperator::_playSound(soundParams params) {
    // Вычисление MIDI ноты
    int Note = (int)(round((log(params.freq) - log(440.0)) / log(2.0) * 12 + 69));
    int Phrase = (params.velocity * 256 + Note) * 256 + 144; // MIDI сообщение для запуска ноты
    midiOutShortMsg(this->_device, (256 * params.instrument) + 192);
    midiOutShortMsg(this->_device, Phrase); // Используйте this->_device
    Sleep((int)(params.duration * (1 / params.tempo + 0.0001))); // Пауза
    Phrase = (params.velocity * 256 + Note) * 256 + 128; // MIDI сообщение для остановки ноты
    midiOutShortMsg(this->_device, Phrase); // Используйте this->_device
}

void TSoundOperator::playSound(int freq, int duration, int velocity, int instrument, float tempo) {
    thread thr(&TSoundOperator::_playSound, this, soundParams{ freq, duration, velocity, instrument, tempo });
    thr.detach();
}
