#include "TrackWave.h"

void TrackWave::set_data() {
	ifstream track(path_to_file, ios::binary);
	if (track.is_open()) {
		set_RIFF_header(track);
		set_subchunk_1(track);
		set_subchunk_2(track);
	}
	else {
		cout << "\n Can`t open the file\n";
	}
	
}
void TrackWave::set_RIFF_header(ifstream& track) {
	track.read((char*)&chunkId, sizeof(chunkId));
	track.read((char*)&chunkSize, sizeof(chunkSize));
	track.read((char*)&format, sizeof(format));

}
void TrackWave::set_subchunk_1(ifstream& track) {
	track.read((char*)&subchunk1Id, sizeof(subchunk1Id));
	track.read((char*)&subchunk1Size, sizeof(subchunk1Size));
	track.read((char*)&audioFormat, sizeof(audioFormat));
	track.read((char*)&numChannels, sizeof(numChannels));
	track.read((char*)&byteRate, sizeof(byteRate));
	track.read((char*)&blockAlign, sizeof(blockAlign));
	track.read((char*)&bitsPerSample, sizeof(bitsPerSample));
}
void TrackWave::set_subchunk_2(ifstream& track) {
	track.seekg(subchunk1Size - 16, ios::cur);
	track.read((char*)&subchunk2Id, sizeof(subchunk2Id));
	track.read((char*)&subchunk2Size, sizeof(subchunk2Size));
	if (bitsPerSample == 8) {
		while (!track.eof()) {
			int8_t buffer;
			track.read((char*)&buffer, sizeof(buffer));
			data_8.push_back(buffer);
		}
	}
	else if (bitsPerSample == 16) {
		while (!track.eof()) {
			int16_t buffer;
			track.read((char*)&buffer, sizeof(buffer));
			data_16.push_back(buffer);
		}
	}
	else {
		cout << "\n You are stupid programmer! I dont have case for " << bitsPerSample / 8 << " bytes. :/\n";
	}
}
void TrackWave::refactor_track(float scale_size) {

}

void TrackWave::write_track(string new_file_path) {

}

void TrackWave::out_info() {
	cout << chunkId << endl << chunkSize << endl << format << endl << subchunk1Id
		<< endl << subchunk1Size << endl << audioFormat << endl << numChannels <<
		endl << sampleRate << endl << byteRate << endl << blockAlign << endl << bitsPerSample
		<< endl << subchunk2Id << endl << subchunk2Size << endl << data_8.size() << endl << data_16.size() << endl;
}