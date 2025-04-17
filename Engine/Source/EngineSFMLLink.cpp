// EngineSFMLLink.cpp
// Automatically links to SFML dynamic libraries for Engine users.

#if defined(_DEBUG)
    // Only link sfml-graphics-d.lib, it will pull in other deps itself
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib") // Only if you're using it
#pragma comment(lib, "FLACd.lib")        // Only in debug
#else
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "FLAC.lib")
#endif

