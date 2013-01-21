#include "testApp.h"




shared_ptr<Clip> clip1,clip2,clip3,clip4;
shared_ptr<Clip> currentClip;
shared_ptr<Sample> sample1,sample2;

int bgcolor;
int counter = 0;


shared_ptr<kClipShow> clip ;
shared_ptr<kCircleButton> btn;


shared_ptr<kRectView> testview;



shared_ptr<TestDB> db;
shared_ptr<TestObj1> obj1;
shared_ptr<TestObj2> obj2;
//
//map<std::string, shared_ptr<kView> >::iterator viewIter;
//map< string, shared_ptr<kView> > view;

shared_ptr<Library> lib;
shared_ptr<Archive> arc;
shared_ptr<SceneBuilder> builder;

//shared_ptr<Archive> arc;


shared_ptr<kField2D> vw;

shared_ptr<TSTVW> tstvw;

shared_ptr<ClockWidget> clock1,clock2,clock3;

ofTrueTypeFont kinhoFont;




#include <assert.h>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>





//shared_ptr<threadedClock> clock;

//--------------------------------------------------------------




void testApp::setup(){
//	synth.loadSound("sounds/1085.wav");
//	synth.setVolume(0.75f);

ofSetWindowPosition(1280,0);



//{ THREADED CLOCK:


    // Set up clock
    tempo = 120.0f;
    clock.notesPerPhrase = 4;
    clock.start(this);




//}

//{ NEWCLIPS
    clip1 = make_shared<Clip>();
    clip1->setName("blood01");
    clip1->setDescription("blood flowing");
//    clip->tags.push_back("tag1");
    clip1 -> setFilename("movies/new/blood01.mp4");

    clip2 = make_shared<Clip>();
    clip2->setName("blood02");
    clip2->setDescription("blood flowing");
//    clip->tags.push_back("tag1");
    clip2->setFilename("movies/new/blood02.mp4");

    clip3 = make_shared<Clip>();
    clip3->setName("blood03");
    clip3->setDescription("blood flowing");
//    clip->tags.push_back("tag1");
    clip3->setFilename("movies/new/blood03.mp4");
/*
    clip4 = make_shared<Clip>();
    clip4->setName("fingers");
    clip4->setDescription("dedos");
//    clip->tags.push_back("tag1");
    clip4->setFilename("movies/fingers.mov");
*/


    sample1 = make_shared<Sample>();
    sample1->setName("audio1");
    sample1->setDescription("...");
//    clip->tags.push_back("tag1");
    sample1->setFilename("audio/audio1.wav");


    sample2 = make_shared<Sample>();
    sample2->setName("audio2");
    sample2->setDescription("···");
//    clip->tags.push_back("tag2");
    sample2->setFilename("audio/audio2.wav");


//}








//{ SETTINGS

    ofSetCircleResolution(200);

    ofEnableSmoothing();

    bgcolor = 0;
    ofBackground(bgcolor);

    ofNoFill();
    ofSetLineWidth(2);

    kinhoFont.loadFont("fonts/constructivist-solid.ttf",20);




//}
//    ofSetWindowPosition


    ctl = make_shared<MainController>( );

    ctl->makeLogins();





/*
builder = make_shared<SceneBuilder>( );

builder->set(100,100,500,300);
builder->applySettings(settings);
builder->setWidgetSettings(settings2);
builder->iiinit();
*/

/*

tstvw = make_shared<TSTVW>( );

tstvw->set(100,100,500,300);
tstvw->applySettings(settings);
tstvw->setWidgetSettings(settings2);
tstvw->init();


*/

/*

    testview = make_shared<kRectView>( );
    testview -> set( 10, 300,300,500 );
    testview->applySettings(settings);
    testview->setWidgetSettings(settings2);
//    testview->initialize();

    shared_ptr<ArchiveWidget> aw = make_shared<ArchiveWidget>();
    aw->applySettings(settings);
    aw->setWidgetSettings(settings2);
    aw->set( 0.7f, 0.1f, 30, 30 );

    testview->addWidget(aw);

    aw->initialize();


    vector< shared_ptr < MediaHolder > > media;
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);


    aw->loadMediaView(media);

    testview->arrangeWidgets();


*/


/*


*/


/*


    shared_ptr<kDropDown> dd = make_shared<kDropDown>();
    dd->applySettings(settings);
    dd->setWidgetSettings(settings2);
    dd->set( 0.1f, 0.1f, 150, 20 );

    testview->addWidget(dd);

    testview->arrangeWidgets();

    dd->initialize();

    vector<string> vecstr;

    vecstr.push_back("uno");
    vecstr.push_back("dos");
    vecstr.push_back("tres");
    vecstr.push_back("cuatro");
    vecstr.push_back("cinco");
    vecstr.push_back("seis");


    dd->addOptions( vecstr );

*/

/*

    shared_ptr<kKnob> k = make_shared<kKnob>( );

    k->set(0.7f,0.3f,15,15);

    testview->addWidget(k);

    testview->arrangeWidgets();




    clock1 = make_shared<ClockWidget>( );

    clock1->applySettings(settings);
    clock1->setWidgetSettings(settings2);
    clock1->set( 0.3f, 0.1f, 40, 40 );
    ofAddListener(*clock1->events.lookup("event"),this,&testApp::tst);
    clock1->initialize();

    testview->addWidget(clock1);


    clock1->play();

    clock1->addEvent(0.4f,"hola");
    clock1->addEvent(0.7f,"adios");


    clock2 = make_shared<ClockWidget>( );

    clock2->applySettings(settings);
    clock2->setWidgetSettings(settings2);
    clock2->set( 0.6f, 0.5f, 40, 40 );
    ofAddListener(*clock2->events.lookup("event"),this,&testApp::tst);
    clock2->initialize();

    testview->addWidget(clock2);


    clock2->play();

    clock2->addEvent(0.4f,"hola2");
    clock2->addEvent(0.7f,"adios2");



    clock3 = make_shared<ClockWidget>( );

    clock3->applySettings(settings);
    clock3->setWidgetSettings(settings2);
    clock3->set( 0.6f, 0.7f, 40, 40 );
    ofAddListener(*clock3->events.lookup("event"),this,&testApp::tst);
    clock3->initialize();

    testview->addWidget(clock3);


    clock3->play();

    clock3->addEvent(0.5f,"hola3");
    clock3->addEvent(0.8f,"adios3");

    testview->arrangeWidgets();
*/







/*
    shared_ptr<kCircleButtonView> csv = make_shared<kCircleButtonView>();
    csv->applySettings(settings);
    csv->setWidgetSettings(settings2);
    csv->set( 0.6f, 0.1f, 60, 60 );
//    ofAddListener(*csv->events.lookup("btnClicked"),this,&testApp::tst);
    testview->addWidget(csv);

    vector<string>labels;

    for (int i=0; i<7; i++)
        labels.push_back(ofToString(i));


    csv->addButtons(labels);

    testview->arrangeWidgets();
*/
//    csv->iiinit();



/*

    shared_ptr<kCircleScrollView> csv = make_shared<kCircleScrollView>();
    csv->applySettings(settings);
    csv->setWidgetSettings(settings2);
    csv->set( 0.6f, 0.1f, 60, 60 );
//    ofAddListener(*csv->events.lookup("btnClicked"),this,&testApp::tst);
    testview->addWidget(csv);

    testview->arrangeWidgets();

    csv->iiinit();


    vw = make_shared<kField2D>( );
    vw -> set( 10, 10,600,250 );
    vw->applySettings(settings);
    vw->setWidgetSettings(settings2);
    vw->initialize();

//    vw->totalW = 1300;
//    vw->totalH = 1300;

//    vw->arrangeWidgets();

////
//            shared_ptr<kVectorHolder> vec = make_shared<kVectorHolder>( );
//            vec->set(0.7f,0.3f,0.3f,0.3f);
//            btn = make_shared<kCircleButton>( );
//            btn->set( ofRandomf(),ofRandomf(), 0.05f,0.05f );
//            vec->set(0.5f,0.5f,40,40);
//
//            vec->addWidget(btn);
//            vw->addWidget(vec);
//
//            vw->arrangeWidgets();
//
//            vec->initialize();
////
//
//            vec = make_shared<kVectorHolder>( );
//            vec->set(0.2f,0.8f,0.1f,0.1f);
////            shared_ptr<kCircleButton> btn = make_shared<kCircleButton>( );
////            btn->set( ofRandomf(),ofRandomf(), 0.1f,0.1f );
////            vec->set(0.5f,0.5f,40,40);
//
////            vec->addWidget(btn);
//            vw->addWidget(vec);
//
//            vw->arrangeWidgets();
//
//            vec->initialize();

        clip = make_shared<kClipShow>();
        clip -> setClip(clip1);
        clip->set( 0.25f, 0.25f, 0.1f, 0.1f);

        vw->addWidget( clip );

for (int i=0; i<10; i++)
{
    btn = make_shared<kCircleButton>( );
    btn->set( 0.75*ofRandomuf(), 0.75*ofRandomuf(), 0.05f, 0.05f);
    vw->addWidget(btn);
    btn->show();
}
*/


/*
    lib = make_shared<Library>( );
//    arc = make_shared<Archive>( );

    lib->applySettings(settings);
    lib->setWidgetSettings(settings2);
//    lib->addClip(clip1);
    lib->addMedia(clip2);
//    lib->addClip(clip3);
//
    shared_ptr<Category> cat=make_shared<Category>( );
    cat->setName("cat1");
    lib->addOntology(cat);
    cat.reset();

    cat=make_shared<Category>( );
    cat->setName("cat2");
    lib->addOntology(cat);
    cat.reset();

    cat=make_shared<Category>( );
    cat->setName("cat3");
    lib->addOntology(cat);
//    cat.reset();

    vector< shared_ptr < MediaHolder > > media;
    media.push_back(clip1);
    media.push_back(clip3);

    lib->setOntology(lib->getOntology("cat1"), clip1 );
    lib->setOntology(lib->getOntology("cat2"), clip2 );

    media.clear();
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(clip1);
    media.push_back(clip2);
    media.push_back(clip3);
    media.push_back(clip4);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);
    media.push_back(sample1);
    media.push_back(sample2);

    lib->setOntology(lib->getOntology("cat3"), media );

    lib->loadView();


*/


/*
//    db = make_shared<TestDB>( );
//    db->setInfo("db01","test",0);
//
//    db->addObj1("uno",200,300);
//    db->addObj2("dos",500,400);
//    db->addObj1("tres",300,640);
//    db->addObj2("cuatro",100,240);
//
//    db->setHierarchy(db->getObjects()[0],db->getObjects()[1]);
//    db->setHierarchy(db->getObjects()[0],db->getObjects()[2]);
//    db->setHierarchy(db->getObjects()[0],db->getObjects()[3]);
//
//
//    db->setRelated(db->getObjects()[2],db->getObjects()[3]);
//    db->setRelated(db->getObjects()[1],db->getObjects()[2]);
//
//    db->removeObject(db->getObject("cuatro"));
//
//    cout << db->getChildren(db->getObjects()[0]).size() << endl;
//    db->setHierarchy(db->getObjects()[1],db->getObjects()[0]);

//    cout << f << endl;



*/


}

