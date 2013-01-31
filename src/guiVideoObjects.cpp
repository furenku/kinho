
#include "guiVideoObjects.h"
//#pragma once

//#ifndef GUIVIDEOOBJECTS_H
//#define GUIVIDEOOBJECTS_H


//----- VIDEO OBJECTS:


        MediaWidget::MediaWidget(){
            name        = "";
            filename    = "";
            description = "";
            type = "mediawidget";

        }
        MediaWidget::~MediaWidget(){
            media.reset();
        }
        void MediaWidget::setMedia( shared_ptr<MediaHolder> _media){
//            media       = _media;
////            name        = _media -> getName();
////            filename    = _media -> getFilename();
//            description = _media -> getDescription();
        }


        kClip::~kClip(){
            clip.reset();
        }

//        void createEvents(){
//            kDragObject::createEvents();
//        }


        void kClip::setClip ( shared_ptr<Clip> _clip ) {

            clip = _clip;

            aspectRatio = _clip -> getAspectRatio();
            string imgPath = _clip -> getFilename();
            string thumbPath = imgPath.substr(0, imgPath.find(".") )+".png";

            cout << thumbPath << endl;
            img.loadImage(thumbPath);

            setMedia(_clip);

        }

        shared_ptr<Clip> kClip::getClip() { return clip; }

        void kClip::draw(ofEventArgs & args){

//            ofCircle(x,y,r);
//            ofSetColor(65);

            ofSetColor(255);
            float w;
            if(isMouseOn){
                w = width*1.5f;
                ofDrawBitmapString(name,x,y);
            }
            else
                w = width;

                img.draw(
                    x-w/2,
                    y-(w/aspectRatio)/2,
                    w,
                    w/aspectRatio
                );


        }







        void kClipShow::createEvents() {
            saveEvent("dragged");
        }



        void kClipShow::mouseReleased( ofMouseEventArgs & mouse){
            kClip::mouseReleased(mouse);
            kDragObject::mouseReleased(mouse);
        }

        void kClipShow::mouseDragged( ofMouseEventArgs & mouse){
            kDragObject::mouseDragged(mouse);
            notify("dragged");
        }




        kClipHolder::kClipHolder( shared_ptr<Settings> _settings ) {
            createEvents();
            autoArrange = false;
            isDraggable = true;
            isDroppable = false;

            applySettings(_settings);
            setWidgetSettings (_settings);
output=-1;

        }



        void kClipHolder::createEvents(){
            saveEvent("killSubView");
            saveEvent("press");
            saveEvent("connect");
            saveEvent("select");
            saveEvent("viewClip");
        }

        void kClipHolder::addBtnView(){
            btnView = make_shared<kCircleButtonView>();
            btnView->set(0,0,1.0f,1.0f);
            btnView -> applySettings ( settings  );
            btnView -> setWidgetSettings ( settings );

            addWidget(btnView);

            vector<string> labels;
            labels.push_back("select");
            labels.push_back("connect");
            labels.push_back("related");
            labels.push_back("scenes");
            labels.push_back("tags");
//
            btnView -> addButtons(labels);
////            for (int i=0; i<labels.size(); i++)
////                ofAddListener( *btnView->events.lookup("btnClicked"),this,&kClipHolder::btnClicked);

            arrangeWidgets();


        }

        void kClipHolder::pressed() {

//            bool hasCreated=false;
            if(!btnView) {
                addBtnView();
//                hasCreated=true;
                notify("viewClip");
            }


//            if(hasCreated==false&&btnView)
//                removeBtnView();


        }

        void kClipHolder::pressedOut() {

            if(btnView)
                if(!subView) {
                    if(!mouseOnWidgets())
                        removeBtnView();
                }

        }




        void kClipHolder::removeBtnView(){
            if(btnView) {
                for (int i=0; i<btnView->widgets.size(); i++)
                    ofRemoveListener( *btnView->events.lookup("btnClicked"),this,&kClipHolder::btnClicked);

                view->addDelete(btnView);

                removeWidget(btnView);
                btnView.reset();
                removeSubView();
                arrangeWidgets();

            }

        }

        void kClipHolder::removeSubView(){
            if(subView) {
                view->addDelete(subView);
                removeWidget(subView);
                subView.reset();
            }
        }


        void kClipHolder::btnClicked(widgetEvent & _event ){
            int index = btnView->value;

            string command = btnView->labels[index];

            if( command == "select" )
               notify("select");

            if( command == "connect" )
                notify("connect");

            if( command == "related" ) {
                addView();
                showView(btnView->widgets[ index ]->x,btnView->widgets[ index ]->y);
            }

            if( command == "scenes" ) {
                addView();
                showView(btnView->widgets[ index ]->x,btnView->widgets[ index ]->y);
            }

            if( command == "tags" ) {
                addView();
                showView(btnView->widgets[ index ]->x,btnView->widgets[ index ]->y);
            }

        }





        void kClipHolder::draw(ofEventArgs & args) {
            kClip::draw(args);
        }

        void kClipHolder::mouseDragged(ofMouseEventArgs & mouse) {
            if(isBeingDragged && !view->inside(mouse.x,mouse.y))
                makeDroppable(mouse.x, mouse.y);

            else
            if(hasBeenMadeDroppable)
                makeDraggable(x,y);


            kDragObject::mouseDragged(mouse);
        }


        void kClipHolder::mouseReleased(ofMouseEventArgs & mouse) {


            if(subView) {
                removeSubView();
            }

//            makeDraggable(x,y);

            kDragObject::mouseReleased(mouse);

        }

        void kClipHolder::deleteView(){
            removeWidget(subView);
            subView->clearWidgets();
            subView.reset();
        }

        void kClipHolder::addView() {

            subView = make_shared<kRectButtonView>();

            subView  -> applySettings ( settings  );
            subView  -> setWidgetSettings ( settings );
            subView  -> set(0,0,2.1f,2.1f);

            addWidget( subView );
//            freezeButtons();


        }


        void kClipHolder::showView(float _x, float _y)   {
            if(subView) {
                subView -> setX( _x );
                subView -> setY( _y );

                subView -> label = "options";
//
                /// ask for ctl to populate it, through notify

                vector<string> labels;
                for (int i=0; i<2; i++)
                {
                    labels.push_back( ofToString(rand()%10) );
                }

                subView -> addButtons(labels);

                subView -> show();

                arrangeWidgets();
            }


        }

        shared_ptr<kClipHolder> kClipHolder::shared_from_this()
        {
            return dynamic_pointer_cast<kClipHolder>(kWidget::shared_from_this());
        }




        void kCategory::mouseDragged(ofMouseEventArgs & mouse) {
            kDragObject::mouseDragged(mouse);
        }




    kClipView::kClipView() { createEvents(); }

    void kClipView::createEvents() {
        saveEvent("clipClicked");
        saveEvent("clipDragged");
    }

    void kClipView::addClip(shared_ptr<Clip> _clip){
        shared_ptr<kClipShow> clip = make_shared<kClipShow>();
        clip -> setClip(_clip);
        clip->set( 0, 0, CLIPVIEW_SIZE, CLIPVIEW_SIZE );

        addWidget( clip );

        clips.push_back(clip);

        ofAddListener( *clip->events.lookup("press"),this,&kClipView::clipClicked );
        ofAddListener( *clip->events.lookup("drag"),this,&kClipView::clipDragged );

//        if(!visible) clip->hide();
        arrangeWidgets();
    }

        void kClipView::clipClicked(widgetEvent & _event){

            shared_ptr<kWidget>sender=dynamic_pointer_cast<kWidget>(_event.sender);

            int index = getWidgetIndex( sender );

            value = index;

            if(clips.size()>index){
                draggingClip = clips[index]->getClip();
                clickedClip =  clips[index]->getClip();
            }
            notify("clipClicked");

        }


        void kClipView::clipDragged(widgetEvent & _event){
            shared_ptr<kWidget>sender=dynamic_pointer_cast<kWidget>(_event.sender);
            int index = getWidgetIndex( sender );
            value = index;
            cout << "index"<<index << endl;
            if(clips.size()>index) {
            draggingClip = clips[index]->getClip();
                cout << "dragggggggggggg" << endl;
            }
            notify("clipDragged");
        }

    void kClipView::removeClip( shared_ptr<kClipShow> _clip ){
        removeWidget( _clip );
    }

    vector< shared_ptr < kClipShow > > & kClipView::getClips() {
        return clips;
    }



    void kClipView::clearClips(){
        for (int j=0; j<clips.size(); j++) {

            removeWidget( clips[j] );
            clips[j].reset();
        }
        clips.clear();
    }

    shared_ptr<Clip> kClipView::getDraggingClip(){ return draggingClip; }






    kClipScrollView::kClipScrollView(){ orientation="vertical"; cols = 2; spacingX=40;spacingY=40; }
