#include "baseGUIObjects.h"
#include <algorithm>

//------------------------------------------------------
//{ SETTINGS


void Settings::addFont(   shared_ptr<ofTrueTypeFont> _font,   shared_ptr<ofColor> _color ){
    font.push_back(_font);
    fontColor.push_back(_color);
}
void Settings::addColor(   shared_ptr<ofColor> _color ){
    color.push_back(_color);
}

shared_ptr<ofTrueTypeFont> Settings::getFont(int _index){
    if(font.size()>0)   return font[ _index % font.size() ];
    else                return make_shared<ofTrueTypeFont>();

}

shared_ptr<ofColor> Settings::getColor(int _index){
    if(color.size()>0)  return color[ _index % color.size() ];
    else                return make_shared<ofColor>(0,0,0);
}

//}


//------------------------------------------------------
//{KWIDGET

        kWidget::kWidget(){
            setupVars();
            enableUpdate();
        }
        kWidget::kWidget(  shared_ptr<Settings> _settings) {
            settings = _settings;
            setupVars();
            enableUpdate();
        }

        kWidget::~kWidget() {

//            tmpRect.reset();

//            cout << 1 << endl;
//            deletingWidgets = false;

//
            view.reset();
            clearWidgets();
            events.dict.clear();
//

            if(view)
                if(view->deletingWidgets==false)
                    view->removeWidget( shared_from_this());

            try {
                disableUpdate();
            } catch (Poco::SystemException) {
                return; // we're leaving anyways so no need to delete
            }
            try {
                hide();
            } catch (Poco::SystemException) {
                return; // we're leaving anyways so no need to delete
            }
            try {
                disable();
            } catch (Poco::SystemException) {
                return; // we're leaving anyways so no need to delete
            }
        }


        void kWidget::setupVars () {
            mouseX=0;mouseY=0;
            isDraggable = false;
            widgetSize= WIDGET_SIZE;
            createEvents();
            deletingWidgets = false;
            toggle = 0;
            value = 0;
            fvalue = 0;
            boolValue = 0;
            mode = TOGGLE_OFF;
            dragX = 0;
            dragY = 0;
            r = 0;
            maxChars = 25;
        }

        void kWidget::enableUpdate(){
            ofAddListener(ofEvents.update, this, &kWidget::update);

        }

        void kWidget::disableUpdate(){
            ofRemoveListener(ofEvents.update, this, &kWidget::update);
        }


        void kWidget::update(ofEventArgs & args){
            if(deleteObjects.size()>0) {
                for (int i=0; i<deleteObjects.size(); i++)
                {
                    deleteObjects[i]->disableUpdate();
                    deleteObjects[i]->hide();
                    deleteObjects[i]->disable();
                    deleteObjects[i]->removeFromView();
                    deleteObjects[i]->clearWidgets();
                    deleteObjects[i].reset();
                }
                deleteObjects.clear();
                arrangeWidgets();
            }

        }

        void kWidget::setLabel (string _label) {

//            _label.resize( maxChars );
//            cout << "MAXCHASRS -------------------: " << maxChars << endl;
            label=_label;
        }

        string kWidget::getLabel() { return label; }

        void kWidget::createEvents () {}

        void kWidget::draw() {}

        void kWidget::drawString(string _text, float _x, float _y) {

            if(settings) {
                vector<shared_ptr<ofTrueTypeFont > > fonts = settings->font;

                int index = find(fonts.begin(),fonts.end(),currentFont )-fonts.begin();

                if(index<fonts.size())
                ofSetColor(  *settings->fontColor[index] );
                if(currentFont){
                    currentFont->drawString(_text,_x,_y);
                }
            }
        }

        void kWidget::color(int _index){
            if(settings)
                if(settings->getColor( _index ))
                    ofSetColor( *(settings->getColor( _index )) );
        }

        void kWidget::font(int _index){
            if(settings)
                if(settings->getFont( _index )) {
                    currentFont = (settings->getFont( _index ));
                }
        }

        void kWidget::applySettings(   shared_ptr<Settings> _settings ) {
            settings = _settings;
            font(0);
        }

        void kWidget::setWidgetSettings( shared_ptr<Settings> _settings ) {
            widgetSettings = _settings;
        }

        void kWidget::mouseMoved( ofMouseEventArgs & mouse ){
            isMouseOn = inside(mouse.x,mouse.y);
            mouseX=mouse.x;
            mouseY=mouse.y;
        }

        void kWidget::mousePressed( ofMouseEventArgs & mouse ){
            if(isMouseOn) {
                hasBeenPressed=true;
                mouseClick.set(mouse.x-(x+width/2),mouse.y-(y+height/2));
                isBeingDragged=true;
            }
            else {
                isBeingDragged=false;
                hasBeenPressed=false;
            }

            mouseX=mouse.x;
            mouseY=mouse.y;
        }

        bool kWidget::mouseOnWidgets() {
            for (int i=0; i<widgets.size(); i++){
                if(widgets[i]->isMouseOn)
                    return true;
            }
            return false;
        };




        void kWidget::dropped( shared_ptr< kWidget > _widget ) {}

        void kWidget::setMode(kButtonMode _mode) {
            mode = _mode;
        }

        kButtonMode kWidget::getMode() {
            return mode;
        }

        ofPoint kWidget::getViewXY() {

            ofPoint point;
            if(view){
                float newX = ( x - view->x ) / ( view->width - view->x );
                float newY = ( y - view->y ) / ( view->height - view->y );
                point.set(newX, newY);
                return point;
            }
            else {
                point.set(0, 0);
                return point;
            }
        }


        void kWidget::addWidget( shared_ptr<kWidget> _widget   ) {
            widgets.push_back( _widget );
            if(widgetSettings) {
                _widget->applySettings( widgetSettings );
            }
            else if(settings) {
                _widget->applySettings( settings );
            }
            _widget->view=shared_from_this();
            ofRectangle tmpRect = _widget->getRect();

            widgetRects[_widget] =  tmpRect;

            if( !visible )
                _widget->hide();

            arrangeWidgets();

        }

        void kWidget::removeWidget( shared_ptr<kWidget> _widget   ) {

                _widget->hide();
                _widget->disable();
                _widget->disableUpdate();
                _widget->clearWidgets();
                _widget->view.reset();

                typedef vector< shared_ptr<kWidget> > widvec;
                typedef widvec::iterator iter;
                iter i = find(widgets.begin(),widgets.end(),_widget);
                if( i != widgets.end() ) {
                    widgetRects.erase( _widget );
                    widgets.erase( i );
                }

//                typedef vector< ofRectangle > rectvec;
//                typedef rectvec::iterator iterect;
//                iterect j = find(widgetRects.begin(),widgetRects.end(),_widget->getRectInView() );
//                if( j != .end() ) {
//                    widgetRects.erase( j );
//                }
                if(_widget->view){ _widget->removeFromView(); }
                addDelete(_widget);

        }

        void kWidget::removeFromView() {
            if(view){



                typedef vector< shared_ptr<kWidget> > widvec;
                typedef widvec::iterator iter;
                iter i = find(view->widgets.begin(),view->widgets.end(),shared_from_this());
                if( i != view->widgets.end() ) {
                    view->widgets.erase( i );
                    view->widgetRects.erase( shared_from_this() );
                }

/*
                typedef vector< ofRectangle > rectvec;
                typedef rectvec::iterator iterect;
                iterect j = find(view->widgetRects.begin(),view->widgetRects.end(),getRectInView() );
                if( j != view->widgetRects.end() ) {
                    view->widgetRects.erase( j );
                }
                view.reset();
*/
//                widgetRects.erase(widgetRects.begin()+index);
//                vector<shared_ptr<kWidget> >::iterator iter;
//                vector<ofRectangle >::iterator iter2;
//                iter = find( widgets.begin(), widgets.end(), shared_from_this() );
//                iter2 = find( widgetRects.begin(), widgetRects.end(), getRectInView() );
//                widgets.erase( iter );
//                widgetRects.erase( iter2 );

            }
        }


        void kWidget::arrangeWidgets() {}


        void kWidget::clearWidgets() {
            deletingWidgets = true;
            for (int i=0; i<widgets.size(); i++)
            {
            	removeWidget(widgets[i]);
            }
            widgets.clear();
            widgetRects.clear();
        }

        vector< shared_ptr < kWidget > > & kWidget::getWidgets(){
            return widgets;
        }

        shared_ptr<kWidget> kWidget::getFirstView(){
            if(view)
                return view->getFirstView();
            else
                return shared_from_this();
        }

        int kWidget::getWidgetIndex( shared_ptr<Observable> _obs ) {
            int index = -1;

            for (int i=0; i<widgets.size(); i++) {
                if( _obs==widgets[i])
                {
                    index = i;
                    break;
            	}
            }

            return index;

        }

        int kWidget::getIndexInView(){
            int  index =    find(   view->widgets.begin(),
                                    view->widgets.end(),
                                    shared_from_this() )
                            - view->widgets.begin();
            return index;
        }

        void kWidget::setRectInView(){
            int index = getIndexInView();    ;
            ofRectangle rect = getRectInView();
            view->widgetRects[ shared_from_this() ] = rect;
        }

        void kWidget::setRectInViewNoArrange(){
            ofRectangle rect = ofRectangle(x,y,width,height);
            view->widgetRects[ shared_from_this() ] = rect;
        }


        ofRectangle kWidget::getRectInView() {

            if(view) {
                ofRectangle tmpRect;
                tmpRect.x=(x-view->x)/view->width;
                tmpRect.y=(y-view->y)/view->height;
                tmpRect.width=(width/view->width);
                tmpRect.height=(height/view->height);
                return tmpRect;

            }


        }

        void kWidget::addDelete( shared_ptr<kWidget> _widget ){
            deleteObjects.push_back(_widget);
        }



        shared_ptr<kWidget> kWidget::shared_from_this()
        {
                return dynamic_pointer_cast<kWidget>(Observable::shared_from_this());
        }


        bool kWidget::getToggle(){ return toggle; }
        int kWidget::getValue() {return value;}

        float kWidget::getMouseX(){ return mouseX; }
        float kWidget::getMouseY(){ return mouseY; }




