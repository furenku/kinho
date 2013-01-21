#pragma once

#include "library.h"
#include "guiVideoObjects.h"

#ifndef archive_h
#define archive_h

class Node: public StoreObject{
    public:
        Node(){

        }
        void setX( int _x ) {
            x=_x;
        }
        void setY( int _y) {
            y=_y;
        }
        float getX() {
            return x;
        }
        float getY() {
            return y;
        }
    protected:

        int x, y;

};


class Field2D: public Storage {

    public:
        Field2D(){}


        shared_ptr<Node> getNode(string _name){
            return dynamic_pointer_cast<Node> ( getObject( _name ) );
        }


    protected:

        vector< shared_ptr < Node > > nodes;


};

class OntDisplay{};




class ArchiveWidget: public StoreObject, virtual public kCircleView, virtual public kDragObject {
    public:

        ArchiveWidget(){
            setType("archivewidget");
            setupVars();
            createEvents();
//            enableUpdate();
        }

    //f

        void setupVars(){
            draggingOntology="";
            autoArrange = false;
            isDraggable = true;
            isDroppable = false;
            hasBeenMadeDroppable = true;
            isMouseOn=false;


            makeDraggable(x,y);
        }

        void initialize() { }/*addBtnView(); addScrollView();}// currentView = btnView;}*/

        void createEvents() {
//            saveEvent("btnClicked");
//            saveEvent("ontologyClicked");
//            saveEvent("ontologyDragged");
//            saveEvent("mediaBtnClicked");
//            saveEvent("mediaDragged");
//
                saveEvent("btnClicked");
                saveEvent("drag");
                saveEvent("mainBtnClicked");
                saveEvent("mediaClicked");
                saveEvent("mediaDragged");
                saveEvent("ontologyDragged");
                saveEvent("ontologyDragged");

        }



        void draw(ofEventArgs & args){

            ofDrawBitmapString( name , x, y );

        }