void testApp::tst(widgetEvent & _event){
shared_ptr<Clock> c = dynamic_pointer_cast<Clock>(_event.sender);
cout << ofGetElapsedTimeMillis() << "  : "<<c->getEvent() << endl;

//cout << v->getCommand() << endl;

}

//float counter=0;

//--------------------------------------------------------------
void testApp::update(){

//	ofSoundUpdate();

}

//--------------------------------------------------------------
void testApp::draw(){
//
ofSetColor(255);
kinhoFont.drawString("KINHO", ofGetWidth()/2-100, 30 );
//kinhoFont.drawString(ofToString(ofGetFrameRate(),2), 30, 30 );

ofSetColor(142,32,222);
//ofDrawBitmapString(ofToString(ofGetFrameRate(),2),50,100);
////ofDrawBitmapString(ofToString(ofGetElapsedTimeMillis()%int(0.5f*1000)),10,60);






//    vector< shared_ptr < kWidget > > w;

//    w = vw->getWidgets();
//    cout << w.size() << endl;
//    for (int i=0; i<w.size(); i++)
//    { ofRect( w[i]->getX() , w[i]->getY() , w[i]->getWidth() , w[i]->getHeight() ); }



//
//
//vector<shared_ptr<Clip> > clips = lib->getClips();
//
//for (int i=0; i<clips.size(); i++)
//{
//	ofDrawBitmapString(clips[i]->getName(),10,50+20*i);
//}

//
//ofSetColor(142,32,222);
//ofNoFill();
//    vector<shared_ptr<StoreObject> > dbo = db->getObjects();
//    vector<shared_ptr<StoreObject> > c;
//
//    for (int i=0; i<dbo.size(); i++)
//    {
//        ofSetColor(150,55,100);
//
//        string str = dbo[i]->getName();
//        string type = dbo[i]->getType();
//    	float x = dbo[i]->getAttribute("xy","x")->getValue(0.0f);
//        float y = dbo[i]->getAttribute("xy","y")->getValue(0.0f);
//        if(type=="testobj1")
//            ofCircle(x,y,30);
//        if(type=="testobj2")
//            ofRect(x-15,y-15,30,30);
//        ofDrawBitmapString(str,x,y);
//        c = db->getChildren(dbo[i]);
//        ofSetColor(0,255,100);
//        for (int j=0; j<c.size(); j++)
//        {
//        	float x2 = c[j]->getAttribute("xy","x")->getValue(0.0f);
//            float y2 = c[j]->getAttribute("xy","y")->getValue(0.0f);
//        	ofLine(x,y,x2,y2);
//        }
//        c = db->getRelated(dbo[i]);
//        ofSetColor(255,0,100);
//        for (int j=0; j<c.size(); j++)
//        {
//        	float x2 = c[j]->getAttribute("xy","x")->getValue(0.0f);
//            float y2 = c[j]->getAttribute("xy","y")->getValue(0.0f);
//        	ofLine(x,y,x2,y2);
//        }
//    }
//
//

}
int ccounter = 0;
//--------------------------------------------------------------
void testApp::keyPressed(int key){
//    if(key=='a'){
//        clock1->hide();
//        clock2->hide();
//        clock3->hide();
//    }
//    if(key=='b'){
//        clock1->show();
//        clock2->show();
//        clock3->show();
//    }
    /*
    if(key=='d'){
        vw->removeWidget(clip);
    }
ccounter++;
    btn = make_shared<kCircleButton>( );
    btn->set( ofRandomuf(), ccounter*0.75f, 0.05f, 0.05f);
    vw->addWidget(btn);
    btn->setLabel("wdgt "+ofToString(ccounter));
    btn->show();

    vw->updateCanvas();
    vw->arrangeWidgets();

    */
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}







//--------------------------------------------------------------
void testApp::phraseComplete()
{
//synth.play();
cout << "fuckjye" << endl;
cout << ofGetElapsedTimeMillis()%100 << endl;

    // Play sounds here
    // This is called exactly at every four measures at 125bpm

}

//--------------------------------------------------------------
int testApp::calculateNoteDuration()
{

    // Translate tempo to milliseconds
    return (int)floor(60000.0000f / tempo);

}
