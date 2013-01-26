//#include "testApp.h"

#pragma once

//#include "ofMain.h"

//#include "ontologies.h"
//#include "mainClasses.h"
//#include "baseGUIObjects.h"
//#include "guiObjects.h"
//#include "guiVideoObjects.h"
//#include "views.h"

testApp * app;


#ifndef timeline_h
#define timeline_h

class EventSource{
    public:
        EventSource(){
            command = "eventsourcecommand";
        }

        string getCommand(){
            return command;
        }

        void setCommand( string _cmd ){
            command = _cmd;
        }

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
        Person(){ command = "carlos iv"; }
};

class NameSayer: public EventTarget {
    public:
        NameSayer(){}

        void happen(){
            cout << "name is : "<< name << endl;
        }
        void stop(){
            cout << "stop : "<< name << endl;
        }

        void setName( string _str ){
            name = _str;
        }

        string name;

};

class LogData{

    public:

    LogData(){}

    void setInt( string _key , int _value ){
        if( ints.find( _key ) != ints.end() ){
            ints[ _key ] = _value;
        }
        else
            cout << "int not in vector!" << endl;
    }
    void setFloat( string _key , float _value ){
        if( floats.find( _key ) != floats.end() ){
            floats[ _key ] = _value;
        }
        else
            cout << "float not in vector!" << endl;
    }
    void setString( string _key, string _value  ){
        if( strings.find( _key ) != strings.end() ){
            strings[ _key ] = _value;
        }
        else
            cout << "string not in vector!" << endl;
    }
    void setBool( string _key, bool _value  ){
        if( bools.find( _key ) != bools.end() ){
            bools[ _key ] = _value;
        }
        else
            cout << "bool not in vector!" << endl;
    }

    int getInt( string _key ){
        if( ints.find( _key ) != ints.end() ){
            return ints[ _key ];
        }
        else
        return -1;
    }
    float getFloat( string _key ){
        if( floats.find( _key ) != floats.end() ){
            return floats[ _key ];
        }
        else
        return -1;
    }
    string getString( string _key ){
        if( strings.find( _key ) != strings.end() ){
            return strings[ _key ];
        }
        else
        return "";
    }
    bool getBool( string _key ){
        if( bools.find( _key ) != bools.end() ){
            return bools[ _key ];
        }
        else
        return false;
    }

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

class Event: public StoreObject {
    public:

        Event(){
            setName("event0");
            setType("event");
            hasBeenTriggered = false;
            loop = false;
            duration = 10;
            loopTimes = 1;
            loopCount = 0;
            updateTotalDuration();
            logData = make_shared<LogData>( );

        }

        void execute(){
            if(target) {
//                if ( source ){
//                    target->setName( source->getCommand() );
//                }

// 1. obtener los datos
// 2. crear el objeto paquete
// 3. asignarle datos
// 4. llamar el evento, pasarle paquete

                target->happen();
            }
        }

        void stop(){
            if(target) {
//                if ( source ){
//                    target->setSource( source );
//                }
                target->stop();
            }
        }

// setlooptimes -1 : inf
        void trigger(){
            hasBeenTriggered=true;
            execute();
        }
        void free(){
            hasBeenTriggered=false;
            stop();
        }

    //{ get / set

        float   getDuration(){      return duration;            }
        float   getLoopTimes(){     return loopTimes;           }
        int     getLoopCount(){     return loopCount;           }
        float   getTotalDuration(){ return totalDuration;       }
        bool    getLoop(){          return loop;                }
        bool    getTriggered(){     return hasBeenTriggered;    }
        shared_ptr<EventSource> getSource(){ return source;     }
        shared_ptr<EventTarget> getTarget(){ return target;     }
        virtual shared_ptr<LogData> getLogData(){ return logData; }


