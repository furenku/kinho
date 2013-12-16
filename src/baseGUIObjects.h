
#define DEFAULT_COLOR 255
#define WIDGET_SIZE 20
#define TEXT_SIZE 20
#define CLIPVIEW_SIZE 80
#define ARCHIVE_CLIP_SIZE 40
#define MAX_ROWS 200
#define MAX_COLS 200
#define SPACING_X 30
#define SPACING_Y 30


#pragma once


//#pragma once

#include "mainClasses.h"

//#ifndef base_gui_objects
//#define base_gui_objects

enum kButtonMode{
	TOGGLE_OFF,
	TOGGLE_ON
};



inline float getDistance(float x1, float y1, float x2, float y2){
    float distance = sqrt( pow( x1-x2, 2 ) + pow( y1-y2, 2 ) );
    return distance;
}



inline float getDistance( shared_ptr<DrawObject> _w1, shared_ptr<DrawObject> _w2 ) {
    return getDistance(_w1->getX(), _w1->getY(), _w2->getX(), _w2->getY() );
}


inline float getInRange(float _val, float _lo, float _hi) {
    float val,range;
    range = _hi-_lo;
    val = _val;
    if (val<=_lo) { val = _lo;}
    else    if (_val>=_hi) { val = _hi;}

    val=(val-_lo)/range;
    return val;
}



inline float getAngle(float _x, float _y,float _x0, float _y0) {

    float GRAD_PI = 180.000 / PI;

    if (_x-_x0 == 0.0) {
      if(_y-_y0 < 0.0)
         return 270;
      else
         return 90;
    } else if (_y-_y0 == 0) {
      if(_x-_x0 < 0)
         return 180;
      else
         return 0;
    }

    if ( _y-_y0 > 0.0)
      if (_x-_x0 > 0.0)
         return atan((_y-_y0)/(_x-_x0)) * GRAD_PI;
      else
         return 180.0 - (atan((_y-_y0)/-(_x-_x0)) * GRAD_PI);
      else
         if (_x-_x0 > 0.0)
            return 360.0 - (atan(-(_y-_y0)/(_x-_x0)) * GRAD_PI);
         else
            return 180.0 + (atan(-(_y-_y0)/-(_x-_x0)) * GRAD_PI);
}


//class kDrawEventArgs : public ofEventArgs {
//  public:
//    ofTrueTypeFont * font;
//};

// fwd declare:
class Controller;
class kView;



//------------------------------------------------------
// GUI SUBCLASSES:

class Settings: public Object {
    public:
        Settings(){}
        ~Settings(){}

        virtual void addFont(   shared_ptr<ofTrueTypeFont> _font,   shared_ptr<ofColor> _color );
        virtual void addColor(   shared_ptr<ofColor> _color );

        virtual  shared_ptr<ofTrueTypeFont> getFont(int _index);

        virtual  shared_ptr<ofColor> getColor(int _index);

        vector< shared_ptr<ofTrueTypeFont > > font;
        vector< shared_ptr<ofColor> > color;
        vector< shared_ptr<ofColor> > fontColor;

};



//KWIDGET

class kWidget: virtual public MouseObject, virtual public DrawObject {
    public:
        kWidget();
        kWidget(  shared_ptr<Settings> _settings);

        virtual ~kWidget();

        void setupVars ();

        virtual void enableUpdate();

        virtual void disableUpdate();


        virtual void update(ofEventArgs & args);

        virtual void setLabel (string _label);

        string getLabel();

        void createEvents ();

        virtual void draw();

        virtual void drawString(string _text, float _x, float _y);

        virtual void color(int _index);

        virtual void font(int _index);

        void applySettings(   shared_ptr<Settings> _settings );

        virtual void setWidgetSettings( shared_ptr<Settings> _settings );

        void mouseMoved( ofMouseEventArgs & mouse );

        virtual void mousePressed( ofMouseEventArgs & mouse );

        bool mouseOnWidgets();




        virtual void dropped( shared_ptr< kWidget > _widget );

        void setMode(kButtonMode _mode);

