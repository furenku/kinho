
#pragma once

// WIDGETS
#include "baseGUIObjects.h"

#ifndef guiobjects_h
#define guiobjects_h


class kDigit: virtual public kRectButton {
    public:
        kDigit();


        void draw( ofEventArgs & args );


};



class kButtonView: virtual public kView{
    public:
        kButtonView();

        ~kButtonView();

        void createEvents();


        void addButtons(vector<string> _labels);

        void removeButtons();

        void addDragButtons(vector<string> _labels);

        void addButton( shared_ptr<kButton> _widget);

        void clearWidgets();

        void btnClicked(widgetEvent & _event);

        void btnDragged(widgetEvent & _event);

        string getCommand();

        vector<string> labels;
        shared_ptr<kWidget> btn;
        string command;

};

class kRectButtonView: virtual public kButtonView, virtual public kRectView{

    public:
        kRectButtonView();

//
//        float getX(int _i){
//            return kRectView::getX(_i);
//        }
//
//        float getY(int _i){
//            return kRectView::getY(_i);
//        }

        void mousePressed(ofMouseEventArgs & mouse);

};

class kCircleButtonView: virtual public kButtonView, virtual public kCircleView {
    public:
        kCircleButtonView():kButtonView(){}

//        float getX(int _i){ kCircleView::getX(_i); }
//        float getY(int _i){ kCircleView::getY(_i); }
        void draw(ofEventArgs & args);

        bool inside(float px, float py);

        void mouseMoved(ofMouseEventArgs & mouse);

        void mousePressed(ofMouseEventArgs & mouse);

        void arrangeWidgets();

};


class kCircleScrollView: virtual public kCircleButtonView {
    public:
        kCircleScrollView();

        void setupVars();

        void initialize();

        void draw(ofEventArgs & draw);

        void iiinit();

        void arrangeWidgets();

        void addButtons(vector<string> _labels);


/*

codigo de addbuttons:

clearWidgets();

            labels.clear();
            for (int i=0; i<_labels.size(); i++)
            {
                labels.push_back(_labels[i]);
                btn = make_shared<kCircleButton>();
                btn->setSize(widgetSize);
                btn->setLabel( _labels[i] );
                btn->setMode( TOGGLE_ON );
                if(i==0)    btn->toggle=true;
                else        btn->toggle=false;

                btn->value = i;
                addWidget( btn );

                ofAddListener( *btn->events.lookup("press"),this,&kButtonView::btnClicked);

                btn.reset();

            }

            arrangeWidgets();
*/

        void createPages();

        void addButtons();

        void addBtnView();

        void removeBtnView();

        void pageSelect(widgetEvent & _event );




    protected:
        int numDisplay;
        int page;
        shared_ptr<kRectButtonView> btnView;

};

class kScrollBar : virtual public kRectView {

    public:

    kScrollBar();

    ~kScrollBar();

    void createEvents();

    void setupVars();

    void initialize();

    void btnClicked(widgetEvent & event);

    void setViewSize ( int _totalW, int _totalH );

    void mouseDragged(ofMouseEventArgs & mouse);

    void setBar();

    void mousePressed(ofMouseEventArgs & mouse);

    void mouseReleased(ofMouseEventArgs & mouse);


    float getScroll();

    string getOrientation();

    shared_ptr<kRectButton> bar;
    vector <shared_ptr<kRectButton> > arrows;

    float totalW,totalH,barW,barH,startX,startY;
    float scrollStep;
    float scroll;

    bool isDraggingBar;


};


class kScrollView: virtual public kRectButtonView {
    public:

    kScrollView();

    virtual ~kScrollView();

    void setupVars();

    void show();

    void hide();

    void initialize();

/*
    void addButtons(vector<string> _labels){
        kRectButtonView::addButtons(_labels);
        arrangeWidgets();
    }


    void addDragButtons(vector<string> _labels){
        kRectButtonView::addDragButtons(_labels);
        arrangeWidgets();
    }


    virtual void btnClicked(widgetEvent & _event) {
        kButtonView::btnClicked(_event);
        notify("btnClicked");

    }

    virtual void btnDragged(widgetEvent & _event) {
        kButtonView::btnDragged(_event);

        notify("btnDragged");

    }

*/

    void set (float px, float py, float w, float h);

    virtual void scrollUp(widgetEvent & event);

    virtual void scrollDown(widgetEvent & event);

    void doScrollX(widgetEvent & event);

    void doScrollY(widgetEvent & event);


    ofPoint getGridXY(int _position);

    void arrangeWidgets();


    virtual void updateCanvas();

    float getScrollPctX();

    float getScrollPctY();


    float getTotalW();
    float getTotalH();


    float scrollStep;

    vector< shared_ptr<kScrollBar> > scrollBars;
    float totalW,totalH;
    ofRectangle canvas;


};




class kField2D: public kScrollView{
    public:
        kField2D();