        void setDuration( float _duration ) {
            duration = _duration;
            updateTotalDuration();
        }
        void setLoopTimes( int _loopTimes) {
            loopTimes = _loopTimes;
            updateTotalDuration();
        }
        void setLoopCount( int _loopCount) {
            loopCount = _loopCount;
        }
        void setLoop( bool _loop ) {    loop = _loop;   }
        void updateTotalDuration() { totalDuration = duration * loopTimes; }
        void setSource( shared_ptr<EventSource> _source ) { source = _source;   }
        void setTarget( shared_ptr<EventTarget> _target ) { target = _target;   }

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
        TimelineEvent(){
        }

        void setHasWidget(bool _hasWidget){
            hasWidget = _hasWidget;
        }
        bool getHasWidget(){ return hasWidget; }

        void setColor( shared_ptr<ofColor> _color){ color = _color; }
        shared_ptr<ofColor> getColor() { return color; }


    protected:
        bool hasWidget;
        shared_ptr<ofColor> color;
        vector < shared_ptr<kCircleButton> > dragButtons;

};

class ControllerEvent: public Event{};

class TimelineEventWidget: public TimelineEvent, virtual public kRectView, virtual public kDragObject {
    public:
        TimelineEventWidget(){
            autoArrange=false;
        }


        ~TimelineEventWidget(){
            cout << "deleted event!" << endl;
        }
        void initialize(){
//
//            dragButtons.push_back( make_shared<kCircleButton>() );
//            dragButtons.back()->set(0,1,0.15f,0.15f);
//            addWidget( dragButtons.back() );
//
//            dragButtons.push_back( make_shared<kCircleButton>() );
//            dragButtons.back()->set(1,1,0.15f,0.15f);
//            addWidget( dragButtons.back() );
//
//            shared_ptr<kCircleButton>  btn = make_shared<kCircleButton>();
//            btn->setLabel("X");
//            btn->set(1,0,0.175f,0.175f);
//            addWidget( btn );
//
//
//            arrangeWidgets();



            // create bottons for dragging
            // add listeners for buttons press and drag
        }

        void draw( ofEventArgs & args ){
            kRectView::draw(args);

        }

        void mouseReleased( ofMouseEventArgs & mouse){
            kDragObject::mouseReleased(mouse);
        }

        void mouseDragged( ofMouseEventArgs & mouse){
            kDragObject::mouseReleased(mouse);
        }


    protected:

};

class Log{

public:
    void addEntry(long _time, shared_ptr<LogData> _logData){
        events[_time] = _logData;
    }

    void saveLog() {
     // iterate through all maps and print them on target
    }

    map < long, shared_ptr<LogData > > events;
};

class Timeline: public DBManager, public EventSource, public EventTarget {

    public:
        Timeline(){
            init();
        }

        void init(){
            // set max time to 2 hrs
            setTotalTime(7200000);

            playHead = 0;
            scopeStart = 0;
            scopeEnd = 60000;
            scroll = 0;

            log = make_shared<Log>();

            latency = 10;

//            iiinit();
        }


        void iiinit(){

            shared_ptr<TimelineEvent> hello, hello2;

            hello = make_shared<TimelineEvent>();
            hello2 = make_shared<TimelineEvent>();


            shared_ptr<Person>  person1 = make_shared<Person>();
            shared_ptr<Person>  person2 = make_shared<Person>();

            person2->setCommand("pedro reyes");

            shared_ptr<NameSayer> nameSayer = make_shared<NameSayer>();

            hello->setDuration( 3 );
            hello->setLoopTimes( 4 );
            hello->setSource( person1 );
            hello->setTarget( nameSayer );

            hello2->setDuration( 3 );
            hello2->setLoopTimes( 1 );
            hello2->setSource( person2 );
            hello2->setTarget( nameSayer );

            addEvent( hello, 3000 );
            addEvent( hello2, 5000 );

        }


        virtual void addEvent( shared_ptr<TimelineEvent> _event, long _time ){
            cout << "ok1" << endl;
            timelineEvents[ _time ] = _event;
            cout << "ok2" << endl;
        }

        void addEvent( shared_ptr<TimelineEvent> _event, shared_ptr<EventSource> _source, shared_ptr<EventTarget> _target ){
        }