        void addBtnView() {
            if(!btnView) {
                btnView = make_shared< kCircleButtonView >();
                btnView->disableUpdate();
            //setup
                btnView->set(0.5f,0.5f,0.3f,0.3f);
                addWidget( btnView );

            // create labels
                vector <string> labels;
                labels.push_back( "add" );
                labels.push_back( "open" );
                labels.push_back( "ontologies" );
                labels.push_back( "remove" );
                labels.push_back( "connect" );
                labels.push_back( "disconnect" );
                btnView->addButtons( labels );
                ofAddListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::btnClicked );

                arrangeWidgets();

}

        }

        void removeBtnView(){

            if(btnView) {

                btnView->hide();
                btnView->disable();
                btnView->disableUpdate();
                btnView->clearWidgets();

//                addDelete(btnView);
                btnView->hide();
                btnView->removeButtons();
//                btnView->removeFromVieew();

                ofRemoveListener( *btnView->events.lookup("btnClicked"),this,&ArchiveWidget::btnClicked);

                removeWidget(btnView);



                btnView.reset();
//                removeSubView();
//                arrangeWidgets();

            }

        }



        void removeBtnViewListeners(){
            ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::btnClicked );
            ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::ontologyClicked );
            ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::mediaClicked );
            ofRemoveListener( *btnView->events.lookup("drag"), this, &ArchiveWidget::ontologyDragged);
            ofRemoveListener( *btnView->events.lookup("drag"), this, &ArchiveWidget::mediaDragged );
        }

        void addScrollView() {
            scrollView = make_shared< kMediaScrollView >();
        //setup
            scrollView->set(0.5f,0.5f,width*2,height*2);

            addWidget( scrollView );

//            scrollView->initialize();

            arrangeWidgets();


            ofAddListener( *scrollView->events.lookup("btnClicked"), this, &ArchiveWidget::mediaClicked);
            ofAddListener( *scrollView->events.lookup("btnDragged"), this, &ArchiveWidget::mediaDragged );

            hideScrollView();

        }

        void showBtnView() {
            btnView->show();
            btnView->enable();
//            scrollView->hide();
//            scrollView->disable();
        }

        void hideBtnView() {
            btnView->hide();
            btnView->disable();
        }

        void showScrollView() {
            scrollView->show();
            scrollView->enable();
//            btnView->hide();
//            btnView->disable();
        }

        void hideScrollView() {
            scrollView->hide();
            scrollView->disable();
        }


        void hideViews() {
            hideBtnView();
            hideScrollView();
        }

        void toggleViews(){

            if( !btnView ) {
                addBtnView();
            }
            else{
                if(!btnView->mouseOnWidgets())
                removeBtnView();
            }

        }



        void loadBtnView(){
            showBtnView();
            currentView = btnView;
        }


        void loadOntologies( vector<string> _ontNames ) {

            hideBtnView();

            scrollView->addDragButtons( _ontNames );

            ofAddListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::ontologyClicked );
            ofAddListener( *btnView->events.lookup("drag"), this, &ArchiveWidget::ontologyDragged);

            currentView = scrollView;

            arrangeWidgets();
        }

        void loadMedia( vector < shared_ptr<MediaHolder> > _media ) {

            scrollView->clearWidgets();

            scrollView->addMedia( _media );

            arrangeWidgets();

            currentView = scrollView;

        }

        //interactividad

        //callbacks

        virtual void addContent(){

        }

        void btnClicked(widgetEvent & _event) {
            command = dynamic_pointer_cast<kButtonView>(_event.sender)->getCommand();

            notify("btnClicked");

        }


        string getCommand() { return command; }

        void ontologyClicked(widgetEvent & _event) {
            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("ontologyClicked");
        }

        void ontologyDragged(widgetEvent & _event) {
            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("ontologyDragged");
        }

        void mediaClicked(widgetEvent & _event) {

            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mediaBtnClicked");
        }

        void mediaDragged(widgetEvent & _event) {
            draggingMedia = dynamic_pointer_cast<MediaWidget>( _event.sender );
            notify("mediaDragged");
        }

        // drag

        string getDraggingOntology() {
            return draggingOntology;
        }

        shared_ptr<MediaWidget> getDraggingMedia() {
            return draggingMedia;
        }

        void mouseMoved( ofMouseEventArgs & mouse ){
            isMouseOn=inside(mouse.x,mouse.y);
            mouseX=mouse.x;
            mouseY=mouse.y;
        }

        void mouseDragged( ofMouseEventArgs & mouse ){
/*
            if(isBeingDragged && !view->inside(mouse.x,mouse.y))
                makeDroppable(mouse.x, mouse.y);

            else
            if(hasBeenMadeDroppable)
                makeDraggable(x,y);


            kDragObject::mouseDragged(mouse);


            if(inside(mouse.x,mouse.y)) {
                setRectInView();
                arrangeWidgets();
            }

*/
            mouseX = mouse.x;
            mouseY = mouse.y;

        }



        void mouseReleased( ofMouseEventArgs & mouse){

            if(hasBeenDragged )
                setRectInView();
            MouseObject::mouseReleased(mouse);

            sourceX = mouse.x;
            sourceY = mouse.y;


            mouseX = mouse.x;
            mouseY = mouse.y;

            kWidget::mouseReleased(mouse);

            notify("release");

        }


    //atts
    //protected:
        shared_ptr<kWidget> mainWidget;
        shared_ptr<MediaWidget> draggingMedia;
        string draggingOntology;

        shared_ptr<kButtonView> currentView;
        shared_ptr<kCircleButtonView> btnView;
        shared_ptr<kMediaScrollView> scrollView;
        string command;


};


class ArchiveMedia: public ArchiveWidget {

     public:

        ArchiveMedia(){
            setupVars();
//            createEvents();
        }

    //f

        void setupVars(){
            setType("media");
        }


        void setMedia( shared_ptr<MediaHolder> _media ) {
            media = _media;
            //delete mainwidget
            //check Media Type
                //create new main widget
                //set its content
//                ofAddListener..."press"...mediaMainClicked
        }
        //atts
        shared_ptr<MediaHolder> media;


};




class ArchiveClip: public ArchiveWidget {

     public:

        ArchiveClip(){
            setupVars();
            createEvents();
        }

        void createEvents() {
            saveEvent("mainBtnClicked");
        }
    //f

