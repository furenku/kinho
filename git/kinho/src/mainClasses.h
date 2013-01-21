#pragma once

//#include "testApp.h"

#ifndef mainclasses_h
#define mainclasses_h

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
        virtual void execute() {
            for (int i=0; i<functors.size(); i++)
            {
            	functors[i]->execute();
            }
        }

        void addFunc(shared_ptr<Functor> _func) {
            functors.push_back(_func);
        }
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
        Observable(){ activeIndex = -1; value = 0; }

        virtual ~Observable(){

//            for (int i=0; i<listeners.size(); i++)
//                listeners[i]->logout(this);
        }

        virtual void addListener(shared_ptr<Observable>  _obs) {
            listeners.push_back(_obs);
        }

        virtual void removeListener(shared_ptr<Observable>  _obs) {

            vector<shared_ptr<Observable> >::iterator it;
            it = find(listeners.begin(),listeners.end(), _obs);
            if(it!=listeners.end())
                listeners.erase(it);
        }

        virtual void addObserved(shared_ptr<Observable>  _obs) {
            observed.push_back(_obs);
        }

        virtual void removeObserved(shared_ptr<Observable>  _obs) {
            vector<shared_ptr<Observable> >::iterator it;
            it = find(observed.begin(),observed.end(), _obs);
            if(it!=observed.end())
                observed.erase(it);
        }

        template <class Obs>
        void login( shared_ptr<Obs> _obs ) {
            vector< shared_ptr<ofEvent<widgetEvent> > > obsEvents = _obs->events.getValues();
            for (int j=0; j<obsEvents.size(); j++)
            {
                ofAddListener(*obsEvents[j],this,&Observable::execute);
            }
            _obs->addListener(shared_from_this());
            addObserved(_obs);
        }

        template <class Obs>
        void logout( shared_ptr<Obs> _obs ) {
            vector< shared_ptr<ofEvent<widgetEvent> > > obsEvents = _obs->events.getValues();
            for (int j=0; j<obsEvents.size(); j++)
            {
                ofRemoveListener( *obsEvents[j],this,&Observable::execute);
            }

            _obs->removeListener(shared_from_this());
            removeObserved(_obs);
        }

        template <class Obs>
        void login( vector<shared_ptr<Obs> > _obsvec ) {
            for (int i=0; i<_obsvec.size(); i++)
            {
                vector< shared_ptr<ofEvent<widgetEvent> > > obsEvents = _obsvec[i]->events.getValues();
                for (int j=0; j<obsEvents.size(); j++)
                {
                	ofAddListener( *obsEvents[j],this,&Observable::execute);
                }

                _obsvec[i]->addListener(shared_from_this());
                addObserved(_obsvec[i]);
            }
        }

        template <class Obs>
        void logout(vector<shared_ptr<Obs> > _obsvec) {
            for (int i=0; i<_obsvec.size(); i++)
            {
                vector< shared_ptr<ofEvent<widgetEvent> > > obsEvents = _obsvec[i]->events.getValues();
                for (int j=0; j<obsEvents.size(); j++)
                {
                	ofRemoveListener( *obsEvents[j],this,&Observable::execute);
                }

                _obsvec[i]->removeListener(shared_from_this());
                removeObserved(_obsvec[i]);
            }
        }

        virtual void execute( widgetEvent & event ){}

        virtual void addEvent( string _cmd, shared_ptr<ofEvent<widgetEvent> > _event ) {
            events.insert(_cmd, _event);
        }

        virtual void saveEvent(string _cmd){
            shared_ptr<ofEvent<widgetEvent> > event (new ofEvent<widgetEvent>);
            events.insert(_cmd, event );
        }

        virtual void notify(string _cmd) {
            shared_ptr<ofEvent<widgetEvent> > event = events.lookup(_cmd);
            if(!event) {
                saveEvent (_cmd);
                event = events.lookup(_cmd);
            }

            widgetEvent eventArgs;
            eventArgs.command = _cmd;
            eventArgs.sender = shared_from_this();
            ofNotifyEvent(*event,eventArgs,this);
        }


        int activeIndex;
        int value;
        string command;

        vector<shared_ptr<Observable> > listeners;
        vector<shared_ptr<Observable> > observed;

        Dictionary <string, ofEvent<widgetEvent> > events;


};






class MouseObject : public Object, public Observable  {
    public:
        MouseObject() {
            enable();

            isPressable = true; isSelectable = true; isDraggable = true;
            isDroppable                                     = false;
            isBeingDragged                                  = false;
            isMouseOn = false; hasBeenPressed = false; hasBeenDragged = false;

        }

        virtual ~MouseObject(){
            try {
            disable();
            } catch (Poco::SystemException) {
            return; // we're leaving anyways so no need to delete
            }

        }

        virtual void enable()  {
            ofRegisterMouseEvents(this);
            enabled = true;
        }
        virtual void disable()  {
            enabled = false;
            try {
	         ofUnregisterMouseEvents(this);
            } catch (Poco::SystemException) {
                return; // we're leaving anyways so no need to delete
            }
//
        }
        virtual void initialize()  {
            isMouseOn=hasBeenPressed=hasBeenDragged=false;
            enabled=true;
        }


        virtual void mouseMoved( ofMouseEventArgs & mouse ){}
        virtual void mousePressed( ofMouseEventArgs & mouse ){
            mouseClick.set(mouse.x,mouse.y);

            if(isMouseOn)   hasBeenPressed=true;
            else            hasBeenPressed=false;
        }