        virtual void removeEvent( long _time ){
            // remove timelineEvents[ _time ] = _event;
        }

        virtual void fwd( int _ms ){

            playHead += _ms;
            playHead %= totalTime;

            setScopeEnd ( ( playHead - scroll ) + getScopeLength() );
            setScopeStart( playHead - scroll );

            for( iter = timelineEvents.begin(); iter != timelineEvents.end(); ++iter) {
                shared_ptr<TimelineEvent> event = iter->second;

                eventLoopCount = event->getLoopCount();

                eventTime = long ( iter->first );
                eventDuration = long( event->getDuration() * 1000 );
                eventTotalDuration = long( event->getTotalDuration() * 1000 );
                eventTriggered = event->getTriggered();

                if( scopeStart > eventTime ) {
                    eventTriggerLogic( event );
                }


            }

        }



        virtual void eventTriggerLogic( shared_ptr < TimelineEvent > _event ){

            // if playHead greater than event time but shorter than time + duration
            if( scopeStart > eventTime && scopeStart < eventTime + eventTotalDuration ) {

                // check if has been triggered
                if( !eventTriggered ){
                    // if not trigger it, which locks it from retriggering until it ends
                    triggerEvent( _event );

                    log->addEntry(eventTime, _event->getLogData() );

                    _event->setLoopCount( eventLoopCount  + 1 );
                }
                else {
                    // if already triggered, find out if its 'duration'  has already ended
//                    if( playHead > eventTime + (eventLoopCount * eventDuration)*1000 ){

                    if( playHead + latency >= eventTime + eventDuration ){
                        // if so, free it
                        freeEvent( playHead, _event );
                    }
                }
            }
//            else if ( scopeStart > eventTime + eventTotalDuration ){
//                // if still locked, and its 'totalDuration' * 1000 has already ended, free it
//                if( eventTriggered ){
//                    _event->free();
//                }
//            }
        }

        virtual void triggerEvent( shared_ptr<TimelineEvent> _event){
            _event->trigger();
        }

        virtual void freeEvent( long _time,  shared_ptr < TimelineEvent > _event ){
            _event->free();
        }
        // get  / set{

        long getTotalTime(){ return totalTime; }
        void setTotalTime( long _ms ) { totalTime = _ms; }

        long getPlayhead(){  return playHead;     }
        void setPlayhead(long _ms)   {   playHead = _ms;  }

        void setScope( long _start, long _end ) {
            scopeStart = _start;
            scopeEnd = _end;
        }
        void setScopeStart( long _start ) { scopeStart = _start;    }
        void setScopeEnd( long _end ) { scopeEnd = _end;    }
        long getScopeStart() { return scopeStart; }
        long getScopeEnd() { return scopeEnd; }
        long getScopeLength() {
            long length = scopeEnd - scopeStart;
            if(length==0) length = 1;
            return length;
        }

        // }

    protected:

        long playHead;
        long totalTime;
        long scopeStart, scopeEnd, scroll;

        int latency;

        int eventLoopCount;
        long eventTime, eventDuration, eventTotalDuration;
        bool eventTriggered;

        shared_ptr<Log> log;

        map < long, shared_ptr<TimelineEvent> > timelineEvents;
        map < long, shared_ptr < TimelineEvent > >::iterator iter;

};



class ChangeWindowEvent: public TimelineEventWidget{
    public:
        ChangeWindowEvent() { init(); }

        void trigger(){
            Event::trigger();
            setColor(ofRandomuf()*255,ofRandomuf()*255,ofRandomuf()*255);
        }

        void stop(){
            Event::stop();
            setColor(0,0,0);
        }

        void setColor( int _r, int _g, int _b ){

            cout << "changeWindow!!" << endl;
//            (testApp*)ofGetAppPtr() -> setColor(_r,_g,_b);
        }

//        shared_ptr<testApp> app;
};

class TimelineTrack: public Timeline, public kRectView {

    public:
        TimelineTrack(){ init(); }

        void init() {
            Timeline::init();
            autoArrange = false;
            setTmpEvent(-1,-1);
            widgetUpdateCounter=0;
        }

