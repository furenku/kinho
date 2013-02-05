#pragma once

#ifndef VIEWS_H
#define VIEWS_H

#include "guiVideoObjects.h"

class kAudioView: virtual public kRectView{
    public:
    kAudioView();

    void initialize();



    void scrollUp(widgetEvent & event);

    void scrollDown(widgetEvent & event);

    void scrolled(widgetEvent & event);

    int noSliders;
    vector< shared_ptr<kSlider> > sliders;



};

class kEditorView: virtual public kClipView {
    public:
        shared_ptr<ofVideoPlayer> video;

        kEditorView();

        void initialize();

        void viewClip(shared_ptr<Clip> _clip);

        void loginRanges();

        void loginClip();

        void createEvents();

        void update(ofEventArgs & args) ;

        void draw(ofEventArgs & args) ;

        shared_ptr<kEditorView> shared_from_this();



    //{ vars


        shared_ptr<Controller>                  ctl;
        shared_ptr<Functor>                     func;
        vector<string>                          labels;
        vector<shared_ptr<TextBox> >            inputs;
        shared_ptr<kButton>                     btn;
        shared_ptr<kView>                       subView;
        shared_ptr<kRectButtonView>             tView;
        shared_ptr<kCircleTool>                 crc;
        shared_ptr<kRectTool>                   rrc;
        shared_ptr<Range>                       range;
        vector < shared_ptr<kRangeHolder> >     ranges;
        vector <string>                         commands;
        vector <bool*>                          boolVec;
        vector <int*>                           intVec;
        vector <float*>                         floatVec;

        shared_ptr<kRangeHolder>                activeRange;
        ofColor                                 currentColor;
        float                                   seekPos;


    //}

};

class kBrowseArchive: virtual public kButtonTree{
    public:

        kBrowseArchive();

//
        void createEvents();

        void createClipView();

        void createSampleView();

        void createTextView();



        void createMediaViews();

        void loadMediaViews();

        void initMediaViews();



        void removeAllViews();

        void removeMediaViews();




        void addClips( vector< shared_ptr<Clip> > _clips );

        void addSamples( vector< shared_ptr<Sample> > _samples );


//        void addTexts( vector< shared_ptr<Text> > _texts ) {
//            textScrollViews.back() -> addTexts(_texts);
//            arrangeWidgets();
//            lastTexts = _texts;
//        }

        void addMedia( vector< shared_ptr<Clip> > _clips, vector< shared_ptr<Sample> > _samples );


        void clearClips();





        void clearSamples();

        void addCol(vector<string> _labels);

        void removeCol(int _i);

        void clearWidgets() ;



//        void arrangeWidgets() {
//             for (int i=0; i<scrollViews.size(); i++) {
//                if(autoArrange) {
//                    scrollViews[i] -> setFromCenter( getX(i), getY(i) );
//                }
//                scrollViews[i]->arrangeWidgets();
//             }
//        }

        void btnClicked(widgetEvent & _event);



        void btnDragged(widgetEvent & _event);



        void clipClicked(widgetEvent & _event);



        void clipDragged(widgetEvent & _event);

        void toggleViews(widgetEvent & _event);

        int getClickedRow();
        string getCommand();

        int clickedRow;
        string command;
        vector<string> labels;
        shared_ptr<kWidget> btn;

        vector< shared_ptr<kScrollView> > scrollViews;
        shared_ptr<kClipScrollView> clipView ;
        shared_ptr<kSampleScrollView> sampleView;
        vector< shared_ptr<kClipScrollView> > clipScrollViews;
        vector< shared_ptr<kSampleScrollView> > sampleScrollViews;
        vector< shared_ptr<kRectView> > mediaViews;

        vector< shared_ptr < Clip > > lastClips;
        vector< shared_ptr < Sample > > lastSamples;
//        vector< shared_ptr < Text > > lastTexts;

        shared_ptr<Clip> clickedClip, draggingClip;

};


class kArchiveView: virtual public kClipView {
    public:
        kArchiveView();

        void initialize() ;

        void createEvents();


void createCats();

void btnClicked(widgetEvent & event);

        void dropped(shared_ptr<kWidget> _dragObj );


//
    virtual bool addClip(shared_ptr<Clip> _clip);

        void showClip(widgetEvent & event);

        void selectClip(widgetEvent & event);

        void connectionStart(widgetEvent & event);

        void connectionAttempt(widgetEvent & event);

        void connectClips(shared_ptr<kClipHolder>_clip) ;


        void mousePressed(ofMouseEventArgs & mouse);


        void fboFill();

        void update(ofEventArgs & args);

//        void draw(ofEventArgs & args) {
//
//
//
////            fbo.begin();
////                glClear(GL_DEPTH_BUFFER_BIT);
////
////                ofEnableAlphaBlending();
////                ofSetColor(255, 255, 255); //you can change the alpha value to modulate the effect
////                ofFill();
////                ofCircle(100, 100, 20);
////
////                for (int i=0; i<widgets.size(); i++)
////                {
////                	widgets[i]->draw(args);
////                }
////
////            fbo.end();
////
////            fbo.draw(x,y,width,height);
//        }

        vector<pair<shared_ptr<kWidget>,shared_ptr<kWidget> > > connections;
        shared_ptr<kClipHolder> connectingClip;

        shared_ptr<kClipHolder> clipSel;

        vector<shared_ptr<kCategory> > categories;

//        ofFbo fbo;

};

class kOutSender: virtual public kDragObject, virtual public kRectButton {
    public:
        kOutSender(){}


        void mouseReleased( ofMouseEventArgs & mouse);

};

class kPlayView: virtual public kClipView{
    public:

shared_ptr<ofVideoPlayer> video, video2;
vector<shared_ptr<kOutSender> >outs;

        kPlayView();

        void initialize();

        void createOuts();

        void update(ofEventArgs & args);

        void createEvents();

        void dropped(shared_ptr<kWidget> _dragObj );

        void playClip(shared_ptr<Clip> _clip, int _out) ;

        void selectClip(widgetEvent & event);

        void connectionStart(widgetEvent & event);

        void connectionAttempt(widgetEvent & event);

        void connectWidgets(shared_ptr<kWidget>_widget) ;



        void mousePressed(ofMouseEventArgs & mouse);


        void draw(ofEventArgs & args);



        vector<pair<shared_ptr<kWidget>,shared_ptr<kWidget> > > connections;
        shared_ptr<kWidget> connectingWidget;

        shared_ptr<kClipHolder> clipSel;
shared_ptr<kClipHolder> connectingClip;

};



#endif
