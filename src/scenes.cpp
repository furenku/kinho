
#include "scenes.h"



//{ SCENEWIDGETS

        SceneWidget::SceneWidget(){
            setType("scenewidget");
            setupVars();
            createEvents();
            enableUpdate();
            lockDrag();
        }

    //f

        void SceneWidget::setupVars(){
            autoArrange = false;
            isDraggable = true;
            isDroppable = false;
            hasBeenMadeDroppable = true;
            isMouseOn=false;


            makeDraggable(x,y);
        }

        void SceneWidget::initialize() { }/*addBtnView(); addScrollView();}// currentView = btnView;}*/

        void SceneWidget::createEvents() {
//            saveEvent("btnClicked");
//            saveEvent("ontologyClicked");
//            saveEvent("ontologyDragged");
//            saveEvent("mediaBtnClicked");
//            saveEvent("mediaDragged");
//
                saveEvent("btnClicked");
                saveEvent("drag");
                saveEvent("release");
                saveEvent("press");
                saveEvent("mainBtnClicked");

        }



        void SceneWidget::draw(ofEventArgs & args){
            ofDrawBitmapString( name , x, y );
        }

        void SceneWidget::addBtnView() {
            if(!btnView) {
                btnView = make_shared< kCircleButtonView >();
                btnView->disableUpdate();
            //setup
                btnView->set(0.5,0.5,1,1);
                addWidget( btnView );

            // create labels
                vector <string> labels;
                labels.push_back( "play" );
                //labels.push_back( "open" );
                labels.push_back( "next" );
                labels.push_back( "remove" );
                labels.push_back( "disconnect" );

                btnView->addButtons( labels );
                ofAddListener( *btnView->events.lookup("btnClicked"), this, &SceneWidget::btnClicked );

                arrangeWidgets();

}

        }

        void SceneWidget::removeBtnView(){

            if(btnView) {

                btnView->disable();
                btnView->disableUpdate();

                addDelete(btnView);

                btnView.reset();

            }

        }



        void SceneWidget::removeBtnViewListeners(){
            ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &SceneWidget::btnClicked );
        }

        void SceneWidget::addScrollView() {
            scrollView = make_shared< kMediaScrollView >();
        //setup
            scrollView->set(0.5f,0.5f,width*2,height*2);

            addWidget( scrollView );

//            scrollView->initialize();

            arrangeWidgets();


            hideScrollView();

        }

        void SceneWidget::showBtnView() {
            btnView->show();
            btnView->enable();
//            scrollView->hide();
//            scrollView->disable();
        }

        void SceneWidget::hideBtnView() {
            btnView->hide();
            btnView->disable();
        }

        void SceneWidget::showScrollView() {
            scrollView->show();
            scrollView->enable();
//            btnView->hide();
//            btnView->disable();
        }

        void SceneWidget::hideScrollView() {
            scrollView->hide();
            scrollView->disable();
        }


        void SceneWidget::hideViews() {
            hideBtnView();
            hideScrollView();
        }

        void SceneWidget::toggleViews(){

            if( !btnView ) {
                addBtnView();
            }
            else{
                if(!btnView->mouseOnWidgets())
                removeBtnView();
            }

        }



        void SceneWidget::loadBtnView(){
            showBtnView();
            currentView = btnView;
        }



        void SceneWidget::loadMedia( vector < shared_ptr<MediaHolder> > _media ) {

            scrollView->clearWidgets();

            scrollView->addMedia( _media );

            arrangeWidgets();

            currentView = scrollView;

        }

        //interactividad

        //callbacks

        void SceneWidget::addContent(){

        }

        void SceneWidget::btnClicked(widgetEvent & _event) {
            command = dynamic_pointer_cast<kButtonView>(_event.sender)->getCommand();
            notify("btnClicked");
            if(btnView) removeBtnView();
        }


        string SceneWidget::getCommand() { return command; }

        void SceneWidget::mediaClicked(widgetEvent & _event) {

//            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mediaBtnClicked");
        }


        void SceneWidget::mouseMoved( ofMouseEventArgs & mouse ){
//
//            if( mouseX>x && mouseX<x+width && mouseY>y && mouseY<y+height) {
//                isMouseOn=true;
//            } else {
//                isMouseOn=false;
//            }
////
            kWidget::mouseMoved(mouse);
            isMouseOn = DrawObject::inside(mouse.x,mouse.y);
        }


        void SceneWidget::lockDrag() {
            dragLocked = true;
        }
        void SceneWidget::unlockDrag() {
            dragLocked = false;
        }

        void SceneWidget::mouseDragged( ofMouseEventArgs & mouse ){

            if ( ! dragLocked ) {

                if(isBeingDragged && !view->inside(mouse.x,mouse.y))
                    makeDroppable(mouse.x, mouse.y);

                else
                if(hasBeenMadeDroppable)
                    makeDraggable(x,y);

                if( hasBeenPressed ) { //(mouse.x,mouse.y)) {
                    kDragObject::mouseDragged(mouse);

                    setRectInView();
                    arrangeWidgets();

                }


                mouseX = mouse.x;
                mouseY = mouse.y;

            }


        }



        void SceneWidget::mousePressed( ofMouseEventArgs & mouse){
             kWidget::mousePressed(mouse);
             if( isMouseOn ) {
                notify("press");
             }
        }


        void SceneWidget::mouseReleased( ofMouseEventArgs & mouse){

            if(hasBeenDragged )
                setRectInView();

            sourceX = mouse.x;
            sourceY = mouse.y;

            if( name != "root" ) {
                if( ! hasBeenDragged && isMouseOn ) {
                    toggleViews();
                }

                if( !isMouseOn) {
                    if(btnView)
                        removeBtnView();
                }
            }

            MouseObject::mouseReleased(mouse);

            mouseX = mouse.x;
            mouseY = mouse.y;


            kWidget::mouseReleased(mouse);

//            notify("release");

        }



    SceneRoot::SceneRoot(){ setType("sceneRoot"); setName("root"); }

    void SceneRoot::draw(ofEventArgs & args){
        ofCircle(x,y,20);
        ofDrawBitmapString("root",x,y);
    }



