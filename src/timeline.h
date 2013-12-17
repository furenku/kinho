
#pragma once


//#include "ontologies.h"
#include "mainClasses.h"
#include "baseGUIObjects.h"
#include "guiObjects.h"
#include "guiVideoObjects.h"
#include "views.h"
#include "threadedClock.h"

#ifndef timeline_h
#define timeline_h


class EventSource{
    public:
        EventSource();

        string getCommand();

        void setCommand( string _cmd );

        string command;

};

class EventTarget{
    public:
        EventTarget(){}

        virtual void happen(){}
        virtual void stop(){}

//        shared_ptr<EventSource> getSource(){    return source;  }

//        virtual void setSource( shared_ptr<EventSource> _source ){
//            source = _source;
//        }

//        shared_ptr<EventSource> source;
};


class Person: public EventSource{
    public:
        Person();
};

class NameSayer: public EventTarget {
    public:
        NameSayer();

        void happen();
        void stop();

        void setName( string _str );

        string name;

};

class LogData{

    public:

    LogData(){}

    void setInt( string _key , int _value );
    void setFloat( string _key , float _value );
    void setString( string _key, string _value  );
    void setBool( string _key, bool _value  );

    int getInt( string _key );
    float getFloat( string _key );
    string getString( string _key );
    bool getBool( string _key );

//    int getIntNo(){     return ints.size();     }
//    int getFloatNo(){   return strings.size();  }
//    int getStringNo(){  return strings.size();  }
//    int getBoolNo(){    return boolean.size();  }

    protected:
        map<string,int> ints;
        map<string,float> floats;
        map<string,string> strings;
        map<string,bool> bools;
};


class TimelineMarker: public Marker, public kRectView {
    public:
        TimelineMarker(){}
};

class Event: public StoreObject {
    public:

        Event();

        void execute();

        void stop();

// setlooptimes -1 : inf
        void trigger();
        void free();

    //{ get / set

        float   getDuration();
        float   getLoopTimes();
        int     getLoopCount();
        float   getTotalDuration();
        bool    getLoop();
        bool    getTriggered();
        shared_ptr<EventSource> getSource();
        shared_ptr<EventTarget> getTarget();
        virtual shared_ptr<LogData> getLogData();


        void setDuration( float _duration );
        void setLoopTimes( int _loopTimes);
        void setLoopCount( int _loopCount);
        void setLoop( bool _loop );
        void updateTotalDuration();
        void setSource( shared_ptr<EventSource> _source );
        void setTarget( shared_ptr<EventTarget> _target );

    //}

    private:

        float duration;
        bool loop;
        int loopCount;
        float loopTimes;
        float totalDuration;

        bool hasBeenTriggered;

        shared_ptr< EventSource > source;
        shared_ptr< EventTarget > target;

        shared_ptr<LogData> logData;

};




class NameEvent: public Event {




};

class TimelineEvent: public Event{

    public:
        TimelineEvent();

        void setHasWidget(bool _hasWidget);

        bool getHasWidget();

        void setColor( shared_ptr<ofColor> _color);
        shared_ptr<ofColor> getColor();


    protected:
        bool hasWidget;
        shared_ptr<ofColor> color;
        vector < shared_ptr<kCircleButton> > dragButtons;

};

class ControllerEvent: public Event{};

class TimelineEventWidget: public TimelineEvent, virtual public kRectView, virtual public kDragObject {
    public:
        TimelineEventWidget();


        ~TimelineEventWidget();
        void initialize();

        void draw( ofEventArgs & args );

        void mouseReleased( ofMouseEventArgs & mouse);

        void mouseDragged( ofMouseEventArgs & mouse);


    protected:

};

class Log{

public:
    void addEntry(long _time, shared_ptr<LogData> _logData);

    void saveLog();

    map < long, shared_ptr<LogData > > events;
};

class Timeline: public DBManager, public EventSource, public EventTarget {

    public:
        Timeline();

        void init();

        void iiinit();

