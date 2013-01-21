
#pragma once


//#include "ontologies.h"
#include "mainClasses.h"
#include "baseGUIObjects.h"
#include "guiObjects.h"
#include "guiVideoObjects.h"
#include "views.h"


#ifndef timeline_h
#define timeline_h


    class ClockManager {
        public:
            ClockManager(){
                lastMs = 0;

                // Set up clock
                tempo = 6000.0f;
                clock.ticksPerBar = 1;
                clock.start(this);


            }

            int lastMs;

            //--------------------------------------------------------------
            void barDone() {
                cout << ofGetElapsedTimeMillis() - lastMs << endl;
                lastMs = ofGetElapsedTimeMillis();
            }

            //--------------------------------------------------------------
            int calculateTickDuration()
            {
                // Translate tempo to milliseconds
                return (int)floor(60000.0000f / tempo);
            }


            private:

            threadedClock clock;
            float tempo;
    };


class Timeline: public DBManager {

    public:
        Timeline(){
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
                //media
        void addMedia(shared_ptr<MediaHolder> _media);
        void removeMedia(shared_ptr<MediaHolder> _media);

        //ontology
        void addOntology(shared_ptr<Ontology> _ont);
        void removeOntology(shared_ptr<Ontology> _ont);



        void setClock(){}



//        //get
//        shared_ptr<MediaHolder> getMedia(string _name);
//        vector< shared_ptr<MediaHolder> > & getMedia();
//        vector< shared_ptr<MediaHolder> > getMedia(shared_ptr<Ontology>);
//
//        shared_ptr<Clip> getClip(string _name);
//        vector< shared_ptr<Clip> > & getClips();
//        vector< shared_ptr<Clip> > getClips(shared_ptr<Ontology>);
//
//        shared_ptr<Sample> getSample(string _name);
//        vector< shared_ptr<Sample> > getSamples();
//        vector< shared_ptr<Sample> > getSamples(shared_ptr<Ontology>);
//
//        shared_ptr<Ontology> getOntology( shared_ptr<MediaHolder> );
//        shared_ptr<Ontology> getOntology( string name );
//        shared_ptr<Ontology> getOntology(int id);
//
//        vector< shared_ptr<Ontology> >  getOntologies(shared_ptr<MediaHolder>);
//        vector< shared_ptr<Ontology> >  getOntologies(string _type);
//        vector< shared_ptr<Ontology> >  getOntologies();



    protected:
//        vector< shared_ptr< MediaHolder > > media;
//        vector< shared_ptr< Clip > > clips;
//        vector< shared_ptr< Sample > > samples;
////        vector< shared_ptr< Text > > texts;
//
//        vector< shared_ptr< Tag > > tags;
//        vector< shared_ptr< Category> > categories;
//        vector< shared_ptr< OntologyObject > > ontObjects;
//        vector< shared_ptr< Place > > places;
//        vector< shared_ptr< Action> > actions;
//        vector< shared_ptr< Web> > webs;

};


#endif
