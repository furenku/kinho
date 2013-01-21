#pragma once
#ifndef functors_h
#define functors_h

//
//
//class ChangeVideo: public Functor(){
//    public:
//        ChangeVideo( shared_ptr<PlayLists> _playlists, shared_ptr<Outputs> _outputs) {
//            playlists = _playlists;   outputs = _outputs;
//        }
//
//        void execute() {
//            outputs->
//        }
//
//        shared_ptr<PlayLists> playlists;
//        shared_ptr<Outputs> outputs;
//
//
//};

class DragLibraryItem: public Functor {

    public:
        DragLibraryItem( shared_ptr<Library> _library, shared_ptr<Archive> _archive) {
            library = _library; archive = _archive;
        }

        void execute() {
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


        shared_ptr<Library> library; shared_ptr<Archive> archive;
};


class AddMedia: public Functor {

    public:
        AddMedia( shared_ptr<Archive> _archive, shared_ptr<kClipScrollView> _selected) {
            selected = _selected; archive = _archive;
        }

        void execute() {
            cout << "ADD" << endl;
            selected->addClip( archive->getNextClip() );
            selected->arrangeWidgets();
        }


        shared_ptr<kClipScrollView> selected; shared_ptr<Archive> archive;
};




class ConnectOntology: public Functor {

    public:
        ConnectOntology( shared_ptr<Archive> _archive,  shared_ptr<Library> _library) {
            library = _library; archive = _archive;
        }

        void execute() {
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


        shared_ptr<Library> library; shared_ptr<Archive> archive;
};


class SetDraggingClip: public Functor {

    public:
        SetDraggingClip( shared_ptr<SceneBuilder> _scene, shared_ptr<kClipScrollView> _selected) {
            selected = _selected; scene = _scene;
        }

        void execute() {
            if(selected->draggingClip) {
                scene->setDraggingClip( selected->draggingClip );
            }
        }

        shared_ptr<kClipScrollView> selected; shared_ptr<SceneBuilder> scene;

};


class SetClipPosition: public Functor {

    public:
        SetClipPosition( shared_ptr<SceneBuilder> _scene, shared_ptr<VideoOutput> _output) {
            output = _output; scene = _scene;
        }

        void execute() {
            scene->savePosition( output->getPosition() );
        }

        shared_ptr<VideoOutput> output; shared_ptr<SceneBuilder> scene;

};


class EndClip: public Functor {

    public:
        EndClip( shared_ptr<SceneBuilder> _scene ) {
            scene = _scene;
        }

        void execute() {
            scene->mediaEnd();
        }

        shared_ptr<SceneBuilder> scene;

};



class PlayClip: public Functor {

    public:
        PlayClip( shared_ptr<SceneBuilder> _scene,  shared_ptr<VideoOutput> _output ) {
            output = _output;
            scene = _scene;
        }

        void execute() {
            output->changeClip ( scene->getCurrentClip()->getFilename() );
            output->play();
        }

        shared_ptr<SceneBuilder> scene;
        shared_ptr<VideoOutput> output;

};




class SetAlpha: public Functor {

    public:
        SetAlpha( shared_ptr< AlphaControl > _alpha,  shared_ptr<VideoOutput> _output ) {
            output = _output;
            alpha = _alpha;
        }

        void execute() {
            output->setAlpha(alpha->getAlpha());
        }

        shared_ptr<AlphaControl> alpha;
        shared_ptr<VideoOutput> output;

};


class VideoStop: public Functor {

    public:
        VideoStop( shared_ptr<VideoOutput> _output ) {
            output = _output;
        }

        void execute() {
            output->stop();
        }

        shared_ptr<VideoOutput> output;

};
/*
vector<string> sortAlpha(vector<string> sortThis)
{
     int swap;
     string temp;

     do
     {
         swap = 0;
         for (int count = 0; count < sortThis.size() - 1; count++)
         {
             if (sortThis.at(count) > sortThis.at(count + 1))
             {
                   temp = sortThis.at(count);
                   sortThis.at(count) = sortThis.at(count + 1);
                   sortThis.at(count + 1) = temp;
                   swap = 1;
             }
         }

     }while (swap != 0);

     return sortThis;
}
*/




#endif;
