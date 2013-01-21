#pragma once

#ifndef control_h
#define control_h


class Clock: public StoreObject, virtual public kWidget {

    public:

        Clock(){
            init();
            createEvents();
            enableUpdate();
        }

        void createEvents(){
            saveEvent("event");
        }

        void init() {

            msThreshold = 15;
            msCounter   = 0;
            duration    = 1.0f;
            durationMs  = 6000;
            playing     = false;
            position    = 0;
            event       = "";
            pausedAt    = 0;
            resumedAt   = 0;
            startedAt   = 0;

        }

    //f
        float getPosition(){ return position; }
        void setPosition( float _position ) { position = _position; }
        float getDurationSecs(){ return duration; }
        float getDurationMs(){ return durationMs; }

        void setDurationSecs( float _dur ) {
            duration = _dur;
            durationMs = _dur * 1000;
        }

        void setDurationMs( int _ms ) {
            duration = float(_ms)/float(1000);
            durationMs = _ms;
        }

        void play() {

            if(!playing) {
                if(pausedAt==0)
                    startedAt = ofGetElapsedTimeMillis();
                else {
                    resumedAt = ofGetElapsedTimeMillis() - startedAt;

                    lastPausedTime = (resumedAt-pausedAt);
                    totalPausedTime += lastPausedTime;

                }
                playing = true;

            }

        }

        void pause() {
            if(playing) {
                pausedAt = ofGetElapsedTimeMillis() - startedAt;
                resumedAt=0;
            }
            playing = false;
        }

        void stop(){
            playing     = false;
            position    = 0;
            msCounter   = 0;
            resumedAt   = 0;
            pausedAt    = 0;
            startedAt   = 0;
            totalPausedTime = 0;
            lastPausedTime  = 0;
        }

        void update(ofEventArgs & args) {
            if(playing){

                msCounter = ( ofGetElapsedTimeMillis() -  startedAt - totalPausedTime ) % durationMs ;

                for (int i=0; i<eventItems.size(); i++)
                {
                    int eventMs =  ( eventItems[i].first * durationMs );
                    if( triggered[i] && abs( eventMs - msCounter ) > msThreshold )
                        triggered[i] = false;
                    if( abs( eventMs - msCounter ) < msThreshold && !triggered[i] ){ triggerEvent(i); }

                }

                position = (float) msCounter / durationMs ;

            }
        }

        void triggerEvent( int _i ){
            triggered[_i] = true;
            event = eventItems[_i].second;
            eventNum = _i;
            notify("event");
        }
    //eventItems
        void addEvent( float _position, string _eventName ){
            eventItems.push_back( make_pair( _position, _eventName ) );
            triggered.push_back(false);
        }


        string getEvent() { return event; }

        int getEventNum() { return eventNum; }


    //atts
        float   position;
        int     msThreshold;
        float   duration;
        int     durationMs;
        int     msCounter;
        bool    playing;
        string  event;
        int     eventNum;
        int     startedAt, pausedAt, resumedAt;
        int totalPausedTime;
        int lastPausedTime;
        vector < pair < float, string > > eventItems;
        vector < bool > triggered;

};

class ClockWidget: virtual public Clock, virtual public kRectView {
    //atts
    public:
        ClockWidget(){  }

        //f
        void draw(ofEventArgs & args) {

            float crcX=x + width * cos(2 * PI * position );
            float crcY=y + height * sin(2 * PI * position );
            ofLine(x,y,crcX,crcY);
            ofCircle(x,y,width);
//
//            if(creatingEvent) {
//                float angle = (float) getAngle(mouseX,mouseY,x,y)/360 ;
//                float eX = x + width * cos(2 * PI * angle );
//                float eY = y + height * sin(2 * PI * angle );
//                ofCircle(eX, eY ,10);
//
//
//            }

        }

        void initialize() {

            autoArrange = false;
            creatingEvent = true;

            setType("controlClock");

            btnView = make_shared<kRectButtonView>();
            btnView -> set( -0.5f, 1.0f , 1.0f,0.25f);

            vector<string> str;

            str.push_back("+");
            str.push_back("play");
            str.push_back("pause");
            str.push_back("stop");

            btnView->addButtons(str);

            addWidget( btnView );

            ofAddListener( *btnView->events.lookup("btnClicked"),this,&ClockWidget::btnClicked);



        }

        void btnClicked( widgetEvent & _event ){

            string command = btnView->getCommand();
            cout << "cc->"<<command << endl;

            if(command == "play")   play();
            if(command == "pause")  pause();
            if(command == "stop")   stop();

            if(command == "+")   creatingEvent = true;


        }





        shared_ptr<kRectButtonView> btnView;
        bool creatingEvent;

};



class AlphaControl: virtual public kRectView{

    public:

        AlphaControl(){
            alpha = 0;
            knob = make_shared<kKnob>( );

            knob->set(0.5f,0.5f,50,50);

            addWidget(knob);

        }


        float getAlpha() { return alpha; }

        float alpha;

        shared_ptr<kKnob> knob;
};

#endif


