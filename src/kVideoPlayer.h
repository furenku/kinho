#ifndef KVIDEOPLAYER_H
#define KVIDEOPLAYER_H

#include "goThreadedVideo2.h"

//#pragma once

class kVideoPlayer {

    public:

    kVideoPlayer()  {
        setup();
    }


    //{ variables:

    string movieName;

    int preload;

    int loadTime;

    int readyTimes;

    bool ready;
    bool    holdOld;
    int     holdCount;

    int category;
    float alpha,r,g,b;
    vector<goThreadedVideo*> videos;

    bool playing;

    goThreadedVideo * video;
//    goThreadedVideo * nextVideo;
//    goThreadedVideo * lastVideo;

    float volume;

    float nextPosition;

    int brightness;
    float speed;

    //}


    //--------------------------------------------------------------
    void setup(){
//        current = 0; next = 1;
        speed=1.0f;
        volume = 1.0f;
        alpha = 1.0f;
        category = 0;
        brightness=255;


        video = new goThreadedVideo();
        video->setup();


        playing  = false;

    }


    void setSpeed(float pct) {
        video->speed = pct;
        speed = pct;
    }

    //--------------------------------------------------------------
    void loadMovie(string _movie){
cout << "load : "<<_movie << endl;

        video->nextPosition=nextPosition;
        video->loadMovie( _movie );

        ofAddListener(video->success, this, &kVideoPlayer::loaded); // this fires when the video is ACTUALLY loaded and ready
        ofAddListener(video->error, this, &kVideoPlayer::error); // this fires if there's a problem loading
    }

    void loaded(string & path){

//        next=current;
//        current++; current%=2;
//
//        video = NULL;
//        video = video;
//
//        if(nextPosition<0.98f)
//            video->setPosition( nextPosition );

//        float ratio = video->getWidth()/video->getHeight();


            video -> setVolume( volume );

//        video -> setPaused(false);
//        video -> setPaused(true);


        playing=true;

        ofRemoveListener(video->success, this, &kVideoPlayer::loaded);
        ofRemoveListener(video->error, this, &kVideoPlayer::error);

//        swap( video, nextVideo );
    }

    void error(goVideoError & err){
        cout << "error loading!" << endl;
        ofRemoveListener(video->success, this, &kVideoPlayer::loaded);
        ofRemoveListener(video->error, this, &kVideoPlayer::error);

//        swap( video, nextVideo );
    }


    //---------------------------------------------------------------

    void close() {

            video -> close();

        playing = false;
    }

    //--------------------------------------------------------------
    void setPosition( float pct ) {
        nextPosition = pct;
    }

    void setAlpha( float pct ) {
        alpha  = pct;
    }


    //--------------------------------------------------------------
    void update(){


            video -> update();

    }



    void setVolume(float pct){

        	video -> setVolume( pct );
        volume = pct;
    }


    void setBrightness( float _val ){
        brightness = _val;
    }


    //--------------------------------------------------------------
    void draw( int _x, int _y, int _w, int _h ){
        if(playing){
//            ofEnableAlphaBlending();
            ofSetColor(255,255,255,brightness);

            video->draw(_x,_y,_w,_h);

            ofDisableAlphaBlending();

        }
        ofSetColor(30);

        ofDrawBitmapString("volume:"+ofToString(volume,1),_x,_y-20);
        ofDrawBitmapString("speed:"+ofToString(speed,1),_x+90,_y-20);

    }

    void stop() {

        video -> stop();
        playing = false;
    }

    void play() {
        video-> play();
        playing = true;
    }


    //---------------------------------------------------------------
    float getPosition(){
        float pct;
        pct = video->getPosition();
        return pct;
    }

    //---------------------------------------------------------------
    int getWidth(){
        int width;
        width = video->getWidth();
        return width;
    }

    //---------------------------------------------------------------
    int getHeight(){
        int height;
        height = video->getHeight();
        return height;
    }

    bool getIsMovieDone() { return video->getIsMovieDone(); }

};


#endif