        void initialize() {

            ArchiveWidget::initialize();

            clipView = make_shared<kClip>( );

            clipView->set(0.5f,0.5f,0.3f,0.3f);

//            clipView->setClip( clip );

            addWidget( clipView );
            ofAddListener( *clipView->events.lookup("press"),this,&ArchiveClip::mediaClicked);


        }

        void setupVars(){
            ArchiveWidget::setupVars();
            setType("clip");

        }


        void setClip( shared_ptr<Clip> _clip ) {
            clip = _clip;
            clipView->setClip( clip );

            arrangeWidgets();
//            addWidget(clipView);
            //delete mainwidget
            //check Media Type
                //create new main widget
                //set its content
//                ofAddListener..."press"...mediaMainClicked
        }


        shared_ptr<Clip> getClip(){ return clip; }


        void mediaClicked(widgetEvent & _event) {
            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mainBtnClicked");
        }


        //atts
        shared_ptr<Clip> clip;
        shared_ptr<kClip> clipView;

};



class ArchiveOntology: public ArchiveWidget {

     public:

        ArchiveOntology(){
            setupVars();
//            createEvents();
        }

        void createEvents() {
            saveEvent("mainBtnClicked");
        }
    //f

        void initialize() {


            ArchiveWidget::initialize();


            shared_ptr<kCircleButton> btn = make_shared<kCircleButton>( );

            btn->set(0.5f,0.5f,0.3f,0.3f);
            btn->setLabel( ontology->getName() );
//            clipView->setClip( clip );

            addWidget( btn );
            btn->font(1);

            ofAddListener( *btn->events.lookup("press"),this,&ArchiveOntology::ontClicked);


        }

        void setupVars(){
            draggingOntology="";
            setType("ontology");
        }

        void setOntology( shared_ptr<Ontology> _ontology) {
            ontology = _ontology;
            //delete main Widget
            //create new main widget
            //set its content
//            ofAddListener..."press"...ontologyMainClicked
        }


        shared_ptr<Ontology> & getOntology() {
            return ontology;
        }

        void ontClicked(widgetEvent & _event) {
            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mainBtnClicked");
        }

        //atts
        shared_ptr<Ontology> ontology;


};







class Archive: public LibraryManager, virtual public kField2D, virtual public kDragSink {
    public:
        Archive(){
            createEvents();
            autoArrange = false;
        }
    //funcs
        //logica
            void createEvents() {
                saveEvent("addMedia");
                saveEvent("openMedia");
                saveEvent("createClip");
                saveEvent("openOntologies");
                saveEvent("createOntology");
                saveEvent("connectOntology");
                saveEvent("connectClip");
                saveEvent("release");
            }


            void loadFile( string _filename ) {
                //openXML
                //ontologies
                //clips
                //connections
            }

            shared_ptr<ArchiveWidget>   getNextWidget() { return nextWidget; }
            shared_ptr<ArchiveMedia>    getNextMedia() { return nextMedia; }
            shared_ptr<Clip>    getNextClip() { return nextClip; }
            shared_ptr<ArchiveOntology> getNextOntology() { return nextOntology; }

            void draw(ofEventArgs & args){

                kRectView::draw(args);

                vector< shared_ptr < StoreObject > > v;

                for (int i=0; i<widgets.size(); i++)
                {
//                    widgets[i]->show();

                    shared_ptr<ArchiveWidget>  aw = dynamic_pointer_cast<ArchiveWidget>( widgets[i] );


                	v = getChildren( aw );

                    ofSetColor(255,0,0);
                    shared_ptr<ArchiveWidget> w;
                	for (int j=0; j<v.size(); j++)
                	{
                	    w = dynamic_pointer_cast<ArchiveWidget>(v[j]);
                		ofLine( widgets[i]->getX() + widgets[i]->getWidth()/2,
                                widgets[i]->getY() + widgets[i]->getHeight()/2,
                                w->getX() + w->getWidth()/2,
                                w->getY() + w->getHeight()/2 );
                	}

                	v = getRelated( dynamic_pointer_cast<ArchiveWidget>(widgets[i]) );
                    ofSetColor(0,122,99);
                	for (int j=0; j<v.size(); j++)
                	{
                	    w = dynamic_pointer_cast<ArchiveWidget>(v[j]);
                		ofLine( widgets[i]->getX() + widgets[i]->getWidth()/2,
                                widgets[i]->getY() + widgets[i]->getHeight()/2,
                                w->getX() + w->getWidth()/2,
                                w->getY() + w->getHeight()/2 );
                	}
                }


                if( connectingClip ) {

                    float posX = connectingClip->getX() + connectingClip->getWidth()/2;
                    float posY = connectingClip->getY() + connectingClip->getHeight()/2;
                    ofLine( posX, posY, mouseX, mouseY );
                }
                if( connectingOntology ) {
                    float posX = connectingOntology->getX() + connectingOntology->getWidth()/2;
                    float posY = connectingOntology->getY() + connectingOntology->getHeight()/2;
                    ofLine( posX, posY, mouseX, mouseY );
                }


/*
                for (int i=0; i<connections.size(); i++)
                {

                    cout << connections[i].first->getX() << endl;
                	ofLine( connections[i].first->getX(),
                            connections[i].first->getY(),
                            connections[i].second->getX(),
                            connections[i].second->getY() );
                }
*/

            }

