

#pragma once

#ifndef controllers_h
#define controllers_h


#include <boost/algorithm/string.hpp>

//#pragma once

//#ifndef controllers_h
//#define controllers_h
#include "ontologies.h"
#include "ontologies.h"
#include "outputs.h"
#include "mainClasses.h"
#include "timeline.h"
#include "library.h"
#include "video.h"
#include "archive.h"
#include "functors.h"
#include "ofxXmlSettings.h"


class MainController: public Controller {
    public:
        MainController();

        void createSettings();

        vector<string> loadAllClips();

        void createModules();

        void loadXml();

        void makeLogins();

        void update();

        void makeClip( string _name );

        void loadXml(string _file);

        void loadSession();

        void makeEditor();

        void makeTimelines();

        void makeArchive();

        void makeOntologies();

        void makeLibrary();

        void makeClipView();

        void catSelected(widgetEvent & _event);

        void tagSelected(widgetEvent & _event);

        void clipClicked(widgetEvent & _event);

        void clipDragged(widgetEvent & _event);

        void makePlayLists();

        void makeVideoOutput();

        void makeSelected();

        void makeScene();

        void makeChooser();

        void chooseView(widgetEvent & _event);


bool xmlLoaded;


map< string,  shared_ptr < Clip > > videos;
vector< shared_ptr<Ontology> > onts;
shared_ptr<Category> tmpCat;
shared_ptr<Tag> tmpTag;

shared_ptr<TimelineView> timelines;
shared_ptr<TimelineTrack> timeline,timeline2;
shared_ptr<ClockManager> clockmngr;

shared_ptr<WordSelect> catSelect,tagSelect,objSelect,placeSelect,actorsSelect,actionsSelect;
shared_ptr<GraphBrowser> graphBrowser;

vector<string> words;

shared_ptr<VideoLoader> videoLoader;



        vector<shared_ptr<MediaHolder> > media;
//        shared_ptr<Editor>  editor;
        shared_ptr<Library> library;
        shared_ptr<LibraryManager> miniLibrary;
        shared_ptr<Archive> archive;
//        shared_ptr<SceneBuilder> scene;
//        vector< shared_ptr<PlayList> > playlists;


        shared_ptr<kRectButtonView> chooser;
        shared_ptr<kClipScrollView> selected;

        shared_ptr<VideoOutput> output;

        ofTrueTypeFont  font,font2,font3, kinhoFont;
        shared_ptr<Settings> settings,settings2;

        ofDirectory DIR;

        ofxXmlSettings XML;


        vector< shared_ptr<kScrollView> > scrollViews;
        shared_ptr<kClipScrollView> clipView ;
        shared_ptr<kSampleScrollView> sampleView;
        vector< shared_ptr<kClipScrollView> > clipScrollViews;
        vector< shared_ptr<kSampleScrollView> > sampleScrollViews;
        vector< shared_ptr<kRectView> > mediaViews;

        vector< shared_ptr < Clip > > lastClips;
        vector< shared_ptr < Sample > > lastSamples;
//        vector< shared_ptr < Text > > lastTexts;

        shared_ptr<Clip> clickedClip, draggingClip;

};



//#endif

#endif
