#include "TrackWave.h"


using namespace std;



int main()
{
    TrackWave track("shoto.wav");
    track.out_info();
    track.write_track("");
    
    return 0;
}