        void update( ofEventArgs & args ){
            kRectView::update(args);
            adjustPreviousEventWidget();
        }

        void draw( ofEventArgs & args ){
            kRectView::draw(args);
            if(tmpEventStart>=0 && tmpEventEnd > 0 )
                ofRect( tmpEventStart * width, y, ( tmpEventEnd-tmpEventStart ) * width, y+height );

            drawString(ofToString(scopeStart/1000),x-30,y-10);
//            for (iter = timelineEvents.begin(); iter != timelineEvents.end(); iter++) {
//                ofCircle( x+ timeToX(iter->first)*width, y + height /2 , 10 );
//            }

        }

        // { get  / set
        // get

        long getPlayHead(){ return playHead; }


        void fwd( int _ms ){
            Timeline::fwd(_ms);

            widgetUpdateCounter++;
            widgetUpdateCounter%=8;

            shared_ptr<ChangeWindowEvent> w;
            long time;
            float newX;

            ofRectangle rect;

            if( widgetUpdateCounter == 0 ) {

                for (iter = timelineEvents.begin(); iter != timelineEvents.end(); iter++) {

                    time = iter->first;
                    w.reset();
                    w = dynamic_pointer_cast<ChangeWindowEvent>( iter->second );
    //                float oldHeight = w -> getHeight();
                    long duration = w->getDuration();

                    newX = timeToX( time ) * width;
                    if(newX>0){
                        rect = w->getRectInView();

//                        w->set( newX, rect.y, rect.width, rect.height );//setHeight(oldHeight*0.99f);
//                        w->setRectInViewNoArrange();
                        w->setX(newX+x);
                        w->arrangeWidgets();
                    }
                    if( time - scopeStart <= 0 ) {

                        // delete widget:
                        w->hide();
                        w->disable();
                        w->disableUpdate();

//                        freeEvent( time, w );
//                        removeWidget(w);
//                        timelineEvents.erase(time);
//
                    }

                }

//                arrangeWidgets();


            }


            // trigger evetns when their index is due
            // when triggered and duration over, kill widget
            // get visible widgets


        }

        //set
        void setDraggingEvent( shared_ptr<TimelineEvent> _event ){
            draggingEvent = _event;
        }


        //{ add / insert / remove events & markers

        void addEvent( shared_ptr<TimelineEvent > _event, long _time ){
//            long position = getNextPosition( _time, _event->getDuration() );
//            if(position>0)
//                timelineEvents[ position ] = _event;
                timelineEvents[ _time ] = _event;

        }

        void removeEvent( long _ms ){
            Timeline::removeEvent( _ms );
            // remove corresponding widget
        }


        long getNextPosition( long _time, long _duration ) {
//cout << "position: " << _time << endl;
            long insertPosition = -1;
            long position = _time;
            long duration = _duration;
            long lastPos, lastDur;
            long nextPos, nextDur;
            lastPos=lastDur=nextPos=nextDur=0;

//cout << "test2" << endl;
            std::map<long, shared_ptr < TimelineEvent > >::iterator before,after;

            while( insertPosition < 0 ) {
                // find position after which our new event is not on other events
                // get closest keys in time map

                before = timelineEvents.lower_bound( position );
                after = timelineEvents.upper_bound( position );
//cout << "test4" << endl;

                if( before != timelineEvents.end() ) {
                    before--;
                    if( before != timelineEvents.end() ){
//    cout << "test5" << endl;

                        // get position
                        lastPos = before->first;
//                        cout << "lastpos: "<< lastPos << endl;
                        // get corresponding event's durations
                        lastDur = before->second->getDuration();
                    }
                } else {
//                cout << "test6" << endl;

                }
                if( after != timelineEvents.end() ) {
                    // get position
                    nextPos = after->first;

                    cout << "nextpos: "<< nextPos << endl;
                    // get corresponding event's durations
                    nextDur = after->second->getDuration();
                }

                if( before != timelineEvents.end() && after != timelineEvents.end()) {
                    if( position > lastPos + lastDur && position + duration < nextPos ) {
                        insertPosition = position;
                    }
                    else{
                        position = nextPos + nextDur + 1;
                    }
                }
                else{
                    if( position + duration < nextPos ) {
                        insertPosition = position;
                    }
                    else{
                        position = nextPos + nextDur + 1;
                    }
                }

                if( before == timelineEvents.end() && after == timelineEvents.end()) {
                    insertPosition = _time;
                }
            }

            return insertPosition;
        }

