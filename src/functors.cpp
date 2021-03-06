
#include "functors.h"


        DragLibraryItem::DragLibraryItem( shared_ptr<Library> _library, shared_ptr<Archive> _archive) {
            library = _library; archive = _archive;
        }

        void DragLibraryItem::execute() {
//            if(archive->inside(archive->getX(),archive->getY())){
            float clickedX = archive->getMouseX() - archive->getX();
            float clickedY = archive->getMouseY() - archive->getY();

            float newX = (clickedX / archive->getWidth()) +  archive->getScrollPctX();
            float newY = (clickedY / archive->getHeight()) + archive->getScrollPctY();

            if( library->draggingClip  ) {
                archive->addClip( library->draggingClip, newX, newY );
                archive->arrangeWidgets();
            }

            if( library->draggingOntology != ""  ) {
                string ontname = library->draggingOntology;
                archive->addOntology( library->getOntology( ontname ), newX, newY );
                archive->arrangeWidgets();
            }

            library->draggingOntology="";
            library->draggingClip.reset();

//            }

        }




        SetTimelineClip::SetTimelineClip( shared_ptr<kThreadClipView> _clipView, shared_ptr<TimelineTrack> _timeline) {
            clipView = _clipView; timeline = _timeline;
        }

        void SetTimelineClip::execute() {
            timeline->setNextClip(clipView->clickedClip);
        }





        AddMedia::AddMedia( shared_ptr<Archive> _archive, shared_ptr<kThreadClipView> _selected) {
            selected = _selected; archive = _archive;
        }

        void AddMedia::execute() {
            cout << "ADD" << endl;
            selected->addClip( archive->getNextClip() );
            selected->arrangeWidgets();
        }




        ConnectOntology::ConnectOntology( shared_ptr<Archive> _archive,  shared_ptr<Library> _library) {
            library = _library; archive = _archive;
        }

        void ConnectOntology::execute() {
cout << "connnnn" << endl;
            if(archive->connectedOntology && archive->connectedClip ){
                library->setOntology(
                    archive->connectedOntology->getOntology()->getName(),
                    archive->connectedClip->getClip()
                );

                cout <<"coonnect:"<< archive->connectedOntology->getOntology()->getName() << endl;
                cout <<"coonnect to:"<< archive->connectedClip->getClip()->getName() << endl;
            }
        }




        PlayClip::PlayClip( shared_ptr<SceneBuilder> _scene,  shared_ptr<VideoOutput> _output ) {
            output = _output;
            scene = _scene;
        }

        void PlayClip::execute() {
            output->changeClip ( scene->getCurrentClip()->getFilename() );
            output->play();
        }





        AddTimelineMarker::AddTimelineMarker( shared_ptr<TimelineTrack> _timeline,  shared_ptr<SceneBuilder> _scene ) {
            scene = _scene;
            timeline = _timeline;
        }

        void AddTimelineMarker::execute() {
            float position = scene->nextClip->getClip()->getDuration();
            timeline->addMarker( position, scene->nextClip->getClip()->getName() );
            //getNextPosition( xToTime(mouse.x), draggingEvent->getDuration() ), draggingEvent->getDuration() );
            cout<<"---Add Marker! dur:"<<position<<endl;
//            timeline->addMarker( position );
        }







        PlayTimelineClip::PlayTimelineClip( shared_ptr<TimelineTrack> _timeline,  shared_ptr<VideoOutput> _output ) {
            output = _output;
            timeline = _timeline;
        }

        void PlayTimelineClip::execute() {
            output->changeClip ( timeline->getNextPlayClip()->getFilename() );
            output->play();
        }





        SelectOntology::SelectOntology( shared_ptr< WordSelect > _wordSelect,  shared_ptr<GraphBrowser> _graphBrowser ) {
            graphBrowser = _graphBrowser;
            wordSelect = _wordSelect;
        }

        void SelectOntology::execute() {
            graphBrowser->browse( wordSelect->getSelected());
        }






        ClearOntology::ClearOntology( shared_ptr< WordSelect > _wordSelect ) {
            wordSelect = _wordSelect;
        }

        void ClearOntology::execute() {

            vector< shared_ptr < kWidget > > widgets = wordSelect->getWidgets();

            for (int j=0; j<widgets.size(); j++)
            {
                widgets[j]->disable();
//                ofRemoveListener( *widgets[j]->events.lookup("press"),this,&kBrowseArchive::btnClicked);
            }
    //                graphBrowser[i]->clearWidgets();
//                graphBrowser[i]->clearSamples();
                wordSelect->clearWidgets();
//                removeWidget(clipScrollViews[i]);
//                clipScrollViews[i].reset();
        }




/*

        OpenOntology::OpenOntology( shared_ptr< WordSelect > _wordSelect, string _type, shared_ptr< LibraryManager > _lib, shared_ptr<kScrollClipView> _clipview ) {
            wordSelect = _wordSelect;
            lib = _lib;
            type = _type;
            clipview = _clipview;
        }

        void OpenOntology::execute() {
            if(type=="cat"){

            }
            if(type=="tag"){

            }
        }

*/



    SetDraggingClip::SetDraggingClip( shared_ptr<SceneBuilder> _scene, shared_ptr<kThreadClipView> _clipView) {
        clipView = _clipView; scene = _scene;
    }

    void SetDraggingClip::execute() {
        if(clipView->draggingClip) {
            scene->setNewDraggingClip( clipView->getDraggingClip() );
        }
    }


    SetClipPosition::SetClipPosition( shared_ptr<SceneBuilder> _scene, shared_ptr<VideoOutput> _output) {
        output = _output; scene = _scene;
    }

    void SetClipPosition::execute() {
        scene->savePosition( output->getPosition() );
    }

    EndClip::EndClip( shared_ptr<SceneBuilder> _scene ) {
        scene = _scene;
    }

    void EndClip::execute() {
        cout << "mediaEND" << endl;
        scene->mediaEnd();
    }
//
//    SetAlpha::SetAlpha( shared_ptr< AlphaControl > _alpha,  shared_ptr<VideoOutput> _output ) {
//        output = _output;
//        alpha = _alpha;
//    }
//
//    void SetAlpha::execute() {
//        output->setAlpha(alpha->getAlpha());
//    }
//
//    VideoStop::VideoStop( shared_ptr<VideoOutput> _output ) {
//        output = _output;
//    }
//
//    void VideoStop::execute() {
//        output->stop();
//    }
