#pragma once

#ifndef outputs_h
#define outputs_h

#include "guiVideoObjects.h"
#include "mediaStorage.h"
#include "kVideoPlayer.h"

class Output{
    public:
        Output(){}

};


class AudioOutput: public Output {
    public:
        AudioOutput(){}


    protected:

        shared_ptr<kVideoPlayer> video;

};



class VideoOutput: virtual public kWidget {
    public:
        VideoOutput();


        void createEvents();

        int blendCount;
        bool videoTriggered;
        string drawStr;
//        ofTexture texture;
//        ofxBlurShader blur;

        bool playing;

        void play();

        void stop();

        void setupVideo();

        void update(ofEventArgs & args);

        unsigned char * createPixels();

        void addRect( float _x, float _y, float _w, float _h);

        void addRect( shared_ptr<ofRectangle> _rect);

        void draw(ofEventArgs & args);

        void changeClip( string _filename );

        void setVolume(float pct);


        void setAlpha(float pct);


        void fade(int _time, int _fadeVal);

        void setFilename ( string _filename );

        void setSpeed(float pct);


        float getPosition();


        void setBrightness( float _val );

//        vector <GLenum> blendSrc,blendDst;
        vector< shared_ptr<ofRectangle> > canvases;

        float volume;
        float alpha;

        string filename;
        int counter;


        int brightness;
        int targetBrightness;

        bool fading;

        long fadeTime;
        int fadeMs;

        int fadeStep;

        float speed;

        unsigned char * newPix;
        unsigned char * pixels;

        shared_ptr<kVideoPlayer> video;

};

class VideoPlayer{};

class Outputs{

    public:
        Outputs() {}

        void addVideoOutput( vector< shared_ptr < ofRectangle > >  _rects );

        void addSampleOutput();

        vector< shared_ptr<VideoOutput> > videoOutputs;
        vector< shared_ptr<AudioOutput> > audioOutputs;


        shared_ptr<VideoOutput> & getVideoOutput( int _index );

};



class PlayList: public kScrollView, public kDragSink {
    public:
        PlayList();



        void changeVideo( widgetEvent & _event);

        void addMedia( shared_ptr < MediaHolder > _media );

        void addClip ( shared_ptr < Clip > _clip );

        vector< shared_ptr < MediaHolder > > media;
        shared_ptr < MediaHolder > currentMedia;
        int currentIndex;

        shared_ptr<MediaHolder> getNextMedia();


        shared_ptr< Clip > getNextClip();

        shared_ptr< VideoOutput > output;
        vector< shared_ptr < kClipShow > > clips;
};



//#endif

#endif
