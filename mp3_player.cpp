#include <iostream>    // For input and output (cout, cin)
#include <filesystem>  // For file system operations (list directories, check files)
#include <string>      // For string manipulation (std::string)
#include <vector>      // For dynamic arrays (std::vector)
#include <emscripten.h> // For Emscripten API
#include <emscripten/html5.h> // For HTML5 API
#include <thread>      // Required for std::this_thread::sleep_for
#include <ctime>       // For srand()
#include <set>         // For set<int>

using namespace std;
namespace fs = filesystem;

// Custom event handler (you will need to modify this for Emscripten)
class MediaPlayerCallback {
public:
    bool hasEnded;

    MediaPlayerCallback() : hasEnded(false) {}

    void onMediaPlayerEvent() {
        hasEnded = true;
    }
};

class song {
    atomic<bool> playing; // Thread-safe flag
public:
    song() : playing(false) {}

    void play_Song(const string &song_Name) {
        MediaPlayerCallback *callback = new MediaPlayerCallback(); // Create callback instance

        if (!fs::exists(song_Name)) {
            cout << "File not found: " << song_Name << endl;
            return;
        }

        // Here you will need to use Emscripten's HTML5 API to play the song

        playing = true; // Mark as playing
        cout << "Playing :" << song_Name;
        // Add code to play the song using Emscripten's HTML5 API
        // For example, you can use `emscripten_run_preload_plugins` to preload and play the audio file

        // Wait for the song to finish
        while (!callback->hasEnded) {
            emscripten_sleep(100);
        }

        playing = false; // Mark as stopped
        cout << endl << "Song finished." << endl;
    }

    bool isPlaying() {
        return playing;
    }
};

// The rest of your code remains mostly unchanged
// ...

int main() {
    startup_Menu menu;
    menu.open_Screen();

    return 0;
}
