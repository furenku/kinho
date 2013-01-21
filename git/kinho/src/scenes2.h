
/*
class SceneRoot: virtual public SceneWidget {
    public:
    SceneRoot(){ setType("sceneRoot"); }

};


class ControllableWidget: public SceneWidget {
        f
    public:
        ControllableWidget(){ setupVars(); }

        void trigger() {
            if( isTriggerable )
                triggerFunc->execute();
        }

        void setTriggerFunc ( shared_ptr< Functor > _func ) {
            triggerFunc = _func;
        }

        void setSetFunc ( shared_ptr< Functor > _func ) {
            setFunc = _func;
        }

        void setupVars() {
            isTriggerable = false;
            isSettable = false;
        }
    atts
        shared_ptr<Functor> triggerFunc, setFunc;
        bool isTriggerable, isSettable;

};

class SceneMedia: public ControllableWidget {
    public:
        SceneMedia(){ setupVars(); }
        atts
            shared_ptr<MediaHolder> media;
            float position;
        f
            void setupVars() {
                isTriggerable = true;
            }

            shared_ptr<MediaHolder> getMedia() { return media; }
            void setMedia( shared_ptr<MediaHolder> _media ) { media = _media; }
            void setPosition( float _position ){ position = _position; }
            float getPosition() { return position; }
};


class SceneClip: public SceneMedia {
    public:
        SceneClip(){ setupVars(); }
        atts
             shared_ptr< TransitionControl >
             shared_ptr< PlayButton >
        atts

                float
                    alpha
                    r
                    g
                    b
                    transitiontime
                bool
                    transitionOn

                int
                    transitionType
        f

            void setupVars() {
                setType("clip");
            }
             clip
            shared_ptr<Clip> getClip() { return clip; }
            void setClip( shared_ptr<Clip> _clip ) { clip = _clip; }

        shared_ptr<Clip> getNextClipOutput() { return nextClipoutput; }
        shared_ptr<Sample> getNextSampleOutput() { return nextSampleOutput; }
        shared_ptr<Text> getNextTextOutput() { return nextTextOutput; }

};

class SceneSample {
    public:
        SceneSample(){}
};
class SceneText {
    public:
        SceneText(){}
};


class ControlWidget: public SceneWidget {
        f
            void activate() {
                forv functors
                    ->execute();
            }
            void disconnect( shared_ptr<ControllableWidget> _target){}
                remove Functor
                remove from targets array
        atts
            vector< shared_ptr<ControllableWidget> > targets;
            vector< shared_ptr<Functors> > funcs;
            kCircleScrollView
                "remove"
                "connect"
                "disconnect"
};

class ControllableControlWidget: public ControllableWidget, public ControlWidget {
};
*/


class Branch {
        //atts
            vector < shared_ptr<SceneMedia> > media;
            vector < shared_ptr<SceneMedia> > alreadyPlayed;
            shared_ptr< SceneMedia > currentMedia, lastMedia, nextMedia;
            shared_ptr<VideoOutput> videoOutput;
            shared_ptr<SampleOutput> sampleOutput;
            shared_ptr<TextOutput> textOutput;
            shared_ptr< BranchControl > controls;
            bool playing;
        //f
            //logica
                void initialize() { addControls(); }

                void addControls() {
                    controls = make_shared< BranchControl >();
                    controls->set( _x + width / 2,_y+_height, width, height);
                    ofAddListener( *controls->events.lookup("play"), this,&Branch::play);
                    ofAddListener( *controls->events.lookup("pause"), this,&Branch::pause);
                    ofAddListener( *controls->events.lookup("rew"), this,&Branch::rew);
                    ofAddListener( *controls->events.lookup("fwd"), this,&Branch::fwd);
                }

            //media
                shared_ptr< SceneMedia > playNextMedia() {
                    vector < shared_ptr<StoreObject> > c = getDescendants ( currentMedia );
                    vector < shared_ptr<SceneMedia> > possibleNext;
                    shared_ptr<SceneMedia> check;
                    nextMedia.reset();

                        bool already = false;
                        for (int i=0; i<c.size(); i++)
                        {
                        	c[i]

                        	check = dynamic_pointer_cast<SceneMedia>( c[ i ] );
                            for (int j=0; j<alreadyPlayed.size(); j++)
                            {
                            	if( check == alreadyPlayed[j] )
                                    already = true;
                                    break;
                            }

                            if(!already)
                                nextMedia = check;
                                possibleNext.push_back( check );

                        }

                        //if has children to play
                        if(possibleNext.size()>0)
//                            random
//                                int index = rand()%possibleNext.size();
//                                nextMedia = possibleNext[ index ];

                            // next one
                                nextMedia = possibleNext[0]
                        else
                            // if has siblings to play
                            // else if has ancestors to play
                            else
                                notify("branchEnd");


                    if( nextMedia ) {
                        lastMedia = currentMedia;
                        currentMedia = nextMedia;
                    }
                    string type = nextMedia -> getType();
                        if( type == "clip") {
                            notify("playClip");
                            nextClip = dynamic_pointer_cast<SceneClip>(nextMedia);
                        }
                        else if( type == "sample") {
                            notify("playSample");
                            nextSample = dynamic_pointer_cast<SceneSample>(nextMedia);
                        }
                        else if( type == "text"){
                            notify("playText");
                            nextText = dynamic_pointer_cast<SceneText>(nextMedia);
                        }
                }


                shared_ptr<SceneMedia> getNextMedia() {
                    return nextMedia;
                }

                void mediaEnd() {
                    playNextMedia();
                    alreadyPlayed.push_back(lastMedia);
                }


                void savePosition( float _position ) {
                    currentMedia->setPosition( _position );
                }

                shared_ptr< SceneMedia > getPrevMedia() {
                    return lastMedia;
                }

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
//                playWidget->set (
//                _media->getX() / width,
//                _media->getY() / height,
//                playWidget->getWidth() / width,
//                playWidget->getHeight() / height
//                );
//                // ?? insert into beginning of array
            }
            */
        //logica
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

};

/*

class BranchControl: virtual public kRectView {
        //f
            void initialize() {
                params = make_shared<ParamView> ();
                shared_ptr<Param> param = make_shared<Param>();
                param->setName("alpha");
            }
        //atts
            shared_ptr<ParamView> params;

};


*/


