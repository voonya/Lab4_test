#include "TrackWave.h"
#include <string>

using namespace std;



int main(int argc, char* argv[])
{
   
    cout << "Input the name of track: "; 
    string name_old; getline(cin, name_old);
    cout << "Input the name of new_track: ";
    string name_new; getline(cin, name_new);
    cout << "Input the scale: ";
    float scale; cin >> scale;
    TrackWave track(name_old, scale);
    track.out_info();
    track.refactor_track();
    track.write_track(name_new);
    track.out_info();
    /*
    string name_old = argv[1];
    string name_new = argv[2];
    float scale = stof(argv[3]);
    TrackWave track(name_old, scale);
    track.out_info();
    track.write_track(name_new);
    cout << "Scaling sound file... Done.\ Written result to " << name_new;
    system("pause");*/
    return 0;
}

