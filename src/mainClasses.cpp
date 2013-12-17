#include "mainClasses.h"


        void FunctorHolder::execute() {
            for (int i=0; i<functors.size(); i++)
            {
            	functors[i]->execute();
            }
        }

        void FunctorHolder::addFunc(shared_ptr<Functor> _func) {
            functors.push_back(_func);
        }


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


/*
//	    Dictionary::Dictionary(){}
	    vector<ID> Dictionary::getKeys(){
            vector<ID> keys;
            typename Map::iterator pos;
            for (pos = dict.begin(); pos != dict.end(); ++pos)
                keys.push_back(pos->first);
            return keys;
	    }
        vector<shared_ptr<Type> > Dictionary::getValues(){
            vector<shared_ptr<Type> > values;
            typename Map::iterator pos;
            for (pos = dict.begin(); pos != dict.end(); ++pos)
                values.push_back(pos->second);
            return values;
	    }


        void Dictionary::insert( ID _id, shared_ptr<Type> _type) {
            dict.insert( make_pair( _id, _type ) );
        }

	    shared_ptr<Type> Dictionary::lookup( ID _id )
	    {
            typename std::map<ID, shared_ptr<Type> >::const_iterator iter;
	        iter = dict.find( _id );
	        if( iter != dict.end() )
	            return iter->second;
	        else
	            return shared_ptr<Type>();
	    }

	    Type Dictionary::erase( ID _id )
	    {
//	        typename std::map<ID, Type>::const_iterator iter;
//	        iter = dict.find( _id );
//	        if( iter != dict.end() )
//	            delete iter->second;
//            else
//                cout << "cmd not found, nothing to delete" << endl;

            dict.erase( _id );

	    }

	    Dictionary::~Dictionary()
        {
            while( dict.begin() != dict.end() )
            {
//                delete dict.begin()->second;
                dict.erase( dict.begin() );
            }
        }



*/







        Observable::Observable(){ activeIndex = -1; value = 0; }

        Observable::~Observable(){

//            for (int i=0; i<listeners.size(); i++)
//                listeners[i]->logout(this);
        }

        void Observable::addListener(shared_ptr<Observable>  _obs) {
            listeners.push_back(_obs);
        }

        void Observable::removeListener(shared_ptr<Observable>  _obs) {

            vector<shared_ptr<Observable> >::iterator it;
            it = find(listeners.begin(),listeners.end(), _obs);
            if(it!=listeners.end())
                listeners.erase(it);
        }

        void Observable::addObserved(shared_ptr<Observable>  _obs) {
            observed.push_back(_obs);
        }

        void Observable::removeObserved(shared_ptr<Observable>  _obs) {
            vector<shared_ptr<Observable> >::iterator it;
            it = find(observed.begin(),observed.end(), _obs);
            if(it!=observed.end())
                observed.erase(it);
        }

        template <class Obs>
        void Observable::login( shared_ptr<Obs> _obs ) {
            vector< shared_ptr<ofEvent<widgetEvent> > > obsEvents = _obs->events.getValues();
            for (int j=0; j<obsEvents.size(); j++)
            {
                ofAddListener(*obsEvents[j],this,&Observable::execute);
            }
            _obs->addListener(shared_from_this());
            addObserved(_obs);
        }

        template <class Obs>
        void Observable::logout( shared_ptr<Obs> _obs ) {
            vector< shared_ptr<ofEvent<widgetEvent> > > obsEvents = _obs->events.getValues();
            for (int j=0; j<obsEvents.size(); j++)
            {
                ofRemoveListener( *obsEvents[j],this,&Observable::execute);
            }

            _obs->removeListener(shared_from_this());
            removeObserved(_obs);
        }

        template <class Obs>
        void Observable::login( vector<shared_ptr<Obs> > _obsvec ) {
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
        void Observable::logout(vector<shared_ptr<Obs> > _obsvec) {
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

        void Observable::execute( widgetEvent & event ){}

        void Observable::addEvent( string _cmd, shared_ptr<ofEvent<widgetEvent> > _event ) {
            events.insert(_cmd, _event);
        }

        void Observable::saveEvent(string _cmd){
            shared_ptr<ofEvent<widgetEvent> > event = make_shared< ofEvent<widgetEvent> >();
            events.insert(_cmd, event );
        }

        void Observable::notify(string _cmd) {
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








        MouseObject::MouseObject() {
            enable();

            isPressable = true; isSelectable = true; isDraggable = true;
            isDroppable                                     = false;
            isBeingDragged                                  = false;
            isMouseOn = false; hasBeenPressed = false; hasBeenDragged = false;

        }

        MouseObject::~MouseObject(){
            try {
            disable();
            } catch (Poco::SystemException) {
            return; // we're leaving anyways so no need to delete
            }

        }

        void MouseObject::enable()  {
            ofRegisterMouseEvents(this);
            enabled = true;
        }
        void MouseObject::disable()  {
            enabled = false;
            try {
	         ofUnregisterMouseEvents(this);
            } catch (Poco::SystemException) {
                return; // we're leaving anyways so no need to delete
            }
//
        }
        void MouseObject::initialize()  {
            isMouseOn=hasBeenPressed=hasBeenDragged=false;
            enabled=true;
        }


        void MouseObject::mouseMoved( ofMouseEventArgs & mouse ){
        }
        void MouseObject::mousePressed( ofMouseEventArgs & mouse ){
            mouseClick.set(mouse.x,mouse.y);

            if(isMouseOn)   hasBeenPressed=true;
            else            hasBeenPressed=false;
        }

        void MouseObject::mouseReleased( ofMouseEventArgs & mouse ){
            hasBeenPressed=false;
            hasBeenDragged=false;
            isBeingDragged=false;
        }
        void MouseObject::mouseDragged( ofMouseEventArgs & mouse ){
            hasBeenDragged = true;
        }


        bool MouseObject::isEnabled() {
            return enabled;
        }







        DrawObject::DrawObject(){ show(); setActiveRange(1.0f); }

        DrawObject::~DrawObject(){
            try {
                hide();
            } catch (Poco::SystemException) {
                return; // we're leaving anyways so no need to delete
            }

        }


        void DrawObject::show()  {
            ofAddListener(ofEvents.draw, this, &DrawObject::draw);
            visible = true;
        }

        void DrawObject::hide(){
            ofRemoveListener(ofEvents.draw, this, &DrawObject::draw);
            visible = false;
        }

        void DrawObject::draw(ofEventArgs & args){

        }


        void DrawObject::set (float px, float py, float pz=0){
        	pt.x    =   x		= px;
            pt.y    =   y		= py;
            z       = pz;
        }
        void DrawObject::set (float px, float py, float w, float h){
        	pt.x    =   x		= px;
            pt.y    =   y		= py;
            wh.x    =   width	= w;
            wh.y    =   height	= h;

        }
		void DrawObject::set (ofPoint pos, float w, float h){
			pt.x    =   x		= pos.x;
            pt.y    =   y		= pos.y;
            wh.x    =   width	= w;
            wh.y    =   height	= h;
		}

        void DrawObject::setFromCenter (float px, float py){
            pt.x    =   x		= px - (width*0.5f);
            pt.y    =   y		= py - (height*0.5f);
        }
		void DrawObject::setFromCenter (float px, float py, float w, float h){
            pt.x    =   x		= px - (w*0.5f);
            pt.y    =   y		= py - (h*0.5f);
            wh.x    =   width	= w;
            wh.y    =   height	= h;
        }
        void DrawObject::setFromCenter (ofPoint pos, float w, float h){
            pt.x    =   x		= pos.x - w*0.5f;
            pt.y    =   y		= pos.y - h*0.5f;
            wh.x    =   width	= w;
            wh.y    =   height	= h;
        }
        void DrawObject::setSize (float _size){
            wh.x    =   width = height = _size;
        }

        void DrawObject::setSize (float _w, float _h){
            wh.x    =   width = _w;
            wh.y    =   height = _h;
        }

        ofPoint DrawObject::getCenter (){
            return ofPoint(x + width * 0.5f, y + height * 0.5f, 0);
        }

        ofRectangle DrawObject::getRect() {
            ofRectangle rect;
            rect.x=x; rect.y=y; rect.width=width; rect.height=height;
            return rect;
        }

        float DrawObject::getX(){ return x; }
        float DrawObject::getY(){ return y; }
        float DrawObject::getWidth(){ return width; }
        float DrawObject::getHeight(){ return height; }
        float DrawObject::getActiveRange(){ return activeRange; }

        void DrawObject::setX( float _x ){                set( _x,y,width,height ); }
        void DrawObject::setWidth( float _width ){        set( x,y,_width,height ); }
        void DrawObject::setY( float _y ){                set( x,_y,width,height ); }
        void DrawObject::setHeight( float _height ){      set( x,y,width,_height ); }
        void DrawObject::setActiveRange( float _range ) { activeRange = _range; }


        bool DrawObject::isVisible() {
            return visible;
        }

//        bool DrawObject::inside (float px, float py){}

        bool DrawObject::inside (float px, float py){
            if(activeRange<1.0f){
                cout << "less than 1 <"<<activeRange << endl;
            }
            if( px > x+(width*(1-activeRange))/2 &&
                py > y+(height*(1-activeRange))/2 &&
                px < x+width-(width*(1-activeRange))/2 &&
                py < y + height-(height*(1-activeRange))/2  )
            {
//                cout << "INSIDDEEEE:::  "<<x << "AR" << activeRange << "  " << x+(width*(1-activeRange))/2 << endl;
                return true;
            } else {
                return false;
            }
        }







// controller:


        Controller::Controller() {
            setup();
        }

        void Controller::setup() {

        }

        template <class Obs>
        void Controller::login( vector<Obs> _obsvec,
                    string _cmd,
                    shared_ptr<Functor> _func
        )
        {
            Observable::login( _obsvec );

            for (int i=0; i<_obsvec.size(); i++)
            	actionList.insert( make_pair(_obsvec[i],_cmd), _func );

        }

//        template <class Obs>
        void Controller::login( shared_ptr<Observable> _obs,
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
        void Controller::logout(    shared_ptr<Obs> _obs, string _cmd ) {
            Observable::logout( _obs);
            actionList.erase( make_pair(_obs,_cmd) );
        }

        template <class Obs>
        void Controller::logout(    vector< ofEvent<widgetEvent> > _events,
                        vector<shared_ptr<Obs> > _obsvec, vector<string> _cmds )
        {
            Observable::logout( _obsvec );
            for (int i=0; i<_obsvec.size(); i++)
            {
//                actionList.erase( make_pair(_obsvec[i],_cmds[i] ) );
            }
        }

        void Controller::execute(widgetEvent & event) {
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




        Range::Range() {
            start=0; end=1; color=ofColor(0);
        }
        Range::~Range(){};








        Notify::Notify( shared_ptr<Observable> _src, string _str ) {
            src = _src;
            str = _str;
        }

        void Notify::execute() {   src->notify(str); }