            void setLibrary( shared_ptr<Library> _library ) { library = _library; }
        //interactivity
            //{callbacks

            void mainBtnClicked( widgetEvent & _event ){

                nextWidget = dynamic_pointer_cast<ArchiveWidget>(_event.sender);
                if( connectingClip ) {
                    connect( connectingClip, nextWidget );
//                        nextWidget->hideViews();
                    connectedClip = connectingClip;

//                        connectedOntology = connectingOntology;
                    notify("connectClip");

                    connectingClip.reset();

                }
                if( connectingOntology ) {

                    connect( connectingOntology, nextWidget );

//                        nextWidget->hideViews();
                    connectedClip = dynamic_pointer_cast<ArchiveClip>(nextWidget);
                    connectedOntology = connectingOntology;

                    notify("connectOntology");

                    connectingOntology.reset();

                }

                //if( disconnectingMedia )
                //    disconnect( disconnectingMedia, nextMedia );
                else
                    notify("openMedia");
            }

            void ontologyMainClicked( widgetEvent & _event ) {
                nextOntology = dynamic_pointer_cast<ArchiveOntology>(_event.sender);
                if( connectingOntology )
                    connect( connectingOntology, nextOntology );
                if( disconnectingOntology )
                    disconnect( disconnectingOntology, nextOntology );
                else
                    notify("openMedia");
            }

            void btnClicked( widgetEvent & _event ) {

                nextWidget = dynamic_pointer_cast<ArchiveWidget>(_event.sender);

                command = nextWidget->getCommand();

//                    cout << command << endl;
                string type = nextWidget->getType();

                if( type == "media" || type == "clip" || type == "sample")
                    nextMedia = dynamic_pointer_cast<ArchiveMedia>(_event.sender);

                else if(nextWidget->getType() == "ontology")
                    nextOntology = dynamic_pointer_cast<ArchiveOntology>(_event.sender);



                if( command == "open" ) {
                    nextClip = dynamic_pointer_cast<ArchiveClip>(_event.sender)->getClip();
                    notify("openMedia");
                }
                else if( command == "add" ) {
                    nextClip = dynamic_pointer_cast<ArchiveClip>(_event.sender)->getClip();
                    notify("addMedia");
                }
                else if( command == "remove" ) {

                    disconnect(nextWidget);
                    removeWidget(nextWidget);
                    nextWidget.reset();


                }
                else if( command == "connect" ) {
                    connectingClip.reset();
                    connectingOntology.reset();
//                        cout << "connect" << endl;

//                        cout << type << endl;
//                        nextWidget->setWidth(0.6f);

                    connecting = true;

                    arrangeWidgets();

                    if( type == "media" || type == "clip" || type == "sample") {
                         connectingClip = dynamic_pointer_cast<ArchiveClip>(nextWidget);

                         cout << connectingClip->getType() << endl;
                    }
                    else if(nextWidget->getType() == "ontology"){

                        nextOntology = dynamic_pointer_cast<ArchiveOntology>(_event.sender);

                        connectingOntology = nextOntology;
                        connectedOntology = nextOntology;

                    }
                }
                else if( command == "disconnect" ) {
                    disconnect(nextWidget);
                }

                else if( command == "ontologies" )
                    notify("openOntologies");
            }

