
#include "outputs.h"




        VideoOutput::VideoOutput() {

            enableUpdate();

            alpha=1.0f;
/*
            blendSrc.push_back(GL_ONE);
            blendSrc.push_back(GL_ONE);
            blendSrc.push_back(GL_ONE);
            blendSrc.push_back(GL_SRC_ALPHA);
            blendSrc.push_back(GL_SRC_ALPHA);

            blendDst.push_back(GL_ZERO);
            blendDst.push_back(GL_ONE);
            blendDst.push_back(GL_ONE_MINUS_DST_ALPHA);
            blendDst.push_back(GL_ONE_EXT);
            blendDst.push_back(GL_ONE_MINUS_SRC_ALPHA);

*/
//            texture.allocate( w,h,GL_RGB );

//            newPix = new unsigned char[w*h*3];

//            play();
            filename="";

            volume = 1.0;

            brightness=255;
            targetBrightness=255;

            fading = false;

            fadeTime = 1000;

            speed = 1.0f;

            playing = false;

createEvents();

            videoTriggered = false;

            setupVideo();

        }


        void VideoOutput::createEvents(){
            saveEvent("videoEnd");
        }


        void VideoOutput::play(){
            video -> play();
            playing = true;
        };

        void VideoOutput::stop(){
            video -> stop();
            playing = false;
        };

        void VideoOutput::setupVideo()  {
            video = make_shared<kVideoPlayer>();
            video->setSpeed(speed);
            video->video->setLoopState(OF_LOOP_NONE);
        }

        void VideoOutput::update(ofEventArgs & args)   {
            if(playing) {
//                counter++;
//                counter %= 30000;

//                if(counter%20==0)
//                    blendCount++;
//                    blendCount%=5;
//                blink=(counter%blinkFreq)>(blinkFreq/2);

//                for (int i=0; i<layer.size(); i++)

                video->update();

                if( video->getPosition() > 0.95f || video->getIsMovieDone() ){
                    if(!videoTriggered) notify("videoEnd");
                    videoTriggered = true;
                }
//                texture.loadData(   createPixels(), w, h, GL_RGB );

            }

            if(fading){
                if(counter%fadeMs==0) {
                    brightness+=fadeStep;
                    video->brightness=brightness;
                }
                if(fadeStep>0) {
                    if( brightness >= targetBrightness )
                        fading = false;
                        //brightness=255;
                }
                if(fadeStep<0) {
                    if( brightness <= targetBrightness )
                        fading = false;
                        //brightness=0;
                }
            }
        }

        unsigned char * VideoOutput::createPixels() {

//            for (int i=0; i<w*h*3; i++)
//                newPix[i]=0;
//
//            ofVideoPlayer * video;
//
//            for (int i=0; i<layer.size(); i++) {
//                    video = video->video;
//
//                    if(video->bLoaded)  {
//                        pixels=video->getPixels();
//                        int ww = video->getWidth();
//                        int hh = video->getHeight();
//
//                        for (int j=0; j<ww*hh*3; j++)
//                            newPix[j] += ( pixels[j] * 0.1f );
//                    }
//
//            }
//
//            return newPix;

        }

        void VideoOutput::addRect( float _x, float _y, float _w, float _h){
            canvases.push_back( make_shared<ofRectangle>(_x,_y,_w,_h) );
        }

        void VideoOutput::addRect( shared_ptr<ofRectangle> _rect){
            canvases.push_back( _rect );
        }

        void VideoOutput::draw(ofEventArgs & args) {
            if(playing) {

//              ofEnableAlphaBlending();
                ofSetColor(brightness,brightness,brightness,brightness);

                for (int i=0; i<canvases.size(); i++)
                {
                    float vh = (
                        float(video->getHeight())
                        /
                        float(video->getWidth())
                    );

                    vh*=canvases[i]->width;

                    if(i==0) setBrightness(205);
                    if(i==1) setBrightness(255);
//ofSetColor(255);
                    video -> draw(
                        canvases[i]->x,
                        canvases[i]->y,
                        canvases[i]->width,
                        vh
                    );



                }

                ofSetColor(50);

            }
        }

        void VideoOutput::changeClip( string _filename )   {

            filename=_filename;
            video -> loadMovie(filename);
            video -> setVolume(volume);

            drawStr=filename;
            drawStr.erase( 0, drawStr.find_last_of("/")+1 );
            playing = true;

            videoTriggered = false;

        }

        void VideoOutput::setVolume(float pct)   {
            video -> setVolume(pct);
            volume = pct;
        }


        void VideoOutput::setAlpha(float pct)   {
            video -> setAlpha(pct);
            alpha = pct;
        }


        void VideoOutput::fade(int _time, int _fadeVal)    {
            fading = true;

            fadeMs=2;

            if(_fadeVal==0) { fadeStep=-10;}
            if(_fadeVal==1) { fadeStep=10; }

            targetBrightness=_fadeVal*255;

        }

        void VideoOutput::setFilename ( string _filename ){
            filename = _filename;
        }

        void VideoOutput::setSpeed(float pct) {
            speed = pct;
            video->setSpeed(speed);
        }


        float VideoOutput::getPosition(){
            return video->getPosition();
        }


        void VideoOutput::setBrightness( float _val ){
            brightness = _val;
            video->setBrightness(_val);
        }





        void Outputs::addVideoOutput( vector< shared_ptr < ofRectangle > >  _rects ){
            videoOutputs.push_back( make_shared<VideoOutput>() );
            for (int i=0; i<_rects.size(); i++)
            {
            	videoOutputs.back()->addRect( _rects[i] );
            }
        }

        void Outputs::addSampleOutput(){

        }

        shared_ptr<VideoOutput> & Outputs::getVideoOutput( int _index ){
            if(videoOutputs[_index])
                return videoOutputs[_index];
        }





        PlayList::PlayList(){
            currentIndex = 0;
            output = make_shared<VideoOutput>( );

            ofAddListener( *output->events.lookup("videoEnd"), this, &PlayList::changeVideo );
        }



        void PlayList::changeVideo( widgetEvent & _event){
            output->changeClip( getNextClip()->getFilename() );

        }

        void PlayList::addMedia( shared_ptr < MediaHolder > _media ){
            media.push_back( _media );
        }

        void PlayList::addClip ( shared_ptr < Clip > _clip ){
            clips.push_back( make_shared<kClipShow>( ) );
            clips.back()->set(0,0,200,130);
            addWidget(clips.back());
            arrangeWidgets();
        }


        shared_ptr<MediaHolder> PlayList::getNextMedia(){
            currentIndex++;
            if(currentIndex<media.size() )
                currentMedia = media[currentIndex];
        }


        shared_ptr< Clip > PlayList::getNextClip(){
            int currentIndex = 0;
            return clips[currentIndex]->getClip();
        }