        vector < shared_ptr <TimelineEvent> > getVisibleEvents(){
            selectEventsInTime( scopeStart, scopeEnd );
        }

        void makeMarker( long _ms ){

        }

        //}

        //{ widget logic:

        void selectEventsInTime(long _rangeStartMs, long _rangeEndMs ){
            eventsInTime.clear();
            // add all events in range to vector:
            std::map<long, shared_ptr < TimelineEvent > >::iterator beforePlayhead, beforeEnd, walker;
            beforePlayhead = timelineEvents.lower_bound( _rangeStartMs );
            beforeEnd= timelineEvents.upper_bound( _rangeEndMs  );
            beforeEnd--;
            //beforePlayhead--;
            int dist = std::distance( beforePlayhead, beforeEnd ) + 1;
            walker = beforePlayhead;
            walker--;
            if ( walker == timelineEvents.end() )
                walker = beforePlayhead;

            if(beforePlayhead != timelineEvents.end() && beforeEnd != timelineEvents.end()) {}
                for (int i=0; i<dist; i++)
                {
                    if(walker!=timelineEvents.end())
                        eventsInTime.push_back( walker->second );
                    walker++;
                }
        }

        //make / delete widgets
        void makeWidgets(){
            // get visible events
            selectEventsInTime( playHead, playHead + scopeEnd );
            // check which visible EventWidgets' events' times+dur are now out of scope, store them in deleteWidgets vector
            // check which visible events don't have a widget
            // make their widgets
            // set their hasWidget status
            // add listeners
        }
        void deleteWidgets(){
            // set their hasWidget status
            // remove listeners for eventWidget
            // remove Widget
        }

        void setTmpEvent( float _start, float _end ){
            tmpEventStart = timeToX( _start );
            tmpEventEnd = timeToX(_end );
        }

        void adjustPreviousEventWidget(){
        }

        //}



        // time / x conversion:

        long xToTime( float _x ){
            float pct = getInRange(_x, x,x+width);

            long time = ( pct * getScopeLength() ) + scopeStart;
            return time;
        }

        float timeToX( long _time ){
            float pct = float ( _time - scopeStart ) / float ( getScopeLength() );
            return pct;
        }

        // mouse
        void mousePressed(ofMouseEventArgs & mouse){

        }

        void mouseDragged(ofMouseEventArgs & mouse) {
            if( inside(mouse.x,mouse.y) ) {
                if( draggingEvent )
                    setTmpEvent( getNextPosition( xToTime(mouse.x), draggingEvent->getDuration() ), draggingEvent->getDuration() );
                    /* if( insertingEvent() )
                        tmpPushEvents( ? )
                        */
            }
        }

        void mouseReleased(ofMouseEventArgs & mouse) {
            if( inside(mouse.x,mouse.y) ) {
                if( draggingEvent )
                    addEvent( draggingEvent, xToTime( getInRange( mouse.x, x, x+width ) ) );
                else{
                    makeMarker( xToTime(mouse.x) );
                }

                shared_ptr< ChangeWindowEvent >  event = make_shared<ChangeWindowEvent>( );

                float duration;

                duration = 3;
                event->setDuration( duration  );

                float timePct = getInRange( mouse.x, x, x+width); // _time );
                long timeMs = xToTime( mouse.x );
                long end =  timeMs + duration  * 1000 ;
                float durPct = timeToX( end );

                event -> set ( timePct , 0, durPct-timePct , 1 );

                addWidget( event );

                event->setLabel( ofToString(timeMs/1000) );

                event -> initialize();

                arrangeWidgets();
                addEvent( event , timeMs );

            }
        }