        kButtonMode getMode();

        ofPoint getViewXY();


        virtual void addWidget( shared_ptr<kWidget> _widget   );

        virtual void removeWidget( shared_ptr<kWidget> _widget   );

        virtual void removeFromView();


        virtual void arrangeWidgets();


        virtual void clearWidgets();

        vector< shared_ptr < kWidget > > & getWidgets();

        shared_ptr<kWidget> getFirstView();

        int getWidgetIndex( shared_ptr<Observable> _obs );

        int getIndexInView();

        void setRectInView();

        void setRectInViewNoArrange();


        ofRectangle getRectInView();

        void addDelete( shared_ptr<kWidget> _widget );



        shared_ptr<kWidget> shared_from_this();

        bool getToggle();

        int getValue();


        float getMouseX();

        float getMouseY();


        shared_ptr<Settings> settings;
        shared_ptr<Settings> widgetSettings;

        shared_ptr<ofTrueTypeFont> currentFont;

        shared_ptr<kWidget> view;
        string label;
        vector<shared_ptr<kWidget> > widgets;
        int widgetSize;
        std::map< shared_ptr<kWidget>, ofRectangle > widgetRects;

        bool deletingWidgets;

        shared_ptr<kWidget> deleteObj;

        bool toggle;
        int value;
        float fvalue;
        bool boolValue;
        kButtonMode mode;

        float dragX, dragY;

        vector< shared_ptr<kWidget> > deleteObjects;

        shared_ptr<kWidget> draggingWidget;

        float mouseX,mouseY;

        int maxChars;

};





class kRect: virtual public kWidget {
    public:
        kRect(){ }

        void draw(ofEventArgs & draw);

//        virtual bool inside (float px, float py);

};

class kCircle: virtual public kWidget {
    public:
        kCircle(){}
        virtual void set (float _x, float _y, float _w, float _h);
        virtual void set (ofPoint pos, float w);

        virtual void setFromCenter (float _x, float _y);

        virtual void setFromCenter (float _x, float _y, float w, float h);

        void setSize (float _size);

        ofPoint getCenter ();

        bool inside (float px, float py);

        void mouseMoved( ofMouseEventArgs & mouse );

        void draw(ofEventArgs & draw);


};

class kDragObject: virtual public kWidget {
    public:
        kDragObject();

        void createEvents();

        void mouseDragged( ofMouseEventArgs & mouse );



        void mouseReleased( ofMouseEventArgs & mouse);

        void makeDroppable(float _x, float _y);

        void makeDraggable(float _x, float _y);

        float sourceX, sourceY;
        bool hasBeenMadeDroppable;

        shared_ptr<kDragObject> shared_from_this();

};

class kDragSink: virtual public kWidget{
    public:
        kDragSink();

        void createEvents();

        void mouseReleased(ofMouseEventArgs & mouse);
};




























//------------------------------------------------------
// BUTTONS:

class kButton: virtual public kWidget{
    public:
        kButton();

        void createEvents();

        virtual void mouseReleased( ofMouseEventArgs & mouse );

        virtual void pressed();
        virtual void pressedOut();

        virtual void draw( ofEventArgs & args );

};



class kRectButton: virtual public kButton, virtual public kRect{
    public:
        kRectButton();

        void draw( ofEventArgs & args );

};

class kCircleButton: virtual public kButton, virtual public kCircle{
    public:
        kCircleButton(){ createEvents(); }
        void draw( ofEventArgs & args );

};




class kLabelButton: virtual public kButton, virtual public kRect{
    public:
        kLabelButton(){ }

        void draw( ofEventArgs & args );

        void setLabel (string _label);


};

class kRectDragButton: virtual public kRectButton, virtual public kDragObject{
    public:
        kRectDragButton(){ createEvents(); }

        void createEvents();

        void mouseReleased( ofMouseEventArgs & mouse);

};

class kCircleDragButton: virtual public kCircleButton, virtual public kDragObject{
    public:
        kCircleDragButton();

        void createEvents();

        void mouseReleased( ofMouseEventArgs & mouse);

};