//}


//------------------------------------------------------
//{KRECT & KCIRCLE:


        void kRect::draw(ofEventArgs & draw){
            ofRect(x,y,width,height);
        }



        void kCircle::set (float _x, float _y, float _w, float _h){
        	x		= _x;
            y		= _y;
            wh.x = wh.y = r = _w; width = _w; height = _w;

        }
		void kCircle::set (ofPoint pos, float w){
			pt.x    =   x		= pos.x;
            pt.y    =   y		= pos.y;
            wh.x = wh.y = width = height = r = w;
		}

        void kCircle::setFromCenter (float _x, float _y){
            pt.x    =   x		= _x;
            pt.y    =   y		= _y;
        }

        void kCircle::setFromCenter (float _x, float _y, float w, float h){
            pt.x    =   x		= _x;
            pt.y    =   y		= _y;
            wh.x = wh.y = r = height = width   = w;
        }

        void kCircle::setSize (float _size){
           wh.x = wh.y = r =  width = height = _size;
        }

        ofPoint kCircle::getCenter (){
            return ofPoint(x, y, 0);
        }

        bool kCircle::inside (float px, float py){
            isMouseOn = getDistance(x,y,px,py) < r;
        }

        void kCircle::mouseMoved( ofMouseEventArgs & mouse ){
            isMouseOn=(getDistance(mouse.x, mouse.y, x, y) < r );
        }
        void kCircle::draw(ofEventArgs & draw){
            ofCircle(x,y,width/2);
        }


