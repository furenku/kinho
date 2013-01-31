//#pragma once

#ifndef archive_h
#define archive_h

#include "library.h"
#include "storage.h"
#include "guiVideoObjects.h"

//#include "library.h"

#include "ontologies.h"






class Node: public StoreObject{
    public:
        Node();

        void setX( int _x );
        void setY( int _y);
        float getX();
        float getY();

    protected:

        int x, y;

};


class Field2D: public Storage {

    public:
        Field2D(){}


        shared_ptr<Node> getNode(string _name);


    protected:

        vector< shared_ptr < Node > > nodes;


};

class OntDisplay{};




class ArchiveWidget: public StoreObject, virtual public kCircleView, virtual public kDragObject {
    public:

        ArchiveWidget();
    //f

        void setupVars();

        void initialize();

        void createEvents();

        void draw(ofEventArgs & args);

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

        void loadOntologies( vector<string> _ontNames );

        void loadMedia( vector < shared_ptr<MediaHolder> > _media );
        //interactividad

        //callbacks

        virtual void addContent();

        void btnClicked(widgetEvent & _event);


        string getCommand();

        void ontologyClicked(widgetEvent & _event);

        void ontologyDragged(widgetEvent & _event);

        void mediaClicked(widgetEvent & _event);

        void mediaDragged(widgetEvent & _event);

        // drag

        string getDraggingOntology();

        shared_ptr<MediaWidget> getDraggingMedia();

        void mouseMoved( ofMouseEventArgs & mouse );

        void mouseDragged( ofMouseEventArgs & mouse );

        void mouseReleased( ofMouseEventArgs & mouse);

    //atts
//    protected:
        shared_ptr<kWidget> mainWidget;
        shared_ptr<MediaWidget> draggingMedia;
        string draggingOntology;

        shared_ptr<kButtonView> currentView;
        shared_ptr<kCircleButtonView> btnView;
        shared_ptr<kMediaScrollView> scrollView;
        string command;


};


class ArchiveMedia: public ArchiveWidget {

     public:

        ArchiveMedia();
    //f

        void setupVars();


        void setMedia( shared_ptr<MediaHolder> _media ) ;

        //atts
        shared_ptr<MediaHolder> media;


};




class ArchiveClip: public ArchiveWidget {

     public:

        ArchiveClip();

        void createEvents();

    //f

        void initialize();

        void setupVars();


        void setClip( shared_ptr<Clip> _clip );

        shared_ptr<Clip> getClip();

        void mediaClicked(widgetEvent & _event);


        //atts
        shared_ptr<Clip> clip;
        shared_ptr<kClip> clipView;

};



class ArchiveOntology: public ArchiveWidget {

     public:

        ArchiveOntology();


        void createEvents();

    //f

        void initialize();

        void setupVars();

        void setOntology( shared_ptr<Ontology> _ontology);


        shared_ptr<Ontology> & getOntology();

        void ontClicked(widgetEvent & _event);

        //atts
        shared_ptr<Ontology> ontology;


};







class Archive: public LibraryManager, virtual public kField2D, virtual public kDragSink {
    public:
        Archive();
    //funcs
        //logica
            void createEvents();

            void loadFile( string _filename );

            shared_ptr<ArchiveWidget>   getNextWidget();
            shared_ptr<ArchiveMedia>    getNextMedia();
            shared_ptr<Clip>            getNextClip();
            shared_ptr<ArchiveOntology> getNextOntology();

            void draw(ofEventArgs & args);

            void setLibrary( shared_ptr<Library> _library );
        //interactivity
            //{callbacks

            void mainBtnClicked( widgetEvent & _event );

            void ontologyMainClicked( widgetEvent & _event );

            void btnClicked( widgetEvent & _event );

            void mediaClicked( widgetEvent & _event );

            void mediaDragged( widgetEvent & _event );

            void ontologyClicked( widgetEvent & _event );

            void ontologyDragged( widgetEvent & _event );

            void widgetDragged( widgetEvent & _event );



            //}


            //get drag objects
                string getDraggingOntology();

                shared_ptr< MediaWidget > getDraggingMedia();

            //{mouse

            void mouseReleased(ofMouseEventArgs & mouse);

            void mouseMoved(ofMouseEventArgs & mouse);

            void mouseDragged(ofMouseEventArgs & mouse);


//                    updateConnections()

            //}

        //add
        void addOntology( shared_ptr<Ontology> _ont, float _x, float _y );

        void addOntology( string _ontName, float _x, float _y );

        void addListeners( shared_ptr<ArchiveWidget> _w );

        void addClip( shared_ptr<Clip> _clip, float _x, float _y );

        void addSample( shared_ptr<Sample> _sample, float _x, float _y );

        //connections

        void connect(shared_ptr<ArchiveWidget> _media1, shared_ptr<ArchiveWidget> _media2);

        void connect(shared_ptr<ArchiveMedia> _media1, shared_ptr<ArchiveMedia> _media2);

        void connect(shared_ptr<ArchiveMedia> _media, shared_ptr<ArchiveOntology> _ont);

        void connect(shared_ptr<ArchiveOntology> _ont , shared_ptr<ArchiveMedia> _media);

        void connect(shared_ptr<ArchiveOntology> _ont1 , shared_ptr<ArchiveOntology> _ont2 );

        void createConnection(shared_ptr<ArchiveWidget> _w1, shared_ptr<ArchiveWidget> _w2);


        //disconnect

        void disconnect( shared_ptr<ArchiveWidget> _w);

        void disconnect( widgetEvent & _event );

        void disconnect(shared_ptr<ArchiveMedia> _media1, shared_ptr<ArchiveMedia> _media2);

        void disconnect(shared_ptr<ArchiveOntology> _ont , shared_ptr<ArchiveMedia> _media);

        void disconnect(shared_ptr<ArchiveOntology> _ont1 , shared_ptr<ArchiveOntology> _ont2 );

        void updateConnections();

        vector< shared_ptr < ArchiveWidget > > getWidgets();

        vector< shared_ptr < ArchiveOntology > > & getOntologyWidgets();

        vector< shared_ptr < ArchiveMedia > > & getMediaWidgets();

    //atts
//        vector< shared_ptr < ArchiveOntology > > ontologyWidgets;
//        vector< shared_ptr < ArchiveMedia > > mediaWidgets;
//        vector< shared_ptr < ArchiveWidget > > archiveWidgets;


        shared_ptr<ArchiveMedia> nextMedia, connectingMedia, disconnectingMedia;
        shared_ptr<ArchiveClip> connectingClip, connectedClip;
        shared_ptr<MediaWidget> draggingMedia;
        shared_ptr<ArchiveWidget> nextWidget, connectingWidget;
        shared_ptr<ArchiveOntology> nextOntology, connectingOntology, connectedOntology, disconnectingOntology;
        string draggingOntology;
        shared_ptr<Library> library;
        shared_ptr<Category> connectedCategory;

        vector < pair< shared_ptr<ArchiveWidget>, shared_ptr<ArchiveWidget> > > connections;

        vector< shared_ptr < kCircleButton > > connectionWidgets;

        shared_ptr<Clip> nextClip;

        bool connecting;



//                void removeObject( shared_ptr<ArchiveWidget>  _w) {
//                    removeObject(_w);
//                    removeWidget(_w);
//                }

};





#endif
