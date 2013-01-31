
#include "scenes.h"




        SceneWidget::SceneWidget(){
            setType("scenewidget");
            setupVars();
            createEvents();
//            enableUpdate();
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
                btnView->set(0,0,0.3f,0.3f);
                addWidget( btnView );

            // create labels
                vector <string> labels;
                labels.push_back( "play" );
                labels.push_back( "open" );
                labels.push_back( "remove" );
                labels.push_back( "connect" );
                labels.push_back( "disconnect" );
                btnView->addButtons( labels );
                ofAddListener( *btnView->events.lookup("btnClicked"), this, &SceneWidget::btnClicked );

                arrangeWidgets();

}

        }

        void SceneWidget::removeBtnView(){

            if(btnView) {

                btnView->hide();
                btnView->disable();
                btnView->disableUpdate();
                btnView->clearWidgets();

//                addDelete(btnView);
                btnView->hide();
                btnView->removeButtons();
//                btnView->removeFromVieew();

                ofRemoveListener( *btnView->events.lookup("btnClicked"),this,&SceneWidget::btnClicked);

                removeWidget(btnView);



                btnView.reset();
//                removeSubView();
//                arrangeWidgets();

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

        }


        string SceneWidget::getCommand() { return command; }

        void SceneWidget::mediaClicked(widgetEvent & _event) {

            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mediaBtnClicked");
        }


        void SceneWidget::mouseMoved( ofMouseEventArgs & mouse ){
            isMouseOn=inside(mouse.x,mouse.y);
            mouseX=mouse.x;
            mouseY=mouse.y;
        }

        void SceneWidget::mouseDragged( ofMouseEventArgs & mouse ){
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



        void SceneWidget::mouseReleased( ofMouseEventArgs & mouse){

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



    SceneRoot::SceneRoot(){ setType("sceneRoot"); }

    void SceneRoot::draw(ofEventArgs & args){
        ofCircle(x,y,20);
        ofDrawBitmapString("root",x,y);
    }




        SceneClip::SceneClip(){
            setupVars();
            createEvents();
        }

        void SceneClip::createEvents() {
            saveEvent("mainBtnClicked");
        }
    //f


        void SceneClip::draw(ofEventArgs & args){
//            ofCircle(x,y,width);
            ofDrawBitmapString(name,x,y);
        }

        void SceneClip::initialize() {

            SceneWidget::initialize();

            clipView = make_shared<kClip>( );

            clipView->set(0,0,0.3f,0.3f);

//            clipView->setClip( clip );

            addWidget( clipView );
            ofAddListener( *clipView->events.lookup("press"),this,&SceneClip::mediaClicked);


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

        void SceneClip::mediaClicked(widgetEvent & _event) {
            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mainBtnClicked");
        }

        void SceneClip::setPosition( float _pos ){
            savedPosition = _pos;
        }







        SceneBuilder::SceneBuilder(){
            autoArrange = false;
            insertThreshold = 30;
        }

        void SceneBuilder::initialize() {
            root = make_shared<SceneRoot>( ),
            root -> set(0.5f, 0.5f,0.05f, 0.05f );
            addWidget(root);

            arrangeWidgets();
        }

        void SceneBuilder::createEvents(){
            saveEvent("playClip");
            saveEvent("branchEnd");
        }


        void SceneBuilder::iiinit(){

            for (int i=0; i<7; i++)
            {
                shared_ptr<SceneWidget> wdgt = make_shared<SceneWidget>( );
                w.push_back( wdgt );

                wdgt->set( ofRandomuf(), ofRandomuf() , 0.1f, 0.1f );

                addWidget( wdgt );

                wdgt -> initialize();
            }


            setHierarchy(w[0],w[1]);
            setHierarchy(w[0],w[2]);
            setHierarchy(w[1],w[3]);
            setHierarchy(w[1],w[4] );
            setHierarchy(w[2],w[5] );
            setHierarchy(w[5],w[6] );


        }


        void SceneBuilder::addClip( shared_ptr<Clip> _clip, float _x, float _y){
            clips.push_back(make_shared<SceneClip>( ));
            clips.back()->set( _x / width, _y / height, 0.2f, 0.2f );

            clips.back()->setName( _clip->getName() );

            addWidget(clips.back());

            clips.back()->initialize();
            clips.back()->setClip(_clip);

            arrangeWidgets();
//            addListeners(clip);
        }


        void SceneBuilder::addListeners( shared_ptr<SceneClip> _w ) {
            ofAddListener( *_w->events.lookup("btnClicked"),this,&SceneBuilder::btnClicked);
            ofAddListener( *_w->events.lookup("drag"),this,&SceneBuilder::widgetDragged);
            ofAddListener( *_w->events.lookup("mainBtnClicked"),this,&SceneBuilder::mainBtnClicked);


        }


        void SceneBuilder::btnClicked(widgetEvent & _event){}

        void SceneBuilder::widgetDragged(widgetEvent & _event){}

        void SceneBuilder::mainBtnClicked(widgetEvent & _event){}

        void SceneBuilder::draw(ofEventArgs & args){

            kRectView::draw(args);

            ofSetColor(20,134,185);

            if(draggingClip) {
                if(inside(mouseX,mouseY))
                    ofCircle( mouseX, mouseY, 10 );
                for (int i=0; i<nextConnections.size(); i++)
                {
                	ofLine(
                        nextConnections[i]->getX(),
                        nextConnections[i]->getY(),
                        mouseX,mouseY
                    );
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
            for (int i=0; i<clips.size(); i++)
            {
            	c = getChildren(clips[i]);

                for (int j=0; j<c.size(); j++)
                {
                    shared_ptr<SceneWidget> cj = dynamic_pointer_cast<SceneWidget>(c[j]);
                    ofLine( clips[i]->getX(), clips[i]->getY(), cj->getX(), cj->getY() );
                }

            }

//




        }



        shared_ptr<Clip> SceneBuilder::getCurrentClip(){}

        void SceneBuilder::setDraggingClip(shared_ptr<Clip> _clip){
            draggingClip = _clip;
            cout << "SET: "<<draggingClip->getName() << endl;
        }


        void SceneBuilder::mouseReleased(ofMouseEventArgs & mouse){
            if(draggingClip)
                addClip( draggingClip, mouse.x-x, mouse.y-y );

            int ncsize=nextConnections.size();

            cout << "NC "<<ncsize << endl;
            if(ncsize==1)
                setHierarchy( nextConnections[0], clips.back() );
            else if(ncsize==2) {
                removeHierarchy( nextConnections[0], nextConnections[1] );
                removeHierarchy( nextConnections[1], nextConnections[0] );
                setHierarchy( nextConnections[1], clips.back() );
                setHierarchy( clips.back(), nextConnections[0] );
//                removeHierarchy( nextConnections[1], nextConnections[0] );
            }

            draggingClip.reset();

            arrangeWidgets();

        }

        void SceneBuilder::mouseDragged(ofMouseEventArgs & mouse){

            if( isVisible() ) {
                vector< shared_ptr < SceneWidget > > sw;

                sw.push_back(root);

                for (int i=0; i<clips.size(); i++)
                    sw.push_back( clips[i] );

                if(draggingClip)
                    nextConnections = getPossibleConnections( mouse.x, mouse.y, sw );
                else
                    nextConnections.clear();
                mouseX = mouse.x;
                mouseY = mouse.y;
            }
        }






        shared_ptr< SceneClip > SceneBuilder::playNextClip() {
            vector < shared_ptr<StoreObject> > c;
            vector < shared_ptr<SceneClip> > possibleNext;
            shared_ptr<SceneClip> check;
            nextClip.reset();
            bool already = false;

            c = getDescendants ( currentClip );

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
                    nextClip = possibleNext[0];
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
                        nextClip = check;
                        possibleNext.push_back( check );
                    }
                }
                //if has children to play
                if(possibleNext.size()>0) {
                    // next one
                        nextClip = possibleNext[0];
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
                            nextClip = possibleNext[0];
                    }
                    else

                        notify("branchEnd");

                }

            }



            if( nextClip ) {
                lastClip = currentClip;
                currentClip = nextClip;

                nextClip = dynamic_pointer_cast<SceneClip>(nextClip);
                notify("playClip");

            }

        }


        vector< shared_ptr < SceneWidget > > SceneBuilder::getPossibleConnections(  float _x, float _y , vector< shared_ptr < SceneWidget > > _v ) {

            vector< shared_ptr < SceneWidget > > possibleConnections;

            float closestDistance = 0;
            int nearestIndex;
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
                if( newDistance <  closestDistance + insertThreshold ){ possibleConnections.push_back( _v[i] ); break; }
            }
            if( _v.size() > nearestIndex)
                possibleConnections.push_back( _v[ nearestIndex ] );

            float rootDistance = getDistance ( _x, _y, root->getX(), root->getY() );
            if( rootDistance < closestDistance && rootDistance < closestDistance - insertThreshold){
                possibleConnections.clear();
                possibleConnections.push_back( root );
            }
            else if ( rootDistance >= closestDistance - insertThreshold && possibleConnections.size()==1 )
                possibleConnections.push_back( root );

            return possibleConnections;

        }



        shared_ptr<SceneClip> SceneBuilder::getNextClip() {
            return nextClip;
        }


        void SceneBuilder::mediaEnd() {
            playNextClip();
            alreadyPlayed.push_back(lastClip);
        }

        void SceneBuilder::savePosition( float _position ) {
            currentClip->setPosition( _position );
//            currentMedia->setPosition( _position );
        }

//        shared_ptr< SceneClip > SceneBuilder::getPrevMedia() {
//            return lastMedia;
//        }