            void mediaClicked( widgetEvent & _event ) {
                draggingMedia = dynamic_pointer_cast<ArchiveMedia>(_event.sender)->getDraggingMedia();
                if(connectingClip) {
                    setRelated(connectingClip, draggingMedia );
                    draggingMedia.reset();
                }
            }

            void mediaDragged( widgetEvent & _event ) {
                draggingMedia = dynamic_pointer_cast<ArchiveWidget>(_event.sender)->getDraggingMedia();
            }

            void ontologyClicked( widgetEvent & _event ) {
                if(connectingOntology) {
                    setHierarchy(connectingOntology, dynamic_pointer_cast<ArchiveWidget>(_event.sender) );
                    draggingOntology="";
                } else {
                    draggingOntology = dynamic_pointer_cast<ArchiveWidget>(_event.sender)->getDraggingOntology();
                }
            }

            void ontologyDragged( widgetEvent & _event ) {
                draggingOntology = dynamic_pointer_cast<ArchiveWidget>(_event.sender)->getDraggingOntology();
            }

            void widgetDragged( widgetEvent & _event ) {
                updateConnections();
            }



            //}


            //get drag objects
                string getDraggingOntology() {
                    return draggingOntology;
                }

                shared_ptr< MediaWidget > getDraggingMedia() { return draggingMedia; }

            //{mouse

            void mouseReleased(ofMouseEventArgs & mouse) {

                mouseX = mouse.x;
                mouseY = mouse.y;

                cout << "X: "<<mouseX << " Y: "<<mouseY << " inside: "<< inside(mouseX,mouseY)<<endl;
//                if( inside( mouseX,mouseY ) ) {
//                    if( draggingOntology != "" ) {
//                        addOntology( draggingOntology, mouse.x, mouse.y );
//                    }
//                    if( draggingMedia ) {
//                        string type = draggingMedia->getType();
//                        //check type
//                        if(type == "clip" ) {
//                            shared_ptr<Clip> clip = dynamic_pointer_cast<Clip>(draggingMedia);
//                            addClip(clip,mouse.x,mouse.y);
//                        }
//                        if(type == "sample" ) {
//                                shared_ptr<Sample> sample = dynamic_pointer_cast<Sample>(draggingMedia);
//                                addSample(sample, mouse.x, mouse.y);
//                        }
////                        if(type == "text" ) {
////                                shared_ptr<Text> text = dynamic_pointer_cast<Text>(draggingMedia);
////                                addText(text, mouse.x, mouse.y);
////                        }
//                    }
//                    else {
//                        notify("release");
//                    }

                    notify("release");


                draggingOntology = ""; draggingMedia.reset();

                if(connecting && !mouseOnWidgets()) {
                    connectingClip.reset(); connectingOntology.reset();
                    connecting = false;
                }


            }

            void mouseMoved(ofMouseEventArgs & mouse) {
                kWidget::mouseMoved(mouse);

                mouseX = mouse.x;
                mouseY = mouse.y;
            }

            void mouseDragged(ofMouseEventArgs & mouse) {
                mouseX = mouse.x;
                mouseY = mouse.y;
            }


//                    updateConnections()

            //}

        //add
        void addOntology( shared_ptr<Ontology> _ont, float _x, float _y ) {

            shared_ptr<ArchiveOntology> ont = make_shared<ArchiveOntology>();

            float offsetX = (0.2f)/2;
            float offsetY = (0.2f)/2;

            ont->set(_x-offsetX, _y-offsetY, 0.2f, 0.2f);

            ont->setOntology( _ont );
            addListeners(ont);
            addWidget(ont);

            ont->initialize();

//                archiveWidgets.push_back(ont);
        }

        void addOntology( string _ontName, float _x, float _y ) {

            shared_ptr<Ontology> ontology = library->getOntology( _ontName );
            shared_ptr<ArchiveOntology> ont = make_shared<ArchiveOntology>();

            float offsetX = (0.2f)/2;
            float offsetY = (0.2f)/2;

            ont->set(_x-offsetX, _y-offsetY, 0.2f, 0.2f);

            ont->setOntology( ontology );
            addListeners(ont);
            addWidget(ont);
            ont->initialize();

        }


