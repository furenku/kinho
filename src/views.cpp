#include "views.h"
#include "guiVideoObjects.h"


    kAudioView::kAudioView(){ noSliders = 6; autoArrange = true; }

    void kAudioView::initialize() {
        for (int i=0; i<noSliders; i++)
        {
            shared_ptr<kSlider>  slider = make_shared<kSlider>();
            slider->set(x,0,20,height/3);
            slider->setSize(20,height/3);//-40);
            slider->setOrientation("vertical");
            slider->applySettings ( settings );
            slider->setWidgetSettings( settings );
            slider->initialize();

//            ofAddListener( *slider->events.lookup("scrollUp"),this,&kAudioView::scrollUp);
//            ofAddListener( *slider->events.lookup("scrollDown"),this,&kAudioView::scrollDown);
//            ofAddListener( *slider->events.lookup("scroll"),this,&kAudioView::scrolled);

            sliders.push_back(slider);


            addWidget(slider);
        }

        arrangeWidgets();

    }



    void kAudioView::scrollUp(widgetEvent & event) {

    }

    void kAudioView::scrollDown(widgetEvent & event) {
    }

    void kAudioView::scrolled(widgetEvent & event) {

    }






        kEditorView::kEditorView(){
            createEvents();
            autoArrange = false;
            currentColor = ofColor(40,100,200);
//            ofAddListener(ofEvents.update, this,&kEditorView::update);
            seekPos = 0.0f;
        }

        void kEditorView::initialize() {

            video = make_shared<ofVideoPlayer>();

            video->loadMovie("movies/blood01.mov");
            video->setPaused(true);

            ctl = make_shared<Controller>();


            autoArrange=false;
            isDraggable=true;


//            ranges.push_back( make_shared<kCircleTool>() );
            ranges.push_back( make_shared<kRectTool>() );

//            ranges[0]->set(0.5f,0.35f,0.335f,0.335f);
            //ADD RANGE AFTER 4:3 Y
            ranges[0]->set(0.01,0.98/(4/3),0.98f,0.08f);

            activeRange = ranges[0];

            for (int i=0; i<ranges.size(); i++)
                addWidget( ranges[i] );

            loginRanges();


            //------------------------

            tView = make_shared<kRectButtonView>();
            tView->set(0.775,0.01,0.2f,0.075);
            tView->applySettings ( settings );
            tView->setWidgetSettings( widgetSettings );
            tView->widgetSize=WIDGET_SIZE;

            addWidget( tView );


            labels.push_back("in");
            labels.push_back("out");

            tView->addButtons(labels);

            boolVec.clear();

            for (int i=0; i<ranges.size(); i++)
                boolVec.push_back( &ranges[i]->inOrOut );

            func = make_shared<Set <bool*> > (boolVec, &tView->boolValue );
            ctl->login( tView, "btnClicked", func );



            for (int i=0; i<4; i++)
            {
                inputs.push_back( make_shared<TextBox>( widgetSettings ) );
                inputs.back()->set(0.05f,0.1+(0.053*i),0.7f,0.05f);
                inputs.back()->setText(0.05f*i);
                addWidget(inputs.back());
            }

            //------------------------------
            btn = make_shared<kRectButton>();
            btn->setLabel("cut");
            btn->set(0.76,0.775,0.225,0.15);

            addWidget( btn );

//            ctl->login(btn,"press",make_shared<Notify>(shared_from_this(),"createRange"));
        }

        void kEditorView::viewClip(shared_ptr<Clip> _clip){
            currentClip = _clip;
//            for (int i=0; i<ranges.size(); i++)
//                ranges[i]->login(_clip);


            video->close();
            video->loadMovie(_clip->getFilename());

//            video->setPaused(false);

            video->play();

            inputs[0]->setText(_clip->getName());
            inputs[1]->setText(_clip->getDescription());

//            string tags;
//            for (int i=0; i<_clip->tags.size(); i++)
//            	tags+=_clip->tags[i]+",";
//
//            inputs[2]->setText(tags);

	            loginClip();

        }

        void kEditorView::loginRanges() {
            shared_ptr<FunctorHolder> funcs;
            for (int i=0; i<ranges.size(); i++)
            {

                floatVec.clear();
                for (int j=0; j<ranges.size(); j++)
                    floatVec.push_back(&ranges[j]->start);

                floatVec.push_back(&seekPos);

                funcs = make_shared<FunctorHolder>();
                funcs->addFunc(make_shared< Set <float* > >  (floatVec, &ranges[i]->clickPosition));
                funcs->addFunc(make_shared< SetPointer<kRangeHolder> > (ranges[i],activeRange));
                funcs->addFunc(make_shared< Notify > (shared_from_this(),"seek"));


                ctl->login(
                    ranges[i],
                    "in",
                    funcs
                );

                floatVec.clear();
                for (int j=0; j<ranges.size(); j++)
                    floatVec.push_back(&ranges[j]->end);
                floatVec.push_back(&seekPos);

                funcs.reset();
                funcs = make_shared<FunctorHolder>();
                funcs->addFunc(make_shared<Set<float*> > (floatVec, &ranges[i]->clickPosition));
                funcs->addFunc(make_shared<SetPointer<kRangeHolder> > (ranges[i],activeRange));
                funcs->addFunc(make_shared< Notify > (shared_from_this(),"seek"));

                ctl->login(
                    ranges[i],
                    "out",
                    funcs
                );
            }
        }

        void kEditorView::loginClip() {
//            for (int i=0; i<ranges.size(); i++)
//            {
////                ranges[i]->login(currentClip);
//
//                floatVec.clear();
//                vector< shared_ptr < Marker > > markers = currentClip->getMarkers();
//                for (int j=0; j<markers.size(); j++)
//                    floatVec.push_back(&markers[j]->getPosition());
//
//                ctl->login(
//                    ranges[i], "start",
//                    make_shared<SetInVector<float*,shared_ptr<kRangeHolder> > >(
//                        floatVec,
//                        ranges[i], &ranges[i]->clickPosition)
//                );
//
//                floatVec.clear();
//                for (int j=0; j<currentClip->ranges.size(); j++)
//                    floatVec.push_back(&markers[j]->getPosition());
//                ctl->login(
//                    ranges[i], "end",
//                    make_shared<SetInVector<float*,shared_ptr<kRangeHolder> > >(
//                        floatVec,
//                        ranges[i], &ranges[i]->clickPosition)
//                );
//
//            }
        }

        void kEditorView::createEvents(){
            saveEvent("createRange");
            saveEvent("seek");

        }

        void kEditorView::update(ofEventArgs & args) {
            video->idleMovie();
            for (int i=0; i<ranges.size(); i++)
            {
            	ranges[i]->playHead = video->getPosition();
            }
        }

        void kEditorView::draw(ofEventArgs & args) {
            if(isMouseOn) color(1);
            else          color(0);
            ofRect(x,y,width,height);

            ofSetColor(255);
            video->draw(x,y+60,width,width/1.77f);


        }

        shared_ptr<kEditorView> kEditorView::shared_from_this()
        {
            return dynamic_pointer_cast<kEditorView>(Observable::shared_from_this());
        }

    //{ vars


        shared_ptr<Controller>                  ctl;
        shared_ptr<Functor>                     func;
        vector<string>                          labels;
        vector<shared_ptr<TextBox> >            inputs;
        shared_ptr<kButton>                     btn;
        shared_ptr<kView>                       subView;
        shared_ptr<kRectButtonView>             tView;
        shared_ptr<kCircleTool>                 crc;
        shared_ptr<kRectTool>                   rrc;
        shared_ptr<Range>                       range;
        vector < shared_ptr<kRangeHolder> >     ranges;
        vector <string>                         commands;
        vector <bool*>                          boolVec;
        vector <int*>                           intVec;
        vector <float*>                         floatVec;

        shared_ptr<kRangeHolder>                activeRange;
        ofColor                                 currentColor;
        float                                   seekPos;


    //}







        kBrowseArchive::kBrowseArchive(){autoArrange=true;rows=1; createEvents();
          enableUpdate();
        }

