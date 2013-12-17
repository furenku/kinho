
#include "timeline.h"


//{ event classes


        EventSource::EventSource(){
            command = "eventsourcecommand";
        }

        string EventSource::getCommand(){
            return command;
        }

        void EventSource::setCommand( string _cmd ){
            command = _cmd;
        }





        Person::Person(){ command = "carlos iv"; }



        NameSayer::NameSayer(){}

        void NameSayer::happen(){
            cout << "name is : "<< name << endl;
        }
        void NameSayer::stop(){
            cout << "stop : "<< name << endl;
        }

        void NameSayer::setName( string _str ){
            name = _str;
        }




//    LogData::LogData(){}

    void LogData::setInt( string _key , int _value ){
        if( ints.find( _key ) != ints.end() ){
            ints[ _key ] = _value;
        }
        else
            cout << "int not in vector!" << endl;
    }
    void LogData::setFloat( string _key , float _value ){
        if( floats.find( _key ) != floats.end() ){
            floats[ _key ] = _value;
        }
        else
            cout << "float not in vector!" << endl;
    }
    void LogData::setString( string _key, string _value  ){
        if( strings.find( _key ) != strings.end() ){
            strings[ _key ] = _value;
        }
        else
            cout << "string not in vector!" << endl;
    }
    void LogData::setBool( string _key, bool _value  ){
        if( bools.find( _key ) != bools.end() ){
            bools[ _key ] = _value;
        }
        else
            cout << "bool not in vector!" << endl;
    }

    int LogData::getInt( string _key ){
        if( ints.find( _key ) != ints.end() ){
            return ints[ _key ];
        }
        else
        return -1;
    }
    float LogData::getFloat( string _key ){
        if( floats.find( _key ) != floats.end() ){
            return floats[ _key ];
        }
        else
        return -1;
    }
    string LogData::getString( string _key ){
        if( strings.find( _key ) != strings.end() ){
            return strings[ _key ];
        }
        else
        return "";
    }
    bool LogData::getBool( string _key ){
        if( bools.find( _key ) != bools.end() ){
            return bools[ _key ];
        }
        else
        return false;
    }





        Event::Event(){
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

        void Event::execute(){
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

        void Event::stop(){
            if(target) {
//                if ( source ){
//                    target->setSource( source );
//                }
                target->stop();
            }
        }

// setlooptimes -1 : inf
        void Event::trigger(){
            hasBeenTriggered=true;
            execute();
        }
        void Event::free(){
            hasBeenTriggered=false;
            stop();
        }

    //{ get / set

        float   Event::getDuration(){      return duration;            }
        float   Event::getLoopTimes(){     return loopTimes;           }
        int     Event::getLoopCount(){     return loopCount;           }
        float   Event::getTotalDuration(){ return totalDuration;       }
        bool    Event::getLoop(){          return loop;                }
        bool    Event::getTriggered(){     return hasBeenTriggered;    }
        shared_ptr<EventSource> Event::getSource(){ return source;     }
        shared_ptr<EventTarget> Event::getTarget(){ return target;     }
        shared_ptr<LogData> Event::getLogData(){ return logData; }


        void Event::setDuration( float _duration ) {
            duration = _duration;
            updateTotalDuration();
        }
        void Event::setLoopTimes( int _loopTimes) {
            loopTimes = _loopTimes;
            updateTotalDuration();
        }
        void Event::setLoopCount( int _loopCount) {
            loopCount = _loopCount;
        }
        void Event::setLoop( bool _loop ) {    loop = _loop;   }
        void Event::updateTotalDuration() { totalDuration = duration * loopTimes; }
        void Event::setSource( shared_ptr<EventSource> _source ) { source = _source;   }
        void Event::setTarget( shared_ptr<EventTarget> _target ) { target = _target;   }


    //}


        TimelineEvent::TimelineEvent(){
        }

        void TimelineEvent::setHasWidget(bool _hasWidget){
            hasWidget = _hasWidget;
        }
        bool TimelineEvent::getHasWidget(){ return hasWidget; }

        void TimelineEvent::setColor( shared_ptr<ofColor> _color){ color = _color; }
        shared_ptr<ofColor> TimelineEvent::getColor() { return color; }









        TimelineEventWidget::TimelineEventWidget(){
            autoArrange=false;
        }


        TimelineEventWidget::~TimelineEventWidget(){
            cout << "deleted event!" << endl;
        }
        void TimelineEventWidget::initialize(){
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

        void TimelineEventWidget::draw( ofEventArgs & args ){
            kRectView::draw(args);

        }

        void TimelineEventWidget::mouseReleased( ofMouseEventArgs & mouse){
            kDragObject::mouseReleased(mouse);
        }

        void TimelineEventWidget::mouseDragged( ofMouseEventArgs & mouse){
            kDragObject::mouseReleased(mouse);
        }





    void Log::addEntry(long _time, shared_ptr<LogData> _logData){
        events[_time] = _logData;
    }

    void Log::saveLog() {
     // iterate through all maps and print them on target
    }


//}


//{ timeline:

        Timeline::Timeline(){
            init();
        }

        void Timeline::init(){
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


        void Timeline::iiinit(){

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


        void Timeline::addEvent( shared_ptr<TimelineEvent> _event, long _time ){
            timelineEvents[ _time ] = _event;
        }

        void Timeline::addEvent( shared_ptr<TimelineEvent> _event, shared_ptr<EventSource> _source, shared_ptr<EventTarget> _target ){
        }


        void Timeline::addMarker( long _time, string _name ) {
            shared_ptr<TimelineMarker> marker = make_shared<TimelineMarker>();
            marker->setName(_name);
            timelineMarkers[ _time ] = marker;

        }

        void Timeline::addMarker( long _time, string _name, string _imgFile ) {

        }


        void Timeline::removeEvent( long _time ){
            // remove timelineEvents[ _time ] = _event;
        }

        void Timeline::fwd( int _ms ){

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
                if( scopeStart <= eventTime ) {
//                    cout << "before and scopestart : " <<  scopeStart << " time: " << eventTime << endl;
                }
                if( scopeStart > eventTime ) {


                    eventTriggerLogic( event );
                }


            }

        }



        void Timeline::eventTriggerLogic( shared_ptr < TimelineEvent > _event ){

            // if playHead greater than event time but shorter than time + duration
            if( scopeStart > eventTime && scopeStart < eventTime + eventTotalDuration ) {
//cout << "IN RANGE" << endl;
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

        void Timeline::triggerEvent( shared_ptr<TimelineEvent> _event){
            _event->trigger();
        }

        void Timeline::freeEvent( long _time,  shared_ptr < TimelineEvent > _event ){
            _event->free();
        }


        // get  / set{

        long Timeline::getTotalTime(){ return totalTime; }
        void Timeline::setTotalTime( long _ms ) { totalTime = _ms; }

        long Timeline::getPlayhead(){  return playHead;     }
        void Timeline::setPlayhead(long _ms)   {   playHead = _ms;  }

        void Timeline::setScope( long _start, long _end ) {
            scopeStart = _start;
            scopeEnd = _end;
        }
        void Timeline::setScopeStart( long _start ) { scopeStart = _start;    }
        void Timeline::setScopeEnd( long _end ) { scopeEnd = _end;    }
        long Timeline::getScopeStart() { return scopeStart; }
        long Timeline::getScopeEnd() { return scopeEnd; }
        long Timeline::getScopeLength() {
            long length = scopeEnd - scopeStart;
            if(length==0) length = 1;
            return length;
        }




        shared_ptr<Clip> Timeline::getNextPlayClip(){
            return nextPlayClip;
        };

        void Timeline::setNextClip(shared_ptr<Clip> _clip){
            nextClip = _clip;
        }




//}


//{ event classes 2

        ClipEvent::ClipEvent() { init(); saveEvent("playClip"); }


        void ClipEvent::trigger(){
            Event::trigger();
            playClip();

        }

        void ClipEvent::stop(){


            Event::stop();
        }

        void ClipEvent::draw( ofEventArgs & args){
            TimelineEventWidget::draw(args);
            ofSetColor(255);
            img.draw(x,y+(height-(height/1.77))/2,height,height/1.77);
        }

        void ClipEvent::setClip( shared_ptr<Clip> _clip ){
            clip = _clip;
            string filePath = _clip -> getFilename();

            string thumbPath = filePath.substr(0, filePath.find(".") )+".png";
            img.loadImage(thumbPath);
//            cout << "IMGPATH : " << thumbPath << endl;


        }
        shared_ptr<Clip> ClipEvent::getClip(){ return clip; }

        void ClipEvent::playClip(){
            notify("playClip");
            track->nextPlayClip = clip;
        }





        ChangeWindowEvent::ChangeWindowEvent() { init(); }

        void ChangeWindowEvent::trigger(){
            Event::trigger();
            setColor(ofRandomuf()*255,ofRandomuf()*255,ofRandomuf()*255);
        }

        void ChangeWindowEvent::stop(){
            Event::stop();
            setColor(0,0,0);
        }

        void ChangeWindowEvent::setColor( int _r, int _g, int _b ){
            cout << "changeWindow!!" << endl;
//            (testApp*)ofGetAppPtr() -> setColor(_r,_g,_b);
        }

//        shared_ptr<testApp> app;



//}


//{ TIMELINE TRACK


        TimelineTrack::TimelineTrack(){ init(); }

        void TimelineTrack::init() {
            Timeline::init();
            autoArrange = false;
            setTmpEvent(-1,-1);
            widgetUpdateCounter=0;
            saveEvent("playClip");
        }

        void TimelineTrack::update( ofEventArgs & args ){
            kRectView::update(args);
            adjustPreviousEventWidget();
        }

        void TimelineTrack::draw( ofEventArgs & args ){
            kRectView::draw(args);
            if(tmpEventStart>=0 && tmpEventEnd > 0 )
                ofRect( tmpEventStart * width, y, ( tmpEventEnd-tmpEventStart ) * width, y+height );

//            if(tmpMarkerStart>=0 && tmpMarkerEnd > 0 )
//                ofRect( tmpMarkerStart * width, y, ( tmpMarkerEnd-tmpMarkerStart ) * width, y+height );

            drawString(ofToString(scopeStart/1000),x-30,y-10);
//            for (iter = timelineEvents.begin(); iter != timelineEvents.end(); iter++) {
//                ofCircle( x+ timeToX(iter->first)*width, y + height /2 , 10 );
//            }

        }

        // { get  / set
        // get

        long TimelineTrack::getPlayHead(){ return playHead; }


        void TimelineTrack::fwd( int _ms ){
            Timeline::fwd(_ms);

            widgetUpdateCounter++;
            widgetUpdateCounter%=8;

            shared_ptr<ClipEvent> w;
            long time;
            float newX;

            ofRectangle rect;

            if( widgetUpdateCounter == 0 ) {

                for (iter = timelineEvents.begin(); iter != timelineEvents.end(); iter++) {

                    time = iter->first;
                    w.reset();
                    w = dynamic_pointer_cast<ClipEvent>( iter->second );
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
        void TimelineTrack::setDraggingEvent( shared_ptr<TimelineEvent> _event ){
            draggingEvent = _event;
        }


        //{ add / insert / remove events & markers

        void TimelineTrack::addEvent( shared_ptr<TimelineEvent > _event, long _time ){
//            long position = getNextPosition( _time, _event->getDuration() );
//            if(position>0)
//                timelineEvents[ position ] = _event;
                timelineEvents[ _time ] = _event;

        }


        void TimelineTrack::addEvent( float _x, float _y, shared_ptr<Clip> _clip ){
//
//                shared_ptr< ClipEvent >  event = make_shared<ClipEvent>( );
//
//                event->setClip ( _clip );
//                float duration;
//
//                duration = _clip->getDuration();
//
//                event->setDuration( duration  );
//
//                float timePct = getInRange( _x, x, x+width); // _time );
//                long timeMs = xToTime( _x );
//                long end =  timeMs + duration  * 1000 ;
//                float durPct = timeToX( end );
//
//                event -> set ( timePct , 0, durPct-timePct , 1 );
//
//                addWidget( event );
//
//                event->setLabel( ofToString(timeMs/1000) );
//
//                event -> initialize();
//
//                arrangeWidgets();
//                addEvent( event , timeMs );

        }

        void TimelineTrack::removeEvent( long _ms ){
            Timeline::removeEvent( _ms );
            // remove corresponding widget
        }


        long TimelineTrack::getNextPosition( long _time, long _duration ) {
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

        vector < shared_ptr <TimelineEvent> > TimelineTrack::getVisibleEvents(){
            selectEventsInTime( scopeStart, scopeEnd );
        }

        void TimelineTrack::makeMarker( long _ms ){

        }

        //}

        //{ widget logic:

        void TimelineTrack::selectEventsInTime(long _rangeStartMs, long _rangeEndMs ){
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
        void TimelineTrack::makeWidgets(){
            // get visible events
            selectEventsInTime( playHead, playHead + scopeEnd );
            // check which visible EventWidgets' events' times+dur are now out of scope, store them in deleteWidgets vector
            // check which visible events don't have a widget
            // make their widgets
            // set their hasWidget status
            // add listeners
        }
        void TimelineTrack::deleteWidgets(){
            // set their hasWidget status
            // remove listeners for eventWidget
            // remove Widget
        }

        void TimelineTrack::setTmpEvent( float _start, float _end ){
            tmpEventStart = timeToX( _start );
            tmpEventEnd = timeToX(_end );
        }

//        void TimelineTrack::setTmpMarker( float _start, float _end ){
//            tmpMarkerStart = timeToX( _start );
//            tmpMarkerEnd = timeToX(_end );
//        }

        void TimelineTrack::adjustPreviousEventWidget(){
        }

        //}



        // time / x conversion:

        long TimelineTrack::xToTime( float _x ){
            float pct = getInRange(_x, x,x+width);

            long time = ( pct * getScopeLength() ) + scopeStart;
            return time;
        }

        float TimelineTrack::timeToX( long _time ){
            float pct = float ( _time - scopeStart ) / float ( getScopeLength() );
            return pct;
        }

        // mouse
        void TimelineTrack::mousePressed(ofMouseEventArgs & mouse){

        }

        void TimelineTrack::mouseDragged(ofMouseEventArgs & mouse) {
            if( inside(mouse.x,mouse.y) ) {
                if( draggingEvent )
                    setTmpEvent( getNextPosition( xToTime(mouse.x), draggingEvent->getDuration() ), draggingEvent->getDuration() );
                    /* if( insertingEvent() )
                        tmpPushEvents( ? )
                        */
            }
        }

        void TimelineTrack::mouseReleased(ofMouseEventArgs & mouse) {
            if( inside(mouse.x,mouse.y) ) {
                if( draggingEvent )
                    addEvent( draggingEvent, xToTime( getInRange( mouse.x, x, x+width ) ) );
                else{
                    makeMarker( xToTime(mouse.x) );
                }
                if(nextClip){
                    shared_ptr< ClipEvent >  event = make_shared<ClipEvent>( );

                    event->setClip ( nextClip );
                    float duration;

                    duration = nextClip->getDuration();
                    event->setDuration( duration  );

                    float timePct = getInRange( mouse.x, x, x+width); // _time );
                    long timeMs = xToTime( mouse.x );
                    long end =  timeMs + duration  * 1000 ;
                    float durPct = timeToX( end );

                    event -> set ( timePct , 0, durPct-timePct , 1 );

                    addWidget( event );

                    event->setLabel( ofToString(timeMs/1000) );

                    event -> initialize();

                    event -> track = shared_from_this();

                    arrangeWidgets();
                    addEvent( event , timeMs );

                    nextClip.reset();
                }
            }
        }


        void TimelineTrack::eventTriggerLogic( shared_ptr < TimelineEvent > _event ){

            // if playHead greater than event time but shorter than time + duration
            if( scopeStart > eventTime && scopeStart < eventTime + eventTotalDuration ) {

                // check if has been triggered
                if( !eventTriggered ){
                    // if not trigger it, which locks it from retriggering until it ends
                    triggerEvent( dynamic_pointer_cast<ClipEvent>( _event ) );

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

        void TimelineTrack::triggerEvent( shared_ptr<ClipEvent> _event){
            dynamic_pointer_cast<ClipEvent>(_event)->trigger();
            notify("playClip");
        }

        void TimelineTrack::freeEvent( long _time, shared_ptr < TimelineEvent > _event ){
            cout << "endit!!!!!!!" << endl;
            _event->free();
            removeWidget( dynamic_pointer_cast< TimelineEventWidget > ( _event ) );
            timelineEvents.erase( _time );


        }

        //callback
        void TimelineTrack::eventWidgetDragged(widgetEvent & _event ){

            //if not on other event
                //setTmpEvent( long_start, long _end );
        }

        void TimelineTrack::eventWidgetReleased(widgetEvent & _event ){

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



        shared_ptr<TimelineTrack> TimelineTrack::shared_from_this()
        {
            return dynamic_pointer_cast<TimelineTrack>(kWidget::shared_from_this());
        }




//}


//{ TIMELINE VIEW


        TimelineView::TimelineView(){
            orientation="vertical";
            cols= 1;
            spacingX=40; spacingY=50;
            autoArrange=true;
        }

        void TimelineView::initialize() {
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


        void TimelineView::draw(ofEventArgs & draw){
            float playHeadPos = float( playHead ) / float ( getScopeLength() );

            ofSetColor(255,180,0);

            ofLine(x+playHeadPos*width,y,x+playHeadPos*width, y+height);
            ofSetColor(255);
        }


//}


//{ CLOCK MANAGER:

    //--------------------------------------------------------------
    ClockManager::ClockManager(){
        lastMs = 0;

        // Set up clock
        tempo = 6000.0f;
        clock.ticksPerBar = 1;
        clock.start(this);


    }


    //--------------------------------------------------------------
    void ClockManager::barDone() {
        lastStep = ofGetElapsedTimeMillis() - lastMs;
        for (int i=0; i<timelines.size(); i++)
        {
            timelines[i]->fwd( lastStep );
        }
        lastMs = ofGetElapsedTimeMillis();
    }


    //--------------------------------------------------------------
    int ClockManager::calculateTickDuration()
    {
        // Translate tempo to milliseconds
        return (int)floor(60000.0000f / tempo);
    }


    //--------------------------------------------------------------
    void ClockManager::addTimeline( shared_ptr<Timeline>  _timeline){
        timelines.push_back( _timeline );
    }


//}



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




