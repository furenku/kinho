
#pragma once
#ifndef functors_h
#define functors_h

#include "timeline.h"
#include "archive.h"
#include "scenes.h"
#include "outputs.h"





class DragLibraryItem: public Functor {

    public:
        DragLibraryItem( shared_ptr<Library> _library, shared_ptr<Archive> _archive);

        void execute();

        shared_ptr<Library> library; shared_ptr<Archive> archive;
};


class SetTimelineClip: public Functor {

    public:
        SetTimelineClip( shared_ptr<kThreadClipView> _clipView, shared_ptr<TimelineTrack> _timeline);
        void execute();

        shared_ptr<kThreadClipView> clipView; shared_ptr<TimelineTrack> timeline;
};


class AddMedia: public Functor {

    public:
        AddMedia( shared_ptr<Archive> _archive, shared_ptr<kThreadClipView> _selected);

        void execute();

        shared_ptr<kThreadClipView> selected; shared_ptr<Archive> archive;
};


class ConnectOntology: public Functor {

    public:
        ConnectOntology( shared_ptr<Archive> _archive,  shared_ptr<Library> _library);

        void execute();


        shared_ptr<Library> library; shared_ptr<Archive> archive;
};


class PlayClip: public Functor {

    public:
        PlayClip( shared_ptr<SceneBuilder> _scene,  shared_ptr<VideoOutput> _output );

        void execute();

        shared_ptr<SceneBuilder> scene;
        shared_ptr<VideoOutput> output;

};


class PlayTimelineClip: public Functor {

    public:
        PlayTimelineClip( shared_ptr<TimelineTrack> _timeline,  shared_ptr<VideoOutput> _output );

        void execute();

        shared_ptr<TimelineTrack> timeline;
        shared_ptr<VideoOutput> output;

};


class SelectOntology: public Functor {

    public:
        SelectOntology( shared_ptr< WordSelect > _wordSelect,  shared_ptr<GraphBrowser> _graphBrowser );

        void execute();

        shared_ptr<WordSelect> wordSelect;
        shared_ptr<GraphBrowser> graphBrowser;

};



class ClearOntology: public Functor {

    public:
        ClearOntology( shared_ptr< WordSelect > _wordSelect );

        void execute();

        shared_ptr<WordSelect> wordSelect;

};


#endif


//{ :


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

class SetDraggingClip: public Functor {

    public:
        SetDraggingClip( shared_ptr<SceneBuilder> _scene, shared_ptr<kThreadClipView> _clipView);

        void execute();


        shared_ptr<kThreadClipView> clipView; shared_ptr<SceneBuilder> scene;

};

class SetClipPosition: public Functor {

    public:
        SetClipPosition( shared_ptr<SceneBuilder> _scene, shared_ptr<VideoOutput> _output);
        void execute();

        shared_ptr<VideoOutput> output; shared_ptr<SceneBuilder> scene;

};


class EndClip: public Functor {

    public:
        EndClip( shared_ptr<SceneBuilder> _scene );

        void execute();

        shared_ptr<SceneBuilder> scene;

};



//
//
//class SetAlpha: public Functor {
//
//    public:
//        SetAlpha( shared_ptr< AlphaControl > _alpha,  shared_ptr<VideoOutput> _output );
//
//        void execute();
//
//        shared_ptr<AlphaControl> alpha;
//        shared_ptr<VideoOutput> output;
//
//};
//
//class VideoStop: public Functor {
//
//    public:
//        VideoStop( shared_ptr<VideoOutput> _output );
//        void execute();
//
//        shared_ptr<VideoOutput> output;
//
//};



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


/*
class OpenOntology: public Functor {

    public:
        OpenOntology( shared_ptr< WordSelect > _wordSelect, string _type, shared_ptr< LibraryManager > _lib, shared_ptr<kScrollClipView> _clipview ) {
            wordSelect = _wordSelect;
            lib = _lib;
            type = _type;
            clipview = _clipview;
        }

        void execute() {
            if(type=="cat"){

            }
            if(type=="tag"){

            }
        }

        shared_ptr<WordSelect> wordSelect;
        shared_ptr<LibraryManager> lib;

};

*/


//}