//
        void kBrowseArchive::createEvents() {
            saveEvent("buttonClicked");
            saveEvent("buttonDragged");
            saveEvent("clipClicked");
            saveEvent("clipDragged");
        }

        void kBrowseArchive::createClipView(){


            clipView = make_shared<kClipScrollView>();

            clipView -> set(0,0.1f,1.0f,0.9f);
            clipView -> applySettings ( settings  );
            clipView -> setWidgetSettings ( settings );
            clipView -> cols=1;
            clipView -> setSpacingY( 65 );

            clipScrollViews.push_back( clipView );

            ofAddListener( *clipView->events.lookup("clipClicked"),this,&kBrowseArchive::clipClicked);
            ofAddListener( *clipView->events.lookup("clipDragged"),this,&kBrowseArchive::clipDragged);



            if(mediaViews.back()) {
                mediaViews.back() -> addWidget(clipView);
                mediaViews.back()->arrangeWidgets();
            }
            clipView -> initialize();

        }

        void kBrowseArchive::createSampleView(){
            sampleView = make_shared<kSampleScrollView>();

            sampleView -> set(0,0.1f,1.0f,0.9f);
            sampleView -> applySettings ( settings  );
            sampleView -> setWidgetSettings ( settings );
            sampleView -> cols=2;

            sampleScrollViews.push_back( sampleView );

            ofAddListener( *sampleView->events.lookup("btnClicked"),this,&kBrowseArchive::btnClicked);
            ofAddListener( *sampleView->events.lookup("btnDragged"),this,&kBrowseArchive::btnClicked);


            if(mediaViews.back()) {
                mediaViews.back() -> addWidget(sampleView);
                mediaViews.back() -> arrangeWidgets();
            }
            sampleView -> show();
            sampleView -> initialize();


        }

        void kBrowseArchive::createTextView(){
        }



        void kBrowseArchive::createMediaViews(){

            createClipView();
            createSampleView();

            for (int i=0; i<sampleScrollViews.size(); i++)
                sampleScrollViews[i]->hide();

            arrangeWidgets();

        }

        void kBrowseArchive::loadMediaViews(){

            createClipView();
            createSampleView();

            for (int i=0; i<sampleScrollViews.size(); i++)
                sampleScrollViews[i]->hide();

            arrangeWidgets();

        }

        void kBrowseArchive::initMediaViews(){

        //media view:

            shared_ptr<kRectView> mediaView= make_shared<kRectView>();
            mediaView -> set(0,0,width/2.5f,height);
            mediaView -> setAutoArrange(false);
            mediaView -> setOrientation("vertical");
            addWidget(mediaView);
            arrangeWidgets();

            mediaViews.push_back( mediaView );


        //view toggle
            shared_ptr<kRectButtonView> tView = make_shared<kRectButtonView>();
            tView->set(0.0,0.0,1.0f,0.1f);
            tView->applySettings ( settings );
            tView->setWidgetSettings( widgetSettings );
            tView->widgetSize=WIDGET_SIZE;

            mediaView -> addWidget( tView );

            vector<string> labels;
            labels.push_back("clips");
            labels.push_back("samples");
            labels.push_back("textos");

            tView->addButtons(labels);

            ofAddListener( *tView->events.lookup("btnClicked"),this,&kBrowseArchive::toggleViews);


        }



        void kBrowseArchive::removeAllViews(){


            for (int i=0; i<clipScrollViews.size(); i++) {
                vector< shared_ptr < kWidget > > widgets = clipScrollViews[i]->getWidgets();

                for (int j=0; j<widgets.size(); j++)
                {
                    removeWidget(widgets[j]);
                }

                ofAddListener( *clipScrollViews[i]->events.lookup("btnClicked"),this,&kBrowseArchive::btnClicked);
                ofAddListener( *clipScrollViews[i]->events.lookup("btnDragged"),this,&kBrowseArchive::btnClicked);

//                clipScrollViews[i]->clearWidgets();
//                clipScrollViews[i]->clearClips();


                clipScrollViews[i]->disable();
                clipScrollViews[i]->disableUpdate();
                clipScrollViews[i]->hide();

                removeWidget(clipScrollViews[i]);
                clipScrollViews[i].reset();

            }
            clipScrollViews.clear();

            for (int i=0; i<sampleScrollViews.size(); i++) {
                vector< shared_ptr < kWidget > > widgets = sampleScrollViews[i]->getWidgets();

                for (int j=0; j<widgets.size(); j++)
                {
                    removeWidget(widgets[j]);
                }

                ofAddListener( *sampleScrollViews[i]->events.lookup("btnClicked"),this,&kBrowseArchive::btnClicked);
                ofAddListener( *sampleScrollViews[i]->events.lookup("btnDragged"),this,&kBrowseArchive::btnClicked);

                sampleScrollViews[i]->disable();
                sampleScrollViews[i]->disableUpdate();
                sampleScrollViews[i]->hide();

                removeWidget(sampleScrollViews[i]);
                sampleScrollViews[i].reset();

            }
            sampleScrollViews.clear();

        }

        void kBrowseArchive::removeMediaViews(){


            removeAllViews();

            for (int i=0; i<mediaViews.size(); i++) {
                vector< shared_ptr < kWidget > > widgets = mediaViews[i]->getWidgets();

                for (int j=0; j<widgets.size(); j++)
                {
                    removeWidget(widgets[j]);
                }
//                ofAddListener( *mediaViews[i]->events.lookup("btnClicked"),this,&kBrowseArchive::btnClicked);

//                mediaViews[i]->clearWidgets();
//                mediaViews[i]->clearClips();


                mediaViews[i]->disable();
                mediaViews[i]->disableUpdate();
                mediaViews[i]->hide();

                removeWidget(mediaViews[i]);
                mediaViews[i].reset();

            }
            mediaViews.clear();



        }




        void kBrowseArchive::addClips( vector< shared_ptr<Clip> > _clips ) {
            clipScrollViews.back() -> addClips(_clips);
            arrangeWidgets();
            lastClips = _clips;
        }

        void kBrowseArchive::addSamples( vector< shared_ptr<Sample> > _samples ) {
            sampleScrollViews.back() -> addSamples(_samples);
            arrangeWidgets();
            lastSamples = _samples;

        }


