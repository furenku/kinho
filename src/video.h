

#ifndef video_h
#define video_h

#include "ofMain.h"


class VideoLoader {
    public:
        VideoLoader(){}

    //funcs
        void setFilename(string _filename) {
            filename = _filename;
        }

        void loadData() {
//            video.play();

            cout << "1" << endl;
            video.loadMovie(filename);
            cout << "2" << endl;
            duration = video.getDuration();

            video.setPaused(true);
//            video.idleMovie();

                        cout << "duration"<<duration << endl;
            cout << "3" << endl;
            width = video.getWidth();
            cout << "4" << endl;
            height = video.getHeight();
            cout << "5" << endl;
            video.close();
        }

        void update(){

        }

        float getDuration(){
            return duration;
        }

        float getWidth() {
            return width;
        }

        float getHeight() {
            return height;
        }

    protected:
    //atts
        ofVideoPlayer video;
        string filename;
        float duration, width, height;


};




#endif
