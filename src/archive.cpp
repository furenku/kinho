#include "archive.h"

//    view["archive"] = make_shared<kArchiveView>();
//    view["archive"]->set(300,30,700,708);
//    view["archive"]->applySettings ( settings );
//    view["archive"]->setWidgetSettings( settings2 );
//    view["archive"]->initialize();




Node::Node(){
}
void Node::setX( int _x ) {
    x=_x;
}
void Node::setY( int _y) {
    y=_y;
}
float Node::getX() {
    return x;
}
float Node::getY() {
    return y;
}


shared_ptr<Node> Field2D::getNode(string _name){
    return dynamic_pointer_cast<Node> ( getObject( _name ) );
}




ArchiveWidget::ArchiveWidget(){
    setType("archivewidget");
    setupVars();
    createEvents();
//            enableUpdate();
}







void ArchiveWidget::setupVars(){
    draggingOntology="";
    autoArrange = false;
    isDraggable = true;
    isDroppable = false;
    hasBeenMadeDroppable = true;
    isMouseOn=false;


    makeDraggable(x,y);
}

void ArchiveWidget::initialize() { }/*addBtnView(); addScrollView();}// currentView = btnView;}*/

void ArchiveWidget::createEvents() {
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



void ArchiveWidget::draw(ofEventArgs & args){

    ofDrawBitmapString( name , x, y );

}

void ArchiveWidget::addBtnView() {
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

void ArchiveWidget::removeBtnView(){

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



void ArchiveWidget::removeBtnViewListeners(){
    ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::btnClicked );
    ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::ontologyClicked );
    ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::mediaClicked );
    ofRemoveListener( *btnView->events.lookup("drag"), this, &ArchiveWidget::ontologyDragged);
    ofRemoveListener( *btnView->events.lookup("drag"), this, &ArchiveWidget::mediaDragged );
}