//        void addTexts( vector< shared_ptr<Text> > _texts ) {
//            textScrollViews.back() -> addTexts(_texts);
//            arrangeWidgets();
//            lastTexts = _texts;
//        }

        void kBrowseArchive::addMedia( vector< shared_ptr<Clip> > _clips, vector< shared_ptr<Sample> > _samples )
        {
            addClips(_clips);
            addSamples(_samples);
        }


        void kBrowseArchive::clearClips(){
            for (int i=0; i<clipScrollViews.size(); i++) {
                vector< shared_ptr < kWidget > > widgets = clipScrollViews[i]->getWidgets();

                for (int j=0; j<widgets.size(); j++)
                {
                    widgets[j]->disable();
                    ofRemoveListener( *widgets[j]->events.lookup("press"),this,&kBrowseArchive::btnClicked);
                }
    //                clipScrollViews[i]->clearWidgets();
//                clipScrollViews[i]->clearClips();
                clipScrollViews[i]->clearWidgets();
//                removeWidget(clipScrollViews[i]);
//                clipScrollViews[i].reset();
            }
            clipScrollViews.clear();
        }






        void kBrowseArchive::clearSamples(){
            for (int i=0; i<sampleScrollViews.size(); i++) {
                vector< shared_ptr < kWidget > > widgets = sampleScrollViews[i]->getWidgets();

                for (int j=0; j<widgets.size(); j++)
                {
                    widgets[j]->disable();
                    ofRemoveListener( *widgets[j]->events.lookup("press"),this,&kBrowseArchive::btnClicked);
                }
    //                sampleScrollViews[i]->clearWidgets();
//                sampleScrollViews[i]->clearSamples();
                sampleScrollViews[i]->clearWidgets();
//                removeWidget(clipScrollViews[i]);
//                clipScrollViews[i].reset();
            }
            sampleScrollViews.clear();
        }

        void kBrowseArchive::addCol(vector<string> _labels){


            shared_ptr<kScrollView> scrollView = make_shared<kScrollView>();
            scrollView -> set(0,0,width/3.5,height);
            scrollView -> applySettings ( settings  );
            scrollView -> setWidgetSettings ( settings );
            scrollView -> cols=1;
            scrollViews.push_back( scrollView );


//            for (int i=0; i<_labels.size(); i++) {
                ofAddListener( *scrollView->events.lookup("btnClicked"),this,&kBrowseArchive::btnClicked);
                ofAddListener( *scrollView->events.lookup("btnDragged"),this,&kBrowseArchive::btnDragged);
//            }


            addWidget(scrollView);


            scrollView -> initialize();
            scrollView -> addDragButtons(_labels);

            arrangeWidgets();



        }

        void kBrowseArchive::removeCol(int _i){
            if(scrollViews.size()>_i){
                if(scrollViews[_i]) {
//                    for (int i=0; i<scrollViews[_i]->widgets.size(); i++) {
                        ofRemoveListener( *scrollViews[_i]->events.lookup("btnClicked"),this,&kBrowseArchive::btnClicked);
                        ofRemoveListener( *scrollViews[_i]->events.lookup("btnDragged"),this,&kBrowseArchive::btnClicked);
//                    }

                    addDelete(scrollViews[_i]);

                    removeWidget(scrollViews[_i]);
    //                scrollViews[_i].reset();
                    scrollViews.erase(scrollViews.begin()+_i);

//                    cout << widgets.size() << endl;

                    arrangeWidgets();
                }
            }
        }

        void kBrowseArchive::clearWidgets() {
            for (int i=0; i<widgets.size(); i++)
            {
                ofRemoveListener( *widgets[i]->events.lookup("press"),this,&kBrowseArchive::btnClicked);
            }

            kWidget::clearWidgets();


        }



