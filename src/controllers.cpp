#include "controllers.h"

MainController::MainController(){

    videoLoader = make_shared<VideoLoader>( );

    loadSession("nosession.xml");



    presentClips = loadAllClips();


    createSettings();

    createModules();

    loadAllClips();

}



void MainController::update() {

    if(!clipInfoLoaded){
//
//        map< string, shared_ptr<Clip> >::iterator iter;
//
//        for( iter = videos.begin(); iter != videos.end(); ++iter) {
////            loadData(iter->second);
////            cout << "duration: "<<iter->second->getDuration() << endl;
//        }
//
//        clipInfoLoaded = true;

    }

}



//{ SETUP:

void MainController::createSettings(){

    font.loadFont("fonts/verdana.ttf",12);
    font2.loadFont("fonts/verdana.ttf",14);
    font3.loadFont("fonts/verdana.ttf",18);


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



vector<string> MainController::loadAllClips() {

    vector<string> clipsUnsorted;
    vector<string> clips;
//            vector <string> sectionsUnsorted;
//            vector <string> catsUnsorted;
//            vector <string> catPath;

//            int nSections = DIR.listDir("movies/new/");
    int nSections = DIR.listDir("movies/");


    for (int i=0; i<nSections; i++)
        clipsUnsorted.push_back(  DIR.getPath(i) );

//            clips = sortAlpha(clipsUnsorted);

    return clipsUnsorted;
//            return clips;

}




void MainController::loadXml(string _file){
    std::vector<std::string> words;
    std::string s;
    if( XML.loadFile(_file) ){
        cout << _file<<" loaded" << endl;
//		message = "mySettings.xml loaded!";
    }else{
        cout << _file<<" not loaded" << endl;
//		message = "unable to load mySettings.xml check data/ folder";
    }

    int numEntries = XML.getNumTags("entry");

    //if there is at least one <STROKE> tag we can read the list of points
    //and then try and draw it as a line on the screen
    if(numEntries > 0){
cout << "noentrys "<< numEntries << endl;
        //we push into the last STROKE tag
        //this temporarirly treats the tag as
        //the document root.
        for (int h=0; h<numEntries; h++)
        {
            XML.pushTag("entry", h );

            cout << "entry"<<h << endl;

            //we see how many points we have stored in <PT> tags
            int numParams = XML.getNumTags("param");
            if(numParams > 0){

                //We then read those x y values into our
                //array - so that we can then draw the points as
                //a line on the screen

                //we have only allocated a certan amount of space for our array
                //so we don't want to read more than that amount of points
//				int totalToRead = MIN(numPtTags, NUM_PTS);
            string fileType = ofToString( XML.getValue("param:value", "", 2) );
            string fileName,description;

            if( fileType.compare("video")==0) {
                for(int i = 0; i < numParams; i++){
                    //the last argument of getValue can be used to specify
                    //which tag out of multiple tags you are refering to.
                    string key = XML.getValue("param:key", "", i);
                    string val = XML.getValue("param:value", "", i);

                //categorías


                switch(i){
                    case 1:
                        fileName = XML.getValue("param:value", "", 1 );

                        if( find( loadMedia.begin(), loadMedia.end(), fileName ) == loadMedia.end() )
                            loadMedia.push_back(fileName);

                        break;
                    case 3:
//                      videos[fileName]->setStartTime( ofToFloat(val) );
                        //startTime
                        break;
                    case 4:
                        //endTime

//                                videos[fileName]->setEndTime( ofToFloat(val) );

                        break;
                    case 5:
                    // categories
                        boost::split(words, val, boost::is_any_of(","), boost::token_compress_on);
                        //else cout << key << endl;
                        cout << "key:"<< key << endl;

                        for (int i=0; i<words.size(); i++)
                        {
                            if(fileName!=""){
                                if( catMedia.find(words[i]) != catMedia.end() ) {
                                    catMedia[ words[i] ].push_back( fileName );
                                }
                                else{
                                    catMedia[ words[i] ] = vector<string>();
                                }
                            }
                        }
                        break;
                    case 6:
                        //tags
                        boost::split(words, val, boost::is_any_of(","), boost::token_compress_on);

                        for (int i=0; i<words.size(); i++)
                        {
                            if(fileName!=""){
                                if( tagMedia.find(words[i]) != tagMedia.end() ) {
                                    tagMedia[ words[i] ].push_back( fileName );
                                }
                                else{
                                    tagMedia[ words[i] ] = vector<string>();
                                }
                            }
                        }
                        break;
                        break;
                    case 7:
                        //descripcion
                        description = XML.getValue("param:value", "", i );
                        break;
                    case 8:
                        // quien
                        break;
                    case 9:
                        //donde
                        break;
                    case 10:
                        // que pasa
                        break;
                    case 11:
                        //objetos
                        break;
                    case 12:
                        //fecha
                        break;

                }
//cout << "FN  "<<fileName<<"  "<<description << endl;


            }
        }


    }

    //this pops us out of the STROKE tag
    //sets the root back to the xml document
    XML.popTag();
    }


    makeOntologies();
    }


}





void MainController::createMedia() {

    vector<string> clips;
    vector<string> thumbs;
cout << "createMeida" << endl;
    for (int i=0; i<loadMedia.size(); i++)
    {
    	cout << "loadMedia" << loadMedia[i] << endl;


        cout << "checkClip! .. " << endl;

        string searchString = mediaDirectory + loadMedia[i];

        if( find (presentClips.begin(), presentClips.end(), searchString) != presentClips.end() ) {


            videos[ loadMedia[i] ] = makeClip( loadMedia[i], "..."  );
cout << "created video: "<< loadMedia[i] << endl;

//            int index = fileName.find(".");
//
//            if ( fileName.substr(index+1, 3) == "png" )
//                thumbs.push_back(fileName);
//            else
//                clips.push_back(fileName);
        }




//        cout << "makeclip!  "<<makeClip( fileName, description ) -> getName() << endl;
//        cout << "videoName" << videos[fileName]->getName() << endl;

    }

}


void MainController::setOntologies(){

    map <string,vector<string> >::iterator it;

    for( it = catMedia.begin(); it!=catMedia.end(); ++it ){

        tmpCat = make_shared<Category>();
        tmpCat->setName( it->first );

        vector < string > vecstr = it->second;

        miniLibrary->addOntology( tmpCat );

        for (int i=0; i<vecstr.size(); i++)
        {
            if( videos.find( vecstr[i] ) != videos.end() ) {
                miniLibrary->setOntology( tmpCat, videos [ vecstr[i] ] );
                cout<<"added media "<< videos[vecstr[i]]->getName() << " in cat - " << it->first <<endl;
            }
        }
    }



    for( it = tagMedia.begin(); it!=tagMedia.end(); ++it ){

        tmpTag = make_shared<Tag>();
        tmpTag->setName( it->first );

        vector < string > vecstr = it->second;

        miniLibrary->addOntology( tmpTag );

        for (int i=0; i<vecstr.size(); i++)
        {
            if( videos.find( vecstr[i] ) != videos.end() ) {
                miniLibrary->setOntology( tmpTag, videos [ vecstr[i] ] );
                cout<<"added media "<< videos[vecstr[i]]->getName() << " in tag - " << it->first <<endl;
            }
        }
    }
}


void MainController::createModules() {
//
//
//
    makeClipView();
//
    makeVideoOutput();

    makeLibrary();

    loadXml("xml/ABISMOTEST02.xml");



    createMedia();

    setOntologies();


    makeOntologies();

    makeTimelines();



    clipInfoLoaded=false;

    map<string,shared_ptr<Clip> >::iterator iter;

    vector<string>c;

    for(iter = videos.begin(); iter != videos.end(); ++iter ){
        c.push_back( iter->first );
    }



//
//
//
//    for (int i=0; i<c.size(); i++)
//    {
//
//
//    }
//
//    vector< shared_ptr < Clip > > loadClips;
//
//    for (int i=0; i<clips.size(); i++)
//    {
//
//        shared_ptr<Clip> clip= make_shared<Clip>();
//        string clipName = c[i].substr(clips[i].find_last_of("/")+1,clips[i].find(".")-1);
//
//        clip->setName( clipName );
//        clip->setDescription("...");
//
//        clip -> setFilename( mediaDirectory + clips[i] );
//        loadClips.push_back(clip);
//
//    }
//
//    clipView->addClips(loadClips);

/*

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



void MainController::makeLogins(){

//            login(catSelect,"selectedWords",make_shared<SelectOntology>( catSelect, graphBrowser ));
//    login(catSelect,"selectedWords",make_shared<ClearOntology>( tagSelect ));

    ofAddListener( *catSelect->events.lookup("selectedWords"),this,&MainController::catSelected );
    ofAddListener( *tagSelect->events.lookup("selectedWords"),this,&MainController::tagSelected );

    login(timeline,"release",make_shared<SetTimelineClip>( clipView,timeline));
    login(timeline2,"release",make_shared<SetTimelineClip>( clipView,timeline2 ));


login(clipView,"clipClicked",make_shared<SetTimelineClip>( clipView,timeline));
login(clipView,"clipClicked",make_shared<SetTimelineClip>( clipView,timeline2));

login(timeline,"playClip",make_shared<PlayTimelineClip>( timeline,output ));
login(timeline,"playClip",make_shared<PlayTimelineClip>( timeline2,output ));

//
//            // archive
//            login(archive,"release",make_shared<DragLibraryItem>( library,archive ));
//            login(archive,"addMedia",make_shared<AddMedia>( archive, selected ));
//            login(archive,"openMedia",make_shared<Say>( "openit" ));
//            login(archive,"connectOntology",make_shared<ConnectOntology>( archive, library ));
//            login(archive,"connectClip",make_shared<ConnectOntology>( archive, library ));
//
//            // selected
//            login(selected,"clipDragged",make_shared<SetDraggingClip>(scene,selected));
//
//
//            // scene
////            login(scene,"release",make_shared<AddSceneClip>(scene, selected));
//            login(scene,"openMedia",make_shared<Say>( "openit" ));
//            login(scene,"playClip",make_shared<PlayClip>( scene,output ));
//            login(scene,"sceneEnd",make_shared<VideoStop>( output ));
//
//            // videoplayer
//            login(output,"videoEnd",make_shared<EndClip>( scene ));
//            login(output,"videoEnd",make_shared<Say>( "endit" ));


}




void MainController::loadSession(string _filename) {

    mediaDirectory="movies/";
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


//}

//{ MEDIA LOGIC


shared_ptr<Clip> MainController::makeClip( string _name, string _description ){
    cout << "movies/"+_name << endl;

    // make video store

    tmpClip = make_shared<Clip>();


//            string clipName = clips[i].substr(clips[i].find_last_of("/")+1,clips[i].find(".")-1);
//                cout << clipName << endl;
    tmpClip->setName( _name );
    tmpClip->setDescription( _description );
//    clip->tags.push_back("tag1");

    tmpClip->setFilename( "movies/"+_name );

    return tmpClip ;

}


void MainController::loadData( shared_ptr<Clip>  clip){
//    videoLoader->setFilename( "movies/" + clip->getName() );
//    videoLoader->loadData();
//    cout << "duration : " << videoLoader->getDuration() << endl;
//    clip->setDuration( videoLoader->getDuration() );
}


//}

//{ ONTOLOGIES
//}

//{ individual modules


void MainController::makeEditor(){
//            editor = make_shared<Editor>();
//            editor->applySettings(settings2);
//            editor->setWidgetSettings(settings);
//            editor->initialize();
//            editor->set(50,50,1200,700);
}

void MainController::makeTimelines(){
    clockmngr = make_shared<ClockManager>( );

    timeline = make_shared<TimelineTrack>( );
    timeline->set(100,100,600,100);
    timeline->applySettings(settings);
    timeline->setWidgetSettings(settings2);
    timeline->initialize();
    timeline->arrangeWidgets();

    clockmngr->addTimeline( timeline );

    timeline2 = make_shared<TimelineTrack>( );
    timeline2->set(100,200,600,100);
    timeline2->applySettings(settings);
    timeline2->setWidgetSettings(settings2);
    timeline2->initialize();
    timeline2->arrangeWidgets();

    clockmngr->addTimeline( timeline2 );

//            timelines = make_shared<TimelineView>( );
//            timelines->set(100,100,600,300);
//            timelines->applySettings(settings);
//            timelines->setWidgetSettings(settings2);
//            timelines->initialize();
//            timelines->arrangeWidgets();



}

void MainController::makeArchive(){

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

void MainController::makeOntologies(){

vector< shared_ptr<Ontology> > cats = miniLibrary->getOntologies("category");
vector< shared_ptr<Ontology> > tags = miniLibrary->getOntologies("tag");
cout << "CATSSSS" << cats.size() << endl;
//CCscout << "a ver "<< miniLibrary->getOntologies("cat")<<"   "<< miniLibrary->getOntologies("cat").size()<<endl;
shared_ptr<kLabelButton> btn;



    catSelect = make_shared<WordSelect>( );
    catSelect->set(700,0,250,250);
    catSelect->setSpacingY(65);
    catSelect->applySettings(settings);
    catSelect->setWidgetSettings(settings2);
    catSelect->initialize();
    catSelect->arrangeWidgets();

    cout << cats.size() << endl;
    for (int i=0; i<cats.size(); i++){
        catSelect->makeButton(cats[i]->getName());
        cout << "cats:" << cats[i]->getName() << endl;
    }


    catSelect->arrangeWidgets();

    tagSelect = make_shared<WordSelect>( );
    tagSelect->set(700,300,250,250 );
    tagSelect->applySettings(settings);
    tagSelect->setWidgetSettings(settings2);
    tagSelect->initialize();
    tagSelect->arrangeWidgets();

    for (int i=0; i<tags.size(); i++) {
        tagSelect->makeButton(tags[i]->getName());
        cout << "tags:" << tags[i]->getName() << endl;
    }

}

void MainController::makeLibrary(){

    miniLibrary = make_shared<LibraryManager>( );
//            miniLibrary->applySettings(settings);
//            miniLibrary->setWidgetSettings(settings2);
//
//            placeSelect = make_shared<WordSelect>( );
//            placeSelect->set(700,320,250,120 );
//            placeSelect->applySettings(settings);
//            placeSelect->setWidgetSettings(settings2);
//            placeSelect->initialize();
//            placeSelect->arrangeWidgets();
//
//            objSelect = make_shared<WordSelect>( );
//            objSelect->set(700,440,250,120 );
//            objSelect->applySettings(settings);
//            objSelect->setWidgetSettings(settings2);
//            objSelect->initialize();
//            objSelect->arrangeWidgets();
//
//
//            actorsSelect = make_shared<WordSelect>( );
//            actorsSelect->set(700,560,250,120 );
//            actorsSelect->applySettings(settings);
//            actorsSelect->setWidgetSettings(settings2);
//            actorsSelect->initialize();
//            actorsSelect->arrangeWidgets();
//
//            actionsSelect = make_shared<WordSelect>( );
//            actionsSelect->set(700,680,250,120);
//            actionsSelect->applySettings(settings);
//            actionsSelect->setWidgetSettings(settings2);
//            actionsSelect->initialize();
//            actionsSelect->arrangeWidgets();
//
//            graphBrowser = make_shared<GraphBrowser>( );

/*
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


*/

}

void MainController::makeClipView() {

    clipView = make_shared<kClipScrollView>();

    clipView -> set(1000,0,280,800);
    clipView -> applySettings ( settings  );
    clipView -> setWidgetSettings ( settings );
    clipView -> cols=2;
    clipView -> setSpacingX( 105 );
    clipView -> setSpacingY( 65 );

//    clipScrollViews.push_back( clipView );

    ofAddListener( *clipView->events.lookup("clipClicked"),this,&MainController::clipClicked);
    ofAddListener( *clipView->events.lookup("clipDragged"),this,&MainController::clipDragged);


//
//            if(mediaViews.back()) {
//                mediaViews.back() -> addWidget(clipView);
//                mediaViews.back()->arrangeWidgets();
//            }
    clipView -> initialize();



}

void MainController::makePlayLists(){
//            playlists.push_back( make_shared<PlayList>( ) );
}

void MainController::makeVideoOutput(){

    output = make_shared<VideoOutput>( );

    output->addRect( make_shared<ofRectangle>( 0,0,ofGetWidth(),ofGetHeight()) );

    output->addRect( make_shared<ofRectangle>(ofGetWidth()-200,ofGetHeight()-150,200,150) );

//            output->changeClip("movies/fingers.mov");
//
//            output->play();

}

void MainController::makeSelected(){
    selected = make_shared<kClipScrollView>( );

    selected->set(1100,50,150,700);

    selected->applySettings(settings);
    selected->setWidgetSettings(settings2);

    selected->initialize();

}

void MainController::makeScene(){
//            scene = make_shared<SceneBuilder>( );
//
//            scene->set(50,50,1050,700);
//
//            scene->applySettings(settings);
//            scene->setWidgetSettings(settings2);
//
//            scene->initialize();
//
//            scene->iiinit();

}

void MainController::makeChooser(){
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


//}


//{ ACTIONS


void MainController::catSelected(widgetEvent & _event){
//            vector< shared_ptr < kWidget > > widgets = clipView->getWidgets();
//            for (int j=0; j<widgets.size(); j++)
//            {
//                widgets[j]->disable();
//            }

//cout << "catSelected" << endl;

    vector<string> vecstr = dynamic_pointer_cast<WordSelect>(_event.sender)->getSelected();
    vector<shared_ptr<Clip> > loadClips;
    for (int i=0; i<vecstr.size(); i++)
    {
        string cleanStr = vecstr[i];

        while ( cleanStr.find ("\n") != string::npos )
        {
            cleanStr.erase ( cleanStr.find ("\n"), 2 );
        }

        shared_ptr<Ontology> catOnt = miniLibrary->getOntology( cleanStr );

        vector< shared_ptr<Clip> > catClips = miniLibrary->getClips( catOnt );

        for (int j=0; j<catClips.size(); j++)
        {
        	cout << "ont"<<catOnt->getName()<<" has "<< catClips[j]->getName() << endl;

            if ( find( loadClips.begin(), loadClips.end(), catClips[j] ) != loadClips.end() ) {
                cout << "found in vector" << endl;
            }{
                loadClips.push_back(catClips[j]);
            }

        }

    clipView->clearClips();

        clipView->addClips(loadClips);

    }
}

void MainController::tagSelected(widgetEvent & _event){
cout << "tagSelected" << endl;

//            vector< shared_ptr < kWidget > > widgets = clipView->getWidgets();
//            for (int j=0; j<widgets.size(); j++)
//            {
//                widgets[j]->disable();
//            }
//            clipView->clearWidgets();

    clipView->clearClips();
//
//
//    vector<string> vecstr = dynamic_pointer_cast<WordSelect>(_event.sender)->getSelected();
//    for (int i=0; i<vecstr.size(); i++)
//    {
//        clipView->addClips(miniLibrary->getClips(miniLibrary->getOntology(vecstr[i])));
//    }
}

void MainController::clipClicked(widgetEvent & _event){
    shared_ptr<kClipScrollView> view = dynamic_pointer_cast<kClipScrollView>(_event.sender);
    clickedClip = dynamic_pointer_cast<kClipShow>(view->getWidgets()[view->getValue()])->getClip();
    cout << clickedClip->getName() << endl;
    notify("clipClicked");
}

void MainController::clipDragged(widgetEvent & _event){
    shared_ptr<kClipScrollView> view = dynamic_pointer_cast<kClipScrollView>(_event.sender);
    cout << view->getValue() << endl;
    draggingClip = dynamic_pointer_cast<kClipShow>(view->getWidgets()[view->getValue()])->getClip();
    notify("clipDragged");
}


void MainController::chooseView(widgetEvent & _event) {
    string command = dynamic_pointer_cast<kButtonView>(_event.sender)->getCommand();

    if(command == "archivo"){
        archive->show(); archive->enable();
//                scene->hide(); scene->disable();
        library->getView()->show();
        library->getView()->enable();
        library->arrangeWidgets();
    }
    if(command == "escena"){
//                scene->show(); scene->enable();
        archive->hide(); archive->disable();
        library->hide(); library->disable();
        library->getView()->hide();
        library->getView()->disable();
        library->arrangeWidgets();
    }


}


//}
