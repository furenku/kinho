
    #include "threadedClock.h"
    #include "testApp.h"

    //--------------------------------------------------------------
    void threadedClock::start( ClockManager * _p)
    {

        // Get parent app
        parent = _p;

        // Initialize note count
        ticks = 0;

        // Start thread -- blocking, venbose
        startThread(true, false);

    }

    //--------------------------------------------------------------
    void threadedClock::stop()
    {

        // Stop thread
        stopThread();

    }

    //--------------------------------------------------------------
    void threadedClock::threadedFunction()
    {

        // Thread is running
        while (isThreadRunning() != 0)
        {

            // Lock thread
            if (lock())
            {

                // Increment count and unlock
                ticks++;
                unlock();

                // Phrase complete
                if (ticks >= ticksPerBar)
                {

                    // Call function on main app
                    parent->barDone();

                    // Reset count
                    ticks = 0;

                }

                // Sleep for duration of one note
                ofSleepMillis(parent->calculateTickDuration());

            }

        }

    }