//}


//------------------------------------------------------
//{KDRAGOBJECT & KDRAGSINK




        kDragObject::kDragObject(){
            sourceX = 0;
            sourceY = 0;

            createEvents();
            hasBeenMadeDroppable = true;
            isMouseOn=false;
        }

        void kDragObject::createEvents() { saveEvent("drag");  }

        void kDragObject::mouseDragged( ofMouseEventArgs & mouse ){

            if(isMouseOn) {
                if(!hasBeenDragged) {
                    sourceX = mouse.x;
                    sourceY = mouse.y;
                }
                isBeingDragged=true;
                hasBeenDragged=true;
                if(isDraggable) {

                    x = mouse.x;
                    y = mouse.y;

                    arrangeWidgets();
                }

                if(isDroppable) {
                    dragX = mouse.x - mouseClick.x - (width/2);
                    dragY = mouse.y - mouseClick.y - (height/2);
                }

//                getFirstView()->draggingWidget = shared_from_this();

                arrangeWidgets();


            }

            if(isBeingDragged) notify("drag");

            mouseX = mouse.x;
            mouseY = mouse.y;
        }



        void kDragObject::mouseReleased( ofMouseEventArgs & mouse){

            if(hasBeenDragged )
                setRectInView();
            MouseObject::mouseReleased(mouse);

            sourceX = mouse.x;
            sourceY = mouse.y;
            mouseX = mouse.x;
            mouseY = mouse.y;
        }

        void kDragObject::makeDroppable(float _x, float _y) {
            hasBeenMadeDroppable = true;
            x = sourceX;
            y = sourceY;
            isDraggable = false;
            isDroppable = true;
            dragX = _x;
            dragY = _y;

        }

        void kDragObject::makeDraggable(float _x, float _y) {
            hasBeenMadeDroppable = false;
            dragX = sourceX = _x;
            dragY = sourceY = _y;
            isDraggable = true;
            isDroppable = false;
        }

        shared_ptr<kDragObject> kDragObject::shared_from_this()
        {
            return dynamic_pointer_cast<kDragObject>(Observable::shared_from_this());
        }


        kDragSink::kDragSink(){ createEvents(); }

        void kDragSink::createEvents(){ saveEvent("release"); }

        void kDragSink::mouseReleased(ofMouseEventArgs & mouse) {
            if(inside(mouse.x,mouse.y)) {
                notify("release");
            }

        }