        virtual void mouseReleased( ofMouseEventArgs & mouse ){
            hasBeenPressed=false;
            hasBeenDragged=false;
            isBeingDragged=false;
        }
        virtual void mouseDragged( ofMouseEventArgs & mouse ){
            hasBeenDragged = true;
        }

        bool isPressable, isSelectable, isDraggable, isDroppable;
        bool isBeingDragged;
        bool isMouseOn,hasBeenPressed,hasBeenDragged;

        ofPoint mouseClick;


        virtual bool isEnabled() {
            return enabled;
        }


        bool enabled;

};






class DrawObject: public Object, public ofPoint {
    public:
        DrawObject(){ show();  }

        virtual ~DrawObject(){
            try {
                hide();
            } catch (Poco::SystemException) {
                return; // we're leaving anyways so no need to delete
            }

        }


        virtual void show()  {
            ofAddListener(ofEvents.draw, this, &DrawObject::draw);
            visible = true;
        }

        virtual void hide(){
            ofRemoveListener(ofEvents.draw, this, &DrawObject::draw);
            visible = false;
        }

        virtual void draw(ofEventArgs & args){

        }


        virtual void set (float px, float py, float pz=0){
        	pt.x    =   x		= px;
            pt.y    =   y		= py;
            z       = pz;
        }
        virtual void set (float px, float py, float w, float h){
        	pt.x    =   x		= px;
            pt.y    =   y		= py;
            wh.x    =   width	= w;
            wh.y    =   height	= h;

        }
		virtual void set (ofPoint pos, float w, float h){
			pt.x    =   x		= pos.x;
            pt.y    =   y		= pos.y;
            wh.x    =   width	= w;
            wh.y    =   height	= h;
		}

        virtual void setFromCenter (float px, float py){
            pt.x    =   x		= px - (width*0.5f);
            pt.y    =   y		= py - (height*0.5f);
        }
		virtual void setFromCenter (float px, float py, float w, float h){
            pt.x    =   x		= px - (w*0.5f);
            pt.y    =   y		= py - (h*0.5f);
            wh.x    =   width	= w;
            wh.y    =   height	= h;
        }
        virtual void setFromCenter (ofPoint pos, float w, float h){
            pt.x    =   x		= pos.x - w*0.5f;
            pt.y    =   y		= pos.y - h*0.5f;
            wh.x    =   width	= w;
            wh.y    =   height	= h;
        }
        virtual void setSize (float _size){
            wh.x    =   width = height = _size;
        }

        virtual void setSize (float _w, float _h){
            wh.x    =   width = _w;
            wh.y    =   height = _h;
        }

        virtual ofPoint getCenter (){
            return ofPoint(x + width * 0.5f, y + height * 0.5f, 0);
        }

        ofRectangle getRect() {
            ofRectangle rect;
            rect.x=x; rect.y=y; rect.width=width; rect.height=height;
            return rect;
        }

        float getX(){ return x; }
        float getY(){ return y; }
        float getWidth(){ return width; }
        float getHeight(){ return height; }

        void setX( float _x ){                set( _x,y,width,height ); }
        void setWidth( float _width ){        set( x,y,_width,height ); }
        void setY( float _y ){                set( x,_y,width,height ); }
        void setHeight( float _height ){      set( x,y,width,_height ); }

        virtual bool inside (float px, float py){}

        bool isVisible() {
            return visible;
        }


        bool visible;

        float width, height, r;

        ofVec2f pt, wh;


};









// controller:

class Controller: public Observable {

    public:
        Controller() {
            setup();
        }

        void setup() {

        }

        template <class Obs>
        void login( vector<Obs> _obsvec,
                    string _cmd,
                    shared_ptr<Functor> _func
        )
        {
            Observable::login( _obsvec );

            for (int i=0; i<_obsvec.size(); i++)
            	actionList.insert( make_pair(_obsvec[i],_cmd), _func );

        }

//        template <class Obs>
        void login( shared_ptr<Observable> _obs,
                    string _cmd,
                    shared_ptr<Functor> _func ) {
            Observable::login( _obs );
            actionList.insert( make_pair( _obs,_cmd), _func );
        }

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
        void logout(    shared_ptr<Obs> _obs, string _cmd ) {
            Observable::logout( _obs);
            actionList.erase( make_pair(_obs,_cmd) );
        }

        template <class Obs>
        void logout(    vector< ofEvent<widgetEvent> > _events,
                        vector<shared_ptr<Obs> > _obsvec, vector<string> _cmds )
        {
            Observable::logout( _obsvec );
            for (int i=0; i<_obsvec.size(); i++)
            {
//                actionList.erase( make_pair(_obsvec[i],_cmds[i] ) );
            }
        }

        void execute(widgetEvent & event) {
            cout << "controller->execute( "<< event.command <<" )" << endl;
            shared_ptr<Functor> func = actionList.lookup(
                        make_pair(
                            shared_ptr<Observable>(event.sender),
                            event.command
                        )
                    );
            if( func ){
                func->execute();
            }
            else
                cout<< "invalid cmd: " << event.command << endl;
        };

//    shared_ptr<Functor> func;
    Dictionary < pair <shared_ptr<Observable>,string>, Functor > actionList;

};




class Range{
    public:
        Range() {
            start=0; end=1; color=ofColor(0);
        }
        ~Range(){};

        float start;
        float end;
        ofColor color;

};




class Say: public Functor {

    public:
        Say( string _str ) { str = _str; }

        void execute() {   cout << str << endl;}

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
        Notify( shared_ptr<Observable> _src, string _str ) {
            src = _src;
            str = _str;
        }

        void execute() {   src->notify(str); }

        shared_ptr<Observable> src;
        string str;

};


#endif
