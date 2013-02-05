#pragma once

#include "ofMain.h"
#include "storage.h"
#include "general.h"
#include "GraphUtils.h"

#ifndef rawvideo_h
#define rawvideo_h




class RawMedia: public StoreObject{
    public:
        RawMedia(){
            init();
        }

        void init() {
            setName("rawmedia");
            setType("raw_media");
            setFilename("");
            setDuration(5);
        }
        //funcs
        //set
            virtual void setFilename(string _filename) {
                filename = _filename;
            }
            virtual void setDuration(float _dur){ duration=_dur;}

        //get
            string getFilename() { return filename; }
            float getDuration() { return duration; }


    protected:
        string filename;
        float duration;

};


class RawVideo: public RawMedia{
    public:
        RawVideo(){
            init();
        }

        void init() {
            RawMedia::init();
            setType("raw_video");
            setAspectRatio(1.33f);
            setWidth(30);
            setHeight(30/1.77f);
        }
        //funcs
        //set
            void setWidth(float _w){ width = _w; }
            void setHeight(float _h){ height = _h; }
            void setAspectRatio(float _r){ aspectRatio=_r;}

        //get
            float getWidth() { return width; }

            float getHeight() { return height; }
            float getAspectRatio() {
                float r = getWidth()/getHeight();
                return r;
            }
            string getResolution() {
                resolution = ofToString(getWidth())+"x"+ofToString(getHeight());
                return resolution;
            }


    protected:

        string resolution;

        float duration;
        float aspectRatio;
        float width;
        float height;


};

class RawAudio: public RawMedia{
    public:
        RawAudio(){
            init();
        }

        void init() {
            RawMedia::init();
            setType("raw_audio");
            setSampleRate(44100);
        }
        //funcs
        //set
            void setSampleRate(float _r){ sampleRate =_r;}

        //get
            float getSampleRate() {
                return sampleRate;
            }


    protected:
        float sampleRate;

};


class Marker: public StoreObject{
    public:
        Marker(){}

        void init(){
            setName("marker");
            setType("marker");
            setDescription("...");
            setPosition(0.0f);
            setLength(0.0f);
        }

        //atts
        //funcs
        //set
        void setDescription(string _desc){ description = _desc; }
//        void setColor(ofColor _color);
        void setPosition(float _pos) { position = _pos; }
        void setLength(float _length) { length = _length; }
        //get
        string getDescription() { return description; }
//        shared_ptr<ofColor> getColor();
        float getPosition() { return position; }
        float getLength() { return length; }

    protected:
        string description;
//        shared_ptr<ofColor> color;
        float position;
        float length;

};

class Param: public StoreObject{
    public:
        Param(){}
        void setValue(float _value){ value=_value; }
        float getValue(){ return value; }

    protected:

        float value;
};


class MediaHolder: public StoreObject, public GraphNode {
    public:
        MediaHolder(){
            init();
        }

        void init() {
            setName("default");
            setType("mediaholder");
            setDescription("...");


            addMarker("inicio");
            addMarker("final",1.0f);

        }


        void createAttributes(){
            addAttribute("author",getAuthor());
            addAttribute("description",getDescription());
            addAttribute("date",getDate());
            addAttribute("audioTrack",getAudioTrack());
            addMarkerAttributes();

        }
        void addMarkerAttributes();
        void addParamAttributes();
        void setAuthor(string _str);
        void setDescription(string _str);
        void setDate(string _str);
        void setAudioTrack(int _track);

        void setParam( shared_ptr<Param> _param, float _val);

        void setMarker( shared_ptr<Marker> _marker, float _min, float _max );
        void addMarker( string _name, float _pos=0.0f, float _len=0.0f, string _desc="" );
        void addMarker( shared_ptr<Marker> _marker );
        void removeMarker( shared_ptr<Marker> _marker );

        void setStartTime( float _start ) {
            start = _start;
        }
        void setEndTime( float _end ) {
            end = _end;
        }


        float getStartTime() { return start; }
        float getEndTime() { return start; }

        string getAuthor();
        string getDescription();

        string getDate();
        int getAudioTrack();
        shared_ptr<Marker> getMarker( string _name );
        vector < shared_ptr<Marker> > & getMarkers(  );
        shared_ptr<Param> & getParams( string _name );


    protected:
    //atts
        string author;
        string description;
        string date;
        string URL;

        float start;
        float end;
        float speed;
        float volume;

        int audioTrack;


        vector< shared_ptr<Marker> > markers;
        vector< shared_ptr<Param> > params;

};

class Clip: public MediaHolder, public RawVideo {
    public:
        Clip(){
            init();
        }
        void init() {
            MediaHolder::init();
            setType("clip");

        }



    protected:

        float alpha;
        float r,g,b;
        float brightness;
        float contrast;

};





class Sample: public MediaHolder, public RawAudio{
    public:
        Sample(){
            init();
        }
        void init() {
            MediaHolder::init();
            setType("sample");

        }



    protected:

};




class Scene: public StoreObject{
    public:
        Scene(){}
};




//INTERACTIVIDAD

class Act: public StoreObject{
    public:
        Act(){}
};



#endif