//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------






//---------------------------------------width-----------------------
// this class is a circular range with a start and ending point
// that can be dragged
//--------------------------------------------------------------


/*
class timeEvent: virtual public kButton {
    public:
        timeEvent();{ position = 0; }

        void draw(ofEventArgs & args) {}

        float position;
};
*/

class kRangeHolder: virtual public kButton {

    public:

        kRangeHolder();

        void createEvents();


        void execute(widgetEvent & _event);

        void setStart ( float _val );

        void setEnd ( float _val );

        void addRange( shared_ptr<Range> _range );

        virtual float getMousePos(ofMouseEventArgs & mouse) {}


        virtual void mousePressed(ofMouseEventArgs & mouse);

        virtual void mouseDragged(ofMouseEventArgs & mouse);

        virtual void mouseReleased(ofMouseEventArgs & mouse);

//        void addTimeEvent( shared_ptr<timeEvent> _event );



        float start, end;
        bool setInOut,inOrOut;
        shared_ptr<Range> currentRange;
        vector <shared_ptr<Range> > ranges;
        float playHead,targetPlayHead;
        float clickPosition;
        float startPos, endPos;
//        vector< shared_ptr<timeEvent> > timeEvents;

        float * draggingPoint;
        shared_ptr<Range> draggingRange;

};


class kRectTool: virtual public kButton, virtual public kRect, virtual public kRangeHolder{

    public:
    kRectTool(){  }

    //{ functions:

    void draw( ofEventArgs & args );

    float getMousePos(ofMouseEventArgs & mouse);

    void mouseMoved(ofMouseEventArgs & mouse);

    void mouseReleased(ofMouseEventArgs & mouse);

    //}

};


class kCircleTool: virtual public kButton, virtual public kRangeHolder{


    public:

    kCircleTool() { thickness = WIDGET_SIZE /2; }


    int thickness;

    //{ functions:


    void draw( ofEventArgs & args );

    void mouseMoved(ofMouseEventArgs & mouse);

    float getMousePos(ofMouseEventArgs & mouse);

    void mouseReleased(ofMouseEventArgs & mouse);

    //}

};







//------------------------------------------------------
// VIEWS:


//--------------------------------------------------------------

class kView: virtual public kWidget {
    public:

    kView();

    void show();

    void hide();

    void enable();

    void disable();


    void arrangeWidgets();

    void mouseDragged( ofMouseEventArgs & mouse );


//    shared_ptr<kView> shared_from_this()
//    {
//            return boost::dynamic_pointer_cast<kView>(Observable::shared_from_this());
//    }



    void setAutoArrange( bool _autoArrange );

    void setOrientation(string _orientation);


    virtual float getGridX( int _i );
    virtual float getGridY( int _i );
    virtual ofPoint getGridXY( int _position );


    float getScrollX();

    float getScrollY();


    void setCols(int _cols);
    void setRows(int _rows);
    int getCols();
    int getRows();

    void setSpacingX(int _spacingX);
    void setSpacingY(int _spacingY);
    int getSpacingX();
    int getSpacingY();

    void setPaddingX(int _paddingX);
    void setPaddingY(int _paddingY);
    int getPaddingX();
    int getPaddingY();



    bool autoArrange;
    string orientation;

    int cols,rows;
    float spacingX,spacingY;
    float paddingX,paddingY;
    float scrollX, scrollY;


};


class kRectView: virtual public kView, virtual public kRect{
    public:
        kRectView();

        float getGridX( int _i );

        float getGridY( int _i );

        ofPoint getGridXY(int _position);

        virtual void draw(ofEventArgs & args);

};

class kCircleView: virtual public kView, virtual public kCircle{
    public:
    kCircleView();

    void setR(int _r);

    float getX();
    float getY();

    float getX( int _i );
    float getY( int _i );

/*
    float getX();{ return x; };
    float getY(){ return y; };
    float getWidth(){ return width; };
    float getHeight(){ return height; };
*/
    void draw(ofEventArgs & args);

};


//#endif
