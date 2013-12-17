


#pragma once

#ifndef scenes_h
#define scenes_h

#include "guiVideoObjects.h"
#include "mediaStorage.h"

//#pragma once

//#ifndef scenes_h
//#define scenes_h

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

        SceneWidget();


    //f

        void setupVars();

        void initialize();

        void createEvents();



        virtual void draw(ofEventArgs & args);

        void addBtnView();

        void removeBtnView();



        void removeBtnViewListeners();


        void addScrollView();

        void showBtnView();

        void hideBtnView();

        void showScrollView();

        void hideScrollView();

        void hideViews();

        void toggleViews();



        void loadBtnView();



        void loadMedia( vector < shared_ptr<MediaHolder> > _media );

        //interactividad

        //callbacks

        virtual void addContent();

        void btnClicked(widgetEvent & _event);


        string getCommand();

        void mediaClicked(widgetEvent & _event);


        void mouseMoved( ofMouseEventArgs & mouse );

        void mouseDragged( ofMouseEventArgs & mouse );


        void mousePressed( ofMouseEventArgs & mouse);
        void mouseReleased( ofMouseEventArgs & mouse);

        void lockDrag();
        void unlockDrag();


    //atts
    //protected:

        shared_ptr<kWidget> mainWidget;
        shared_ptr<MediaWidget> draggingMedia;
        string draggingOntology;

        shared_ptr<kButtonView> currentView;
        shared_ptr<kCircleButtonView> btnView;
        shared_ptr<kMediaScrollView> scrollView;
        string command;

        bool dragLocked;


};


class SceneRoot: virtual public SceneWidget {
    public:
    SceneRoot();

    void draw(ofEventArgs & args);

};


class SceneClip: public SceneWidget {

     public:

        SceneClip();

        void createEvents();

        void draw(ofEventArgs & args);

        void initialize();

        void setupVars();


        void setClip( shared_ptr<Clip> _clip );
        shared_ptr<Clip> getClip();

        void mediaClicked(widgetEvent & _event);

        void setPosition( float _pos );

        //atts
        shared_ptr<Clip> clip;
        shared_ptr<kClip> clipView;

        float savedPosition;
};





class SceneBuilder: public DBManager, virtual public kRectView{

    public:
        SceneBuilder();

        void initialize();

        void createEvents();


        void iiinit();


        void addClip( shared_ptr<Clip> _clip, float _x, float _y);

        void connectWidget( shared_ptr<SceneWidget> _clip );
        void disconnectWidget( shared_ptr<SceneWidget> _clip );

        void removeClip( shared_ptr<SceneClip> _clip );


        void addListeners( shared_ptr<SceneClip> _w );
        void removeListeners( shared_ptr<SceneClip> _w );


        void rootClicked(widgetEvent & _event);
        void clipBtnClicked(widgetEvent & _event);

        void btnClicked(widgetEvent & _event);

        void widgetPressed(widgetEvent & _event);
        void widgetDragged(widgetEvent & _event);

        void mainBtnClicked(widgetEvent & _event);

        void draw(ofEventArgs & args);



        shared_ptr<Clip> getCurrentClip();
        void setCurrentClip(shared_ptr<SceneClip> _clip);

        void setNewDraggingClip(shared_ptr<Clip> _clip);

        void setDraggingWidget(shared_ptr<SceneWidget> _clip);




        void mouseReleased(ofMouseEventArgs & mouse);

        void mouseDragged(ofMouseEventArgs & mouse);



        shared_ptr< SceneClip > selectNextClip();

        int getNearestIndex( float _x, float _y , vector< shared_ptr < SceneWidget > > _v  );

        vector< shared_ptr < SceneWidget > > getPossibleConnections( float _x, float _y , vector< shared_ptr < SceneWidget > > _v );
        vector< shared_ptr < SceneWidget > > getPossibleConnections( shared_ptr<SceneWidget> _widget, vector< shared_ptr < SceneWidget > > _v );
        shared_ptr<SceneClip> getNextClip();




        void mediaEnd();

        void play();
        void next();
        void previous();
        void pause();
        void stop();

        void savePosition( float _position );


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

        int insertThreshold;
        int autoConnectThreshold;
        shared_ptr<SceneRoot> root;

    vector< ofVec2f > draggingWidgetChildrenPositions;

//
//


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
//        shared_ptr<ClockWidget> clock;

        vector< shared_ptr<SceneWidget> > w;
        vector< shared_ptr<SceneClip> > clips;
        vector< shared_ptr<SceneWidget> > nextConnections;

        shared_ptr<Clip> newDraggingClip;


        shared_ptr<SceneClip> nextClip, currentClip, lastClip;
        shared_ptr<SceneWidget> draggingWidget;





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


//#endif


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

#endif