        void addWidget(shared_ptr<kWidget> _widget);

        void updateCanvas();

        void setScroll();

        void mousePressed(ofMouseEventArgs & mouse);

        void mouseReleased(ofMouseEventArgs & mouse);



    protected:


    bool isDraggingField;
};


class kSlider:virtual public kScrollBar{
    public:
    kSlider(){}
    void initialize();

    void setBar();

    void mouseDragged(ofMouseEventArgs & mouse);


};



class kKnob: public kButton {
    public:

    kKnob();

    void createEvents();


    float angle,value;

    float rangeStart,rangeEnd;

    //{ functions:

    void draw( ofEventArgs & args );

    void mouseMoved(ofMouseEventArgs & mouse);

    void mouseDragged(ofMouseEventArgs & mouse);

    void mousePressed(ofMouseEventArgs & mouse);

    void mouseReleased(ofMouseEventArgs & mouse);


    //}

};





class kButtonTree: virtual public kRectButtonView{
    public:

        kButtonTree();


        void createEvents();


        virtual void addCol(vector<string> _labels);

        void removeCol(int _i);

        void clearWidgets();




        void btnClicked(widgetEvent & _event);


        vector<string> labels;
        shared_ptr<kWidget> btn;
        string command;

        vector< shared_ptr<kButtonView> > btnViews;

};



//--------------------------------------------------------------

class TextBox: public kRectButton {
    public:
        TextBox(shared_ptr<Settings> _settings );


        void createEvents();

        void reset ();


        void draw(ofEventArgs & args);

        void setText(string _str);

        void setText(float _value);

        void setText(int _value);

        void addKey( int key );

        void enable();

        void disable();

        void keyPressed(ofKeyEventArgs & key);



        void mouseReleased(ofMouseEventArgs & mouse);


        void focus();


        void unFocus();



        shared_ptr<ofTrueTypeFont> font;

        bool hasFocus;

        string str,drawStr;

};


class TextInput: virtual public kRectView, virtual public TextBox {
    public:
    TextInput(shared_ptr<Settings> _settings ):TextBox(_settings){
        createEvents();
        settings = _settings;
        applySettings(settings);
        setWidgetSettings(settings);
        autoArrange=false;
        height = TEXT_SIZE * 1.5f;
        isDraggable = false;
        int offset = ( height - ( TEXT_SIZE * 1.2f ) ) / 2;

        textBox        =   make_shared<TextBox>( _settings );
        textBox->set(0.0f,0.0f,0.9f,1.0f);
        addWidget(textBox);

        submitBtn      =   make_shared<kButton>();
        submitBtn->set(0.9f,0.0f,0.1f,1.0f);
        submitBtn->notify("press");
        addWidget(submitBtn);

        shouldResetAfterSubmit = true;
        enable();
    }

    void createEvents();

    void set(float _x, float _y, float _w, float _h);

    void draw(ofEventArgs & args);

    void enable();

    void disable();

    void submit(widgetEvent & _event);

    void addKey ( int key );

    shared_ptr<TextBox> textBox;
    shared_ptr<kButton> submitBtn;


    bool shouldResetAfterSubmit;

};

//-----



class kDropDown: virtual public kRectView {
    public:
        kDropDown();
        ~kDropDown();


        void createEvents();


        void initialize();

        void displayList(widgetEvent & _event);

        void hideList(widgetEvent & _event);

        void addOptions(vector<string> _options);


        void btnClicked(widgetEvent & _event);

//        addWidget( clip );
//        if(!visible) clip->hide();
//        arrangeWidgets();
        vector<string> options;
        shared_ptr<TextBox> text;
        shared_ptr<kScrollView> list;
        bool displaying;
};



class kNode: virtual public kCircleButton{
    public:
        kNode();


        vector <shared_ptr<kNode> > parents;
        vector <shared_ptr<kNode> > silblings;
        vector <shared_ptr<kNode> > children;

};