//        void arrangeWidgets() {
//             for (int i=0; i<scrollViews.size(); i++) {
//                if(autoArrange) {
//                    scrollViews[i] -> setFromCenter( getX(i), getY(i) );
//                }
//                scrollViews[i]->arrangeWidgets();
//             }
//        }

        void kBrowseArchive::btnClicked(widgetEvent & _event){

            kButtonView::btnClicked(_event);
            int row=-1;
            shared_ptr<kRectButtonView>sender=dynamic_pointer_cast<kRectButtonView>(_event.sender);

            for (int i=0; i<scrollViews.size(); i++)
            {
                if( sender==scrollViews[i]) {
                    row=i;
                    break;
                }
            }
//

            clickedRow = row;

            string label = scrollViews[row]->labels[scrollViews[row]->value];

            command = label;


            if(row<2)
                notify("buttonClicked");
//            else
//                notify("clipClicked");

        }



        void kBrowseArchive::btnDragged(widgetEvent & _event){

            kButtonView::btnDragged(_event);
            int row=-1;
            shared_ptr<kRectButtonView>sender=dynamic_pointer_cast<kRectButtonView>(_event.sender);

            for (int i=0; i<scrollViews.size(); i++)
            {
                if( sender==scrollViews[i]) {
                    row=i;
                    break;
                }
            }
//

            clickedRow = row;

            string label = scrollViews[row]->labels[scrollViews[row]->value];

            command = label;


            if(row<2)
                notify("buttonDragged");
//            else
//                notify("clipDragged");
//                cout << "dragged" << endl;

        }



        void kBrowseArchive::clipClicked(widgetEvent & _event){
            shared_ptr<kClipScrollView> view = dynamic_pointer_cast<kClipScrollView>(_event.sender);
            clickedClip = dynamic_pointer_cast<kClipShow>(view->getWidgets()[view->getValue()])->getClip();
            cout << clickedClip->getName() << endl;
            notify("clipClicked");
        }



        void kBrowseArchive::clipDragged(widgetEvent & _event){
            shared_ptr<kClipScrollView> view = dynamic_pointer_cast<kClipScrollView>(_event.sender);
            cout << view->getValue() << endl;
            draggingClip = dynamic_pointer_cast<kClipShow>(view->getWidgets()[view->getValue()])->getClip();
            notify("clipDragged");
        }

        void kBrowseArchive::toggleViews(widgetEvent & _event){

            int value = dynamic_pointer_cast<kButtonView>(_event.sender)->getValue();

            switch(value){
                case 0:
                    removeAllViews();
                    createClipView();
                    addClips(lastClips);
                break;
                case 1:
                    removeAllViews();
                    createSampleView();
                    addSamples(lastSamples);
                break;
                case 2:
                    removeAllViews();
                    createTextView();
//                    addTexts(lastTexts)
                break;
            }
        }

        int kBrowseArchive::getClickedRow() { return clickedRow; }
        string kBrowseArchive::getCommand() { return command; }








        kArchiveView::kArchiveView(){
            createEvents(); autoArrange = false;
//            fbo.allocate(300,300,GL_RGBA);
//            ofAddListener(ofEvents.update,this,&kArchiveView::update);


        }

        void kArchiveView::initialize() {
//            shared_ptr<kVectorHolder> vec = make_shared<kVectorHolder>( );
//            vec->set(0.7f,0.3f,0.3f,0.3f);
////            shared_ptr<kCircleButton> btn = make_shared<kCircleButton>( );
////            btn->set( ofRandomf(),ofRandomf(), 0.1f,0.1f );
////            vec->set(0.5f,0.5f,40,40);
//
////            vec->addWidget(btn);
//            addWidget(vec);
//
//            arrangeWidgets();
//
//            vec->initialize();
//
//
//            vec = make_shared<kVectorHolder>( );
//            vec->set(0.2f,0.8f,0.1f,0.1f);
////            shared_ptr<kCircleButton> btn = make_shared<kCircleButton>( );
////            btn->set( ofRandomf(),ofRandomf(), 0.1f,0.1f );
////            vec->set(0.5f,0.5f,40,40);
//
////            vec->addWidget(btn);
//            addWidget(vec);
//
//            arrangeWidgets();
//
//            vec->initialize();

    vector<string> labels;
    labels.push_back("clip1");
    labels.push_back("clip2");
    labels.push_back("clip3");

            shared_ptr<kCircleButtonView> cat;
            for (int i=0; i<10; i++)
            {
                cat = make_shared<kCircleButtonView>();
                cat->set(ofRandomuf(),ofRandomuf(),0.03f,0.04);
                cat->widgetSize=WIDGET_SIZE/2;

                addWidget( cat );
                cat->addButtons(labels);
            }

        }

        void kArchiveView::createEvents(){
            saveEvent("clipSel");
            saveEvent("viewClip");
            saveEvent("tagClicked");
        }


