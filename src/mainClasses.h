#pragma once



#ifndef mainclasses_h
#define mainclasses_h


#include "ofMain.h"



#include <map>
#include <tr1/memory>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>



using boost::shared_ptr;
using boost::enable_shared_from_this;
using boost::dynamic_pointer_cast;
using boost::make_shared;





struct null_deleter
{
    void operator()(void const *) const
    {
    }
};



class Functor {
    public:
        virtual void execute() {};
        virtual ~Functor(){}
};


class FunctorHolder: public Functor {
    public:
        virtual void execute();

        void addFunc(shared_ptr<Functor> _func);

        vector< shared_ptr<Functor> > functors;
};

class Object {
    public:
        Object() {}
        virtual ~Object() {}

};



/*
template < typename ID, typename Type >
class Dictionary {
    public:
        typedef std::map<ID,Type> Map;

        Map dict;

	public:
	    Dictionary(){}
	    vector<ID> getKeys(){
            vector<ID> keys;
            typename Map::iterator pos;
            for (pos = dict.begin(); pos != dict.end(); ++pos)
                keys.push_back(pos->first);
            return keys;
	    }
        vector<Type> getValues(){
            vector<Type> values;
            typename Map::iterator pos;
            for (pos = dict.begin(); pos != dict.end(); ++pos)
                values.push_back(pos->second);
            return values;
	    }


        void insert( ID _id, Type _type) {
            dict.insert( make_pair( _id, _type ) );
        }

	    Type lookup( ID _id )
	    {
            typename std::map<ID, Type>::const_iterator iter;
	        iter = dict.find( _id );
	        if( iter != dict.end() )
	            return iter->second;
	        else
	            return NULL;
	    }

	    Type erase( ID _id )
	    {
	        typename std::map<ID, Type>::const_iterator iter;
	        iter = dict.find( _id );
	        if( iter != dict.end() )
	            delete iter->second;
            else
                cout << "cmd not found, nothing to delete" << endl;

            dict.erase( _id );

	    }

	    ~Dictionary()
        {
            while( dict.begin() != dict.end() )
            {
//                delete dict.begin()->second;
                dict.erase( dict.begin() );
            }
        }
};
*/



template < typename ID, typename Type >
class Dictionary {
    public:
        typedef std::multimap<ID,shared_ptr<Type> > Map;

        Map dict;

	public:
	    Dictionary(){}
	    vector<ID> getKeys(){
            vector<ID> keys;
            typename Map::iterator pos;
            for (pos = dict.begin(); pos != dict.end(); ++pos)
                keys.push_back(pos->first);
            return keys;
	    }
        vector<shared_ptr<Type> > getValues(){
            vector<shared_ptr<Type> > values;
            typename Map::iterator pos;
            for (pos = dict.begin(); pos != dict.end(); ++pos)
                values.push_back(pos->second);
            return values;
	    }


        void insert( ID _id, shared_ptr<Type> _type) {
            dict.insert( make_pair( _id, _type ) );
        }

	    shared_ptr<Type> lookup( ID _id )
	    {
            typename std::map<ID, shared_ptr<Type> >::const_iterator iter;
	        iter = dict.find( _id );
	        if( iter != dict.end() )
	            return iter->second;
	        else
	            return shared_ptr<Type>();
	    }

	    Type erase( ID _id )
	    {
//	        typename std::map<ID, Type>::const_iterator iter;
//	        iter = dict.find( _id );
//	        if( iter != dict.end() )
//	            delete iter->second;
//            else
//                cout << "cmd not found, nothing to delete" << endl;

            dict.erase( _id );

	    }

	    ~Dictionary()
        {
            while( dict.begin() != dict.end() )
            {
//                delete dict.begin()->second;
                dict.erase( dict.begin() );
            }
        }
};




class Observable;

class widgetEvent: public ofEventArgs {
  public:
    shared_ptr<Observable>   sender;
    string              command;
};





class Observable: public Object, public enable_shared_from_this<Observable> {

    public:
        Observable();

        virtual ~Observable();

        virtual void addListener(shared_ptr<Observable>  _obs);

        virtual void removeListener(shared_ptr<Observable>  _obs);

        virtual void addObserved(shared_ptr<Observable>  _obs);

        virtual void removeObserved(shared_ptr<Observable>  _obs);

        template <class Obs>
        void login( shared_ptr<Obs> _obs );

        template <class Obs>
        void logout( shared_ptr<Obs> _obs );

        template <class Obs>
        void login( vector<shared_ptr<Obs> > _obsvec );

        template <class Obs>
        void logout(vector<shared_ptr<Obs> > _obsvec);

        virtual void execute( widgetEvent & event );

        virtual void addEvent( string _cmd, shared_ptr<ofEvent<widgetEvent> > _event );

        virtual void saveEvent(string _cmd);

        virtual void notify(string _cmd) ;


        int activeIndex;
        int value;
        string command;

        vector<shared_ptr<Observable> > listeners;
        vector<shared_ptr<Observable> > observed;

