
#pragma once


#include "ontologies.h"
#include "mainClasses.h"
#include "baseGUIObjects.h"
#include "guiObjects.h"
#include "guiVideoObjects.h"
#include "views.h"


#ifndef library_h
#define library_h



class LibraryManager: public DBManager {

    public:
        LibraryManager(){
            init();
        }

        void init(){
//            shared_ptr<Ontology> ont = make_shared<Ontology>();
//            ont->setName("uncategorized");
//            addOntology(ont);
        }
        //funcs
            //API
            //add
                //clip
        void addMedia(shared_ptr<MediaHolder> _media);
        void addMedia(shared_ptr<MediaHolder> _media, shared_ptr<Ontology> _ont);
        void removeMedia(shared_ptr<MediaHolder> _media);
                //ontology
        void addOntology(shared_ptr<Ontology> _ont);

        void removeOntology(shared_ptr<Ontology> _ont);



        void loadMedia();
        void loadOntologies();
        void setOntology(shared_ptr<Ontology> _ont, shared_ptr<MediaHolder> _obj);
        void setOntology(string _ontname, shared_ptr<MediaHolder> _obj);
        void setOntology(shared_ptr<Ontology> _ont, vector< shared_ptr<MediaHolder> > _objs);
        void desetOntology(shared_ptr<Ontology> _ont, shared_ptr<MediaHolder> _obj);
        void desetOntology(shared_ptr<Ontology> _ont, vector< shared_ptr<MediaHolder> > _objs);


        //get
        shared_ptr<MediaHolder> getMedia(string _name);
        vector< shared_ptr<MediaHolder> > & getMedia();
        vector< shared_ptr<MediaHolder> > getMedia(shared_ptr<Ontology>);

        shared_ptr<Clip> getClip(string _name);
        vector< shared_ptr<Clip> > & getClips();
        vector< shared_ptr<Clip> > getClips(shared_ptr<Ontology>);

        shared_ptr<Sample> getSample(string _name);
        vector< shared_ptr<Sample> > getSamples();
        vector< shared_ptr<Sample> > getSamples(shared_ptr<Ontology>);

        shared_ptr<Ontology> getOntology( shared_ptr<MediaHolder> );
        shared_ptr<Ontology> getOntology( string name );
        shared_ptr<Ontology> getOntology(int id);

        vector< shared_ptr<Ontology> >  getOntologies(shared_ptr<MediaHolder>);
        vector< shared_ptr<Ontology> >  getOntologies(string _type);
        vector< shared_ptr<Ontology> >  getOntologies();
        vector< shared_ptr<Ontology> >  getChildOntologies(shared_ptr<Ontology>);



    protected:
        vector< shared_ptr< MediaHolder > > media;
        vector< shared_ptr< Clip > > clips;
        vector< shared_ptr< Sample > > samples;
//        vector< shared_ptr< Text > > texts;

        vector< shared_ptr< Tag > > tags;
        vector< shared_ptr< Category> > categories;
        vector< shared_ptr< OntologyObject > > ontObjects;
        vector< shared_ptr< Place > > places;
        vector< shared_ptr< Action> > actions;
        vector< shared_ptr< Web> > webs;

};



class Library: public LibraryManager, virtual public kView{
    public:
        Library(){
//            manager = make_shared<LibraryManager>();
            shared_ptr<Category> cat = make_shared<Category>( );
            cat->setName("uncat");
            addOntology(cat);
//            for (int i = 0; i<10; i++ ) {
//                shared_ptr<Clip> clip = make_shared<Clip>();
//                clip->setInfo("clip"+ofToString(i),"clip",0);
//                addClip(clip);
//            }

//            cout<<manager->getOntology("uncat")->getType()<<endl;
//            setOntology(getOntology("uncat"),getMedia());

            initView();
        }

        shared_ptr<kBrowseArchive> getView();

        void initView();

        void loadView();




        //callback:
        void btnClicked( widgetEvent & _event );
        void btnDragged( widgetEvent & _event );

        void clipClicked( widgetEvent & _event );
        void clipDragged( widgetEvent & _event );

        void setClips();

        shared_ptr<MediaHolder> getDraggingMedia();
        shared_ptr<Clip> getDraggingClip();
        string getDraggingOntology();


        void mouseReleased(ofMouseEventArgs & mouse);

//    protected:

        shared_ptr<kBrowseArchive> view;

        string draggingOntology;
        shared_ptr<Clip> draggingClip, nextClip;
        shared_ptr<MediaHolder> draggingMedia, nextMedia;

};














class WordSelect:public kScrollView{
    public:
        WordSelect();
        ~WordSelect();

        void initialize();

        void btnClicked(widgetEvent & _event);

        void makeButton(string _str);

        void clear();

        vector<string> & getSelected();

    /*
        toggleButton press ->p

    */


    protected:
        vector<string> selectedStrings;

};



class GraphBrowser{
    public: GraphBrowser();

    void browse( vector<string> & _selectedStrings );

};





#endif
