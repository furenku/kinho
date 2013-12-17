#include "controllers.h"

string getFileExt(const string& s) {

   size_t i = s.rfind('.', s.length( ));
   if (i != string::npos) {
      return(s.substr(i+1, s.length( ) - i));
   }

   return("");
}


MainController::MainController(){

    videoLoader = make_shared<VideoLoader>( );

    loadSession("nosession.xml");



    presentClips = loadAllClips();


    createSettings();

    int mode = ofGetWindowMode();

    if( mode == OF_WINDOW) {
        windowW = int( ofGetWidth() );
        windowH = int( ofGetHeight() );
    } else  {
        windowW = int( ofGetScreenWidth() );
        windowH = int( ofGetScreenHeight() );
    }


    paddingX = paddingY = 70;
    spacingX = spacingY = 15;

    paddedW = windowW - 2 * paddingX;
    paddedH = windowH - 2 * paddingY;
//
//    paddingXpct = (float) paddingX / windowW;
//    paddingYpct = (float) paddingY /  windowH;

    spacingXpct = (float) spacingX / paddedW;
    spacingYpct = (float) spacingY /  paddedH;


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



//{ PREPARE:


void MainController::loadSession(string _filename) {

    xmlFile = "xml/ABISMOTEST02.xml";
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



void MainController::createSettings(){

    font.loadFont("fonts/verdana.ttf",10);
    font2.loadFont("fonts/verdana.ttf",12);
    font3.loadFont("fonts/verdana.ttf",14);


    settings = make_shared<Settings>();
    settings2 = make_shared<Settings>();
    settings -> addColor(make_shared<ofColor>(180));
    settings -> addColor(make_shared<ofColor>(255));
    settings2 -> addColor(make_shared<ofColor>(80));
    settings2 -> addColor(make_shared<ofColor>(210));

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


    for (int i=0; i<nSections; i++) {
        clipsUnsorted.push_back(  DIR.getPath(i) );
        cout << DIR.getPath(i) << endl;
    }

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
//cout << "noentrys "<< numEntries << endl;
        //we push into the last STROKE tag
        //this temporarirly treats the tag as
        //the document root.
        for (int h=0; h<numEntries; h++)
        {
            XML.pushTag("entry", h );

//            cout << "entry"<<h << endl;

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

                        for (int i=0; i<words.size(); i++)
                        {
                            if(fileName!="" && words[i] != "" && words[i] != " "){
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
                            if(fileName!="" && words[i] != "" && words[i] != " "){

                                if( tagMedia.find(words[i]) != tagMedia.end() ) {
                                    tagMedia[ words[i] ].push_back( fileName );
                                }
                                else{
                                    tagMedia[ words[i] ] = vector<string>();
                                }
                            }
                        }
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


//    makeOntologies();
    }


}



//}


//{ SETUP


void MainController::createMedia() {

    vector<string>::iterator it;
    vector<string> clips;
    vector<string> uncategorized;
    vector<string> thumbs;
    for (int i=0; i<loadMedia.size(); i++)
    {

        string filePath = mediaDirectory + loadMedia[i];
        it = find (presentClips.begin(), presentClips.end(), filePath);

        if( it != presentClips.end() ) {

            videos[ loadMedia[i] ] = makeClip( loadMedia[i], "..."  );
//            presentClips.erase(it);

//cout << "created video: "<< loadMedia[i] << endl;

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

//    for(int i=0; i<presentClips.size(); i++){
//        string ext = getFileExt( presentClips[i] );
//
////        if( ext == "mov" ) { //|| ext == "avi" || ext = "mp4" || ext == "mpg" ) {
////            string basename = presentClips[i].substr(7,string::npos);
//////            cout << " -------------------------------------- " << endl;
//////            cout << " -------------------------------------- " << endl;
//////            cout << presentClips[i]<< endl;
//////            cout << " -------------------------------------- " << endl;
//////            cout << " -------------------------------------- " << endl;
////
//////            videos[  basename ] = makeClip( basename , "..."  );
//////            uncategorized.push_back( basename );
////        }
//
////        cout << "pC: " << uncategorized.back() << endl;
//    }

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
                //cout<<"added media "<< videos[vecstr[i]]->getName() << " in cat - " << it->first <<endl;
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
//                cout<<"added media "<< videos[vecstr[i]]->getName() << " in tag - " << it->first <<endl;
            }
        }
    }
//
//    tmpCat = make_shared<Category>();
//    tmpCat->setName( "uncategorized" );
//
//    miniLibrary->addOntology( tmpCat );
//
//
//    for (int i=0; i<uncategorized.size(); i++)
//    {
//        cout << "UNC: "<<uncategorized[i] << endl;
//        if( videos.find( uncategorized[i] ) != videos.end() ) {
//            miniLibrary->setOntology( tmpCat, videos [ uncategorized[i] ] );
//        }
//    }


}


void MainController::createModules() {
//
//
//
    makeChooser();

    makeClipView();
//
    makeVideoOutput();

    makeLibrary();

    loadXml(xmlFile);



    createMedia();
//
    setOntologies();
//
//
    makeOntologies();

    makeTimelines();


    clipInfoLoaded=false;


    makeScene();



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
//
//    login(catSelect,"selectedWords",make_shared<SelectOntology>( catSelect, graphBrowser ));
//    login(catSelect,"selectedWords",make_shared<ClearOntology>( tagSelect ));
//
    ofAddListener( *catSelect->events.lookup("selectedWords"),this,&MainController::catSelected );
    ofAddListener( *tagSelect->events.lookup("selectedWords"),this,&MainController::tagSelected );

    login(timeline,"release",make_shared<SetTimelineClip>( clipView,timeline));
    login(timeline2,"release",make_shared<SetTimelineClip>( clipView,timeline2 ));


    shared_ptr<FunctorHolder> funcs = make_shared<FunctorHolder>();

    funcs->addFunc(make_shared<SetTimelineClip>( clipView,timeline));
    funcs->addFunc(make_shared<SetTimelineClip>( clipView,timeline2));

    login(clipView,"clipClicked",funcs);
//    login(clipView,"clipClicked",make_shared<SetTimelineClip>( clipView,timeline));
//    login(clipView,"clipClicked",make_shared<SetTimelineClip>( clipView,timeline2));

    login(timeline,"playClip",make_shared<PlayTimelineClip>( timeline,output ));
    login(timeline2,"playClip",make_shared<PlayTimelineClip>( timeline2,output2 ));

    login(clipView,"clipDragged",make_shared<SetDraggingClip>(scene,clipView));

//
//            // archive
//            login(archive,"release",make_shared<DragLibraryItem>( library,archive ));
//            login(archive,"addMedia",make_shared<AddMedia>( archive, selected ));
//            login(archive,"openMedia",make_shared<Say>( "openit" ));
//            login(archive,"connectOntology",make_shared<ConnectOntology>( archive, library ));
//            login(archive,"connectClip",make_shared<ConnectOntology>( archive, library ));
//
//            // selected
//
//
//            // scene
////            login(scene,"release",make_shared<AddSceneClip>(scene, selected));
//            login(scene,"playClip",make_shared<Say>( "openit" ));
            funcs.reset();
            funcs = make_shared<FunctorHolder>();
            funcs->addFunc( make_shared<PlayClip>( scene,output ) );
            funcs->addFunc( make_shared<AddTimelineMarker>( timeline , scene) );
            login(scene,"playClip",funcs);

//            login(scene,"sceneEnd",make_shared<VideoStop>( output ));
//
//            // videoplayer
            login(output,"videoEnd",make_shared<EndClip>( scene ));
//            login(output,"videoEnd",make_shared<Say>( "endit" ));


}


//}


//{ MEDIA LOGIC


shared_ptr<Clip> MainController::makeClip( string _name, string _description ){

    // make video store

    tmpClip = make_shared<Clip>();


//            string clipName = clips[i].substr(clips[i].find_last_of("/")+1,clips[i].find(".")-1);
//                cout << clipName << endl;
    tmpClip->setName( _name );
    tmpClip->setDescription( _description );
//    clip->tags.push_back("tag1");

    tmpClip->setFilename( mediaDirectory+_name );
    loadData(tmpClip);

    return tmpClip ;

}


void MainController::loadData( shared_ptr<Clip>  clip){
    videoLoader->setFilename( "movies/" + clip->getName() );
    videoLoader->loadData();
    cout << "duration : " << videoLoader->getDuration() << endl;
    clip->setDuration( videoLoader->getDuration() );
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
    timeline->set(
        paddingX,
        paddingY + ( float(4/6.0f) + 2*spacingYpct) * paddedH,
        4/5.0f * paddedW,
        1/6.0f * paddedH
    );

    timeline->setName("tmln1");
    timeline->applySettings(settings);
    timeline->setWidgetSettings(settings2);
    timeline->initialize();
    timeline->arrangeWidgets();

    clockmngr->addTimeline( timeline );

    timeline2 = make_shared<TimelineTrack>( );
    timeline2->set(
        paddingX,
        paddingY + ( float(5/6.0f) + 3*spacingYpct) * paddedH,
        4/5.0f * paddedW,
        1/6.0f * paddedH
    );

//    set(
//        ( spacingXpct ) * paddedW,
//        ( 0.833f + 2*spacingYpct  ) * paddedH,
//        ( 0.8f - spacingXpct  ) * paddedW,
//        ( 0.166f - spacingYpct  ) * paddedH
//    );
    timeline2->setName("tmln2");
    timeline2->applySettings(settings);
    timeline2->setWidgetSettings(settings2);
    timeline2->initialize();
    timeline2->arrangeWidgets();

    clockmngr->addTimeline( timeline2 );
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


void MainController::makeOntologies(){

vector< shared_ptr<Ontology> > cats = miniLibrary->getOntologies("category");
vector< shared_ptr<Ontology> > tags = miniLibrary->getOntologies("tag");

//CCscout << "a ver "<< miniLibrary->getOntologies("cat")<<"   "<< miniLibrary->getOntologies("cat").size()<<endl;

    int newH = 0.33f * paddedH - spacingY/2;


    catSelect = make_shared<WordSelect>( );
    catSelect->set(
        paddingX,
        paddingY + spacingY,
        0.166f * paddedW,
        newH
    );
    catSelect->setLabel( "Categorias" );
    catSelect->setSpacingY(65);
    catSelect->applySettings(settings);
    catSelect->setWidgetSettings(settings2);
    catSelect->initialize();
    catSelect->arrangeWidgets();

    for (int i=0; i<cats.size(); i++){
        catSelect->makeButton(cats[i]->getName());
        //cout << "cats:" << cats[i]->getName() << endl;
    }


    catSelect->arrangeWidgets();

    tagSelect = make_shared<WordSelect>( );
    tagSelect->set(
        paddingX,
        paddingY + 2*spacingY + newH,
        0.166f * paddedW,
        newH
    );

    tagSelect->setLabel( "Tags" );
    tagSelect->setSpacingY(65);

    tagSelect->applySettings(settings);
    tagSelect->setWidgetSettings(settings2);
    tagSelect->initialize();
    tagSelect->arrangeWidgets();

    for (int i=0; i<tags.size(); i++) {
        tagSelect->makeButton(tags[i]->getName());
//        cout << "tags:" << tags[i]->getName() << endl;
    }

}


void MainController::makeSessionGUI() {



}


void MainController::makeClipView() {

    clipView = make_shared<kThreadClipView>();

    clipView -> set(
        ( 0.166f ) * paddedW + spacingX + paddingX,
        spacingY + paddingY,
        ( 0.166f - spacingXpct  ) * paddedW,
        ( 0.66f * paddedH )
    );

    clipView -> applySettings ( settings  );
    clipView -> setWidgetSettings ( settings );
    clipView -> cols=1;
    clipView -> setPaddingX( 60 );
    clipView -> setSpacingX( 60 );
    clipView -> setSpacingY( 60 );

//    clipScrollViews.push_back( clipView );

//    ofAddListener( *clipView->events.lookup("clipClicked"),this,&MainController::clipClicked);
//    ofAddListener( *clipView->events.lookup("clipDragged"),this,&MainController::clipDragged);


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
    output2 = make_shared<VideoOutput>( );

//    int mode = ofGetWindowMode();
//    if( mode == OF_WINDOW) {
//        output->addRect( make_shared<ofRectangle>( 0,ofGetHeight()/6,ofGetWidth()/2,ofGetHeight()/2) );
//        output2->addRect( make_shared<ofRectangle>( ofGetWidth()/2,ofGetHeight()/6,ofGetWidth()/2,ofGetHeight()/2) );
//
//    } else  {
//        output->addRect( make_shared<ofRectangle>( 0,ofGetScreenHeight()/6,ofGetScreenWidth()/2,ofGetScreenHeight()/2) );
//        output2->addRect( make_shared<ofRectangle>( ofGetScreenWidth()/2,ofGetScreenHeight()/6,ofGetScreenWidth()/2,ofGetScreenHeight()/2) );
//    }

    output->addRect( make_shared<ofRectangle>(
        paddingX + 4.2f/5.0f * paddedW,
        paddingY + ( float(4/6.0f) + 2*spacingYpct) * paddedH,
        0.8f/5.0f * paddedW,
        1/6.0f * paddedH
    ) );

    output2->addRect( make_shared<ofRectangle>(
        paddingX + 4.2f/5.0f * paddedW,
        paddingY + ( float(5/6.0f) + 3*spacingYpct) * paddedH,
        0.8f/5.0f * paddedW,
        1/6.0f * paddedH
    ) );


}


void MainController::makeSelected(){
    selected = make_shared<kClipScrollView>( );

    selected->set(1100,50,150,700);

    selected->applySettings(settings);
    selected->setWidgetSettings(settings2);

    selected->initialize();

}


void MainController::makeScene(){
    scene = make_shared<SceneBuilder>( );

    scene->set(
        paddingX + 2*spacingX + ( 0.33f  ) * paddedW,
        spacingY + paddingX,
        0.66f * paddedW,
        0.66f * paddedH
    );
    scene->applySettings(settings);
    scene->setWidgetSettings(settings2);

    scene->initialize();

    scene->iiinit();
}


void MainController::makeChooser(){
    chooser = make_shared<kRectButtonView>( );
    chooser->set(
        paddingX,
        0,
        200,
        paddingY
    );
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

    clipView->clearClips();
    vector<string> vecstr = dynamic_pointer_cast<WordSelect>(_event.sender)->getSelected();
    vector<shared_ptr<Clip> > loadClips;
    vector<string> loadedTagNames;

    tagSelect->clear();


    for (int i=0; i<vecstr.size(); i++)
    {


        string cleanStr = vecstr[i];
        while ( cleanStr.find ("\n") != string::npos )
        {
            cleanStr.erase ( cleanStr.find ("\n"), 2 );
        }

        shared_ptr<Ontology> catOnt = miniLibrary->getOntology( cleanStr );

        if(catOnt) {

            vector< shared_ptr<Clip> > catClips = miniLibrary->getClips( catOnt );

            for (int j=0; j<catClips.size(); j++)
            {
//                cout << "ont"<<catOnt->getName()<<" has "<< catClips[j]->getName() << endl;

                if ( find( loadClips.begin(), loadClips.end(), catClips[j] ) == loadClips.end() ) {
                    loadClips.push_back(catClips[j]);

                    vector< shared_ptr < Ontology > > onts = miniLibrary->getOntologies(catClips[j]);

                    for (int k=0; k<onts.size(); k++)
                    {
                    	if( onts[k]->getType() == "tag" ){
                            string ontName = onts[k]->getName();

                            if ( find( loadedTagNames.begin(), loadedTagNames.end(), ontName ) == loadedTagNames.end() ) {
                                loadedTagNames.push_back( ontName );
                            }
                    	}
                    }
                }
            }

        }


    }

        for (int k=0; k<loadedTagNames.size(); k++)
        {
            tagSelect->makeButton( loadedTagNames[k] );
        }


        clipView->addClips(loadClips);


}

void MainController::tagSelected(widgetEvent & _event){


    clipView->clearClips();

    vector<string> vecstr = dynamic_pointer_cast<WordSelect>(_event.sender)->getSelected();
    vector<shared_ptr<Clip> > loadClips;


    for (int i=0; i<vecstr.size(); i++)
    {

        string cleanStr = vecstr[i];

        while ( cleanStr.find ("\n") != string::npos )
        {
            cleanStr.erase ( cleanStr.find ("\n"), 2 );
        }

        cout << "CHECKINGGGGGGGGGGGGGGGGG : " << cleanStr << endl;

        shared_ptr<Ontology> tagOnt = miniLibrary->getOntology( cleanStr );

        if(tagOnt) {

            vector< shared_ptr<Clip> > tagClips = miniLibrary->getClips( tagOnt );

            for (int j=0; j<tagClips.size(); j++)
            {
//                cout << "ont"<<tagOnt->getName()<<" has "<< tagClips[j]->getName() << endl;
                if ( find( loadClips.begin(), loadClips.end(), tagClips[j] ) != loadClips.end() ) {
                    cout << "found in vector" << endl;
                }
                else {
                    loadClips.push_back(tagClips[j]);
                }
            }

        }




    }

   for (int i=0; i<loadClips.size(); i++)
            {
            	cout << "CLIPNAME:  : " << loadClips[i]->getName() << endl;
            }
    clipView->addClips(loadClips);

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
        clipView->show();//set(150,50,200,500);
        catSelect->show();
        tagSelect->show();
        timeline->show();
        timeline2->show();
        scene->setWidgetSize(0.05f);
        scene->set(
            paddingX + 2*spacingX + ( 0.33f  ) * paddedW,
            spacingY + paddingX,
            0.66f * paddedW,
            0.66f * paddedH
        );
        scene->arrangeWidgets();
   }
    if(command == "escena"){
        clipView->hide();//set(150,50,200,500);
        catSelect->hide();
        tagSelect->hide();
        timeline->hide();
        timeline2->hide();
        scene->setWidgetSize(0.035f);
        scene->set(paddingX,paddingY,paddedW, paddedH);
        scene->arrangeWidgets();
   }


}


//}
