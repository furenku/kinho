
#include "ofMain.h"
#include "ofMain.h"

#ifndef video_h
#define video_h

class VideoLoader {
    public:
        VideoLoader(){}

    //funcs
        void setFilename(string _filename) {
            filename = _filename;
        }

        void loadData() {
            video.loadMovie(filename);
            duration = video.getDuration();
            width = video.getWidth();
            height = video.getHeight();
            video.close();
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