        void eventTriggerLogic( shared_ptr < TimelineEvent > _event ){

            // if playHead greater than event time but shorter than time + duration
            if( scopeStart > eventTime && scopeStart < eventTime + eventTotalDuration ) {

                // check if has been triggered
                if( !eventTriggered ){
                    // if not trigger it, which locks it from retriggering until it ends
                    triggerEvent( dynamic_pointer_cast<ChangeWindowEvent>( _event ) );

                    log->addEntry(eventTime, _event->getLogData() );

                    _event->setLoopCount( eventLoopCount  + 1 );
                }
                else {
                    // if already triggered, find out if its 'duration'  has already ended
//                    if( playHead > eventTime + (eventLoopCount * eventDuration)*1000 ){

                    if( playHead + latency >= eventTime + eventDuration ){
                        // if so, free it
                        freeEvent( playHead, _event );
                    }
                }
            }
//            else if ( scopeStart > eventTime + eventTotalDuration ){
//                // if still locked, and its 'totalDuration' * 1000 has already ended, free it
//                if( eventTriggered ){
//                    _event->free();
//                }
//            }
        }

        void triggerEvent( shared_ptr<ChangeWindowEvent> _event){
            dynamic_pointer_cast<ChangeWindowEvent>(_event)->trigger();
        }

        void freeEvent( long _time, shared_ptr < TimelineEvent > _event ){
            cout << "endit!!!!!!!" << endl;
            _event->free();
            removeWidget( dynamic_pointer_cast< TimelineEventWidget > ( _event ) );
            timelineEvents.erase( _time );


        }

        //callback
        void eventWidgetDragged(widgetEvent & _event ){

            //if not on other event
                //setTmpEvent( long_start, long _end );
        }

        void eventWidgetReleased(widgetEvent & _event ){

            //if not on other event
                //setEventTime( long _ms );
        }

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

    protected:
        float tmpEventStart, tmpEventEnd;

        shared_ptr <TimelineEvent> draggingEvent;
        vector < shared_ptr <TimelineEvent> > eventsInTime;
        std::map<long, shared_ptr < TimelineEvent > >::iterator iter;
        int widgetUpdateCounter;

};



class TimelineView: public Timeline, public kRectView {
    public:
        TimelineView(){
            orientation="vertical";
            cols= 1;
            spacingX=40; spacingY=50;
            autoArrange=true;
        }

        void initialize() {
            kRectView::initialize();
            for (int i=0; i<6; i++)
            {
                timelines.push_back( make_shared<TimelineTrack>( ));
                timelines.back()->set(0.0f, 0.0f,600,50);
                addWidget( timelines.back() );
                timelines.back()->initialize();

            }
            arrangeWidgets();

        }


        void draw(ofEventArgs & draw){
            float playHeadPos = float( playHead ) / float ( getScopeLength() );

            ofSetColor(255,180,0);

            ofLine(x+playHeadPos*width,y,x+playHeadPos*width, y+height);
            ofSetColor(255);
        }


    protected:
    vector< shared_ptr < TimelineTrack > >  timelines;

};



class ClockManager {
    public:
        ClockManager(){
            lastMs = 0;

            // Set up clock
            tempo = 6000.0f;
            clock.ticksPerBar = 1;
            clock.start(this);


        }

        int lastMs, lastStep;

        //--------------------------------------------------------------
        void barDone() {
            lastStep = ofGetElapsedTimeMillis() - lastMs;
            for (int i=0; i<timelines.size(); i++)
            {
                timelines[i]->fwd( lastStep );
            }
            lastMs = ofGetElapsedTimeMillis();
        }


        //--------------------------------------------------------------
        int calculateTickDuration()
        {
            // Translate tempo to milliseconds
            return (int)floor(60000.0000f / tempo);
        }


        void addTimeline( shared_ptr<Timeline>  _timeline){
            timelines.push_back( _timeline );
        }


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



#endif
