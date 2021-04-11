#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class TrackWave
{
    float scale;
    string path_to_file;
    int32_t chunkId;   // Завжди містить значення 0x52494646 (літери "RIFF")
    int32_t chunkSize; // 36 + розмір другого підрозділу в байтах
                       // Іншими словами 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
                       // Це розмір всього файла мінус 8 байтів які займають поля chunkId та chunkSize
    int32_t format;
    int32_t subchunk1Id;   // Завжди 0x666d7420 – літери "fmt "
    int32_t subchunk1Size; // Завжди 16 для аудіо PCM. Це розмір частини підрозділу, що слідує після цього числа
    int16_t audioFormat;   // PCM = 1
    int16_t numChannels;   // Mono = 1, Stereo = 2
    int32_t sampleRate;    // Наприклад 44100
    int32_t byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
    int16_t blockAlign;    // == NumChannels * BitsPerSample/8
    int16_t bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
    int32_t subchunk2Id;   // 0x64617461 – літери "data"
    int32_t subchunk2Size; // == NumSamples * NumChannels * BitsPerSample/8, кількість байтів аудіоданих
    vector<int8_t> data_8;         // семпли 8bit
    vector<int16_t> data_16;         // семпли 16bit
    void set_data();
    void set_RIFF_header(ifstream& track);
    void set_subchunk_1(ifstream& track);
    void set_subchunk_2(ifstream& track);
    string get_path();
public:
    TrackWave(string name_file,float scale): scale(scale){
        path_to_file = get_path() + "/" + name_file + ".wav";
        set_data();
    }
    void refactor_track();
    void write_track(string new_file_path);
    void out_info();
};
int16_t interpolate(int32_t x0, int32_t x1, int16_t y0, int16_t y1, int32_t x);