        void addListeners( shared_ptr<ArchiveWidget> _w ) {
            ofAddListener( *_w->events.lookup("btnClicked"),this,&Archive::btnClicked);
            ofAddListener( *_w->events.lookup("drag"),this,&Archive::widgetDragged);
            ofAddListener( *_w->events.lookup("mainBtnClicked"),this,&Archive::mainBtnClicked);
            ofAddListener( *_w->events.lookup("mediaClicked"),this,&Archive::mediaClicked);
            ofAddListener( *_w->events.lookup("mediaDragged"),this,&Archive::mediaDragged);
            ofAddListener( *_w->events.lookup("ontologyDragged"),this,&Archive::ontologyDragged);
            ofAddListener( *_w->events.lookup("ontologyDragged"),this,&Archive::ontologyDragged);

        }



        void addClip( shared_ptr<Clip> _clip, float _x, float _y ) {

            shared_ptr<ArchiveClip> clip = make_shared<ArchiveClip>();

            float offsetX = (0.2f)/2;
            float offsetY = (0.2f)/2;

            clip->set(_x-offsetX, _y-offsetY, 0.2f, 0.2f);

cout << _x-offsetX << endl;
            addWidget(clip);

            clip->initialize();
            clip->setClip(_clip);

            addListeners(clip);


        }


        void addSample( shared_ptr<Sample> _sample, float _x, float _y ) {
////                shared_ptr<ArchiveSample> sample = make_shared<kArchiveSample>()
//
//            float offsetX = (0.2f)/2;
//            float offsetY = (0.2f)/2;
//
//            clip->set(_x-offsetX, _y-offsetY, 0.2f, 0.2f);
//
////                sample->set(_x,_y);
////                sample->setSample(_sample);
////                addListeners(sample);
////                addWidget(sample);
////                archiveWidgets.push_back(ont);
            }

////            void addText( shared_ptr<Text> _text  , float _x, float _y ) {
////                shared_ptr<ArchiveText> text  = make_shared<kArchiveText>()
//
//            float offsetX = (0.2f)/2;
//            float offsetY = (0.2f)/2;
//
//            clip->set(_x-offsetX, _y-offsetY, 0.2f, 0.2f);
//
//
////                text ->set(_x,_y);
////                text->setText(_text);
////                addListeners(text);
////                addWidget(text);
////                archiveWidgets.push_back(ont);
////            }

        //connections

        void connect(shared_ptr<ArchiveWidget> _media1, shared_ptr<ArchiveWidget> _media2) {
            setRelated( _media1, _media2 );
//                createConnection(_media1,_media2);
        }

        void connect(shared_ptr<ArchiveMedia> _media1, shared_ptr<ArchiveMedia> _media2) {
            setRelated( _media1, _media2 );
//                createConnection(_media1,_media2);
        }

        void connect(shared_ptr<ArchiveMedia> _media, shared_ptr<ArchiveOntology> _ont) {
            setRelated( _ont, _media );
//                createConnection(_media1,_media2);
        }

        void connect(shared_ptr<ArchiveOntology> _ont , shared_ptr<ArchiveMedia> _media) {
            setHierarchy(_ont, _media );
              nextOntology = _ont;
            connectingClip = dynamic_pointer_cast<ArchiveClip>(_media);

//                notify("connectedOntology");
        }

        void connect(shared_ptr<ArchiveOntology> _ont1 , shared_ptr<ArchiveOntology> _ont2 ) {
            bool hierarchy = false;
            if (   ( _ont1->getType() == "category"
                    && _ont2->getType() != "category" )
                    ||
                    ( _ont1->getType() != "category"
                    && _ont2->getType()  == "category" ))
                hierarchy = true;

            if( hierarchy )
                setHierarchy( _ont1, _ont2 );
            else
                setRelated( _ont1, _ont2 );
        }

        void createConnection(shared_ptr<ArchiveWidget> _w1, shared_ptr<ArchiveWidget> _w2) {
                connections.push_back( make_pair( _w1, _w2 ) );
                shared_ptr<kCircleButton> btn = make_shared<kCircleButton> ();
                btn->setLabel("x");
                ofAddListener( *btn->events.lookup("press"), this, &Archive::disconnect);
                connectionWidgets.push_back(btn);

cout << _w1->getX() << endl;

cout << connections.size() << endl;

                updateConnections();
//                    ofAddListener..."removeConnection"...disconnect

            }


