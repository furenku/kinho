
    #include "threadedClock.h"
    #include "testApp.h"

    //--------------------------------------------------------------
    void threadedClock::start(testApp* p)
    {

        // Get parent app
        parent = p;

        // Initialize note count
        notes = 0;

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
                notes++;
                unlock();

                // Phrase complete
                if (notes >= notesPerPhrase)
                {

                    // Call function on main app
                    parent->phraseComplete();

                    // Reset count
                    notes = 0;

                }

                // Sleep for duration of one note
                ofSleepMillis(parent->calculateNoteDuration());

            }

        }

    }
