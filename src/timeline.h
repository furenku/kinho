
#pragma once


//#include "ontologies.h"
#include "mainClasses.h"
#include "baseGUIObjects.h"
#include "guiObjects.h"
#include "guiVideoObjects.h"
#include "views.h"


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

        shared_ptr<EventSource> getSource(){    return source;  }

        virtual void setSource( shared_ptr<EventSource> _source ){
            source = _source;
        }

        shared_ptr<EventSource> source;
};


class Person: public EventSource{
    public:
        Person(){ command = "carlos iv"; }


};
class NameSayer: public EventTarget {
    public:
        NameSayer(){}

        void happen(){
            if(source) {
                cout << "name is : "<< source->getCommand() << endl;
            }
        }
        void stop(){
            if(source) {
                cout << "stop : "<< source->getCommand() << endl;
            }
        }

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
        }

        void execute(){
            if(target) {
                if ( source ){
                    target->setSource( source );
                }
                target->happen();
            }
        }

        void stop(){
            if(target) {
                if ( source ){
                    target->setSource( source );
                }
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

};

class TimelineEvent: public Event{

 public:
    TimelineEvent(){}



    ofColor color;


};

class ControllerEvent: public Event{};

class TimelineEventWidget{

};

class TimelineWidget{

};





class Timeline: public DBManager, public EventSource, public EventTarget {

    public:
        Timeline(){
            init();
        }

        void init(){
            setMaxMs(60000);
            counter = 0;

//            shared_ptr<Ontology> ont = make_shared<Ontology>();
//            ont->setName("uncategorized");
//            addOntology(ont);


            iiinit();


        }


        void iiinit(){

            shared_ptr<TimelineEvent> hello, hello2;

            hello = make_shared<TimelineEvent>();
            hello2 = make_shared<TimelineEvent>();


            shared_ptr<Person>  person1 = make_shared<Person>();
            shared_ptr<Person>  person2 = make_shared<Person>();

            person2->setCommand("pedro reyes");

            shared_ptr<NameSayer> nameSayer = make_shared<NameSayer>();

            hello->setLoopTimes( 4 );
            nameSayer->setSource( person1 );
            hello->setTarget( nameSayer );

            hello2->setLoopTimes( 1 );
            hello2->setSource( person2 );
            hello2->setTarget( nameSayer );

            addEvent( hello, 3000 );
            addEvent( hello2, 16000 );

        }

        //funcs
            //API
            //add
                //media
        void addMedia(shared_ptr<MediaHolder> _media);
        void removeMedia(shared_ptr<MediaHolder> _media);

        //ontology
        void addOntology(shared_ptr<Ontology> _ont);
        void removeOntology(shared_ptr<Ontology> _ont);

        void addEvent( shared_ptr<TimelineEvent> _event, long _time ){
            events[ _time ] = _event;
        }

        void addEvent( shared_ptr<TimelineEvent> _event, shared_ptr<EventSource> _source, shared_ptr<EventTarget> _target ){
        }



        void fwd( int _ms ){
            shared_ptr < TimelineEvent > event;
            map < long, shared_ptr < TimelineEvent > >::iterator it;

            counter += _ms;
            counter %= maxMs;

            for( it = events.begin(); it != events.end(); ++it) {
                event = it->second;

                int loopCount = event->getLoopCount();

                long eventTime = long ( it->first );
                long eventDuration = long( event->getDuration() * 1000 );
                long eventTotalDuration = long( event->getTotalDuration() * 1000 );
//                cout << counter << "    :    " << eventTime <<  "  " << duration << "  " << totalDuration << endl;
                bool triggered = event->getTriggered();

                // if counter greater than event time but shorter than time + duration
                if( counter > eventTime && counter < eventTime + eventTotalDuration ) {
                    cout << ".";

                    // check if has been triggered
                    if( !triggered ){
                        // if not trigger it, which locks it from retriggering until it ends
                        event->trigger();
                        event->setLoopCount( loopCount + 1 );
                    }
                    else {
                        // if already triggered, find out if its 'duration' * 1000 has already ended
                        if( counter > eventTime + loopCount*eventDuration ){
                            // if so, free it
                            event->free();
                        }
                    }
                }
                else{
                    // if still locked, and its 'totalDuration' * 1000 has already ended, free it
                    if( triggered ){
                        event->free();
                        event->setLoopCount( 0 );

                    }
                }
            }

        }

        // get  / set{

        long getCounter(){  return counter;     }
        long getMaxMs(){    return maxMs;       }

        void setCounter(long _ms)   {   counter = _ms;  }
        void setMaxMs(long _ms)     {   maxMs = _ms;    }


        // }



//        //get
//        shared_ptr<MediaHolder> getMedia(string _name);
//        vector< shared_ptr<MediaHolder> > & getMedia();
//        vector< shared_ptr<MediaHolder> > getMedia(shared_ptr<Ontology>);
//
//        shared_ptr<Clip> getClip(string _name);
//        vector< shared_ptr<Clip> > & getClips();
//        vector< shared_ptr<Clip> > getClips(shared_ptr<Ontology>);
//
//        shared_ptr<Sample> getSample(string _name);getTotalDuration
//        vector< shared_ptr<Sample> > getSamples();
//        vector< shared_ptr<Sample> > getSamples(shared_ptr<Ontology>);
//
//        shared_ptr<Ontology> getOntology( shared_ptr<MediaHolder> );
//        shared_ptr<Ontology> getOntology( string name );
//        shared_ptr<Ontology> getOntology(int id);
//
//        vector< shared_ptr<Ontology> >  getOntologies(shared_ptr<MediaHolder>);
//        vector< shared_ptr<Ontology> >  getOntologies(string _type);
//        vector< shared_ptr<Ontology> >  getOntologies();

//    vector< shared_ptr < TimelineEventWidget > > eventWidgets;

    protected:
        long counter;
        long maxMs;

        map < long, shared_ptr<TimelineEvent> > events;

        shared_ptr<TimelineEvent> tmpevent;


        class TimelineWidget{

        };

//        vector< shared_ptr< MediaHolder > > media;
//        vector< shared_ptr< Clip > > clips;
//        vector< shared_ptr< Sample > > samples;
////        vector< shared_ptr< Text > > texts;
//
//        vector< shared_ptr< Tag > > tags;
//        vector< shared_ptr< Category> > categories;
//        vector< shared_ptr< OntologyObject > > ontObjects;
//        vector< shared_ptr< Place > > places;
//        vector< shared_ptr< Action> > actions;
//        vector< shared_ptr< Web> > webs;

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




#endif