void kArchiveView::createCats(){

    float newX,newY;


    for (int i=0; i<4; i++)
    {
        newX = (ofRandomuf()*0.5f)+0.3f;
        newY = (ofRandomuf()*0.5f)+0.3f;

        categories.push_back( make_shared<kCategory>( ) );
        categories.back()->set(newX,newY,0.05f,0.05f);
        addWidget( categories.back() );

        vector<string> labels;
        labels.push_back("select");
        labels.push_back("connect");
        labels.push_back("related");
        labels.push_back("scenes");
        labels.push_back("tags");

        categories.back() -> addButtons(labels);
//        for (int i=0; i<labels.size(); i++)
//            ofAddListener( *categories.back()->events.lookup("btnClicked"),this,&kArchiveView::btnClicked);

        arrangeWidgets();

    }

}

void kArchiveView::btnClicked(widgetEvent & event){
    notify("tagClicked");
}

        void kArchiveView::dropped(shared_ptr<kWidget> _dragObj ) {
        cout << "YEA" << endl;
            if(_dragObj) {
                if(inside(_dragObj -> dragX,_dragObj -> dragY) ) {
                    float newX = (_dragObj -> dragX - x) / width;
                    float newY = (_dragObj -> dragY - y) / height;
                    shared_ptr<kClipHolder> newclip = make_shared<kClipHolder>(widgetSettings);
                    newclip->set(newX,newY,0.05f,0.05f);
                    newclip->setClip(dynamic_pointer_cast<kClipShow>(_dragObj)->clip);
                    addWidget ( newclip );
    ///SEARCH FOR VISIBLE RELATED CLIPS, ADD CONNECTIONS IF FOUND!
    // i think this is wrong: the events should only in clipholer?
//                    ofAddListener(*newclip->events.lookup("select"),this,&kArchiveView::selectClip);
//                    ofAddListener(*newclip->events.lookup("connect"),this,&kArchiveView::connectionStart);
//                    ofAddListener(*newclip->events.lookup("press"),this,&kArchiveView::connectionAttempt);
//                    ofAddListener(*newclip->events.lookup("viewClip"),this,&kArchiveView::showClip);
                }
            }

        }


