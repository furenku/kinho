

#pragma once

#ifndef controllers_h
#define controllers_h

class MainController: public Controller {
    public:
        MainController(){
            createSettings();
            createModules();
        }

        void createSettings(){

            font.loadFont("fonts/verdana.ttf",8);
            font2.loadFont("fonts/verdana.ttf",12);
            font3.loadFont("fonts/verdana.ttf",15);


            settings = make_shared<Settings>();
            settings2 = make_shared<Settings>();
            settings -> addColor(make_shared<ofColor>(80,80,30));
            settings -> addColor(make_shared<ofColor>(155,155,30));
            settings2 -> addColor(make_shared<ofColor>(150,90,40));
            settings2 -> addColor(make_shared<ofColor>(250,120,0));

            settings -> addFont( shared_ptr<ofTrueTypeFont>(&font2), make_shared<ofColor>(150 ) );
            settings2 -> addFont( shared_ptr<ofTrueTypeFont>(&font), make_shared<ofColor>( 250 ) );
            settings2 -> addFont( shared_ptr<ofTrueTypeFont>(&font3), make_shared<ofColor>( 150 ) );

        }


        vector<string> loadAllClips() {

            vector<string> clipsUnsorted;
            vector<string> clips;
//            vector <string> sectionsUnsorted;
//            vector <string> catsUnsorted;
//            vector <string> catPath;

            int nSections = DIR.listDir("movies/new/");


            for (int i=0; i<nSections; i++)
                clipsUnsorted.push_back(  DIR.getPath(i) );

//            clips = sortAlpha(clipsUnsorted);

            return clipsUnsorted;
//            return clips;

        }





shared_ptr<TimelineView> timelines;
shared_ptr<TimelineTrack> timeline;
shared_ptr<ClockManager> clockmngr;

        void createModules() {
            makeTimelines();

/*
            vector<string>c = loadAllClips();
            vector<string> clips;
            vector<string> thumbs;
            for (int i=0; i<c.size(); i++)
            {
            	int index = c[i].find(".");

            	if ( c[i].substr(index+1, 3) == "png" )
                    thumbs.push_back(c[i]);
                else
                    clips.push_back(c[i]);
            }

            for (int i=0; i<clips.size(); i++)
            {

                shared_ptr<Clip> clip= make_shared<Clip>();
                string clipName = clips[i].substr(clips[i].find_last_of("/")+1,clips[i].find(".")-1);
//                cout << clipName << endl;
                clip->setName( clipName );
                clip->setDescription("...");
            //    clip->tags.push_back("tag1");
                clip -> setFilename(clips[i]);
                media.push_back(clip);

            }

            loadSession();

            makeVideoOutput();

            makeEditor();
            editor->hide();
            editor->disable();



            makeArchive();

            //{archive


        //    cout << archive->getMedia()[0]->getX() << endl;
        //
        //
//            archive->connect(
//                archive->getWidgets()[0],
//                archive->getWidgets()[1]
//            );
//
//            for (int i=0; i<4; i++)
//            {
//                archive->setHierarchy(
//                    archive->getWidgets().back(),
//                    archive->getWidgets()[i*2]
//                );
//            }

            //}


            makeLibrary();
//
            makeScene();

            scene->hide();
            scene->disable();

            makeSelected();


            makeChooser();




//            login(archive,"release",make_shared<Say>("yeah"));//make_shared<DragLibraryItem>( library,archive ));

//            login(archive,"release",make_shared<Say>("yeah"));//make_shared<DragLibraryItem>( library,archive ));

            //{ outputs


//            outputs = make_shared<Outputs>( );

//            vector<shared_ptr<ofRectangle> > rectvec;
//
//            rectvec.push_back( make_shared<ofRectangle>(900,650,280,130) );
////            rectvec.push_back( make_shared<ofRectangle>(50,50,30,20) );
//
//            outputs->addVideoOutput( rectvec );
//
//            outputs->getVideoOutput( 0 )->changeClip("movies/fingers.mov");
//            outputs->getVideoOutput( 0 )->play();

//            login(outputs,"videoEnd", ChangeVideo( playlists, outputs ) );
            //}
*/
        }

        void makeLogins(){


            // archive
            login(archive,"release",make_shared<DragLibraryItem>( library,archive ));
            login(archive,"addMedia",make_shared<AddMedia>( archive, selected ));
            login(archive,"openMedia",make_shared<Say>( "openit" ));
            login(archive,"connectOntology",make_shared<ConnectOntology>( archive, library ));
            login(archive,"connectClip",make_shared<ConnectOntology>( archive, library ));

            // selected
            login(selected,"clipDragged",make_shared<SetDraggingClip>(scene,selected));


            // scene
//            login(scene,"release",make_shared<AddSceneClip>(scene, selected));
            login(scene,"openMedia",make_shared<Say>( "openit" ));
            login(scene,"playClip",make_shared<PlayClip>( scene,output ));
            login(scene,"sceneEnd",make_shared<VideoStop>( output ));

            // videoplayer
            login(output,"videoEnd",make_shared<EndClip>( scene ));
            login(output,"videoEnd",make_shared<Say>( "endit" ));


        }





        void loadSession() {
            //library
                // load all video clips
                // with the video loader
                //videoLoader->
                // load all ontologies

                //create ontologies

                // add media to them
            // archive

                // load all objects
                // create their relationships

        }

        void makeEditor(){
            editor = make_shared<Editor>();
            editor->applySettings(settings2);
            editor->setWidgetSettings(settings);
            editor->initialize();
            editor->set(50,50,1200,700);
        }

