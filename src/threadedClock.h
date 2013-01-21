/*
THANKS TO: LetsGoOutside (http://forum.openframeworks.cc/index.php?topic=3404.0)
*/
    #ifndef _THREADED_CLOCK
    #define _THREADED_CLOCK

    #include "ofMain.h"
    #define OF_ADDON_USING_OFXTHREAD
    #include "ofxThread.h"

    class testApp;

    class threadedClock : public ofxThread
    {

    public:

        // Timing properties
        int notes;
        int notesPerPhrase;

        // Methods
        void start(testApp* p);
        void stop();
        void threadedFunction();

    private:

        // Parent application
        testApp* parent;

    };

    #endif