//}


//{ SCENECLIP

        SceneClip::SceneClip(){
            setupVars();
            createEvents();

        }

        void SceneClip::createEvents() {
            saveEvent("mainBtnClicked");
        }
    //f


        void SceneClip::draw(ofEventArgs & args){
//            SceneWidget::draw(args);

//            ofCircle(x,y,width);
//            ofDrawBitmapString(name,x,y);
        }

        void SceneClip::initialize() {

            SceneWidget::initialize();

            clipView = make_shared<kClip>( );

            clipView->set(0,0,1,1);

//            clipView->setClip( clip );

            addWidget( clipView );
            ofAddListener( *clipView->events.lookup("press"),this,&SceneClip::mediaClicked);

            arrangeWidgets();


        }

        void SceneClip::setupVars(){
            SceneWidget::setupVars();
            setType("clip");

        }


        void SceneClip::setClip( shared_ptr<Clip> _clip ) {
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


        shared_ptr<Clip> SceneClip::getClip( ) {
            return clip;

        }

        void SceneClip::mediaClicked(widgetEvent & _event) {
//            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mainBtnClicked");
        }

        void SceneClip::setPosition( float _pos ){
            savedPosition = _pos;
        }


//}


//{ SCENEBUILDER

        SceneBuilder::SceneBuilder(){
            autoArrange = false;
            insertThreshold = 30;
            autoConnectThreshold = ofGetWidth() / 10;
        }

        void SceneBuilder::initialize() {

            root = make_shared<SceneRoot>( ),
            root -> set(0.5f, 0.5f,0.05f, 0.05f );
            root->setActiveRange(2);
            addWidget(root);

            ofAddListener( *root->events.lookup("press"),this,&SceneBuilder::rootClicked );

            shared_ptr<kRectButtonView> btns = make_shared<kRectButtonView>( );
            btns->set(0,0,0.25f,0.085f);
            btns->setSpacingX(40);

            addWidget(btns);

            vector<string> labels;

            labels.push_back("play");
            labels.push_back("pause");

            labels.push_back("->");
            labels.push_back("<-");
            labels.push_back("|");

            btns->addButtons( labels );

            ofAddListener( *btns->events.lookup("btnClicked"),this,&SceneBuilder::btnClicked );

            arrangeWidgets();

            saveEvent("playClip");
        }

        void SceneBuilder::createEvents(){
            saveEvent("playClip");
            saveEvent("stop");
            saveEvent("branchEnd");
        }

        void SceneBuilder::iiinit(){

//            for (int i=0; i<7; i++)
//            {
//                shared_ptr<SceneWidget> wdgt = make_shared<SceneWidget>( );
//                w.push_back( wdgt );
//
//                wdgt->set( ofRandomuf(), ofRandomuf() , 0.1f, 0.1f );
//
//                addWidget( wdgt );
//
//                wdgt -> initialize();
//            }


//            setHierarchy(w[0],w[1]);
//            setHierarchy(w[0],w[2]);
//            setHierarchy(w[1],w[3]);
//            setHierarchy(w[1],w[4] );
//            setHierarchy(w[2],w[5] );
//            setHierarchy(w[5],w[6] );


        }



        void SceneBuilder::addClip( shared_ptr<Clip> _clip, float _x, float _y){
            clips.push_back(make_shared<SceneClip>( ));
            clips.back()->set( _x / width, _y / height, 0.05f, 0.05f );

            clips.back()->setName( _clip->getName() );
//            clips.back()->setFilename( _clip->getFilename() );

            addWidget(clips.back());

            clips.back()->initialize();
            clips.back()->setClip(_clip);

            arrangeWidgets();
            addListeners(clips.back());
        }



        void SceneBuilder::removeClip( shared_ptr<SceneClip> _clip){

            removeListeners(_clip);
            removeWidget(_clip);

            vector< shared_ptr<SceneClip> >::iterator it;
            it = find (clips.begin(), clips.end(), _clip);
            clips.erase( it );
            arrangeWidgets();
        }


        void SceneBuilder::addListeners( shared_ptr<SceneClip> _w ) {
            ofAddListener( *_w->events.lookup("btnClicked"),this,&SceneBuilder::clipBtnClicked);
            ofAddListener( *_w->events.lookup("press"),this,&SceneBuilder::widgetPressed);
            ofAddListener( *_w->events.lookup("drag"),this,&SceneBuilder::widgetDragged);
            ofAddListener( *_w->events.lookup("mainBtnClicked"),this,&SceneBuilder::mainBtnClicked);


        }

        void SceneBuilder::removeListeners( shared_ptr<SceneClip> _w ) {
            ofRemoveListener( *_w->events.lookup("btnClicked"),this,&SceneBuilder::btnClicked);
            ofRemoveListener( *_w->events.lookup("press"),this,&SceneBuilder::widgetPressed);
            ofRemoveListener( *_w->events.lookup("drag"),this,&SceneBuilder::widgetDragged);
            ofRemoveListener( *_w->events.lookup("mainBtnClicked"),this,&SceneBuilder::mainBtnClicked);
        }


        void SceneBuilder::rootClicked(widgetEvent & _event){
            cout << "root CLICK" << endl;
            currentClip.reset();
        }


        void SceneBuilder::connectWidget( shared_ptr<SceneWidget> _widget ){
            int ncsize=nextConnections.size();

            if(ncsize==1){
                setHierarchy( nextConnections[0], _widget);

//                cout << "SET:               -  : " << nextConnections[0]->getName() << endl;
//                cout << "TO:               -  : " << clips.back()->getName() << endl;
            }
            else if(ncsize==2) {
                removeHierarchy( nextConnections[0], nextConnections[1] );
                removeHierarchy( nextConnections[1], nextConnections[0] );
                setHierarchy( nextConnections[1], _widget);
                setHierarchy( clips.back(), nextConnections[0] );
////                removeHierarchy( nextConnections[1], nextConnections[0] );
//
//                cout << "SET:               -  : " << nextConnections[1]->getName() << endl;
//                cout << "TO:               -  : " << clips.back()->getName() << endl;
//                cout << "TO 2 :               -  : " << nextConnections[0]->getName() << endl;

            }


        }



        void SceneBuilder::disconnectWidget( shared_ptr<SceneWidget> _widget ) {

            vector < shared_ptr<StoreObject> > parents = getParents( _widget );
            vector < shared_ptr<StoreObject> > children = getChildren( _widget );

            shared_ptr<StoreObject> parent;

            if( parents.size() > 0 ) {
                parent = parents[0];
                removeHierarchy( parent, _widget );
            }
            if( children.size() > 0 ) {
                for(int i = 0; i<children.size(); i++) {
                    removeHierarchy( _widget, children[i] );
                    if( parent ) {
                        setHierarchy(parent,children[i]);
                    }
                }
            }
        }



        void SceneBuilder::clipBtnClicked(widgetEvent & _event){

            shared_ptr< SceneClip > clip = dynamic_pointer_cast<SceneClip>(_event.sender);

            string command = clip->getCommand();

            if(command == "remove") {
                disconnectWidget( clip );
                removeClip( clip );
            }


//            if(command == "connect") {
//                //disconnectWidget( clip );
//            }

            if(command == "disconnect") {
                disconnectWidget( clip );
            }


            if(command == "next") {
                nextClip = clip;
            }
        }

        void SceneBuilder::btnClicked(widgetEvent & _event){

            shared_ptr< kRectButtonView > view = dynamic_pointer_cast<kRectButtonView>(_event.sender);

            switch( view->getValue() ) {
                // play:
                case 0:
                    play();
                    break;
                case 1:
                    pause();
                    break;
                case 2:
                    nextClip = selectChild();
                    break;
                case 3:
                    nextClip = selectParent();
                    break;
                case 4:
                    nextClip = selectSibling();
                    break;
            }
        }

        void SceneBuilder::widgetPressed(widgetEvent & _event){
            shared_ptr<SceneWidget> widget = dynamic_pointer_cast<SceneWidget>(_event.sender);

            vector< shared_ptr < StoreObject > > children = getChildren( widget );

            cout << "CH: " << children.size() << endl;

        }


        void SceneBuilder::widgetDragged(widgetEvent & _event){}

        void SceneBuilder::mainBtnClicked(widgetEvent & _event){
//            nextClip = dynamic_pointer_cast<SceneClip>(_event.sender);

            //cout << "nextClip:  "<<nextClip->getClip()->getName() << endl;
        }

        void SceneBuilder::draw(ofEventArgs & args){

            kRectView::draw(args);

            if(draggingWidget ){
                if(nextConnections.size()>=1) {
                    ofSetColor(20,134,185);
                    ofLine(
                        nextConnections[0]->getX(), nextConnections[0]->getY(),
                        mouseX, mouseY
                    );
                }

            }

            if( newDraggingClip ) {

                if( inside(mouseX,mouseY) ) {
                    ofSetColor(20,134,185);
                    ofCircle( mouseX, mouseY, 10 );
                    for (int i=0; i<nextConnections.size(); i++)
                    {
                        //cout<<nextConnections[i]->getName()<<endl;
                        ofLine(
                            nextConnections[i]->getX(),
                            nextConnections[i]->getY(),
                            mouseX,mouseY
                        );
                    }
                }
            }
//
//            vector< shared_ptr < StoreObject > > c = getDescendants(w[0]);
//
//ofSetColor(0,244,0);
//            for (int i=0; i<c.size(); i++)
//            {
//                shared_ptr<SceneWidget> ci = dynamic_pointer_cast<SceneWidget>(c[i]);
//                ofLine( w[0]->getX(), w[0]->getY(), ci->getX(), ci->getY() );
//            }
//
//
ofSetColor(244);
vector< shared_ptr < StoreObject > > c;
vector< shared_ptr < kWidget > > w = widgets;
            for (int i=0; i<w.size(); i++)
            {
            	c = getChildren( dynamic_pointer_cast<SceneWidget>(w[i]));

                for (int j=0; j<c.size(); j++)
                {
                    shared_ptr<SceneWidget> cj = dynamic_pointer_cast<SceneWidget>(c[j]);
                    ofLine( w[i]->getX(), w[i]->getY(), cj->getX(), cj->getY() );
                }

            }

            if(nextClip){
                ofSetLineWidth(2.5f);

                ofSetColor(20,134,185);
                ofSetLineWidth(5);
//                ofCircle(nextClip->x+nextClip->width/2,nextClip->y+nextClip->height/2,50);

                ofRect( nextClip->getX(),nextClip->getY(),nextClip->getWidth(),nextClip->getWidth()*9/16.0f);

            }

            if(currentClip){
                ofSetLineWidth(2.5f);

                ofSetColor(80,184,185);
                ofSetLineWidth(5);
//                ofCircle(nextClip->x+nextClip->width/2,nextClip->y+nextClip->height/2,50);

                ofRect( currentClip->getX(),currentClip->getY(),currentClip->getWidth(),currentClip->getWidth()*9/16.0f);

            }

            ofSetLineWidth(1);
//




        }

        void SceneBuilder::setCurrentClip( shared_ptr<SceneClip> _clip ){ currentClip = _clip; }

        shared_ptr<Clip> SceneBuilder::getCurrentClip(){ return currentClip->getClip(); }

        void SceneBuilder::setNewDraggingClip( shared_ptr<Clip> _clip ) {
            newDraggingClip = _clip;
        }


        void SceneBuilder::setDraggingWidget(shared_ptr<SceneWidget> _widget){
            draggingWidget = _widget;
        }


        void SceneBuilder::mouseReleased(ofMouseEventArgs & mouse){

            if(newDraggingClip) {
                if(inside(mouse.x,mouse.y))
                {
                    addClip( newDraggingClip, mouse.x-x, mouse.y-y );
                    connectWidget( clips.back() );
                    arrangeWidgets();
                }
            }


            if( !newDraggingClip && draggingWidget ) {
                if(inside(mouse.x,mouse.y))
                {
                    if(nextConnections.size()>0) {
                        connectWidget( draggingWidget );
                        nextConnections.clear();
                    }
                    arrangeWidgets();
                }
            }


            draggingWidget.reset();
            newDraggingClip.reset();

        }

        void SceneBuilder::mouseDragged(ofMouseEventArgs & mouse){

            if( isVisible() ) {
                vector< shared_ptr < SceneWidget > > sw;

                sw.push_back(root);

                for (int i=0; i<clips.size(); i++)
                    sw.push_back( clips[i] );

                if(newDraggingClip) {
                    nextConnections.clear();
                    nextConnections = getPossibleConnections( mouse.x, mouse.y, sw );
                }
                else {
                    if( draggingWidget ) {
//                        cout << "DW<"<<draggingWidget->getName() << endl;
//                        draggingWidget->setX(mouse.x);
//                        draggingWidget->setY(mouse.y);
//                        draggingWidget->setRectInView();
//                        arrangeWidgets();
                        nextConnections.clear();
                        nextConnections = getPossibleConnections( draggingWidget, sw );
                    }
                    else {
                        int nearestIndex = getNearestIndex(mouse.x,mouse.y,sw);
                        if( nearestIndex >= 0 && nearestIndex < sw.size() ) {
                            for (int i=0; i<sw.size(); i++) {
                                sw[ i ] -> lockDrag();
                            }
                            if( sw[ nearestIndex ] -> isMouseOn ) { //inside( mouse.x, mouse.y ) ) {
                                sw[ nearestIndex ] -> unlockDrag();
                                setDraggingWidget( sw[ nearestIndex ] );
                            }

                        }
                    }

                }
                mouseX = mouse.x;
                mouseY = mouse.y;
            }
        }


        shared_ptr< SceneClip > SceneBuilder::selectChild() {
            shared_ptr< SceneClip > next;
            vector < shared_ptr<StoreObject> > possibleNext;
            if( nextClip ) {
                possibleNext = getChildren( nextClip );
            }
            else if( currentClip )
                possibleNext = getChildren( currentClip );
            if(possibleNext.size()>0) {
                int index = rand() % possibleNext.size();
                next = dynamic_pointer_cast<SceneClip>(possibleNext[index]);
            }
            return next;

        }


        shared_ptr< SceneClip > SceneBuilder::selectParent() {
            shared_ptr< SceneClip > next;
            vector < shared_ptr<StoreObject> > possibleNext;
            if( nextClip ) {
                possibleNext = getParents( nextClip );
            }
            else if( currentClip )
                possibleNext = getParents( currentClip );
            if(possibleNext.size()>0) {
                int index = rand() % possibleNext.size();
                next = dynamic_pointer_cast<SceneClip>(possibleNext[index]);
            }
            return next;
        }


        shared_ptr< SceneClip > SceneBuilder::selectSibling() {
            shared_ptr< SceneClip > next;
            vector < shared_ptr<StoreObject> > possibleNext;
            if( nextClip ) {
                possibleNext = getSiblings( nextClip );
                for(int i = 0; i<possibleNext.size(); i++){
                    cout << possibleNext[i]->getName() << endl;
                }
            }
            else if( currentClip )
                possibleNext = getSiblings( currentClip );

            if(possibleNext.size()>0) {
                int index = rand() % possibleNext.size();
                next = dynamic_pointer_cast<SceneClip>(possibleNext[index]);
            }
            return next;
        }



        shared_ptr< SceneClip > SceneBuilder::selectNextClip() {


            vector < shared_ptr<StoreObject> > c;
            vector < shared_ptr<SceneClip> > possibleNext;
            shared_ptr<SceneClip> next;
            shared_ptr<SceneClip> check;

            bool already = false;


            if( currentClip )
                c = getDescendants ( currentClip );
            else
                c = getDescendants ( root );

            for (int i=0; i<c.size(); i++)
            {


                check = dynamic_pointer_cast<SceneClip>( c[ i ] );
                for (int j=0; j<alreadyPlayed.size(); j++)
                {
                    if( check == alreadyPlayed[j] ){
                        already = true;
                        break;
                    }
                }
                if(!already) {
                    next = check;
                    possibleNext.push_back( check );
                }
            }

            //if has children to play
            if(possibleNext.size()>0) {
                // next one
                int index = rand() % possibleNext.size();
                next = possibleNext[index];
            }
            else {

                // if has siblings to play

                c = getSiblings( currentClip );

                for (int i=0; i<c.size(); i++)
                {


                    check = dynamic_pointer_cast<SceneClip>( c[ i ] );
                    for (int j=0; j<alreadyPlayed.size(); j++)
                    {
                        if( check == alreadyPlayed[j] ){
                            already = true;
                            break;
                        }
                    }

                    if(!already) {
                        next = check;
                        possibleNext.push_back( check );
                    }
                }
                //if has children to play
                if(possibleNext.size()>0) {
                    // next one
                        int index = rand() % possibleNext.size();
                        next = possibleNext[index];
                }

            // else if has ancestors to play
                else {

                    c = getAncestors( currentClip );

                    for (int i=0; i<c.size(); i++)
                    {
                        check = dynamic_pointer_cast<SceneClip>( c[ i ] );
                        for (int j=0; j<alreadyPlayed.size(); j++)
                        {
                            if( check == alreadyPlayed[j] ){
                                already = true;
                                break;
                            }
                        }

                        if(!already) {
                            nextClip = check;
                            possibleNext.push_back( check );
                        }
                    }
                    //if has children to play
                    if(possibleNext.size()>0) {
                    // next one
                        int index = rand() % possibleNext.size();
                        next = possibleNext[index];
                    }
                    else

                        notify("branchEnd");

                }

            }

            return next;

        }

        int SceneBuilder::getNearestIndex( float _x, float _y , vector< shared_ptr < SceneWidget > > _v  ){

            float closestDistance = 0;
            int nearestIndex = -1;
            //check if array is valid
            if(_v.size()>0)
                closestDistance = getDistance( _x, _y, _v[0]->getX(), _v[0]->getY() );


            for (int i=0; i<_v.size(); i++)
            {
                float newDistance = getDistance( _x, _y, _v[i]->getX(), _v[i]->getY() );
                if(newDistance < closestDistance ){ closestDistance = newDistance; nearestIndex = i; }

            }
            for (int i=0; i<_v.size(); i++)
            {
                float newDistance = getDistance(  _x, _y, _v[i]->getX(), _v[i]->getY() );
                if( newDistance <  closestDistance + insertThreshold ){
                    nearestIndex = i; break;
                }
            }

            return nearestIndex;

        }



        vector< shared_ptr < SceneWidget > > SceneBuilder::getPossibleConnections( shared_ptr<SceneWidget> _widget, vector< shared_ptr < SceneWidget > > _v ) {

            for (int i=0; i<_v.size(); i++)
            {
                vector< shared_ptr < SceneWidget > >::iterator it;
            	it = find( _v.begin(), _v.end(), _widget);
            	if( it!=_v.end()){
                    _v.erase(it);
            	}

            	return getPossibleConnections( _widget->getX(), _widget->getY(), _v );

            }

        }

        vector< shared_ptr < SceneWidget > > SceneBuilder::getPossibleConnections(  float _x, float _y , vector< shared_ptr < SceneWidget > > _v ) {

            vector< shared_ptr < SceneWidget > > possibleConnections;

            int nearestIndex = getNearestIndex(_x, _y, _v );
            float closestDistance = 0;

            if( _v.size() > nearestIndex && nearestIndex >= 0 ){

                closestDistance = getDistance( _x, _y, _v[nearestIndex]->getX(), _v[nearestIndex]->getY() );

                if(closestDistance < autoConnectThreshold ) {
                    possibleConnections.push_back( _v[ nearestIndex ] );
                }

            }

            float rootDistance = getDistance ( _x, _y, root->getX(), root->getY() );

            if( rootDistance < closestDistance && rootDistance < closestDistance - insertThreshold){
                possibleConnections.clear();
                possibleConnections.push_back( root );
            }
            else if ( rootDistance <= closestDistance - insertThreshold && possibleConnections.size()==1 )
                possibleConnections.push_back( root );

            return possibleConnections;

        }



        shared_ptr<SceneClip> SceneBuilder::getNextClip() {
            return nextClip;
        }


        void SceneBuilder::mediaEnd() {
//            cout << "kill---"<<lastClip->getClip()->getName() << endl;
            alreadyPlayed.push_back(lastClip);
            next();
            play();
        }

        void SceneBuilder::savePosition( float _position ) {
            currentClip->setPosition( _position );
//            currentMedia->setPosition( _position );
        }

        void SceneBuilder::play(){
//            nextClip = selectNextClip();
            if( nextClip ) {
                lastClip = currentClip;
                currentClip = nextClip;

//                nextClip = dynamic_pointer_cast<SceneClip>(nextClip);
                notify("playClip");

            }
        }
        void SceneBuilder::next(){
            nextClip = selectNextClip();
        }
        void SceneBuilder::previous(){}
        void SceneBuilder::pause(){}
        void SceneBuilder::stop(){}

        void SceneBuilder::setWidgetSize( float _ws ) {
            root->setSize(_ws*width*0.8);
            root->setRectInView();
            for (int i=0; i<clips.size(); i++) {
            	clips[i]->setSize(_ws*width);
            	clips[i]->setRectInView();
            }
        }

//        shared_ptr< SceneClip > SceneBuilder::getPrevMedia() {
//            return lastMedia;
//        }



//}