        void makeTimelines(){

            timeline = make_shared<TimelineTrack>( );
            timeline->set(100,100,600,300);
            timeline->applySettings(settings);
            timeline->setWidgetSettings(settings2);
            timeline->initialize();
            timeline->arrangeWidgets();



//            timelines = make_shared<TimelineView>( );
//            timelines->set(100,100,600,300);
//            timelines->applySettings(settings);
//            timelines->setWidgetSettings(settings2);
//            timelines->initialize();
//            timelines->arrangeWidgets();

            //{ CLOCK:

            clockmngr = make_shared<ClockManager>( );

            clockmngr->addTimeline( timeline );

            //}
        }

        void makeArchive(){

            archive = make_shared<Archive>( );

            archive->set(250,50,850,700);

            archive->applySettings(settings);
            archive->setWidgetSettings(settings2);

            archive->initialize();

            for (int i=0; i<2; i++)
            {
        //        archive->addClip( clip1, 0.2+0.3*i,0.4 );
        //        archive->addClip( clip2, 0.4+0.3*i,0.4 );
        //        archive->addClip( clip3, 0.6+0.3*i,0.4 );
        //        archive->addClip( clip4, 0.8+0.3*i,0.4 );
//                archive->addClip( clip3, ofRandomuf(),ofRandomuf() );
//                archive->addClip( clip4, ofRandomuf(), ofRandomuf() );
//                archive->addClip( clip3, ofRandomuf(),ofRandomuf() );
//                archive->addClip( clip4, ofRandomuf(), ofRandomuf() );
        //
        //
            }

            for (int i=0; i<archive->getWidgets().size(); i++)
            {
                archive->getWidgets()[i]->setName("m_"+ofToString(i));
            }


//            shared_ptr<Category> cat = make_shared<Category>( );
//            cat->setName("cat1");
//            archive->addOntology(cat,0.5f,0.5f);
//            cat.reset();

            archive->arrangeWidgets();


        }

        void makeLibrary(){

         //kinhoFont.drawString(ofToString(ofGetFrameRate(),2), 30, 30 );
   library = make_shared<Library>( );
//    arc = make_shared<Archive>( );

            library->applySettings(settings);
            library->setWidgetSettings(settings2);
        //    library->addClip(clip1);

        //    library->addClip(clip3);
        //
            shared_ptr<Category> cat=make_shared<Category>( );
            cat->setName("agua");
            library->addOntology(cat);
            cat.reset();

            cat=make_shared<Category>( );
            cat->setName("tierra");
            library->addOntology(cat);
            cat.reset();

            cat=make_shared<Category>( );
            cat->setName("aire");
            library->addOntology(cat);
        //    cat.reset();

            cat=make_shared<Category>( );
            cat->setName("fuego");
            library->addOntology(cat);


            library->setOntology(library->getOntology("agua"), media[0] );
            library->setOntology(library->getOntology("tierra"), media[1] );
            library->setOntology(library->getOntology("aire"), media[2] );
            library->setOntology(library->getOntology("fuego"), media[3] );

            library->setHierarchy( library->getOntology("uncat"), library->getOntology("agua") );
            library->setHierarchy( library->getOntology("uncat"), library->getOntology("tierra") );


            library->setOntology(library->getOntology("uncat"), media );

            library->loadView();



        }

        void makePlayLists(){
            playlists.push_back( make_shared<PlayList>( ) );
        }

        void makeVideoOutput(){

            output = make_shared<VideoOutput>( );

            output->addRect( make_shared<ofRectangle>( 0,0,ofGetWidth(),ofGetHeight()) );

            output->addRect( make_shared<ofRectangle>(ofGetWidth()-200,ofGetHeight()-150,200,150) );

//            output->changeClip("movies/fingers.mov");
//
//            output->play();

        }


        void makeSelected(){
            selected = make_shared<kClipScrollView>( );

            selected->set(1100,50,150,700);

            selected->applySettings(settings);
            selected->setWidgetSettings(settings2);

            selected->initialize();

        }

        void makeScene(){
            scene = make_shared<SceneBuilder>( );

            scene->set(50,50,1050,700);

            scene->applySettings(settings);
            scene->setWidgetSettings(settings2);

            scene->initialize();

            scene->iiinit();

        }


        void makeChooser(){
            chooser = make_shared<kRectButtonView>( );
            chooser->set(50,0,200,50);
            chooser->setSpacingX(70);
            chooser->applySettings(settings2);
            chooser->setWidgetSettings(settings);
            chooser->initialize();

            vector<string> labels;

            labels.push_back("archivo");
            labels.push_back("escena");

            chooser->addButtons(labels);

            ofAddListener(*chooser->events.lookup("btnClicked"), this, &MainController::chooseView);
        }


        void chooseView(widgetEvent & _event) {
            string command = dynamic_pointer_cast<kButtonView>(_event.sender)->getCommand();

            if(command == "archivo"){
                archive->show(); archive->enable();
                scene->hide(); scene->disable();
                library->getView()->show();
                library->getView()->enable();
                library->arrangeWidgets();
            }
            if(command == "escena"){
                scene->show(); scene->enable();
                archive->hide(); archive->disable();
                library->hide(); library->disable();
                library->getView()->hide();
                library->getView()->disable();
                library->arrangeWidgets();
            }


        }

        vector<shared_ptr<MediaHolder> > media;
        shared_ptr<Editor>  editor;
        shared_ptr<Library> library;
        shared_ptr<Archive> archive;
        shared_ptr<SceneBuilder> scene;
        vector< shared_ptr<PlayList> > playlists;


        shared_ptr<kRectButtonView> chooser;
        shared_ptr<kClipScrollView> selected;

        shared_ptr<VideoOutput> output;

        ofTrueTypeFont  font,font2,font3, kinhoFont;
        shared_ptr<Settings> settings,settings2;

        ofxDirList DIR;




};



#endif

