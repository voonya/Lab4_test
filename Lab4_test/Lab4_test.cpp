#include <iostream>
#include <fstream>
#include <vector>



using namespace std;



int main()
{
    ifstream sound("sound.wav",ios::binary);
    int32_t chunk_size;
    //string word;
    //string format;
    string subchunk_id_1;
    int32_t subchunk_size_1;
    int32_t audio_format;
    int32_t num_channels;
    int32_t sample_rate;
    int32_t byte_rate;
    int32_t block_align;
    int32_t bits_per_sample;
    int32_t extra_param_size;
    //tring subchunk_id_2;
    int32_t subchunk_size_2;
    vector<int32_t> data;
    int32_t sample;
   // sound.read((char*)&word,sizeof(int32_t));
    sound.seekg(4, ios::beg);
    sound.read((char*)&chunk_size, sizeof(int32_t));
    //sound.read((char*)&format, sizeof(int32_t));
    sound.seekg(8, ios::cur);
    //sound.read((char*)&subchunk_id_1, sizeof(int32_t));
    sound.read((char*)&subchunk_size_1, 4);
    sound.read((char*)&audio_format, 2);
    sound.read((char*)&num_channels, 2);
    sound.read((char*)&sample_rate, 4);
    sound.read((char*)&byte_rate, 4);
    sound.read((char*)&block_align, 2);
    sound.read((char*)&bits_per_sample, 2);
    sound.read((char*)&extra_param_size, 2);
    sound.seekg(20, ios::cur);
    //sound.read((char*)&subchunk_id_2, sizeof(string));
    sound.read((char*)&subchunk_size_2, sizeof(int32_t));
    while (!sound.eof()) {
        sound.read((char*)&sample, sizeof(int32_t));
        data.push_back(sample);
    }
    sound.close();
    cout <<  chunk_size << "\n";
    cout << subchunk_size_1 << "\n" << audio_format << "\n" << num_channels << "\n" << sample_rate << "\n";
    cout << byte_rate << "\n" << block_align << "\n" << subchunk_size_2 << "\n";
    for (int i = 0; i < data.size(); i++) {
        cout << data[i] << "\n";
    }

    
    return 0;
}