/*
    void addButtons(vector<string> _labels){


            clearWidgets();

            labels=_labels;
            for (int i=0; i<labels.size(); i++)
            {
                btn = make_shared<kCircleButton>();
                btn->setSize(widgetSize);
                btn->setLabel( labels[i] );
                btn->setMode(TOGGLE_ON);
                if(i==0)    btn->toggle=true;
                else        btn->toggle=false;
                btn->value = i ;

                ofAddListener( *btn->events.lookup("press"),this,&kScrollView::btnClicked);

                addWidget( btn );

                btn.reset();

            }

        }

*/

    void kClipScrollView::initialize() {

        kScrollView::initialize();

    }

    void kClipScrollView::addClips(vector< shared_ptr<Clip> > _clips){
        for (int i=0; i<_clips.size(); i++)
            addClip(_clips[i]);
        /*shared_ptr<kClipShow> clip;
        for (int i=0; i<_clips.size(); i++)
        {
        	clip = make_shared<kClipShow>();
            clip -> setClip( _clips[i] );
            clip->set( 0, 0, CLIPVIEW_SIZE, CLIPVIEW_SIZE );

            kScrollView::addWidget( clip );


        }
        kScrollView::arrangeWidgets();*/
    }

    vector< shared_ptr < kClipShow > > & kClipScrollView::getClips() {
        return clips;
    }






        kMediaScrollView::kMediaScrollView(){
            createEvents();
        }




        void kMediaScrollView::createEvents() {
            saveEvent("btnClicked");
            saveEvent("btnDragged");
        }






        void kMediaScrollView::addMedia( vector<shared_ptr<MediaHolder> > _media ){

            clearWidgets();
            string type;

            for (int i=0; i<_media.size(); i++)
            {

                type = _media[i]->getType();

                if(type == "clip") {
                    shared_ptr<kClipShow> btn = make_shared<kClipShow>();
                    btn->setSize(widgetSize);

                    shared_ptr< Clip > clip = dynamic_pointer_cast< Clip >( _media[i] );

                    btn->setClip( clip );

                    btn->value = i;
                    addWidget( btn );

                    ofAddListener( *btn->events.lookup("press"),this,&kMediaScrollView::btnClicked);
                    ofAddListener( *btn->events.lookup("drag"),this,&kMediaScrollView::btnDragged);

                }
                else if(type == "sample") {

//                    shared<kSampleShow> btn = make_shared<kSampleShow>();
//                    btn->setSize(widgetSize);
//                    btn->setSample( _samples[i] );
//
//                    btn->value = i;
//                    addWidget( btn );
//
//                    ofAddListener( *btn->events.lookup("press"),this,&kButtonView::btnClicked);
//                    ofAddListener( *btn->events.lookup("drag"),this,&kButtonView::btnDragged);

                }
                else if(type == "text") {

//                    shared<kTextShow> btn = make_shared<kTextShow>();
//                    btn->setSize(widgetSize);
//                    btn->setText( _texts[i] );
//
//                    btn->value = i;
//                    addWidget( btn );
//
//                    ofAddListener( *btn->events.lookup("press"),this,&kButtonView::btnClicked);
//                    ofAddListener( *btn->events.lookup("drag"),this,&kButtonView::btnDragged);

                }



            }



            arrangeWidgets();


        }


        void kMediaScrollView::btnClicked(widgetEvent & _event){
            shared_ptr<kWidget>sender=dynamic_pointer_cast<kWidget>(_event.sender);

            int index = getWidgetIndex( sender );

            for (int i=0; i<widgets.size(); i++) {
                widgets[i]->toggle=false;
            }

            if(index>=0) {
                widgets[index]->toggle = true;
                value = index;
                command = labels[index];
            }

//            cout << value << endl;


            if(value>0) boolValue = true;
            else        boolValue = false;
            notify("btnClicked");

        }



        void kMediaScrollView::btnDragged(widgetEvent & _event){
            shared_ptr<kWidget>sender=dynamic_pointer_cast<kWidget>(_event.sender);
            for (int i=0; i<widgets.size(); i++) {
                if(sender!=widgets[i])
                {
//                    widgets[i]->toggle=false;
                }
            	else {
//            	    widgets[i]->toggle = true;
                    value = i;
                    break;
            	}
            }
//            cout << value << endl;
            command = labels[value];
//
//            if(value>0) boolValue = true;
//            else        boolValue = false;
            notify("btnDragged");

        }







        kSample::kSample(){

            sampleRate = 44100;
//            settings = _settings;
        }