//}


//------------------------------------------------------
//{ BUTTONS:


        kButton::kButton() { value = 0; toggle = false; createEvents(); }

        void kButton::createEvents() { saveEvent("press"); }

        void kButton::mouseReleased( ofMouseEventArgs & mouse ){
            if(!hasBeenDragged) {
                if( isMouseOn ){
                    pressed();
                    if(mode == TOGGLE_ON)  toggle=!toggle;
                    notify("press");
                }
                else {
                    pressedOut();
                }
            }

            kWidget::mouseReleased(mouse);


        }

        void kButton::pressed() {}
        void kButton::pressedOut() {}

        void kButton::draw( ofEventArgs & args ){
            if(isMouseOn)   color(1);
            else            color(0);

            if(mode==TOGGLE_ON)
                if(toggle)  ofFill();
                else        ofNoFill();

            ofColor(255);

            drawString(label,getCenter().x-width/2,getCenter().y-height*0.75f);


        }



        kRectButton::kRectButton(){ }

        void kRectButton::draw( ofEventArgs & args ){
            kButton::draw(args);
            ofRect(x,y,width,height);
        }


        void kCircleButton::draw( ofEventArgs & args ){
            kButton::draw(args);
            ofCircle(x,y,r/2);
            ofNoFill();
        }




        void kLabelButton::setLabel( string _label ){

            int charCount=  0;
            int maxChars2 = 7;
            int len = _label.size();
            for (int i = 0; i < len; i++){
                charCount++;
                if( charCount>=maxChars2 && _label[i] == ' ' ){
                    _label.insert(i," \n");
                    charCount=0;
                }

            }
//            replace(_label.begin(), _label.end(), ' ', '\n');
            kWidget::setLabel(_label);
        }


        void kLabelButton::draw( ofEventArgs & args ){
            color(0);
            if(mode==TOGGLE_ON)
                if(toggle)  ofFill();
                else        ofNoFill();

            ofRectangle rect = settings->font.back()->getStringBoundingBox(label,x,y);

            if(isMouseOn)   color(155);
            else            color(50);
            ofRect(x,y,width,height);
            ofNoFill();

            drawString(label,getCenter().x-rect.width/3,getCenter().y );
//            ofDrawBitmapString(label,getCenter().x-width/3,getCenter().y );

        }



        kRectDragButton::kRectDragButton();

        void kRectDragButton::createEvents() {
            kRectButton::createEvents();
            kDragObject::createEvents();
        }


        void kRectDragButton::mouseReleased( ofMouseEventArgs & mouse){
            kRectButton::mouseReleased(mouse);
        }






        kCircleDragButton::kCircleDragButton(){ createEvents(); }

        void kCircleDragButton::createEvents() {
            kCircleButton::createEvents();
            kDragObject::createEvents();
        }

        void kCircleDragButton::mouseReleased( ofMouseEventArgs & mouse){
            kCircleButton::mouseReleased(mouse);
        }



//}







//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------




//{ KRANGE HOLDERS:

//---------------------------------------width-----------------------
// this class is a circular range with a start and ending point
// that can be dragged
//--------------------------------------------------------------







//        timeEvent::timeEvent(){ position = 0; }

