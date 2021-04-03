#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class TrackWave
{
    string path_to_file;
    int32_t chunkId;   // ������ ������ �������� 0x52494646 (����� "RIFF")
    int32_t chunkSize; // 36 + ����� ������� �������� � ������
                       // ������ ������� 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
                       // �� ����� ������ ����� ���� 8 ����� �� �������� ���� chunkId �� chunkSize
    int32_t format;
    int32_t subchunk1Id;   // ������ 0x666d7420 � ����� "fmt "
    int32_t subchunk1Size; // ������ 16 ��� ���� PCM. �� ����� ������� ��������, �� ���� ���� ����� �����
    int16_t audioFormat;   // PCM = 1
    int16_t numChannels;   // Mono = 1, Stereo = 2
    int32_t sampleRate;    // ��������� 44100
    int32_t byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
    int16_t blockAlign;    // == NumChannels * BitsPerSample/8
    int16_t bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
    int32_t subchunk2Id;   // 0x64617461 � ����� "data"
    int32_t subchunk2Size; // == NumSamples * NumChannels * BitsPerSample/8, ������� ����� ���������
    vector<int8_t> data_8;         // ������ 8bit
    vector<int16_t> data_16;         // ������ 8bit
    void set_data();
    void set_RIFF_header(ifstream& track);
    void set_subchunk_1(ifstream& track);
    void set_subchunk_2(ifstream& track);
public:
    TrackWave(string path_to_file) : path_to_file(path_to_file) {
        set_data();
    }
    void refactor_track(float scale_size);
    void write_track(string new_file_path);
    void out_info();
};