//        void createEvents(){
//            kDragObject::createEvents();
//        }

//        shared_ptr<Sample> sample;

        void kSample::setSample ( shared_ptr<Sample> _sample ) {
            sample = _sample;
            sampleRate = _sample -> getSampleRate();
            setMedia(_sample);
        }

        void kSample::draw(ofEventArgs & args){

//            ofCircle(x,y,r);
//            ofSetColor(65);
            if(isMouseOn)
                ofSetColor(255,200,0);
            else
                ofSetColor(255,125,0);
            float w;
            if(isMouseOn)
                w = width*1.5f;
            else
                w = width;

            ofRect(x,y,w,w);

            ofSetColor(155);
            ofDrawBitmapString(filename,x,y);


        }







//        kSampleShow::kSampleShow(): kSample() { isDroppable = true; }

        void kSampleShow::mouseReleased( ofMouseEventArgs & mouse){
            kSample::mouseReleased(mouse);
            kDragObject::mouseReleased(mouse);
        }





//    kSampleView::kSampleView() {}

    void kSampleView::addSample(shared_ptr<Sample> _sample){

        shared_ptr<kSampleShow> sample = make_shared<kSampleShow>();
        sample -> setSample(_sample);
        sample->set( 0, 0, CLIPVIEW_SIZE, CLIPVIEW_SIZE );

        addWidget( sample );
//        samples.push_back( sample );

    }

    void kSampleView::removeSample(shared_ptr<kSampleShow> _sample){
        removeWidget( _sample );
    }

    vector< shared_ptr < kSampleShow > > & kSampleView::getSamples() {
        return samples;
    }