//        void timeEvent::draw(ofEventArgs & args) {}



        kRangeHolder::kRangeHolder(){
            createEvents();
            start = -1;
            end = -1;
            playHead=targetPlayHead=0;
            inOrOut=false;
            setInOut = true;
            clickPosition = 0.0f;
            draggingPoint = 0;
            startPos = 0;
            endPos = 1;
//            currentRange = NULL;
        }

        void kRangeHolder::createEvents() {
            saveEvent("start");
                saveEvent("end");
                    saveEvent("in");
                        saveEvent("out");
        }


        void kRangeHolder::execute(widgetEvent & _event) {
            if(observed.back()) {
                ranges.clear();
//                ranges=dynamic_pointer_cast<Clip>(_event.sender)->ranges;
            }
        }

        void kRangeHolder::setStart ( float _val) {
            start = _val;
        }

        void kRangeHolder::setEnd ( float _val ) {
            end = _val;
        }

        void kRangeHolder::addRange( shared_ptr<Range> _range ) {
            ranges.push_back(_range);
            currentRange = ranges.back();
        }

//        float kRangeHolder::getMousePos(ofMouseEventArgs & mouse) {}

        void kRangeHolder::mousePressed(ofMouseEventArgs & mouse)    {
            kWidget::mousePressed(mouse);
            float distance;
            float pos = getMousePos(mouse);
            clickPosition = pos;
            if(isMouseOn) {
                if(ranges.size()>0) {

                    draggingPoint = &ranges[0]->start;
                    draggingRange = ranges[0];
                    activeIndex=0;
                    distance = fabs( ranges[0]->start - pos );

                    for (int i=0; i<ranges.size(); i++)
                    {
                        if( fabs( ranges[i]->start - pos ) < distance ) {
                            draggingPoint = &ranges[i]->start;
                            draggingRange = ranges[i];
                            activeIndex=i;
                            distance = fabs( ranges[i]->start - pos );
                        }

                        if( fabs( ranges[i]->end - pos ) < distance ) {
                            draggingPoint = &ranges[i]->end;
                            draggingRange = ranges[i];
                            activeIndex=i;
                            distance = fabs( ranges[i]->end - pos );
                        }

                    }
                }
            }
        }

        void kRangeHolder::mouseDragged(ofMouseEventArgs & mouse)  {
            if(isBeingDragged)    {
                hasBeenDragged=true;

                float pos=getMousePos(mouse);
                clickPosition=pos;

                if(draggingRange) {
                    startPos = draggingRange->start;
                    endPos   = draggingRange->end;


                    if( fabs( startPos - pos ) < fabs( endPos - pos ) ) {
                        draggingRange->start = pos;
                        notify("start");
                    }
                    else    {
                        draggingRange->end = pos;
                        notify("end");

                    }
                }
            }

        }

        void kRangeHolder::mouseReleased(ofMouseEventArgs & mouse)  {

            if(isMouseOn)
                if(!hasBeenDragged) {
                    if(setInOut) {
                        if(inOrOut==0)
                            notify("in");
                        else if(inOrOut==1)
                            notify("out");
                }
            }

            activeIndex = -1;

            hasBeenDragged=false;

            kWidget::mouseReleased(mouse);


        }

/*
        void kRangeHolder::addTimeEvent( shared_ptr<timeEvent> _event ) {
            timeEvents.push_back(_event);
        }
*/