//--------------------------------------------------------------
/*
class Node: public Button  {
    public:
    Node(int _x, int _y, int _s, string _type, int _id, Object * _target):Button(_x,_y,_s,_type,_id,_target)
    {
        parent          =   NULL;
        isConnecting    =   false;
        isPlaying       =   false;

        isDraggable = true;

        targetScreen    =   0 ;
    }
    virtual ~Node() {
        disable();
        for ( int i = 0; i < connectors.size() ; i++ )
        {
        	delete connectors[i];
        }
        connectors.clear();
        descendants.clear();
        children.clear();

    }


    //--------------------------------------------------------------
    void drawConnections(){
//        if(hasBeenCreated)  {
        if(isConnecting)    {
            ofSetColor(0x444444);
            ofLine(x,y,mouseX,mouseY);
        }
        else
            if(parent!=NULL){
                ofSetColor(0xAAAAAA);
                ofLine(x,y,parent->x,parent->y);
            }
//        }
    }

    //--------------------------------------------------------------
    void draw(){
        ofCircle(x,y,s);
    }

    //--------------------------------------------------------------
    void mouseReleased(ofMouseEventArgs & mouse)   {


        if(!isConnecting)  {
            if(mouseOn) if(!hasBeenDragged) click();
            hasBeenDragged  =   false;
            isBeingDragged  =   false;
            isSelected      =   false;

            mouseX = mouse.x;
            mouseY = mouse.y;

        }


        if(isConnecting)    {

            target->getCall( this, "attemptNodeConnection", id);

            isConnecting=false;

            updateConnectors();

        }

        Object::mouseReleased(mouse);

    }

    //--------------------------------------------------------------
    void mousePressed(ofMouseEventArgs & mouse) {
        Object::mousePressed(mouse);

        recordX=mouse.x;
        recordY=mouse.y;

        hasGotDescendants=false;

    }

    //--------------------------------------------------------------
    void mouseDragged(ofMouseEventArgs & mouse) {

        Object::mouseDragged(mouse);

        if(isBeingDragged)  {

            if(!hasGotDescendants)  {
                getDescendants();
                getDescendantsXY();
            }

            updateConnectors();
            for(int i=0; i<children.size(); i++){
                children[i]->updateConnectors();
            }

            for(int i=0; i<descendants.size(); i++){
                descendants[i]->x = descendantsX[i]+(mouse.x-recordX);
                descendants[i]->y = descendantsY[i]+(mouse.y-recordY);
                descendants[i]->updateConnectors();
            }

        }

    }

    //--------------------------------------------------------------
    void mouseMoved(ofMouseEventArgs & mouse) {

        Object::mouseMoved(mouse);

        if(isConnecting)
            updateConnectors();
    }


    //--------------------------------------------------------------
    void updateConnectors(){

        float angle;

        if(isConnecting)
            angle = getAngle( mouseX, mouseY, x, y ) * ( TWO_PI / 360 );
        else
            if(parent!=NULL)
                angle = getAngle( parent->x, parent->y, x, y ) * ( TWO_PI / 360 );
            else
                angle = getAngle( x, y - ( s * 0.6 ), x, y ) * ( TWO_PI / 360 );

        for(int i =0; i<connectors.size(); i++)    {
            connectors[i]->x=x + ( cos( angle ) * ( s * 0.6 ) );
            connectors[i]->y=y + ( sin( angle ) * ( s * 0.6 ) );
        }

    }


    //--------------------------------------------------------------
    void getCall( Object * source, string message, float param){

        if(allowCalls)  {
            if(message == "connector") {
                isConnecting  =   true;
            }
        }
    }


    //--------------------------------------------------------------
    void getDescendants()    {

        descendants.clear();
        getAllChildren(this);
        hasGotDescendants=true;

    }


    //--------------------------------------------------------------
    void getDescendantsXY()  {
        descendantsX.clear();
        descendantsY.clear();

        for (int i=0; i<descendants.size(); i++ )
        {
        	descendantsX.push_back(descendants[i]->x);
            descendantsY.push_back(descendants[i]->y);
        }

    }


    //--------------------------------------------------------------
    void getAllChildren(Node * parentNode)  {

        // using recursion to find all nodes
        // (based on http://stackoverflow.com/questions/177277/how-to-get-a-list-of-all-child-nodes-in-a-treeview-in-net)
        for(int i = 0 ; i<parentNode->children.size(); i++)  {
            descendants.push_back(parentNode->children[i]);
            getAllChildren(parentNode->children[i]);
        }
    }


    //--------------------------------------------------------------
    int getBranch(Node * descendantNode )    {

        int currentBranch;

            bool foundRoot = false;

            for (int i=0; i<children.size(); i++ )
            {
                if( children[i] == descendantNode ) {
                    currentBranch = i;
                    foundRoot = true;
                    break;
                }
            }

            for (int i=0; i<children.size(); i++ )
            {
                children[i]->getDescendants();
                for (int j = 0; j < children[ i ] -> descendants.size(); j++ )
                {
                    if( children[ i ]->descendants[ j ] == descendantNode )    {
                        currentBranch = i;
                        foundRoot = true;
                        break;
                    }

                    if(foundRoot)   break;
                }
            }

        return currentBranch;

    }



    bool hasBeenCreated;

    bool isConnecting;


    Node * parent;
    vector<Node*> children;

    vector <Node*> descendants;

    vector <int> descendantsX;
    vector <int> descendantsY;

    int targetScreen;

/&/    vector<Button *> demásconnectors;

    int recordX,recordY;

    bool hasGotDescendants;

    bool isPlaying;



};

*/





/*
class kDigit: public kRectButton{
    public:
        kDigit(){}

        int getValue(int amount){
            value += amount;
            value%=10;
        }


        void mousePressed(ofMouseEventArgs & mouse) {

        }
        void mouseDragged(ofMouseEventArgs & mouse) {
        }



};

*/

#endif