//
//    vector< shared_ptr < kSampleShow > > kSampleView::samples;

    void kSampleView::clearSamples(){
        for (int j=0; j<samples.size(); j++) {
            removeWidget( samples[j] );
            samples[j].reset();
        }
        samples.clear();
    }





    kSampleScrollView::kSampleScrollView(){ orientation="vertical"; cols = 1; spacingX=40;spacingY=40; }
/*
    void addButtons(vector<string> _labels){


            clearWidgets();

            labels=_labels;
            for (int i=0; i<labels.size(); i++)
            {
                btn = make_shared<kCircleButton>();
                btn->setSize(widgetSize);
                btn->setLabel( labels[i] );
                btn->setMode(TOGGLE_ON);
                if(i==0)    btn->toggle=true;
                else        btn->toggle=false;
                btn->value = i ;

                ofAddListener( *btn->events.lookup("press"),this,&kScrollView::btnClicked);

                addWidget( btn );

                btn.reset();

            }

        }

*/


    void kSampleScrollView::addSamples(vector< shared_ptr<Sample> > _samples){
        for (int i=0; i<_samples.size(); i++)
        {
        	addSample(_samples[i]);
        }

    }








//--------------------------------------------------------------

//class Node: public kCircleButton  {
//    public:
//    Node()
//    {
//        isConnecting    =   false;
//        isActive        =   false;
//        createEvents();
//    }
//
//    void createEvents() {
//        saveEvent("attemptNodeConnection");
//    }
//
//    //--------------------------------------------------------------
//    void drawConnections(){
////        if(hasBeenCreated)  {
//        if(isConnecting)    {
//            ofSetColor(0x444444);
//            ofLine(x,y,mouseX,mouseY);
//        }
//        else
//            if(parent!=NULL){
//                ofSetColor(0xAAAAAA);
//                ofLine(x,y,parent->x,parent->y);
//            }
////        }
//    }
//
//    //--------------------------------------------------------------
//
//    //--------------------------------------------------------------
//    void mouseReleased(ofMouseEventArgs & mouse)   {
//
//        if(!isConnecting)  {
//            kCircleButton::mouseReleased(mouse);
//        }
//
//        if(isConnecting)    {
//            notify("attemptNodeConnection");
//
//            isConnecting=false;
//
//            updateConnectors();
//        }
//    }
//
//    //--------------------------------------------------------------
//    void mousePressed(ofMouseEventArgs & mouse) {
//        kCircleButton::mousePressed(mouse);
//
//        recordX=mouse.x;
//        recordY=mouse.y;
//
//        hasGotDescendants=false;
//
//    }
//
//    //--------------------------------------------------------------
//    void mouseDragged(ofMouseEventArgs & mouse) {
//
//        kCircleButton::mouseDragged(mouse);
//
//        if(isBeingDragged)  {
//
//            if(!hasGotDescendants)  {
//                getDescendants();
//                getDescendantsXY();
//            }
//
//            updateConnectors();
//
//            for(int i=0; i<children.size(); i++){
//                children[i]->updateConnectors();
//            }
//
//            for(int i=0; i<descendants.size(); i++){
//                descendants[i]->x = descendantsX[i]+(mouse.x-recordX);
//                descendants[i]->y = descendantsY[i]+(mouse.y-recordY);
//                descendants[i]->updateConnectors();
//            }
//
//        }
//
//    }
//
//    //--------------------------------------------------------------
//    void mouseMoved(ofMouseEventArgs & mouse) {
//
//        kCircleButton::mouseMoved(mouse);
//
//        if(isConnecting)
//            updateConnectors();
//    }
//
//
//    //--------------------------------------------------------------
//    void updateConnectors(){
//
//        float angle;
//
//        if(isConnecting)
//            angle = getAngle( mouseX, mouseY, x, y ) * ( TWO_PI / 360 );
//        else
//            if(parent!=NULL)
//                angle = getAngle( parent->x, parent->y, x, y ) * ( TWO_PI / 360 );
//            else
//                angle = getAngle( x, y - ( width * 0.6 ), x, y ) * ( TWO_PI / 360 );
//
//        for(int i =0; i<connectors.size(); i++)    {
//            connectors[i]->x=x + ( cos( angle ) * ( width * 0.6 ) );
//            connectors[i]->y=y + ( sin( angle ) * ( width * 0.6 ) );
//        }
//
//    }
//
//
//    //--------------------------------------------------------------
//    void btnPressed( widgetEvent & event ){
////        if(allowCalls)  {
////            Button::getCall( source, message,param);
//
//            if(event.command == "connector") isConnecting  =   true;
////        }
//    }
//
//
//    //--------------------------------------------------------------
//    void getDescendants()    {
//
//        descendants.clear();
//        getAllChildren(shared_from_this());
//        hasGotDescendants=true;
//
//    }
//
//
//    //--------------------------------------------------------------
//    void getDescendantsXY()  {
//        descendantsX.clear();
//        descendantsY.clear();
//
//        for (int i=0; i<descendants.size(); i++ )
//        {
//        	descendantsX.push_back(descendants[i]->x);
//            descendantsY.push_back(descendants[i]->y);
//        }
//
//    }
//
//
//    //--------------------------------------------------------------
//    void getAllChildren(shared_ptr<Node> parentNode)  {
//
//        // using recursion to find all nodes
//        // (based on http://stackoverflow.com/questions/177277/how-to-get-a-list-of-all-child-nodes-in-a-treeview-in-net)
//        for(int i = 0 ; i<parentNode->children.size(); i++)  {
//            descendants.push_back(parentNode->children[i]);
//            getAllChildren(parentNode->children[i]);
//        }
//    }
//
//
//    //--------------------------------------------------------------
//    int getBranch(shared_ptr<Node> descendantNode )    {
//
//        int currentBranch;
//
//            bool foundRoot = false;
//
//            for (int i=0; i<children.size(); i++ )
//            {
//                if( children[i] == descendantNode ) {
//                    currentBranch = i;
//                    foundRoot = true;
//                    break;
//                }
//            }
//
//            for (int i=0; i<children.size(); i++ )
//            {
//                children[i]->getDescendants();
//                for (int j = 0; j < children[ i ] -> descendants.size(); j++ )
//                {
//                    if( children[ i ]->descendants[ j ] == descendantNode )    {
//                        currentBranch = i;
//                        foundRoot = true;
//                        break;
//                    }
//
//                    if(foundRoot)   break;
//                }
//            }
//
//        return currentBranch;
//
//    }
//
//
//    shared_ptr<Node> shared_from_this()
//    {
//        return dynamic_pointer_cast<Node>(kWidget::shared_from_this());
//    }
//
//
//
//
//    bool hasBeenCreated;
//    bool isConnecting;
//
//
//    shared_ptr<Node>  parent;
//    vector<shared_ptr<Node> > children;
//
//    vector <shared_ptr<Node> > descendants;
//
//    vector <int> descendantsX;
//    vector <int> descendantsY;
//
//    vector< shared_ptr<kCircleButton> > connectors;
//
//    int recordX,recordY;
//
//    bool hasGotDescendants;
//
//    bool isActive;
//
//
//};