//    kRectTool::kRectTool(){  }

    //{ functions:

    void kRectTool::draw( ofEventArgs & args ){
        color(1);
        float pos = playHead;
        ofLine( x+(pos*width), y, x+(pos*width), y+height );
        color(1);
        if(isMouseOn) {
            pos = targetPlayHead;
            ofLine( x+(pos*width), y, x+(pos*width), y+height );
        }
/*
        for (int i=0; i<timeEvents.size(); i++)
        {
            pos = timeEvents[i]->position;
            ofLine( x+(pos*width), y, x+(pos*width), y+height );

        }

*/
        //{ draw start end points
        if(start!=-1) {
            pos = start;
            ofLine( x+(pos*width), y, x+(pos*width), y+height );
            ofDrawBitmapString("start", x+(pos*width), y );
        }

        if(end!=-1) {
            pos = end;
            ofLine( x+(pos*width), y, x+(pos*width), y+height );
            ofDrawBitmapString("end", x+(pos*width), y );
        }

    //}

        //{ draw selector:

        color(0);

        ofRect(x,y,width,height);

        for (int i=0; i<ranges.size(); i++)
        {
            ofSetColor(ranges[i]->color);

        	startPos  = ranges[i]->start*width;
        	endPos    = ranges[i]->end*width-startPos;

        	ofRect( x + startPos,y,endPos,height);
        }
        //}

    }

    float kRectTool::getMousePos(ofMouseEventArgs & mouse) {
        float position=(mouse.x-x)/width;
        return position;
    }


    void kRectTool::mouseMoved(ofMouseEventArgs & mouse)    {

        kRect::mouseMoved(mouse);

        if(isMouseOn)
            targetPlayHead = (mouse.x-x)/width;


    }



    void kRectTool::mouseReleased(ofMouseEventArgs & mouse)  {
        if( isMouseOn && !hasBeenDragged )
            clickPosition = getMousePos(mouse);
        kRangeHolder::mouseReleased(mouse);
    }








//    kCircleTool::kCircleTool() { thickness = WIDGET_SIZE /2; }




    void kCircleTool::draw( ofEventArgs & args ){
        thickness = width/3;

        color(1);

        float angle = (TWO_PI/360)*(playHead*360);
        ofLine(
            x+(cos(angle)*width),
            y+(sin(angle)*width),
            x+(cos(angle)*(width+thickness)),
            y+(sin(angle)*(width+thickness))
        );
        color(1);
        if(isMouseOn){
            float angle = (TWO_PI/360)*(targetPlayHead*360);
            ofLine(
                x+(cos(angle)*width),
                y+(sin(angle)*width),
                x+(cos(angle)*(width+thickness)),
                y+(sin(angle)*(width+thickness))
            );
        }
/*
        for (int i=0; i<timeEvents.size(); i++)
        {
            angle = (TWO_PI/360)*(timeEvents[i]->position*360);

        	ofLine(
                x+(cos(angle)*width),
                y+(sin(angle)*width),
                x+(cos(angle)*(width+thickness)),
                y+(sin(angle)*(width+thickness))
            );
        }
*/

        //{ draw start end points
        if(start!=-1) {
            angle = (TWO_PI/360)*(start*360);

        	ofLine(
                x+(cos(angle)*width),
                y+(sin(angle)*width),
                x+(cos(angle)*(width+thickness*2)),
                y+(sin(angle)*(width+thickness*2))
            );
            ofDrawBitmapString("start",
                x+(cos(angle)*(width+thickness*2)),
                y+(sin(angle)*(width+thickness*2))
            );
        }

        if(end!=-1) {
            angle = (TWO_PI/360)*(end*360);

        	ofLine(
                x+(cos(angle)*width),
                y+(sin(angle)*width),
                x+(cos(angle)*(width+thickness*2)),
                y+(sin(angle)*(width+thickness*2))
            );
            ofDrawBitmapString("end",
                x+(cos(angle)*(width+thickness*2)),
                y+(sin(angle)*(width+thickness*2))
            );
        }

    //}

        //{ draw selector:


        color(0);

        ofCircle(x,y,width);
        ofCircle(x,y,width+thickness);

        float angleStep = TWO_PI / 360.0f;

        glPushMatrix();     glTranslatef(x,y,0);

        ofSetPolyMode(OF_POLY_WINDING_ODD);

        for (int i=0; i<ranges.size(); i++)
        {

            ofSetColor(ranges[i]->color);


        	startPos  = ranges[i]->start * 360;
        	endPos    = ranges[i]->end * 360;

        	ofBeginShape();
                ofVertex(width*cos(startPos*angleStep),width*sin(startPos*angleStep));
                    for (int j = startPos; j <= endPos; j++){
                        float anglef = j*angleStep;
                        float vx = width* cos(anglef);
                        float vy = width * sin(anglef);
                        ofVertex(vx,vy);
                    }
                    width+=thickness;
                    for (int j = endPos; j >= startPos; j--){
                        float anglef = j*angleStep;
                        float vx = width * cos(anglef);
                        float vy = width * sin(anglef);
                        ofVertex(vx,vy);
                    }
                    width-=thickness;
                ofVertex(width*cos(startPos*angleStep),width*sin(startPos*angleStep));
            ofEndShape(OF_CLOSE);


        }

        glPopMatrix();




        //}

    }


    void kCircleTool::mouseMoved(ofMouseEventArgs & mouse)    {

        int d = getDistance(x,y,mouse.x,mouse.y);

        if(d>width&&d<(width+thickness))    isMouseOn=true;
        else                                isMouseOn=false;

        if(isMouseOn)
            targetPlayHead = getAngle(mouse.x,mouse.y,x,y)/360.0f;

    }

    float kCircleTool::getMousePos(ofMouseEventArgs & mouse) {
        float position=getAngle(mouse.x,mouse.y,x,y)/360.0f;
        return position;
    }


    void kCircleTool::mouseReleased(ofMouseEventArgs & mouse)  {
        if( isMouseOn && !hasBeenDragged ) {
            clickPosition = getMousePos(mouse);
        }
        kRangeHolder::mouseReleased(mouse);
    }