//
    void kArchiveView::addClip(shared_ptr<Clip> _clip){

        shared_ptr<kClipShow> clip = make_shared<kClipShow>();
        clip -> setClip(_clip);
        clip->set( 0, 0, CLIPVIEW_SIZE,CLIPVIEW_SIZE  );

        addWidget( clip );

        clip->hide();


    }

        void kArchiveView::showClip(widgetEvent & event) {
            currentClip = dynamic_pointer_cast<kClipHolder>(event.sender)->clip;
            notify("viewClip");
        }

        void kArchiveView::selectClip(widgetEvent & event) {
            clipSel = dynamic_pointer_cast<kClipHolder>(event.sender);
            currentClip = clipSel->clip;
            notify("clipSel");
        }

        void kArchiveView::connectionStart(widgetEvent & event){
            connectingClip = dynamic_pointer_cast<kClipHolder>(event.sender);

        }

        void kArchiveView::connectionAttempt(widgetEvent & event){
            if(connectingClip) {
                connectClips(dynamic_pointer_cast<kClipHolder>(event.sender));
            }
            connectingClip.reset();
        }

        void kArchiveView::connectClips(shared_ptr<kClipHolder>_clip) {
//            connectingClip---->_clip
            // add connection to database
            // add to local viewable selections
            connections.push_back(make_pair(connectingClip,_clip));
//            connectingClip->width = 100;
//            connectingClip=_clip;
        }


        void kArchiveView::mousePressed(ofMouseEventArgs & mouse) {
            if(!mouseOnWidgets())
                if(connectingClip)
                    connectingClip.reset();
        }


        void kArchiveView::fboFill() {
//            fbo.begin();
//                ofNoFill();
//                ofSetColor(255,0,0);
//                if(isMouseOn) color(1);
//                else          color(0);
//                ofCircle(150,150,50);
//            fbo.end();
        }

        void kArchiveView::update(ofEventArgs & args) {
            fboFill();
//                ofRect(x,y,width,height);
//
//                if(isMouseOn) {
//                    if(connectingClip)
//                        ofLine(
//                            ofGetAppPtr()->mouseX,
//                            ofGetAppPtr()->mouseY,
//                            connectingClip->x,
//                            connectingClip->y
//                        );
//                }
//
//                for (int i=0; i<connections.size(); i++)
//                {
//                    ofLine(
//                        connections[i].first->x,
//                        connections[i].first->y,
//                        connections[i].second->x,
//                        connections[i].second->y
//                    );
//                }

//                for (int i=0; i<widgets.size(); i++)
//                {
//                	widgets[i]->draw(args);
//                }


        }

