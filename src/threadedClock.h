/*
THANKS TO: LetsGoOutside (http://forum.openframeworks.cc/index.php?topic=3404.0)
*/



    #ifndef _THREADED_CLOCK
    #define _THREADED_CLOCK

    #include "general.h"


    #define OF_ADDON_USING_OFXTHREAD
    #include "ofxThread.h"

    class ClockManager;

    class threadedClock : public ofxThread
    {

    public:

        // Timing properties
        int ticks;
        int ticksPerBar;

        // Methods
        void start( ClockManager * parent );
        void stop();
        void threadedFunction();

    private:

        // clock manager
        ClockManager * parent;

    };




    #endif