//}

//}

//------------------------------------------------------
//{ VIEWS:



    kView::kView(){
        isDraggable=true; autoArrange=true;
        orientation="horizontal";

        spacingX = SPACING_X;
        spacingY = SPACING_Y;
        paddingX = spacingX; paddingY = spacingY;
        cols = MAX_COLS;
        rows = 1;

        scrollX = 0;
        scrollY = 0;

    }


    void kView::show(){
        DrawObject::show();
        for (int i=0; i < widgets.size(); i++)
        	if( !widgets[i] -> isVisible() )
                widgets[i] -> show();
    }

    void kView::hide(){
        DrawObject::hide();
        for (int i=0; i<widgets.size(); i++)
        	if( widgets[i] -> isVisible() )
                widgets[i] -> hide();
    }

    void kView::enable(){
        MouseObject::enable();
        for (int i=0; i < widgets.size(); i++)
        	if( !widgets[i] -> isEnabled() )
                widgets[i] -> enable();
    }

    void kView::disable(){
        MouseObject::disable();
        for (int i=0; i<widgets.size(); i++)
        	if( widgets[i] -> isEnabled() )
                widgets[i] -> disable();
    }

    void kView::arrangeWidgets() {

         for (int i=0; i<widgets.size(); i++) {
            if(autoArrange) {
                widgets[i] -> setFromCenter( getGridX(i), getGridY(i) );
            }
            else {

                widgets[i] -> set(
                    x + widgetRects[widgets[i]].x*width,
                    y + widgetRects[widgets[i]].y*height,
                    widgetRects[widgets[i]].width*width,
                    widgetRects[widgets[i]].height*height
                );
            }
         if(!visible) widgets[i]->hide();

            widgets[i]->arrangeWidgets();
         }

    }


    void kView::mouseDragged( ofMouseEventArgs & mouse ){
        bool widgetDragged=false;

        for (int i=0; i < widgets.size(); i++)
        {
        	if( widgets[i]->hasBeenPressed )
        	{
        	    widgetDragged = true;

        	    break;

        	}
        }

        if(!widgetDragged) {
            if(isBeingDragged) {
                kWidget::mouseDragged(mouse);
                for (int i=0; i < widgets.size(); i++)
                    widgets[i]->mouseDragged(mouse);
                arrangeWidgets();
            }
        }

        mouseX = mouse.x;
        mouseY = mouse.y;

    }


//    shared_ptr<kView> shared_from_this()
//    {
//            return boost::dynamic_pointer_cast<kView>(Observable::shared_from_this());
//    }



    void kView::setAutoArrange( bool _autoArrange ){ autoArrange = _autoArrange; }

    void kView::setOrientation(string _orientation) {
        orientation = _orientation;
    }


    float kView::getGridX( int _i ) {}
    float kView::getGridY( int _i ) {}
    ofPoint kView::getGridXY( int _position ) {}


    float kView::getScrollX()  {
        return scrollX;
    }
    float kView::getScrollY() {
        return scrollY;
    }


    void kView::setCols(int _cols) { cols = _cols; }
    void kView::setRows(int _rows) { rows = _rows; }
    int kView::getCols() { return cols; }
    int kView::getRows() { return rows; }

    void kView::setSpacingX(int _spacingX) { spacingX = _spacingX; }
    void kView::setSpacingY(int _spacingY) { spacingY = _spacingY; }
    int kView::getSpacingX() { return spacingX; }
    int kView::getSpacingY() { return spacingY; }

    void kView::setPaddingX(int _paddingX) { paddingX = _paddingX; }
    void kView::setPaddingY(int _paddingY) { paddingY = _paddingY; }
    int kView::getPaddingX() { return paddingX; }
    int kView::getPaddingY() { return paddingY; }