        Dictionary <string, ofEvent<widgetEvent> > events;


};






class MouseObject : public Object, public Observable  {
    public:
        MouseObject();

        virtual ~MouseObject();

        virtual void enable();

        virtual void disable();

        virtual void initialize();


        virtual void mouseMoved( ofMouseEventArgs & mouse );

        virtual void mousePressed( ofMouseEventArgs & mouse );

        virtual void mouseReleased( ofMouseEventArgs & mouse );

        virtual void mouseDragged( ofMouseEventArgs & mouse );

        bool isPressable, isSelectable, isDraggable, isDroppable;
        bool isBeingDragged;
        bool isMouseOn,hasBeenPressed,hasBeenDragged;

        ofPoint mouseClick;


        virtual bool isEnabled();


        bool enabled;

};






class DrawObject: public Object, public ofPoint {
    public:
        DrawObject();

        virtual ~DrawObject();


        virtual void show();

        virtual void hide();

        virtual void draw(ofEventArgs & args);


        virtual void set (float px, float py, float pz);

        virtual void set (float px, float py, float w, float h);

        virtual void set (ofPoint pos, float w, float h);

        virtual void setFromCenter (float px, float py);

        virtual void setFromCenter (float px, float py, float w, float h);

        virtual void setFromCenter (ofPoint pos, float w, float h);

        virtual void setSize (float _size);

        virtual void setSize (float _w, float _h);

        virtual ofPoint getCenter ();

        ofRectangle getRect();

        float getX();
        float getY();
        float getWidth();
        float getHeight();
        float getActiveRange();

        void setX( float _x );
        void setWidth( float _width );
        void setY( float _y );
        void setHeight( float _height );
        void setActiveRange( float _range );

        virtual bool inside (float px, float py);
//        virtual bool inside (float px, float py, float pct);

        bool isVisible();


        bool visible;

        float width, height, r;

        ofVec2f pt, wh;

        float activeRange;


};









// controller:

class Controller: public Observable {

    public:
        Controller();

        void setup();

        template <class Obs>
        void login( vector<Obs> _obsvec,
                    string _cmd,
                    shared_ptr<Functor> _func
        );

//        template <class Obs>
        void login( shared_ptr<Observable> _obs,
                    string _cmd,
                    shared_ptr<Functor> _func );

/*  INTENTO FALLIDO DE MODULARIZAR _:/
        void loginCtls(
            vector<Observable*> _obsvec,
            vector<string>      _cmdvec,
            vector<Type>        _valvec,
            vector<Functor*>    _funcvec
        ){
            for (int j=0; j<_obsvec.size(); j++)
                valVec->push_back(*targetVal);
            for (int i=0; i<_obsvec.size(); i++)
            {

       ctl->login(
            ranges,
            commands[3]+ofToString(i),
            new Set <float*> (floatVec, &ranges[i]->clickPosition)
        );

            }


        }

*/

        template <class Obs>
        void logout(    shared_ptr<Obs> _obs, string _cmd );

        template <class Obs>
        void logout(    vector< ofEvent<widgetEvent> > _events,
                        vector<shared_ptr<Obs> > _obsvec, vector<string> _cmds );


        void execute(widgetEvent & event);

//    shared_ptr<Functor> func;
    Dictionary < pair <shared_ptr<Observable>,string>, Functor > actionList;

};




class Range{
    public:
        Range();

        ~Range();

        float start;
        float end;
        ofColor color;

};




class Say: public Functor {

    public:
        Say( string _str );

        void execute();

        string str;

};






template<typename type>
class Set: public Functor {

    public:
        Set( type _target, type _value ) {
            target = _target;
            value = _value;
        }

        Set( vector<type> _targets, type _value){
            targets = _targets;
            value = _value;

        }
        void execute() {

            if(targets.size()==0) { *target = *value; }
            for (int i=0; i<targets.size(); i++)
            {
            	if(targets[i])
                    *targets[i] = *value;
            }
        }

        vector <type> targets;
        type target;
        type value;

};

template<typename Type, class Source >
class SetInVector: public Functor {

    public:

        SetInVector( vector<Type> _targets, Source _source, Type _value){
            targets = _targets;
//            target = NULL;
            value = _value;
            if(_source)
                activeIndex = _source->activeIndex;
        }

        void execute() {
            if( activeIndex!=-1 && targets[activeIndex ] )
                *targets[activeIndex ] = *value;
        }

        vector <Type> targets;
        Type target;
        Type value;
        int activeIndex;

};

template<typename Type>
class SetPointer: public Functor {

    public:
        SetPointer( shared_ptr<Type> _src, shared_ptr<Type> _trgt ) {
            src = _src; trgt = _trgt;
        }

        void execute() {
            trgt = src;
        }

        shared_ptr<Type> src, trgt;

};


class Notify: public Functor {

    public:
        Notify( shared_ptr<Observable> _src, string _str );

        void execute();

        shared_ptr<Observable> src;
        string str;

};




#endif