void ArchiveWidget::addScrollView() {
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

void ArchiveWidget::showBtnView() {
    btnView->show();
    btnView->enable();
//            scrollView->hide();
//            scrollView->disable();
}

void ArchiveWidget::hideBtnView() {
    btnView->hide();
    btnView->disable();
}

void ArchiveWidget::showScrollView() {
    scrollView->show();
    scrollView->enable();
//            btnView->hide();
//            btnView->disable();
}

void ArchiveWidget::hideScrollView() {
    scrollView->hide();
    scrollView->disable();
}


void ArchiveWidget::hideViews() {
    hideBtnView();
    hideScrollView();
}

void ArchiveWidget::toggleViews(){

    if( !btnView ) {
        addBtnView();
    }
    else{
        if(!btnView->mouseOnWidgets())
        removeBtnView();
    }

}



void ArchiveWidget::loadBtnView(){
    showBtnView();
    currentView = btnView;
}


void ArchiveWidget::loadOntologies( vector<string> _ontNames ) {

    hideBtnView();

    scrollView->addDragButtons( _ontNames );

    ofAddListener( *btnView->events.lookup("btnClicked"), this, &ArchiveWidget::ontologyClicked );
    ofAddListener( *btnView->events.lookup("drag"), this, &ArchiveWidget::ontologyDragged);

    currentView = scrollView;

    arrangeWidgets();
}

void ArchiveWidget::loadMedia( vector < shared_ptr<MediaHolder> > _media ) {

    scrollView->clearWidgets();

    scrollView->addMedia( _media );

    arrangeWidgets();

    currentView = scrollView;

}

//interactividad

//callbacks

void ArchiveWidget::addContent(){

}

void ArchiveWidget::btnClicked(widgetEvent & _event) {
    command = dynamic_pointer_cast<kButtonView>(_event.sender)->getCommand();

    notify("btnClicked");

}


string ArchiveWidget::getCommand() { return command; }

void ArchiveWidget::ontologyClicked(widgetEvent & _event) {
    draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
    notify("ontologyClicked");
}

void ArchiveWidget::ontologyDragged(widgetEvent & _event) {
    draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
    notify("ontologyDragged");
}

void ArchiveWidget::mediaClicked(widgetEvent & _event) {

    toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
    notify("mediaBtnClicked");
}

void ArchiveWidget::mediaDragged(widgetEvent & _event) {
    draggingMedia = dynamic_pointer_cast<MediaWidget>( _event.sender );
    notify("mediaDragged");
}

// drag

string ArchiveWidget::getDraggingOntology() {
    return draggingOntology;
}

shared_ptr<MediaWidget> ArchiveWidget::getDraggingMedia() {
    return draggingMedia;
}

void ArchiveWidget::mouseMoved( ofMouseEventArgs & mouse ){
    isMouseOn=inside(mouse.x,mouse.y);
    mouseX=mouse.x;
    mouseY=mouse.y;
}

void ArchiveWidget::mouseDragged( ofMouseEventArgs & mouse ){
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



void ArchiveWidget::mouseReleased( ofMouseEventArgs & mouse){

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






ArchiveMedia::ArchiveMedia(){
    setupVars();
//            createEvents();
}

//f

void ArchiveMedia::setupVars(){
    setType("media");
}


void ArchiveMedia::setMedia( shared_ptr<MediaHolder> _media ) {
    media = _media;
    //delete mainwidget
    //check Media Type
        //create new main widget
        //set its content
//                ofAddListener..."press"...mediaMainClicked
}










ArchiveClip::ArchiveClip(){
    setupVars();
    createEvents();
}

void ArchiveClip::createEvents() {
    saveEvent("mainBtnClicked");
}
//f

void ArchiveClip::initialize() {

    ArchiveWidget::initialize();

    clipView = make_shared<kClip>( );

    clipView->set(0.5f,0.5f,0.3f,0.3f);

//            clipView->setClip( clip );

    addWidget( clipView );
    ofAddListener( *clipView->events.lookup("press"),this,&ArchiveClip::mediaClicked);


}

void ArchiveClip::setupVars(){
    ArchiveWidget::setupVars();
    setType("clip");

}


void ArchiveClip::setClip( shared_ptr<Clip> _clip ) {
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


shared_ptr<Clip> ArchiveClip::getClip(){ return clip; }


void ArchiveClip::mediaClicked(widgetEvent & _event) {
    toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
    notify("mainBtnClicked");
}







ArchiveOntology::ArchiveOntology(){
    setupVars();
//            createEvents();
}

void ArchiveOntology::createEvents() {
    saveEvent("mainBtnClicked");
}

//f

void ArchiveOntology::initialize() {


    ArchiveWidget::initialize();


    shared_ptr<kCircleButton> btn = make_shared<kCircleButton>( );

    btn->set(0.5f,0.5f,0.3f,0.3f);
    btn->setLabel( ontology->getName() );
//            clipView->setClip( clip );

    addWidget( btn );
    btn->font(1);

    ofAddListener( *btn->events.lookup("press"),this,&ArchiveOntology::ontClicked);


}

void ArchiveOntology::setupVars(){
    draggingOntology="";
    setType("ontology");
}

void ArchiveOntology::setOntology( shared_ptr<Ontology> _ontology) {
    ontology = _ontology;
    //delete main Widget
    //create new main widget
    //set its content
//            ofAddListener..."press"...ontologyMainClicked
}


shared_ptr<Ontology> & ArchiveOntology::getOntology() {
    return ontology;
}

void ArchiveOntology::ontClicked(widgetEvent & _event) {
    toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
    notify("mainBtnClicked");
}



















Archive::Archive(){
    createEvents();
    autoArrange = false;
}
//funcs
//logica
    void Archive::createEvents() {
        saveEvent("addMedia");
        saveEvent("openMedia");
        saveEvent("createClip");
        saveEvent("openOntologies");
        saveEvent("createOntology");
        saveEvent("connectOntology");
        saveEvent("connectClip");
        saveEvent("release");
    }


    void Archive::loadFile( string _filename ) {
        //openXML
        //ontologies
        //clipsfa
        //connections
    }

    shared_ptr<ArchiveWidget>   Archive::getNextWidget() { return nextWidget; }
    shared_ptr<ArchiveMedia>    Archive::getNextMedia() { return nextMedia; }
    shared_ptr<Clip>    Archive::getNextClip() { return nextClip; }
    shared_ptr<ArchiveOntology> Archive::getNextOntology() { return nextOntology; }

    void Archive::draw(ofEventArgs & args){

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

    void Archive::setLibrary( shared_ptr<Library> _library ) { library = _library; }
//interactivity
    //{callbacks

    void Archive::mainBtnClicked( widgetEvent & _event ){

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

    void Archive::ontologyMainClicked( widgetEvent & _event ) {
        nextOntology = dynamic_pointer_cast<ArchiveOntology>(_event.sender);
        if( connectingOntology )
            connect( connectingOntology, nextOntology );
        if( disconnectingOntology )
            disconnect( disconnectingOntology, nextOntology );
        else
            notify("openMedia");
    }

    void Archive::btnClicked( widgetEvent & _event ) {

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

    void Archive::mediaClicked( widgetEvent & _event ) {
        draggingMedia = dynamic_pointer_cast<ArchiveMedia>(_event.sender)->getDraggingMedia();
        if(connectingClip) {
            setRelated(connectingClip, draggingMedia );
            draggingMedia.reset();
        }
    }

    void Archive::mediaDragged( widgetEvent & _event ) {
        draggingMedia = dynamic_pointer_cast<ArchiveWidget>(_event.sender)->getDraggingMedia();
    }

    void Archive::ontologyClicked( widgetEvent & _event ) {
        if(connectingOntology) {
            setHierarchy(connectingOntology, dynamic_pointer_cast<ArchiveWidget>(_event.sender) );
            draggingOntology="";
        } else {
            draggingOntology = dynamic_pointer_cast<ArchiveWidget>(_event.sender)->getDraggingOntology();
        }
    }

    void Archive::ontologyDragged( widgetEvent & _event ) {
        draggingOntology = dynamic_pointer_cast<ArchiveWidget>(_event.sender)->getDraggingOntology();
    }

    void Archive::widgetDragged( widgetEvent & _event ) {
        updateConnections();
    }



    //}


    //get drag objects
        string Archive::getDraggingOntology() {
            return draggingOntology;
        }

        shared_ptr< MediaWidget > Archive::getDraggingMedia() { return draggingMedia; }

    //{mouse

    void Archive::mouseReleased(ofMouseEventArgs & mouse) {

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

    void Archive::mouseMoved(ofMouseEventArgs & mouse) {
        kWidget::mouseMoved(mouse);

        mouseX = mouse.x;
        mouseY = mouse.y;
    }

    void Archive::mouseDragged(ofMouseEventArgs & mouse) {
        mouseX = mouse.x;
        mouseY = mouse.y;
    }


//                    updateConnections()

    //}

//add
void Archive::addOntology( shared_ptr<Ontology> _ont, float _x, float _y ) {

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

void Archive::addOntology( string _ontName, float _x, float _y ) {

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


void Archive::addListeners( shared_ptr<ArchiveWidget> _w ) {
    ofAddListener( *_w->events.lookup("btnClicked"),this,&Archive::btnClicked);
    ofAddListener( *_w->events.lookup("drag"),this,&Archive::widgetDragged);
    ofAddListener( *_w->events.lookup("mainBtnClicked"),this,&Archive::mainBtnClicked);
    ofAddListener( *_w->events.lookup("mediaClicked"),this,&Archive::mediaClicked);
    ofAddListener( *_w->events.lookup("mediaDragged"),this,&Archive::mediaDragged);
    ofAddListener( *_w->events.lookup("ontologyDragged"),this,&Archive::ontologyDragged);
    ofAddListener( *_w->events.lookup("ontologyDragged"),this,&Archive::ontologyDragged);

}



void Archive::addClip( shared_ptr<Clip> _clip, float _x, float _y ) {

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


void Archive::addSample( shared_ptr<Sample> _sample, float _x, float _y ) {
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

void Archive::connect(shared_ptr<ArchiveWidget> _media1, shared_ptr<ArchiveWidget> _media2) {
    setRelated( _media1, _media2 );
//                createConnection(_media1,_media2);
}

void Archive::connect(shared_ptr<ArchiveMedia> _media1, shared_ptr<ArchiveMedia> _media2) {
    setRelated( _media1, _media2 );
//                createConnection(_media1,_media2);
}

void Archive::connect(shared_ptr<ArchiveMedia> _media, shared_ptr<ArchiveOntology> _ont) {
    setRelated( _ont, _media );
//                createConnection(_media1,_media2);
}

void Archive::connect(shared_ptr<ArchiveOntology> _ont , shared_ptr<ArchiveMedia> _media) {
    setHierarchy(_ont, _media );
      nextOntology = _ont;
    connectingClip = dynamic_pointer_cast<ArchiveClip>(_media);

//                notify("connectedOntology");
}

void Archive::connect(shared_ptr<ArchiveOntology> _ont1 , shared_ptr<ArchiveOntology> _ont2 ) {
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

void Archive::createConnection(shared_ptr<ArchiveWidget> _w1, shared_ptr<ArchiveWidget> _w2) {
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

void Archive::disconnect( shared_ptr<ArchiveWidget> _w) {
    removeObject(_w );
}

void Archive::disconnect( widgetEvent & _event ) {
    //get position in array
    //get widget pair
    //delete widget from array
    //get widget types
    //dynamic_pointer_cast<type>
//                disconnect( cast1,cast2 )
}

void Archive::disconnect(shared_ptr<ArchiveMedia> _media1, shared_ptr<ArchiveMedia> _media2){
    removeRelated( _media1, _media2 );

}

void Archive::disconnect(shared_ptr<ArchiveOntology> _ont , shared_ptr<ArchiveMedia> _media){
    removeHierarchy(_ont, _media );
}

void Archive::disconnect(shared_ptr<ArchiveOntology> _ont1 , shared_ptr<ArchiveOntology> _ont2 ) {
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



void Archive::updateConnections() {
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

vector< shared_ptr < ArchiveWidget > > Archive::getWidgets() {
    vector< shared_ptr < ArchiveWidget > > v;

    for (int i=0; i<widgets.size(); i++)
    {
        v.push_back( dynamic_pointer_cast<ArchiveWidget>(widgets[i]) );
    }
    return v;
}

/*


vector< shared_ptr < ArchiveOntology > > & Archive::getOntologyWidgets() {
    return ontologyWidgets;
}

vector< shared_ptr < ArchiveMedia > > & Archive::getMediaWidgets() {
    return mediaWidgets;
}
*/