//        void draw(ofEventArgs & args) {
//
//
//
////            fbo.begin();
////                glClear(GL_DEPTH_BUFFER_BIT);
////
////                ofEnableAlphaBlending();
////                ofSetColor(255, 255, 255); //you can change the alpha value to modulate the effect
////                ofFill();
////                ofCircle(100, 100, 20);
////
////                for (int i=0; i<widgets.size(); i++)
////                {
////                	widgets[i]->draw(args);
////                }
////
////            fbo.end();
////
////            fbo.draw(x,y,width,height);
//        }







        void kOutSender::mouseReleased( ofMouseEventArgs & mouse){
            kRectButton::mouseReleased(mouse);
            kDragObject::mouseReleased(mouse);
        }




        void kPlayView::initialize() {
            createOuts();
        }

        void kPlayView::createOuts(){

            for (int i=0; i<2; i++)
            {
                shared_ptr<kOutSender> out;
                out = make_shared<kOutSender>();
                out->set(0.33f*(i+1),0.8f,0.1f,0.1f);
                out->setLabel("out"+ofToString(i));
//                ofAddListener(*out->events.lookup("press"),this,&kPlayView::connectionAttempt);

                addWidget(out);
                outs.push_back(out);
            }

        }

        void kPlayView::update(ofEventArgs & args) {
//video->idleMovie();
//video2->idleMovie();
        }

        void kPlayView::createEvents(){
            saveEvent("clipSel");
        }

        void kPlayView::dropped(shared_ptr<kWidget> _dragObj ) {

            if(_dragObj) {
                if(inside(_dragObj -> dragX,_dragObj -> dragY) ) {
                    float newX = (_dragObj -> dragX - x) / width;
                    float newY = (_dragObj -> dragY - y) / height;
                    shared_ptr<kClipHolder> newclip = make_shared<kClipHolder>(widgetSettings);
                    newclip->set(newX,newY,0.05f,0.05f);
                    newclip->setClip(dynamic_pointer_cast<kClipShow>(_dragObj)->clip);
                    addWidget ( newclip );
    ///SEARCH FOR VISIBLE RELATED CLIPS, ADD CONNECTIONS IF FOUND!
    // i think this is wrong: the events should only in clipholer?
//                    ofAddListener(*newclip->events.lookup("select"),this,&kPlayView::selectClip);
//                    ofAddListener(*newclip->events.lookup("connect"),this,&kPlayView::connectionStart);
//                    ofAddListener(*newclip->events.lookup("press"),this,&kPlayView::connectionAttempt);
                }
            }

        }

        void kPlayView::playClip(shared_ptr<Clip> _clip, int _out) {
            currentClip = _clip;
switch(_out) {
    case 0 :
        video->close();
        video->loadMovie(_clip->getFilename());
        video->play();
        break;
    case 1 :
        video2->close();
        video2->loadMovie(_clip->getFilename());
        video2->play();
        break;
}
        }
