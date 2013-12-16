#pragma once

#ifndef control_h
#define control_h

#include "storage.h"
#include "guiObjects.h"


class Clock: public StoreObject, virtual public kWidget {

    public:

        Clock();

        void createEvents();

        void init();

    //f
        float getPosition();

        void setPosition( float _position );

        float getDurationSecs();

        float getDurationMs();

        void setDurationSecs( float _dur );

        void setDurationMs( int _ms );

        void play();

        void pause();

        void stop();

        void update(ofEventArgs & args);

        void triggerEvent( int _i );

    //eventItems

        void addEvent( float _position, string _eventName );

        string getEvent();

        int getEventNum();

    //atts
        float   position;
        int     msThreshold;
        float   duration;
        int     durationMs;
        int     msCounter;
        bool    playing;
        string  event;
        int     eventNum;
        int     startedAt, pausedAt, resumedAt;
        int totalPausedTime;
        int lastPausedTime;
        vector < pair < float, string > > eventItems;
        vector < bool > triggered;

};

class ClockWidget: virtual public Clock, virtual public kRectView {
    //atts
    public:
        ClockWidget(){  }

        //f
        void draw(ofEventArgs & args);

        void initialize();

        void btnClicked( widgetEvent & _event );

        shared_ptr<kRectButtonView> btnView;

        bool creatingEvent;

};



class AlphaControl: virtual public kRectView{

    public:

        AlphaControl();

        float getAlpha();

        float alpha;

        shared_ptr<kKnob> knob;
};

#endif


