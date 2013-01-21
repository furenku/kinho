


#pragma once

#ifndef scenes_h
#define scenes_h

/*

class SceneWidget: public StoreObject, virtual public kRectView{
    public:
        SceneWidget(){}

        void initialize(){


        }

        void draw(ofEventArgs & args){
            kRectView::draw(args);
            ofSetColor(255);
//            ofNoFill();
            ofCircle(x,y,width);

        }



        //mouse
            void mouseDragged(ofMouseEventArgs & mouse) {
//                RightAncestor::mouseDragged(mouse);
                if(isMouseOn)
                    notify("dragged");
            }
        protected:
};



*/

class SceneWidget: public StoreObject, virtual public kCircleView, virtual public kDragObject {
    public:

        SceneWidget(){
            setType("scenewidget");
            setupVars();
            createEvents();
//            enableUpdate();
        }

    //f

        void setupVars(){
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

        }



        void draw(ofEventArgs & args){

            ofDrawBitmapString( name , x, y );

        }

        void addBtnView() {
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

                ofRemoveListener( *btnView->events.lookup("btnClicked"),this,&SceneWidget::btnClicked);

                removeWidget(btnView);



                btnView.reset();
//                removeSubView();
//                arrangeWidgets();

            }

        }



        void removeBtnViewListeners(){
            ofRemoveListener( *btnView->events.lookup("btnClicked"), this, &SceneWidget::btnClicked );
        }

        void addScrollView() {
            scrollView = make_shared< kMediaScrollView >();
        //setup
            scrollView->set(0.5f,0.5f,width*2,height*2);

            addWidget( scrollView );

//            scrollView->initialize();

            arrangeWidgets();


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

        void mediaClicked(widgetEvent & _event) {

            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mediaBtnClicked");
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


class SceneRoot: virtual public SceneWidget {
    public:
    SceneRoot(){ setType("sceneRoot"); }

    void draw(ofEventArgs & args){
        ofCircle(x,y,20);
        ofDrawBitmapString("root",x,y);
    }
};


class SceneClip: public SceneWidget {

     public:

        SceneClip(){
            setupVars();
            createEvents();
        }

        void createEvents() {
            saveEvent("mainBtnClicked");
        }
    //f


        void draw(ofEventArgs & args){
//            ofCircle(x,y,width);
            ofDrawBitmapString(name,x,y);
        }

        void initialize() {

            SceneWidget::initialize();

            clipView = make_shared<kClip>( );

            clipView->set(0,0,0.3f,0.3f);

//            clipView->setClip( clip );

            addWidget( clipView );
            ofAddListener( *clipView->events.lookup("press"),this,&SceneClip::mediaClicked);


        }

        void setupVars(){
            SceneWidget::setupVars();
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

        void mediaClicked(widgetEvent & _event) {
            toggleViews();
//            draggingOntology  = dynamic_pointer_cast<kWidget>(_event.sender)->getLabel();
            notify("mainBtnClicked");
        }

        void setPosition( float _pos ){
            savedPosition = _pos;
        }

        //atts
        shared_ptr<Clip> clip;
        shared_ptr<kClip> clipView;

        float savedPosition;
};





class SceneBuilder: public DBManager, virtual public kRectView{

    public:
        SceneBuilder(){
            autoArrange = false;
            insertThreshold = 30;
        }

        void initialize() {
            root = make_shared<SceneRoot>( ),
            root -> set(0.5f, 0.5f,0.05f, 0.05f );
            addWidget(root);

            arrangeWidgets();
        }

        void createEvents(){
            saveEvent("playClip");
            saveEvent("branchEnd");
        }


        void iiinit(){

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


        void addClip( shared_ptr<Clip> _clip, float _x, float _y){
            clips.push_back(make_shared<SceneClip>( ));
            clips.back()->set( _x / width, _y / height, 0.2f, 0.2f );

            clips.back()->setName( _clip->getName() );

            addWidget(clips.back());

            clips.back()->initialize();
            clips.back()->setClip(_clip);

            arrangeWidgets();
//            addListeners(clip);
        }


        void addListeners( shared_ptr<SceneClip> _w ) {
            ofAddListener( *_w->events.lookup("btnClicked"),this,&SceneBuilder::btnClicked);
            ofAddListener( *_w->events.lookup("drag"),this,&SceneBuilder::widgetDragged);
            ofAddListener( *_w->events.lookup("mainBtnClicked"),this,&SceneBuilder::mainBtnClicked);


        }


        void btnClicked(widgetEvent & _event){}

        void widgetDragged(widgetEvent & _event){}

        void mainBtnClicked(widgetEvent & _event){}

        void draw(ofEventArgs & args){

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



        shared_ptr<Clip> getCurrentClip(){}

        void setDraggingClip(shared_ptr<Clip> _clip){
            draggingClip = _clip;
            cout << "SET: "<<draggingClip->getName() << endl;
        }


        void mouseReleased(ofMouseEventArgs & mouse){
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

        void mouseDragged(ofMouseEventArgs & mouse){

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





//        //atts
//            vector < shared_ptr<SceneMedia> > media;
            vector < shared_ptr<SceneClip> > alreadyPlayed;
//            shared_ptr< SceneMedia > currentMedia, lastMedia, nextMedia;
//            shared_ptr<VideoOutput> videoOutput;
//            shared_ptr<SampleOutput> sampleOutput;
//            shared_ptr<TextOutput> textOutput;
//            shared_ptr< BranchControl > controls;
            bool playing;
//        //f
//            //logica
//                void initialize() { addControls(); }
//
//                void addControls() {
//                    controls = make_shared< BranchControl >();
//                    controls->set( _x + width / 2,_y+_height, width, height);
//                    ofAddListener( *controls->events.lookup("play"), this,&Branch::play);
//                    ofAddListener( *controls->events.lookup("pause"), this,&Branch::pause);
//                    ofAddListener( *controls->events.lookup("rew"), this,&Branch::rew);
//                    ofAddListener( *controls->events.lookup("fwd"), this,&Branch::fwd);
//                }
//
//            //media

        shared_ptr< SceneClip > playNextClip() {
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


        vector< shared_ptr < SceneWidget > > getPossibleConnections(  float _x, float _y , vector< shared_ptr < SceneWidget > > _v ) {

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

        int insertThreshold;

        shared_ptr<SceneRoot> root;
//
//
        shared_ptr<SceneClip> getNextClip() {
            return nextClip;
        }


        void mediaEnd() {
            playNextClip();
            alreadyPlayed.push_back(lastClip);
        }

        void savePosition( float _position ) {
            currentClip->setPosition( _position );
//            currentMedia->setPosition( _position );
        }

//        shared_ptr< SceneClip > getPrevMedia() {
//            return lastMedia;
//        }


/*
            //set
                //output
                    void setVideoOutput( shared_ptr<VideoOutput> _output) {
                        videoOutput = _output;
                    }
                    void setSampleOutput( shared_ptr<SampleOutput> _output) {
                        sampleOutput = _output;
                    }
                    void setTextOutput( shared_ptr<TextOutput> _output) {
                        textOutput = _output;
                    }
            //add
                void addMedia( shared_ptr<SceneMedia> _media ) {
                    media.push_back( media );
                }

            //controls
                void play( widgetEvent & _event ) {
                    notify("play");
                }

                void pause( widgetEvent & _event ) {
                    notify("pause");
                }
                void rew( widgetEvent & _event ) {
                    notify("rew");
                }

                void fwd( widgetEvent & _event ) {
                    notify("fwd");
                }
            // external control
                void play() {
                    if(!playing)
                        if(currentMedia)
                            nextMedia = currentMedia;
                            notify("play");
                        playing = true;
                }

                void pause(); {
                    if(playing)
                        playing = true;
                        notify("pause");
                        lastMedia = currentMedia;
                }

            void createEvents() { saveEvent("play"); }


            void setHead( shared_ptr<SceneMedia> _media ) {
                playWidget->set (
                _media->getX() / width,
                _media->getY() / height,
                playWidget->getWidth() / width,
                playWidget->getHeight() / height
                );
                // ?? insert into beginning of array
            }

        logica
            void initialize() {
                rootBtn = make_shared<kCircleButton>();
            }


        //get output
            shared_ptr<VideoOutput> getOutput( shared_ptr<SceneClip> _clip ) {
                return videoOutput;
            }

            shared_ptr<SampleOutput> getOutput( shared_ptr<SceneSample> _sample ) {
                return sampleOutput;
            }

            shared_ptr<TextOutput> getOutput( shared_ptr<SceneText> _text ) {
                return textOutput;
            }


*/
        shared_ptr<ClockWidget> clock;

        vector< shared_ptr<SceneWidget> > w;
        vector< shared_ptr<SceneClip> > clips;
        vector< shared_ptr<SceneWidget> > nextConnections;

        shared_ptr<Clip> draggingClip;

        shared_ptr<SceneClip> nextClip, currentClip, lastClip;





};




/*

class SceneManager: public DBManager {
    public:
        SceneManager(){}



        void initialize() {
            builder = make_shared<SceneBuilder> ();
//            //loadListeners
//                "saveScene"..saveScene
//                "loadScenes"..loadScenes
//                "loadScene"..loadScene
            //set builder default outputs
//                builder->setVideoOutput( videoOutput );
//                builder->setSampleOutput( sampleOutput );
//                builder->setTextOutput( textOutput );
        }


    //f
        shared_ptr<Scene> getNextScene() {}


        //save/load
            void saveScene() {
//                // create scene object
//                // get all data from builder!
//                // save scene name
//                // save scene date
//                // get all branches
//                forv branches
//                    // save media
//                        //mediaholder name
//                        //x,y position
//                    // save branch hierarchy node by node
//                    // save branch parameters
//                        //transition parameters
//                // save outputs
//                    name
//                    //x,y
//                // save connections to outpus
//                // save control widgets
//                    //save type
//                    //save params
//                    //save source
//                        "source class", "source name", rangeMin, rangeMax
//                    //save targets
//                        forv targets
//                            "controllableName"
//                    //save functors
//                        "FunctorName","controllableName"
//                // notify of new scene creation for updating...
            }


            void loadScene() {
//                // create scene object
//                // load scene name
//                // load scene date
//                // get all branches
//                forv branches
//                    // load media
//                        //mediaholder name
//                        //x,y position
//                    // load branch hierarchy node by node
//                    // load branch parameters
//                        //transition parameters
//                // load outputs
//                    name
//                    //x,y
//                // load connections to outpus
//                // load control widgets
//                    //load type
//                    //load params
//                    //load source
//                        "source class", "source name", rangeMin, rangeMax
//                    //load targets
//                        forv targets
//                            "controllableName"
//                    //load functors
//                        "FunctorName","controllableName"
//                currentScene = scene;
//                builder -> loadScene ( scene );
            }

            void loadScenes() {}


    //atts
        shared_ptr<SceneBuilder> builder;
        shared_ptr<Scene> currentScene, previousScene, nextScene;
//        shared_ptr< VideoManager > video;

    //outputs
//            shared_ptr<VideoOutput> videoOutput;
//            shared_ptr<SampleOutput> sampleOutput;
//            shared_ptr<TextOutput> textOutput;

};

*/


#endif


/*
class SceneWidget: public
        //f
            //mouse
                void mouseDragged(ofMouseArgs & mouse)
                    RightAncestor::mouseDragged(mouse);
                    if(isMouseOn)
                        notify("dragged");
            void addBtnView()
                btnView = make_shared< kCircleButtonView >();
                vecstr labels;
                labels.push_back();
                    "play"
                    "open"
                    "remove"
                    "connect"
                    "disconnect"
                //add, init, prepare,addbuttons, listeners
                    btnView->addButton( labels );
        //atts
            kCircleButtonView btnView;


    */


/*


//class SceneRoot: virtual public SceneWidget {
//    public:
//    SceneRoot(){ setType("sceneRoot"); }
//
//};
//
//
//class ControllableWidget: public SceneWidget {
//        f
//    public:
//        ControllableWidget(){ setupVars(); }
//
//        void trigger() {
//            if( isTriggerable )
//                triggerFunc->execute();
//        }
//
//        void setTriggerFunc ( shared_ptr< Functor > _func ) {
//            triggerFunc = _func;
//        }
//
//        void setSetFunc ( shared_ptr< Functor > _func ) {
//            setFunc = _func;
//        }
//
//        void setupVars() {
//            isTriggerable = false;
//            isSettable = false;
//        }
//    atts
//        shared_ptr<Functor> triggerFunc, setFunc;
//        bool isTriggerable, isSettable;
//
//};
//
//class SceneMedia: public ControllableWidget {
//    public:
//        SceneMedia(){ setupVars(); }
//        atts
//            shared_ptr<MediaHolder> media;
//            float position;
//        f
//            void setupVars() {
//                isTriggerable = true;
//            }
//
//            shared_ptr<MediaHolder> getMedia() { return media; }
//            void setMedia( shared_ptr<MediaHolder> _media ) { media = _media; }
//            void setPosition( float _position ){ position = _position; }
//            float getPosition() { return position; }
//};
//
//
//class SceneClip: public SceneMedia {
//    public:
//        SceneClip(){ setupVars(); }
//        atts
//             shared_ptr< TransitionControl >
//             shared_ptr< PlayButton >
//        atts
//
//                float
//                    alpha
//                    r
//                    g
//                    b
//                    transitiontime
//                bool
//                    transitionOn
//
//                int
//                    transitionType
//        f
//
//            void setupVars() {
//                setType("clip");
//            }
//             clip
//            shared_ptr<Clip> getClip() { return clip; }
//            void setClip( shared_ptr<Clip> _clip ) { clip = _clip; }
//
//        shared_ptr<Clip> getNextClipOutput() { return nextClipoutput; }
//        shared_ptr<Sample> getNextSampleOutput() { return nextSampleOutput; }
//        shared_ptr<Text> getNextTextOutput() { return nextTextOutput; }
//
//};
//
//class SceneSample {
//    public:
//        SceneSample(){}
//};
//class SceneText {
//    public:
//        SceneText(){}
//};
//
//
//class ControlWidget: public SceneWidget {
//        f
//            void activate() {
//                forv functors
//                    ->execute();
//            }
//            void disconnect( shared_ptr<ControllableWidget> _target){}
//                remove Functor
//                remove from targets array
//        atts
//            vector< shared_ptr<ControllableWidget> > targets;
//            vector< shared_ptr<Functors> > funcs;
//            kCircleScrollView
//                "remove"
//                "connect"
//                "disconnect"
//};
//
//class ControllableControlWidget: public ControllableWidget, public ControlWidget {
//};
//
//
//
//class Branch {
//        //atts
//            vector < shared_ptr<SceneMedia> > media;
//            vector < shared_ptr<SceneMedia> > alreadyPlayed;
//            shared_ptr< SceneMedia > currentMedia, lastMedia, nextMedia;
//            shared_ptr<VideoOutput> videoOutput;
//            shared_ptr<SampleOutput> sampleOutput;
//            shared_ptr<TextOutput> textOutput;
//            shared_ptr< BranchControl > controls;
//            bool playing;
//        //f
//            //logica
//                void initialize() { addControls(); }
//
//                void addControls() {
//                    controls = make_shared< BranchControl >();
//                    controls->set( _x + width / 2,_y+_height, width, height);
//                    ofAddListener( *controls->events.lookup("play"), this,&Branch::play);
//                    ofAddListener( *controls->events.lookup("pause"), this,&Branch::pause);
//                    ofAddListener( *controls->events.lookup("rew"), this,&Branch::rew);
//                    ofAddListener( *controls->events.lookup("fwd"), this,&Branch::fwd);
//                }
//
//            //media
//                shared_ptr< SceneMedia > playNextMedia() {
//                    vector < shared_ptr<StoreObject> > c = getDescendants ( currentMedia );
//                    vector < shared_ptr<SceneMedia> > possibleNext;
//                    shared_ptr<SceneMedia> check;
//                    nextMedia.reset();
//
//                        bool already = false;
//                        for (int i=0; i<c.size(); i++)
//                        {
//                        	c[i]
//
//                        	check = dyncast<SceneMedia>( c[ i ] );
//                            for (int j=0; j<alreadyPlayed.size(); j++)
//                            {
//                            	if( check == alreadyPlayed[j] )
//                                    already = true;
//                                    break;
//                            }
//
//                            if(!already)
//                                nextMedia = check;
//                                possibleNext.push_back( check );
//
//                        }
//
//                        //if has children to play
//                        if(possibleNext.size()>0)
////                            random
////                                int index = rand()%possibleNext.size();
////                                nextMedia = possibleNext[ index ];
//
//                            // next one
//                                nextMedia = possibleNext[0]
//                        else
//                            // if has siblings to play
//                            // else if has ancestors to play
//                            else
//                                notify("branchEnd");
//
//
//                    if( nextMedia )
//                        lastMedia = currentMedia;
//                        currentMedia = nextMedia;
//                        string type = nextMedia -> getType();
//                        if( type == "clip")
//                            notify("playClip");
//                            nextClip = dyncast<SceneClip>(nextMedia);
//                        else if( type == "sample")
//                            notify("playSample");
//                            nextSample = dyncast<SceneSample>(nextMedia);
//                        else if( type == "text")
//                            notify("playText");
//                            nextText = dyncast<SceneText>(nextMedia);
//
//                }
//
//
//                shared_ptr<SceneMedia> getNextMedia() {
//                    return nextMedia;
//                }
//
//                void mediaEnd() {
//                    playNextMedia();
//                    alreadyPlayed.push_back(lastMedia);
//                }
//
//
//                void savePosition( float _position ) {
//                    currentMedia->setPosition( _position );
//                }
//
//                shared_ptr< SceneMedia > getPrevMedia() {
//                    return lastMedia;
//                }
//
//            //set
//                //output
//                    void setVideoOutput( shared_ptr<VideoOutput> _output) {
//                        videoOutput = _output;
//                    }
//                    void setSampleOutput( shared_ptr<SampleOutput> _output) {
//                        sampleOutput = _output;
//                    }
//                    void setTextOutput( shared_ptr<TextOutput> _output) {
//                        textOutput = _output;
//                    }
//            //add
//                void addMedia( shared_ptr<SceneMedia> _media ) {
//                    media.push_back( media );
//                }
//
//            //controls
//                void play( widgetEvent & _event ) {
//                    notify("play");
//                }
//
//                void pause( widgetEvent & _event ) {
//                    notify("pause");
//                }
//                void rew( widgetEvent & _event ) {
//                    notify("rew");
//                }
//
//                void fwd( widgetEvent & _event ) {
//                    notify("fwd");
//                }
//            // external control
//                void play() {
//                    if(!playing)
//                        if(currentMedia)
//                            nextMedia = currentMedia;
//                            notify("play");
//                        playing = true;
//                }
//
//                void pause(); {
//                    if(playing)
//                        playing = true;
//                        notify("pause");
//                        lastMedia = currentMedia;
//                }
//
//            void createEvents() { saveEvent("play"); }
//
//
//            void setHead( shared_ptr<SceneMedia> _media ) {
//                playWidget->set (
//                _media->getX() / width,
//                _media->getY() / height,
//                playWidget->getWidth() / width,
//                playWidget->getHeight() / height
//                );
//                // ?? insert into beginning of array
//            }
//
//        logica
//            void initialize() {
//                rootBtn = make_shared<kCircleButton>();
//            }
//
//
//        //get output
//            shared_ptr<VideoOutput> getOutput( shared_ptr<SceneClip> _clip ) {
//                return videoOutput;
//            }
//
//            shared_ptr<SampleOutput> getOutput( shared_ptr<SceneSample> _sample ) {
//                return sampleOutput;
//            }
//
//            shared_ptr<TextOutput> getOutput( shared_ptr<SceneText> _text ) {
//                return textOutput;
//            }
//
//};
//
//class BranchControl: virtual public kRectView {
//        //f
//            void initialize() {
//                params = make_shared<ParamView> ();
//                shared_ptr<Param> param = make_shared<Param>();
//                param->setName("alpha");
//            }
//        //atts
//            shared_ptr<ParamView> params;
//
//};
//
//
//

*/