//
        void kPlayView::selectClip(widgetEvent & event) {
            clipSel = dynamic_pointer_cast<kClipHolder>(event.sender);
            notify("clipSel");
        }

        void kPlayView::connectionStart(widgetEvent & event){
            connectingWidget = dynamic_pointer_cast<kWidget>(event.sender);
connectingClip = dynamic_pointer_cast<kClipHolder>(event.sender);
        }

        void kPlayView::connectionAttempt(widgetEvent & event){

            if(connectingWidget) {
                connectWidgets(dynamic_pointer_cast<kWidget>(event.sender));
int output = -1;
for (int i=0; i<outs.size(); i++)
{
    if( dynamic_pointer_cast<kOutSender>(event.sender)==outs[i])
    output = i;
}

connectingClip -> output = output;
            }
            else {
if(dynamic_pointer_cast<kClipHolder>(event.sender)->output>-1){
    playClip(
        dynamic_pointer_cast<kClipHolder>(event.sender)->clip,
        dynamic_pointer_cast<kClipHolder>(event.sender)->output
    );
}
            }
            connectingWidget.reset();
        }

        void kPlayView::connectWidgets(shared_ptr<kWidget>_widget) {
            // add connection to database
            // add to local viewable selections
            connections.push_back(make_pair(connectingWidget,_widget));
//            connectingClip=_clip;
        }

        void kPlayView::mousePressed(ofMouseEventArgs & mouse) {
            if(!mouseOnWidgets())
                if(connectingWidget)
                    connectingWidget.reset();
        }

        void kPlayView::draw(ofEventArgs & args) {
ofSetColor(255,255,255);
//
//video->draw(
//    outs[0]->x,
//    outs[0]->y,
//    outs[0]->width,
//    outs[0]->height
//);
//video->draw(
//    970,
//    415,
//    260,
//    260/1.77f
//);
//
//video2->draw(
//    outs[1]->x,
//    outs[1]->y,
//    outs[1]->width,
//    outs[1]->height
//);
//video2->draw(
//    970,
//    585,
//    260,
//    260/1.77f
//);


            if(isMouseOn) color(1);
            else          color(0);
            ofRect(x,y,width,height);


            if(isMouseOn) {
                if(connectingWidget)
                    ofLine(
                        ofGetAppPtr()->mouseX,
                        ofGetAppPtr()->mouseY,
                        connectingWidget->x,
                        connectingWidget->y
                    );
            }

            for (int i=0; i<connections.size(); i++)
            {
            	ofLine(
                    connections[i].first->x,
                    connections[i].first->y,
                    connections[i].second->x,
                    connections[i].second->y
                );
            }
        }