//
//    ofRectangle kView::getWidgetRect( shared_ptr<kWidget>  _w ){
//
//            typedef vector< shared_ptr<kWidget> > widvec;
//            typedef widvec::iterator iter;
//            iter i = find(widgets.begin(),widgets.end(),_widget);
//            if( i != widgets.end() ) {
//                ofRectangle tmpRect( (i->getX()-x-scrollX)/width, (i->getY()-y-scrollY)/height,
//                    i->getWidth() / width, i->getHeight() / height );
//                return tmpRect;
//            }
//            else {
//                return ofRectangle();
//            }
//
//    }






        kRectView::kRectView(){
            rows=1; cols = MAX_COLS;
            spacingX=SPACING_X; spacingY = SPACING_Y;
        }


        float kRectView::getGridX( int _i ) {

            if(orientation=="horizontal") {
                if(width>0){


                    float newX=0;
                    float totalWidth=0;

                    for (int i=0; i<widgets.size(); i++)
                    	if(widgets[i]->width>spacingX)
                            totalWidth+=widgets[i]->width;
                        else
                            totalWidth+=spacingX;

                    for (int i=0; i<_i; i++)
                        if(widgets[i]->width>spacingX)
                            newX+=widgets[i]->width;
                        else
                            newX+=spacingX;


                    float offsetX = (width - totalWidth)/2;

                    newX +=  (x + offsetX)+widgets[_i]->width/2;

                    return newX;

                }
                else {
                    cout << "view has 0 w" << endl;
                    return 0;
                }
            }
            else{
                return x + width*0.5f;
            }
        }


        float kRectView::getGridY( int _i ) {
            if(orientation=="horizontal") {
                return y + height*0.5f;
            }
            else {

                if(height>0){

                    float newY=0;
                    float totalHeight=0;

                    for (int i=0; i<widgets.size(); i++)
                    	if(widgets[i]->height>spacingY)
                            totalHeight+=widgets[i]->height;
                        else
                            totalHeight+=spacingY;

                    for (int i=0; i<_i; i++)
                        if(widgets[i]->height>spacingY)
                            newY+=widgets[i]->height;
                        else
                            newY+=spacingY;


                    float offsetY = (height - totalHeight)/2;

                    newY +=  (x + offsetY)+widgets[_i]->height/2;

                    return newY;
                }
                else {
                    cout << "view has 0 h" << endl;
                    return 0;
                }
            }
        }

        ofPoint kRectView::getGridXY(int _position) {
            float gridX, gridY;

            if(orientation=="horizontal") {
                gridX = x + ((floor(_position /rows)+0.5f) * spacingX);
                gridY = y + (((_position % rows)+0.5f) * spacingY);
            }
            else {
                gridX = x + (((_position % cols)+0.5f) * spacingX);
                gridY = y + ((floor(_position / cols)+0.5f) * spacingY);

            }

            ofPoint pt(gridX,gridY);

            return pt;
        }


        void kRectView::draw(ofEventArgs & args) {
//
//            ofEnableAlphaBlending();
//                ofSetColor(70,70,70,80);
//                ofFill();
//                ofRect(x,y,width,height);
//                ofNoFill();
//            ofDisableAlphaBlending();

            drawString(label,x,y-currentFont->getLineHeight() );
            if(isMouseOn) color(1);
            else          color(0);
            ofRect(x,y,width,height);


        }




    kCircleView::kCircleView(){ autoArrange=true; }

    void kCircleView::setR(int _r){ r=_r; arrangeWidgets();}

    float kCircleView::getX( int _i ) {
        int noWidgets=widgets.size();
        float step = TWO_PI / noWidgets;
        float newX = x+(cos(step*_i)*r);

        return newX;
    }

    float kCircleView::getY( int _i ) {
        int noWidgets=widgets.size();
        float step = TWO_PI / noWidgets;
        float newY=y+(sin(step*_i)*r);
        return newY;
    }

    float kCircleView::getX(){ return x; };
    float kCircleView::getY(){ return y; };

    void kCircleView::draw(ofEventArgs & args) {

    }

//}

//#endif