        virtual void addEvent( shared_ptr<TimelineEvent> _event, long _time );


        virtual void addMarker( long _time, string _name );
        virtual void addMarker( long _time, string _name, string _imgFile );

        void addEvent( shared_ptr<TimelineEvent> _event, shared_ptr<EventSource> _source, shared_ptr<EventTarget> _target );

        virtual void removeEvent( long _time );

        virtual void fwd( int _ms );



        virtual void eventTriggerLogic( shared_ptr < TimelineEvent > _event );

        virtual void triggerEvent( shared_ptr<TimelineEvent> _event);

        virtual void freeEvent( long _time,  shared_ptr < TimelineEvent > _event );


        // get  / set{

        long getTotalTime();
        void setTotalTime( long _ms );

        long getPlayhead();
        void setPlayhead(long _ms);

        void setScope( long _start, long _end );
        void setScopeStart( long _start );
        void setScopeEnd( long _end );
        long getScopeStart();
        long getScopeEnd();
        long getScopeLength();





        shared_ptr<Clip> getNextPlayClip();

        void setNextClip(shared_ptr<Clip> _clip);


shared_ptr<Clip> nextClip,nextPlayClip;


        // }

    protected:


//        shared_ptr<Clip> nextPlayClip;

        long playHead;
        long totalTime;
        long scopeStart, scopeEnd, scroll;

        int latency;

        int eventLoopCount;
        long eventTime, eventDuration, eventTotalDuration;
        bool eventTriggered;

        shared_ptr<Log> log;

        map < long, shared_ptr<TimelineMarker> > timelineMarkers;
        map < long, shared_ptr<TimelineEvent> > timelineEvents;
        map < long, shared_ptr < TimelineEvent > >::iterator iter;

};

class ClipEvent: public TimelineEventWidget{
    public:
        ClipEvent();


        void trigger();

        void stop();
        void draw( ofEventArgs & args);

        void setClip( shared_ptr<Clip> _clip );

        shared_ptr<Clip> getClip();

        void playClip();

        ofImage img;

        shared_ptr<Timeline> track;

        shared_ptr<Clip> clip;

//        shared_ptr<testApp> app;
};



class ChangeWindowEvent: public TimelineEventWidget{
    public:
        ChangeWindowEvent();

        void trigger();

        void stop();

        void setColor( int _r, int _g, int _b );

//        shared_ptr<testApp> app;
};

class TimelineTrack: public Timeline, public kRectView {

    public:
        TimelineTrack();

        void init();

        void update( ofEventArgs & args );

        void draw( ofEventArgs & args );

        // { get  / set
        // get

        long getPlayHead();


        void fwd( int _ms );


        //set
        void setDraggingEvent( shared_ptr<TimelineEvent> _event );


        //{ add / insert / remove events & markers

        void addEvent( shared_ptr<TimelineEvent > _event, long _time );


        void addEvent( float _x, float _y, shared_ptr<Clip> _clip );

        void removeEvent( long _ms );


        long getNextPosition( long _time, long _duration );

        vector < shared_ptr <TimelineEvent> > getVisibleEvents();

        void makeMarker( long _ms );

        //}

        //{ widget logic:

        void selectEventsInTime(long _rangeStartMs, long _rangeEndMs );

        //make / delete widgets
        void makeWidgets();

        void deleteWidgets();

        void setTmpEvent( float _start, float _end );


        void adjustPreviousEventWidget();

        //}



        // time / x conversion:

        long xToTime( float _x );

        float timeToX( long _time );

        // mouse
        void mousePressed(ofMouseEventArgs & mouse);

        void mouseDragged(ofMouseEventArgs & mouse);

        void mouseReleased(ofMouseEventArgs & mouse);


        void eventTriggerLogic( shared_ptr < TimelineEvent > _event );

        void triggerEvent( shared_ptr<ClipEvent> _event);

        void freeEvent( long _time, shared_ptr < TimelineEvent > _event );

        //callback
        void eventWidgetDragged(widgetEvent & _event );