        //disconnect

        void disconnect( shared_ptr<ArchiveWidget> _w) {
            removeObject(_w );
        }

        void disconnect( widgetEvent & _event ) {
            //get position in array
            //get widget pair
            //delete widget from array
            //get widget types
            //dynamic_pointer_cast<type>
//                disconnect( cast1,cast2 )
        }

        void disconnect(shared_ptr<ArchiveMedia> _media1, shared_ptr<ArchiveMedia> _media2){
            removeRelated( _media1, _media2 );

        }

        void disconnect(shared_ptr<ArchiveOntology> _ont , shared_ptr<ArchiveMedia> _media){
            removeHierarchy(_ont, _media );
        }

        void disconnect(shared_ptr<ArchiveOntology> _ont1 , shared_ptr<ArchiveOntology> _ont2 ) {
                bool hierarchy = false;
                if (    (_ont1->getType() == "category"
                        && _ont2->getType() != "category" )
                        ||
                        ( _ont1->getType() != "category"
                        && _ont2->getType()  == "category" ))

                    hierarchy = true;
                if( hierarchy )
                    removeHierarchy( _ont1, _ont2 );
                else
                    removeRelated( _ont1, _ont2 );
            }



        void updateConnections() {
            for (int i=0; i<connections.size(); i++)
            {
                float x1, y1, x2, y2;
                x1 = connections[i].first->getX();
                x2 = connections[i].second->getX();
                y1 = connections[i].first->getY();
                y2 = connections[i].second->getY();
            // get middle point of every connection
                ofPoint middle = ofPoint( (x1+x2)/2, (y1+y2)/2 );
            // place widget there
                connectionWidgets[i]->set(middle.x / width, middle.y / height, 0.05f, 0.05f);

            }
            arrangeWidgets();
        }

        vector< shared_ptr < ArchiveWidget > > getWidgets() {
            vector< shared_ptr < ArchiveWidget > > v;

            for (int i=0; i<widgets.size(); i++)
            {
            	v.push_back( dynamic_pointer_cast<ArchiveWidget>(widgets[i]) );
            }
            return v;
        }
/*


        vector< shared_ptr < ArchiveOntology > > & getOntologyWidgets() {
            return ontologyWidgets;
        }

        vector< shared_ptr < ArchiveMedia > > & getMediaWidgets() {
            return mediaWidgets;
        }
*/
    //atts
//        vector< shared_ptr < ArchiveOntology > > ontologyWidgets;
//        vector< shared_ptr < ArchiveMedia > > mediaWidgets;
//        vector< shared_ptr < ArchiveWidget > > archiveWidgets;


        shared_ptr<ArchiveMedia> nextMedia, connectingMedia, disconnectingMedia;
        shared_ptr<ArchiveClip> connectingClip, connectedClip;
        shared_ptr<MediaWidget> draggingMedia;
        shared_ptr<ArchiveWidget> nextWidget, connectingWidget;
        shared_ptr<ArchiveOntology> nextOntology, connectingOntology, connectedOntology, disconnectingOntology;
        string draggingOntology;
        shared_ptr<Library> library;
        shared_ptr<Category> connectedCategory;

        vector < pair< shared_ptr<ArchiveWidget>, shared_ptr<ArchiveWidget> > > connections;

        vector< shared_ptr < kCircleButton > > connectionWidgets;

        shared_ptr<Clip> nextClip;

        bool connecting;



//                void removeObject( shared_ptr<ArchiveWidget>  _w) {
//                    removeObject(_w);
//                    removeWidget(_w);
//                }

};







/*

class Archive: public LibraryManager{
    public:
        Archive(){

            field = make_shared<Field2D>();
            field->setName("field1");
            shared_ptr<Node> node = make_shared<Node>( );
            node->setName("node1");
            node->setX(30);
            node->setY(30);
            field->addObject(node);
            int tin= field->getNode("node1")->getX();
            cout <<  tin  << endl;


        }


    protected:
        shared_ptr<Field2D> field;

};

*/
#endif
