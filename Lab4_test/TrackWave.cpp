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
	track.read((char*)&sampleRate, sizeof(sampleRate));
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
	ofstream out("shoto_2.wav",ios::binary);
	chunkSize += subchunk2Size;
	subchunk2Size *= 2;
	out.write((char*)&chunkId, sizeof(chunkId));
	out.write((char*)&chunkSize, sizeof(chunkSize));
	out.write((char*)&format, sizeof(format));
	out.write((char*)&subchunk1Id, sizeof(subchunk1Id));
	out.write((char*)&subchunk1Size, sizeof(subchunk1Size));
	out.write((char*)&audioFormat, sizeof(audioFormat));
	out.write((char*)&numChannels, sizeof(numChannels));
	out.write((char*)&sampleRate, sizeof(sampleRate));
	out.write((char*)&byteRate, sizeof(byteRate));
	out.write((char*)&blockAlign, sizeof(blockAlign));
	out.write((char*)&bitsPerSample, sizeof(bitsPerSample));
	out.write((char*)&subchunk2Id, sizeof(subchunk2Id));
	out.write((char*)&subchunk2Size, sizeof(subchunk2Size));
	for (int i = 0; i < data_16.size(); i++) {
		out.write((char*)&data_16[i], bitsPerSample / 8);
		out.write((char*)&data_16[i], bitsPerSample / 8);
	}
	out.close();
}

void TrackWave::out_info() {
	cout << "chunkId: " << chunkId << endl;
	cout << "chunkSize: " << chunkSize << endl;
	cout << "format: " << format << endl;
	cout << "subchunk1Id: " << subchunk1Id << endl;
	cout << "subchunk1Size: " << subchunk1Size << endl;
	cout << "audioFormat: " << audioFormat << endl;
	cout << "numChannels: " << numChannels << endl;
	cout << "sampleRate: " << sampleRate << endl;
	cout << "byteRate: " << byteRate << endl;
	cout << "blockAlign: " << blockAlign << endl;
	cout << "bitsPerSample: " << bitsPerSample << endl;
	cout << "subchunk2Id: " << subchunk2Id << endl;
	cout << "subchunk2Size: " << subchunk2Size << endl;
	cout << "data_8.size(): " << data_8.size() << endl;
	cout << "data_16.size(): " << data_16.size() << endl;
}