        void eventWidgetReleased(widgetEvent & _event );

        //{ FUTURE VERSION
        /*
            void adjustPreviousEventWidget(){}
                // find if there is a last event before timeline scope
                    // find if its dur after its time its still visible inside scope
                        // if so set widget to just show the range visible
            void tmpPushEvents( long _fromMs, long _amountMs ){}
            void pushEvents( long _fromMs, long _amountMs ){}
            bool insertingEvent( long _ms ){}
                // check if inserting event
                    // check if insert or divide older clip
                    return true;
        */
        //}



        shared_ptr<TimelineTrack> shared_from_this();


    protected:
        float tmpEventStart, tmpEventEnd;

        shared_ptr <TimelineEvent> draggingEvent;
        vector < shared_ptr <TimelineEvent> > eventsInTime;
        std::map<long, shared_ptr < TimelineEvent > >::iterator iter;
        int widgetUpdateCounter;

};



class TimelineView: public Timeline, public kRectView {
    public:
        TimelineView();

        void initialize();


        void draw(ofEventArgs & draw);


    protected:
    vector< shared_ptr < TimelineTrack > >  timelines;

};



class ClockManager {
    public:
        ClockManager();

        int lastMs, lastStep;

        //--------------------------------------------------------------
        void barDone();


        //--------------------------------------------------------------
        int calculateTickDuration();


        void addTimeline( shared_ptr<Timeline>  _timeline);


        private:

        threadedClock clock;
        float tempo;

        vector< shared_ptr < Timeline > > timelines;

};




/*



class TimelineWidget: public Timeline, public kRectView {
    public:
        TimelineWidget(){ orientation="horizontal"; autoArrange=false; rows = 2; spacingX=40;spacingY=40; }

        void initialize() {

//            kScrollView::initialize();

            createEventWidget();

        }

        void createEventWidget(){
            shared_ptr<TimelineEventWidget> timelineEvent = make_shared<TimelineEventWidget>( );
            timelineEvent -> set(0.3f,0,0.2f,1.0f);
            addWidget( timelineEvent );
            arrangeWidgets();
            timelineEvent->initialize();
            timelineWidgets.push_back( timelineEvent );


        }

        void arrangeWidgets(){
            kRectView::arrangeWidgets();

            // get visible widgets
            // set their widths depending on their x, timeline scroll, timeline zoom and timeline scope
        }

//        vector< shared_ptr < TimelineEventWidget > > & getVisibleWidgets(){
//            visibleWidgets.clear();

//            for (int i=0; i<widgets.size(); i++)
//            {
//            	timelineWidgets[i]-->getTime()
//            }
//        }

        void mouseReleased(ofMouseEventArgs & mouse)    {
            float position = getInRange(mouse.x,x,width+x);
            // get click position
            // multiply by timeline scope
            // add timeline scroll in relation to scope
        }

        void mouseDragged(ofMouseEventArgs & mouse){

        }


        void fwd( int _ms ){
//            shared_ptr < TimelineEvent > event;
//            map < long, shared_ptr < TimelineEvent > >::iterator it;
//
//            counter += _ms;
//            counter %= maxMs;
//
//            for( it = timelineEvents.begin(); it != timelineEvents.end(); ++it) {
//                event = it->second;
//
//                eventLoopCount = event->getLoopCount();
//
//                eventTime = long ( it->first );
//                eventDuration = long( event->getDuration() * 1000 );
//                eventTotalDuration = long( event->getTotalDuration() * 1000 );
//                eventTriggered = event->getTriggered();
//
//                eventTriggerLogic();
//
//                if( checkIsVisibleWidget() ){
//                    // add widget to visible widgets' list
//                    visibleWidgets.push_back(%$&);
//                }
//            }

        }

        bool checkIsVisibleWidget(){
            return true;
        }

    protected:
        vector< shared_ptr < TimelineEventWidget > > timelineWidgets;
        vector< shared_ptr < TimelineEventWidget > > visibleWidgets;

};

*/



//#endif

#endif
