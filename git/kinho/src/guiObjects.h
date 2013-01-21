
#pragma once

// WIDGETS


#ifndef guiobjects_h
#define guiobjects_h




class kButtonView: virtual public kView{
    public:
        kButtonView(){ enableUpdate(); autoArrange=true; createEvents(); command=""; value = 0; boolValue = false; }
        ~kButtonView() {
            hide();
            disable();
            clearWidgets();
        }


        void createEvents() {
            saveEvent("btnClicked");
            saveEvent("btnViewClicked");
            saveEvent("btnDragged");
        }


        void addButtons(vector<string> _labels){

//cout << "addbtn1" << endl;
            clearWidgets();

            labels.clear();
            for (int i=0; i<_labels.size(); i++)
            {
                labels.push_back(_labels[i]);
                btn = make_shared<kCircleButton>();
                btn->setSize(widgetSize);
                btn->setLabel( _labels[i] );
                btn->setMode( TOGGLE_ON );
                if(i==0)    btn->toggle=true;
                else        btn->toggle=false;

                btn->value = i;
                addWidget( btn );

                ofAddListener( *btn->events.lookup("press"),this,&kButtonView::btnClicked);

                btn.reset();

            }

            arrangeWidgets();
////cout << "addbtn2" << endl;
        }

        void removeButtons(){
            for (int i=0; i<widgets.size(); i++)
            {
                btn->disable();
                btn->disableUpdate();
                btn->hide();
                btn = widgets[i];
                addDelete(btn);
                btn->removeFromView();
                removeWidget( btn );

                ofRemoveListener( *btn->events.lookup("press"),this,&kButtonView::btnClicked);

                btn.reset();

            }

            clearWidgets();
        }

        void addDragButtons(vector<string> _labels){

//cout << "addbtn1" << endl;
            clearWidgets();

            labels.clear();
            for (int i=0; i<_labels.size(); i++)
            {
                labels.push_back(_labels[i]);
                btn = make_shared<kCircleDragButton>();
                btn->setSize(widgetSize);
                btn->setLabel( _labels[i] );
                btn->setMode( TOGGLE_ON );
                if(i==0)    btn->toggle=true;
                else        btn->toggle=false;

                btn->value = i;
                addWidget( btn );

                ofAddListener( *btn->events.lookup("press"),this,&kButtonView::btnClicked);
                ofAddListener( *btn->events.lookup("drag"),this,&kButtonView::btnDragged);

                btn.reset();

            }

            arrangeWidgets();
////cout << "addbtn2" << endl;
        }


        void addButton( shared_ptr<kButton> _widget){
            addWidget(_widget);
            labels.push_back( _widget->getLabel() );
            ofAddListener( *_widget->events.lookup("press"),this,&kButtonView::btnClicked);
        }

        void clearWidgets() {

            for (int i=0; i<widgets.size(); i++)
            {
                ofRemoveListener( *widgets[i]->events.lookup("press"),this,&kButtonView::btnClicked);
            }

            kWidget::clearWidgets();


        }

        void btnClicked(widgetEvent & _event){

            shared_ptr<kWidget>sender=dynamic_pointer_cast<kWidget>(_event.sender);

            int index = getWidgetIndex( sender );

            for (int i=0; i<widgets.size(); i++) {
                widgets[i]->toggle=false;
            }

            if(index>=0) {
                widgets[index]->toggle = true;
                value = index;
                if(labels.size()>index)
                    command = labels[index];
            }

            else command = "";

//            cout << value << endl;


            if(value>0) boolValue = true;
            else        boolValue = false;
            notify("btnClicked");

        }


        void btnDragged(widgetEvent & _event){
            shared_ptr<kWidget>sender=dynamic_pointer_cast<kWidget>(_event.sender);
            for (int i=0; i<widgets.size(); i++) {
                if(sender!=widgets[i])
                {
//                    widgets[i]->toggle=false;
                }
            	else {
//            	    widgets[i]->toggle = true;
                    value = i;
                    break;
            	}
            }
//            cout << value << endl;
            if(value<labels.size() )
            command = labels[value];
//
//            if(value>0) boolValue = true;
//            else        boolValue = false;
            notify("btnDragged");

        }

        string getCommand(){
            return command;
        }

        vector<string> labels;
        shared_ptr<kWidget> btn;
        string command;

};

class kRectButtonView: virtual public kButtonView, virtual public kRectView{

    public:
        kRectButtonView(){autoArrange=true;orientation="horizontal";}

//
//        float getX(int _i){
//            return kRectView::getX(_i);
//        }
//
//        float getY(int _i){
//            return kRectView::getY(_i);
//        }

        void mousePressed(ofMouseEventArgs & mouse) {
            kRectView::mousePressed(mouse);
        }

};

class kCircleButtonView: virtual public kButtonView, virtual public kCircleView {
    public:
        kCircleButtonView():kButtonView(){}

//        float getX(int _i){ kCircleView::getX(_i); }
//        float getY(int _i){ kCircleView::getY(_i); }
        void draw(ofEventArgs & args){}
        bool inside(float px, float py){return kCircle::inside(px,py);}

        void mouseMoved(ofMouseEventArgs & mouse) {
            kCircleView::mouseMoved(mouse);
        }
        void mousePressed(ofMouseEventArgs & mouse) {
            kCircleView::mousePressed(mouse);
        }


        void arrangeWidgets() {

//            for (int i=0; i<widgets.size(); i++)
//            {
//            	widgets[i]->hide();
//                widgets[i]->disable();
//            }

            for (int i=0; i<widgets.size(); i++)
            {

                int steps = widgets.size() ;

//                float angle = i/f;

                float posX=x + width * cos(2 * PI * i / steps);
                float posY=y + height * sin(2 * PI * i / steps);

//                float posY=sin( angle*360 / TWO_PI );
//                posY*= height;
//                posY+=y;

            	widgets[i]->setX(posX);
            	widgets[i]->setY(posY);

            }


          //  kView::arrangeWidgets();

        }



};


class kCircleScrollView: virtual public kCircleButtonView {
    public:
        kCircleScrollView() {
            autoArrange=false;
            setupVars();

        }

        void setupVars() {

            numDisplay = 8;
            page = 0;

        }

        void initialize() {

            addBtnView();
        }

        void draw(ofEventArgs & draw) {

            ofCircle(x,y,widgetSize);

        }

        void iiinit() {

            vector<string> labels;

            for (int i=0; i<20; i++)
            {
                labels.push_back(ofToString(i));

            }

            addButtons();

            arrangeWidgets();


//            for (int i=0; i<labels.size(); i++)
//                ofAddListener( *btnView->events.lookup("btnClicked"),this,&kCircleScrollView::btnClicked);


        }

        void arrangeWidgets() {

            for (int i=0; i<widgets.size(); i++)
            {
            	widgets[i]->hide();
                widgets[i]->disable();
            }

            for (int i=0; i<numDisplay; i++)
            {
                int index = (page*numDisplay)+i;
                if( index < widgets.size() ) {

                int steps = numDisplay ;

//                float angle = i/f;

                float posX=x + width * cos(2 * PI * i / steps);
                float posY=y + height * sin(2 * PI * i / steps);

//                float posY=sin( angle*360 / TWO_PI );
//                posY*= height;
//                posY+=y;

            	widgets[index]->setX(posX);
            	widgets[index]->setY(posY);

            	widgets[index]->show();
                widgets[index]->enable();
                }

            }

            if(btnView) {

                if(widgets.size()>numDisplay) {
                    btnView->show();
                    btnView->enable();
                    btnView->setX(x-(btnView->getWidth()/2));
                    btnView->setY(y+height*1.25f);
                }

            }

          //  kView::arrangeWidgets();

        }

        void addButtons(vector<string> _labels){

            kButtonView::clearWidgets();
            kButtonView::addButtons(_labels);

            createPages();
            arrangeWidgets();

        }


/*

codigo de addbuttons:

clearWidgets();

            labels.clear();
            for (int i=0; i<_labels.size(); i++)
            {
                labels.push_back(_labels[i]);
                btn = make_shared<kCircleButton>();
                btn->setSize(widgetSize);
                btn->setLabel( _labels[i] );
                btn->setMode( TOGGLE_ON );
                if(i==0)    btn->toggle=true;
                else        btn->toggle=false;

                btn->value = i;
                addWidget( btn );

                ofAddListener( *btn->events.lookup("press"),this,&kButtonView::btnClicked);

                btn.reset();

            }

            arrangeWidgets();
*/

        void createPages() {

            removeBtnView();

            int pages = ceil( float(widgets.size()) / float(numDisplay) );

            if(pages>1) {

                addBtnView();

                vector<string>strvec;
                for (int i=0; i<pages; i++)
                {
                    strvec.push_back(ofToString(i));
                }

                if(btnView)
                    btnView->addButtons(strvec);

            }

        }

        void addButtons(){
            vector<string> labels;
            for (int i=0; i<25; i++)
            {
            	labels.push_back(ofToString(i));
            }

            addButtons(labels);

        }

        void addBtnView(){
            btnView = make_shared<kRectButtonView>();
            btnView->set(0,0,80.0f,40.0f);
            btnView -> applySettings ( settings  );
            btnView -> setWidgetSettings ( settings );

            addWidget(btnView);

            ofAddListener( *btnView->events.lookup("btnClicked"),this,&kCircleScrollView::pageSelect);

        }


        void removeBtnView(){
            if(btnView) {
                ofRemoveListener( *btnView->events.lookup("btnClicked"),this,&kCircleScrollView::pageSelect);

                view->addDelete(btnView);

                removeWidget(btnView);
                btnView.reset();
//                removeSubView();
                arrangeWidgets();

            }

        }



        void pageSelect(widgetEvent & _event ){

            page = btnView->value;

            arrangeWidgets();
        }




    protected:
        int numDisplay;
        int page;
        shared_ptr<kRectButtonView> btnView;

};

class kScrollBar : virtual public kRectView {

    public:

    kScrollBar() { setupVars(); createEvents(); }
    ~kScrollBar() {
        for (int i=0; i<arrows.size(); i++)
        {
        	arrows[i]->hide();
        	arrows[i]->disable();
        }
        bar->hide();
    }

    void createEvents() {
        saveEvent("scrollUp");
        saveEvent("scrollDown");
        saveEvent("scrollX");
        saveEvent("scrollY");
    }

    void setupVars() {
        orientation = "vertical";
        totalW = width;
        totalH = height;
        barW = width;
        barH = height;
        startX = 0;
        startY = 0;
        scrollStep = 1;
        scroll = 0;
        isDraggingBar = false;

        isDraggable = false;
        autoArrange=false;
    }

    void initialize() {



        vector<ofRectangle>tmpRects;

        if(orientation == "vertical") {

            tmpRects.push_back(ofRectangle(0.0f,0.0f,1.0f,width/height) );
            tmpRects.push_back(ofRectangle(0.0f,width/height,1.0f,1.0f-(width/height)));
            tmpRects.push_back(ofRectangle(0.0f,1.0f-(width/height),1.0f,width/height) );

        }
        if(orientation == "horizontal") {

            tmpRects.push_back(ofRectangle(0.0f,0.0f,height/width,1.0f) );
            tmpRects.push_back(ofRectangle(height/width,0.0f,1.0f-(height/width),1.0f));
            tmpRects.push_back(ofRectangle(1.0f-(height/width),0,height/width,1.0f) );

        }

        shared_ptr<kRectButton> btn;

        for (int i=0; i<tmpRects.size(); i++)
        {
            btn = make_shared<kRectButton>();
        	btn->set(tmpRects[i].x,tmpRects[i].y,tmpRects[i].width,tmpRects[i].height);
            btn->setMode(TOGGLE_OFF);
            btn->value = i;
            addWidget( btn );


            if(i==1) {
                bar = btn;
            }
            else {
                ofAddListener( *btn->events.lookup("press"),this,&kScrollBar::btnClicked);
                arrows.push_back(btn);
            }

        }

        scroll = 0;
        scrollStep = 30;

        startX=0;
        startY=0;
        barH=1.0f;
        barW=1.0f;
        totalW = 1;
        totalH = 1;

        setBar();

    }


    void btnClicked(widgetEvent & event){

        switch( event.sender->value )     {
            case 0:

                if(orientation=="vertical") {
                    if(barH<1.0f) {
                        if(scroll < 0)  scroll +=scrollStep;
                        else            scroll = 0;
                        bar -> set(startX,fabs(scroll/totalH),barW,barH );
                        bar -> setRectInView();
                        notify("scrollUp");
                    }
                }

                break;

            case 1:

                if(orientation=="vertical") {
                    if(barH<1.0f) {
                        if(scroll > (-totalH + height ) )
                                scroll -= scrollStep;
                        else    scroll = (-totalH + height );
                        bar -> set(startX,fabs(scroll/totalH),barW,barH );
                        bar -> setRectInView();
                        notify("scrollDown");
                    }
                }

        }
    }


    void setViewSize ( int _totalW, int _totalH )    {

        if(orientation=="horizontal"){

            totalW = _totalW;
            if(totalW<width-(2*height)) totalW=width-(2*height);
        }


        if(orientation=="vertical") {
            totalH = _totalH;
            if(totalH<height-(2*width)) totalH=height-(2*width);
        }

        setBar();

    }


    void mouseDragged(ofMouseEventArgs & mouse) {
        if( isDraggingBar )  {
            bool scrolled=false;
            float value;

            if(orientation=="vertical") {
                value = getInRange(mouse.y,y+width,y+height-width);

                startY = value;

                if(startY < 1.0f-barH) {
                    scrolled=true;
                    scroll = startY * totalH;
                    scroll *= -1;
                    notify("scrollY");

                }

                barW=1.0f;
                startX=0.0f;
            }
            if(orientation=="horizontal") {
                value = getInRange(mouse.x,x+height,x+width-height);

                startX = value;

                if(startX < 1.0f-barW) {
                    scrolled=true;
                    scroll = startX * totalW;
                    scroll *= -1;
                    notify("scrollX");

                }

                barH=1.0f;
                startY=0.0f;
            }


            if(scrolled)
                setBar();


        }


    }

    void setBar() {
        if(orientation=="vertical") {
            barH = (height-(2*width))/totalH;
            startY=0;
            startY = fabs(scroll/totalH)+width/height;
            startX=0;
            barW=1;
            bar->set(x,y+(startY*(height-2*width)),width,barH*(height-(2*width)));
        }
        else if(orientation=="horizontal") {
            barW = (width-(2*height))/totalW;
            startX=0;
            startX = fabs(scroll/totalW)+height/width;
            startY=0;
            barH=1;
            bar->set(x+(startX*(width-(2*height))),y,barW*(width-(2*height)),height);
        }

        bar->setRectInView();
        arrangeWidgets();

    }


    void mousePressed(ofMouseEventArgs & mouse)   {
        isDraggingBar = false;

        if(inside(mouse.x,mouse.y))
            isDraggingBar = true;

        if(arrows.size()>0)
            if(arrows[0]->inside(mouse.x,mouse.y) ||
               arrows[1]->inside(mouse.x,mouse.y) )
                isDraggingBar=false;


    }

    void mouseReleased(ofMouseEventArgs & mouse)    {
        isDraggingBar = false;
    }


    float getScroll() { return scroll; }

    string getOrientation() { return orientation; }

    shared_ptr<kRectButton> bar;
    vector <shared_ptr<kRectButton> > arrows;

    float totalW,totalH,barW,barH,startX,startY;
    float scrollStep;
    float scroll;

    bool isDraggingBar;


};


class kScrollView: virtual public kRectButtonView {
    public:

    kScrollView(){ setupVars();  }
    virtual ~kScrollView(){
        hide();
        disable();
        for (int i=0; i<scrollBars.size(); i++)
        {
        	scrollBars[i]->hide();
        	scrollBars[i]->disable();
            ofRemoveListener( *scrollBars[i]->events.lookup("scrollUp"),this,&kScrollView::scrollUp);
            ofRemoveListener( *scrollBars[i]->events.lookup("scrollDown"),this,&kScrollView::scrollDown);
            if(scrollBars[i]->getOrientation()=="vertical")
                ofRemoveListener( *scrollBars[i]->events.lookup("scrollY"),this,&kScrollView::doScrollY);
            if(scrollBars[i]->getOrientation()=="horizontal")
                ofRemoveListener( *scrollBars[i]->events.lookup("scrollX"),this,&kScrollView::doScrollX);

        }


    }
    void setupVars() {
        orientation="vertical";
        cols = 2; spacingX=40;spacingY=40; paddingX = spacingX; paddingY = spacingY;
        scrollX = 0;
        scrollY = 0;
        scrollStep =1;
        totalW = 0;
        totalH = 0;
    }

    void show() {
        kView::show();
        for (int i=0; i<scrollBars.size(); i++)
        	scrollBars[i]->show();
    }
    void hide() {
        kView::hide();
        for (int i=0; i<scrollBars.size(); i++)
        	scrollBars[i]->hide();
    }

    void initialize() {

        shared_ptr<kScrollBar> scrollBar;

        if(orientation=="vertical") {
                scrollBar = make_shared<kScrollBar>();

                scrollBar->set(x+width,y,20,height);
                scrollBar->setOrientation("vertical");
                scrollBar->applySettings ( settings );
                scrollBar->setWidgetSettings( settings );
                scrollBar->initialize();

                ofAddListener( *scrollBar->events.lookup("scrollUp"),this,&kScrollView::scrollUp);
                ofAddListener( *scrollBar->events.lookup("scrollDown"),this,&kScrollView::scrollDown);
                ofAddListener( *scrollBar->events.lookup("scrollY"),this,&kScrollView::doScrollY);

                scrollBars.push_back(scrollBar);
        }
        if(orientation=="horizontal") {
                scrollBar = make_shared<kScrollBar>();

                scrollBar->set(x,y+height,width,20);
                scrollBar->setOrientation("horizontal");
                scrollBar->applySettings ( settings );
                scrollBar->setWidgetSettings( settings );
                scrollBar->initialize();

                ofAddListener( *scrollBar->events.lookup("scrollUp"),this,&kScrollView::scrollUp);
                ofAddListener( *scrollBar->events.lookup("scrollDown"),this,&kScrollView::scrollDown);
                ofAddListener( *scrollBar->events.lookup("scrollX"),this,&kScrollView::doScrollX);

                scrollBars.push_back(scrollBar);
        }
        if(orientation=="xy") {

            scrollBar = make_shared<kScrollBar>();
            scrollBar->set(x+width,y,20,height);
            scrollBar->setOrientation("vertical");
            scrollBar->applySettings ( settings );
            scrollBar->setWidgetSettings( settings );
            scrollBar->initialize();

            ofAddListener( *scrollBar->events.lookup("scrollUp"),this,&kScrollView::scrollUp);
            ofAddListener( *scrollBar->events.lookup("scrollDown"),this,&kScrollView::scrollDown);
            ofAddListener( *scrollBar->events.lookup("scrollY"),this,&kScrollView::doScrollY);

            scrollBars.push_back(scrollBar);


            scrollBar.reset();


            scrollBar = make_shared<kScrollBar>();
            scrollBar->set(x,y+height,width,20);
            scrollBar->setOrientation("horizontal");
            scrollBar->applySettings ( settings );
            scrollBar->setWidgetSettings( settings );
            scrollBar->initialize();

            ofAddListener( *scrollBar->events.lookup("scrollUp"),this,&kScrollView::scrollUp);
            ofAddListener( *scrollBar->events.lookup("scrollDown"),this,&kScrollView::scrollDown);
            ofAddListener( *scrollBar->events.lookup("scrollX"),this,&kScrollView::doScrollX);

            scrollBars.push_back(scrollBar);

        }

        arrangeWidgets();

        scrollY=0;
        scrollX=0;

    }

/*
    void addButtons(vector<string> _labels){
        kRectButtonView::addButtons(_labels);
        arrangeWidgets();
    }


    void addDragButtons(vector<string> _labels){
        kRectButtonView::addDragButtons(_labels);
        arrangeWidgets();
    }


    virtual void btnClicked(widgetEvent & _event) {
        kButtonView::btnClicked(_event);
        notify("btnClicked");

    }

    virtual void btnDragged(widgetEvent & _event) {
        kButtonView::btnDragged(_event);

        notify("btnDragged");

    }

*/

    void set (float px, float py, float w, float h){
        DrawObject::set(px,py,w,h);
        updateCanvas();
    }

    virtual void scrollUp(widgetEvent & event) {
        if(scrollY < 0)
            scrollY +=scrollStep;
        else
            scrollY = 0;

        arrangeWidgets();
    }

    virtual void scrollDown(widgetEvent & event) {
        if(scrollY > (-totalH + height ) )
            scrollY -= scrollStep;
        else
            scrollY = (-totalH + height );

        arrangeWidgets();
    }

    void doScrollX(widgetEvent & event)  {
        scrollX = dynamic_pointer_cast<kScrollBar> (event.sender) -> getScroll();
        arrangeWidgets();
    }
    void doScrollY(widgetEvent & event) {
        scrollY = dynamic_pointer_cast<kScrollBar> (event.sender) -> getScroll();
        arrangeWidgets();
    }



    ofPoint getGridXY(int _position) {
        float gridX, gridY;

        if(orientation=="horizontal") {
            gridX = x + scrollX + ((floor(_position /rows)+1) * spacingX);
            gridY = y + scrollY + (((_position % rows)+0.5f) * spacingY);
        }
        else {
            gridX = x + paddingX + scrollX + (((_position % cols)) * spacingX);
            gridY = y + paddingY + scrollY + ((floor(_position / cols)) * spacingY);

        }

        ofPoint pt(gridX,gridY);

        return pt;
    }

    void arrangeWidgets() {
        for (int i=0; i<widgets.size(); i++) {

            if(autoArrange) {
                ofPoint pt = getGridXY(i);
                widgets[i] -> set( pt.x,pt.y,widgets[i]->width,spacingX*0.5f);
            }
            else {

                widgets[i] -> set(
                    x + scrollX + widgetRects[widgets[i]].x*width,
                    y + scrollY + widgetRects[widgets[i]].y*height,
                    widgetRects[widgets[i]].width*width,
                    widgetRects[widgets[i]].height*height
                );
            }

            widgets[i]->hide();


            if(orientation=="vertical") {
                if( inside( widgets[i]->x,
                            widgets[i]->y + widgets[i]->height/3)
                    &&
                    inside( widgets[i]->x,
                            widgets[i]->y - widgets[i]->height/3)
                )

                if(visible) widgets[i]->show();
                else        widgets[i]->hide();

            }
            else if(orientation=="horizontal"){
                if( inside( widgets[i]->x + widgets[i]->width/2,
                            widgets[i]->y)
                    &&
                    inside( widgets[i]->x - widgets[i]->width/2,
                            widgets[i]->y)
                )

                if(visible) widgets[i]->show();
                else        widgets[i]->hide();

            }
            else if(orientation=="xy"){

                if( inside( widgets[i]->x + widgets[i]->width/2,
                            widgets[i]->y + widgets[i]->height)
                    &&
                    inside( widgets[i]->x - widgets[i]->width/2,
                            widgets[i]->y - widgets[i]->height)
                )

                if(visible) widgets[i]->show();
                else        widgets[i]->hide();

            }

            widgets[i]->arrangeWidgets();

        }

        updateCanvas();

        for (int i=0; i<scrollBars.size(); i++)
        {
            switch(i) {
                case 0:
                    scrollBars[i]->set(x+width-20,y,20,height);
                break;
                case 1:
                    scrollBars[i]->set(x,y+height-20,width,20);
                break;

            }
            scrollBars[i]->setViewSize(totalW,totalH);

        }

    }


    virtual void updateCanvas() {
        if(widgets.size()>0) {
            if(orientation=="horizontal") {
                totalW = (widgets.size() / (rows-0.5f) ) * spacingX;
                totalH = rows * spacingY;
            }
            if(orientation=="vertical") {
                totalW = cols * spacingX;
                totalH = (widgets.size() / cols ) * spacingY;
            }

        }
        else {
            totalW = 1.0f;
            totalH = 1.0f;
        }


    }

    float getScrollPctX() {
        float scrollPct;
        if( totalW>0  )
            scrollPct = fabs( scrollX / totalW );
        else
            scrollPct = 0;
        return scrollPct;
    }

    float getScrollPctY() {
        float scrollPct;
        if( totalH>0  )
            scrollPct = fabs( scrollY / totalH );
        else
            scrollPct = 0;
        return scrollPct;
    }


    float getTotalW() { return totalW; }
    float getTotalH() { return totalH; }


    float scrollStep;

    vector< shared_ptr<kScrollBar> > scrollBars;
    float totalW,totalH;
    ofRectangle canvas;


};




class kField2D: public kScrollView{
    public:
        kField2D() {    orientation="xy"; autoArrange = false;    }


        void addWidget(shared_ptr<kWidget> _widget){
            kWidget::addWidget(_widget);
            float threshold;
            threshold=2*WIDGET_SIZE;

            float offsetX, offsetY;
            offsetY = _widget->getY()+height/3;
            offsetX = _widget->getX()+width/3;

            if( _widget->getX() <= x+threshold) {
                //ADD WIDTH
                totalW += offsetX;

                // SHIFT ALL WIDGETS RIGHT
                for (int i=0; i<widgets.size(); i++)
                	widgets[i]->setX( widgets[i]->getX()  + offsetX );

            }
            if( _widget->getX() >= x+totalW-threshold) {
                //ADD WIDTH
                totalW += offsetX;
            }
            if( _widget->getY() <= y+threshold) {
                //ADD H
                totalH += offsetY;
                // SHIFT ALL WIDGETS DOWN
                for (int i=0; i<widgets.size(); i++)
                	widgets[i]->setY( widgets[i]->getY()  + offsetY );
            }
            if( _widget->getY() >= y+totalH-threshold) {
                //ADD H
                totalH += offsetY;
            }
            _widget->setRectInView();
            arrangeWidgets();


            for (int i=0; i<scrollBars.size(); i++)
            {
                switch(i) {
                    case 0:
                        scrollBars[i]->set(x+width-20,y,20,height);
                    break;
                    case 1:
                        scrollBars[i]->set(x,y+height-20,width,20);
                    break;

                }
                scrollBars[i]->setViewSize(totalW,totalH);

            }

        }

        void updateCanvas() {
/*
            float minX,minY,maxX,maxY=0;

            if(widgets.size()>0){
                ofRectangle rect = widgets[0]->getRectInView();
                minX=maxX=rect.x;
                minY=maxY=rect.y;
            }
            for (int i=0; i<widgets.size(); i++)
            {
                ofRectangle w = widgets[i]->getRectInView();
            	if(w.x < minX){ minX = w.x; }
            	if(w.y < minY){ minY = w.y; }
            	if(w.x > maxX){ maxX = w.x; }
            	if(w.y > maxY){ maxY = w.y; }

                totalW = (fabs(maxX-minX)*width)+width/3;
                totalH = (fabs(maxY-minY)*height)+height/3;

            }

            for (int i=0; i<scrollBars.size(); i++)
            {
            	scrollBars[i]->setViewSize(totalW,totalH);
            }
*/
        }






        void setScroll() {

            arrangeWidgets();

        }


        void mousePressed(ofMouseEventArgs & mouse)   {

            if( inside(mouse.x,mouse.y) && !mouseOnWidgets() )
            isBeingDragged = false;


        }

        void mouseReleased(ofMouseEventArgs & mouse)    {
            isBeingDragged = false;
        }



    protected:


    bool isDraggingField;
};


class kSlider:virtual public kScrollBar{
    public:
    kSlider(){}
    void initialize() {
        kScrollBar::initialize();
        fvalue=0.5f;
        startY=0.5f;
        setBar();
    }

    void setBar() {
        if(orientation=="vertical") {
            barH = 0.1f;
            startY=fvalue*(1.0f-barH);
            startX=0;
            barW=1;
            bar->set(x,y+width+(startY*(height-2*width)),width,barH*(height-(2*width)));

        }
        else {
            barW = 0.1f;
            startX=0;
            startX = fvalue*(1.0f-barW);
            startY=0;
            barH=1;
            bar->set(x+height+(startX*(width-(2*height))),y,barW*(width-(2*height)),height);
        }

        bar->setRectInView();
        arrangeWidgets();

    }

    void mouseDragged(ofMouseEventArgs & mouse) {
        if( isDraggingBar )  {
            if(orientation=="vertical")
                fvalue = getInRange(mouse.y,y+width,y+height-width);
            else
                fvalue = getInRange(mouse.x,x+height,x+width-height);

            setBar();
        }
    }


};



class kKnob: public kButton {
    public:

    kKnob()
    {
//        isSelectable    =   false;
//        isDraggable     =   false;
        width = 0;
        height = 0;

        createEvents();

        angle = 0;
        value = 0;

        rangeStart=0.0f;
        rangeEnd=1.0f;
        value=rangeStart;
    }

    void createEvents() { saveEvent("knobDrag"); }


    float angle,value;

    float rangeStart,rangeEnd;

    //{ functions:

    void draw( ofEventArgs & args ){

        float valueAngle;
        int w;
        if(isMouseOn)   w = width+2;
        else            w = width;

        ofSetColor(30,30,30,127);
        ofCircle(x,y,width);

        ofSetColor(130,130,130,127);

        valueAngle=(value-rangeStart)/(rangeEnd-rangeStart);
        ofCircle(x+((width-(width/3))*cos(valueAngle*2*PI)),
                 y+((width-(width/3))*sin(valueAngle*2*PI)),
                 width/4);

        ofLine(x+(width-10),y,x+width,y);

        ofDrawBitmapString(ofToString(value,3),x-20,y);
        ofDrawBitmapString(label,x-20,y-20);

    }

    void mouseMoved(ofMouseEventArgs & mouse)    {

        int d = sqrt(pow(x-mouse.x,2)+pow(y-mouse.y,2));

        if(d<width)    isMouseOn=true;
        else       isMouseOn=false;

    }

    void mouseDragged(ofMouseEventArgs & mouse)  {
        if(isBeingDragged)    {
            hasBeenDragged=true;
            angle=getAngle(mouse.x,mouse.y,x,y);
            value=((angle/360.0f)*(rangeEnd-rangeStart))+rangeStart;

            notify("knobDrag");


        }

    }

    void mousePressed(ofMouseEventArgs & mouse)  {

        if(isMouseOn)       isBeingDragged=true;
        else                isBeingDragged=false;
    }

    void mouseReleased(ofMouseEventArgs & mouse)  {
        isBeingDragged=false;
    }


    //}

};





class kButtonTree: virtual public kRectButtonView{
    public:

        kButtonTree(){ createEvents(); autoArrange=true; value=0; }


        void createEvents() {
            saveEvent("btnClicked");
            saveEvent("btnDragged");
        }


        virtual void addCol(vector<string> _labels){

//            btnViews.push_back( make_shared<kRectButtonView>() );
//            btnViews.back() -> set(0,0,width/4,height);
//            btnViews.back() -> applySettings ( settings  );
//            btnViews.back() -> setWidgetSettings ( settings );
//
//            btnViews.back() -> addButtons(_labels);
//
//            for (int i=0; i<_labels.size(); i++)
//                ofAddListener( *btnViews.back()->events.lookup("btnClicked"),this,&kButtonTree::btnClicked);
//
//            addWidget(btnViews.back() );
//
//            arrangeWidgets();


        }

        void removeCol(int _i){
//            if(btnViews[_i]) {
//                for (int i=0; i<btnViews[_i]->widgets.size(); i++)
//                    ofRemoveListener( *btnViews[_i]->events.lookup("btnClicked"),this,&kButtonTree::btnClicked);
//
//                addDelete(btnViews[_i]);
//
//                removeWidget(btnViews[_i]);
//                btnViews[_i].reset();
//                btnViews.erase(btnViews.begin()+_i);
//                arrangeWidgets();
//            }
        }

        void clearWidgets() {
            for (int i=0; i<widgets.size(); i++)
            {
                ofRemoveListener( *widgets[i]->events.lookup("press"),this,&kButtonTree::btnClicked);
            }

            kWidget::clearWidgets();


        }




        void btnClicked(widgetEvent & _event){

            removeCol(1);
            labels.clear();
            labels.push_back("aaa");
            labels.push_back("bbb");
            addCol(labels);
//            shared_ptr<kWidget>sender=dynamic_pointer_cast<kWidget>(_event.sender);
//            for (int i=0; i<widgets.size(); i++) {
//                if(sender!=widgets[i])
//                {
//                    widgets[i]->toggle=false;
//                }
//            	else {
//            	    widgets[i]->toggle = true;
//                    value = i;
//            	}
//            }
//
//            command = labels[value];
//
//            if(value>0) boolValue = true;
//            else        boolValue = false;
//            notify("btnClicked");

        }


        vector<string> labels;
        shared_ptr<kWidget> btn;
        string command;

        vector< shared_ptr<kButtonView> > btnViews;

};



//--------------------------------------------------------------

class TextBox: public kRectButton {
    public:
        TextBox(shared_ptr<Settings> _settings ){
            createEvents();
            settings = _settings;
            font = settings->font.back();
            isDraggable = false;
            reset();
            hasFocus = false;
            enable();

        }


        void createEvents() {
            saveEvent("enter");
            saveEvent("focus");
            saveEvent("unfocus");
        }

        void reset ()  {
            str = "";
            drawStr = "...";
            hasFocus = false;
        }


        void draw(ofEventArgs & args) {

            ofSetColor(0);
            ofFill();
            ofRect(x,y,width,height);

            ofNoFill();
            ofSetColor(60);
            drawString(label, x+5, y-height  );

            ofRect(x,y,width,height);

            drawString(drawStr, x+5, y+height*0.8  );


            if( hasFocus )  {
                if(isMouseOn)
                ofSetColor(255);
                ofNoFill();
                ofRect(x,y,width,height);
            }
    //            cursorCounter++;
    //            cursorCounter%=FPS;
    //            if(cursorCounter==0)
    //                showCursor = ! showCursor;
    //
    //            if(showCursor)
    //                font.drawString("|",
    //                    x + font.stringWidth( str.substr( 0, cursorPos ) ),
    //                    y + h );
    //        }

        }

        void setText(string _str){
            str=_str;
            drawStr=str;
        }

        void setText(float _value){
            str=ofToString(_value);
            drawStr=str;
        }

        void setText(int _value){
            str=ofToString(_value);
            drawStr=str;
        }

        void addKey( int key ) {
            if(hasFocus){

                bool isChar=true;

                switch(key) {

                    case 356:   //left
    //                            cursorPos--;
    //                            if(cursorPos<=0) cursorPos = 0;
                                isChar = false;
                                break;
                    case 357:   //up
    //                            cursorPos--;
    //                            if( cursorPos <= 0 ) cursorPos = 0;
                                isChar = false;
                                break;
                    case 358:   //right
    //                            cursorPos++;
    //                            if( cursorPos >= str.size() ) cursorPos = str.size();
                                isChar = false;
                                break;
                    case 359:   //down
                                isChar = false;
                                break;

                    case 8:     // backspace:
                                if(str.size()>0)    {
                                    str = str.substr(0, str.size()-1);
                                }
                                isChar = false;
                                break;
                    case 13:    // enter:
                                notify("enter");
                                isChar = false;
                                break;

                }

                if(isChar)  {
    //                if( cursorPos == str.size() )
                        str.append (1, (char)key );
    //                else
    //                    str.insert ( cursorPos, 1, (char)key );

    //                cursorPos++;

                }


                drawStr = str;

                if(font)
                    while( font->stringWidth(drawStr) > width ) {
                        drawStr.erase(0,1);
                    }
            }

        }

        void enable(){
            MouseObject::enable();
            ofAddListener(ofEvents.keyPressed, this, &TextBox::keyPressed);
        }

        void disable(){
            MouseObject::disable();
            ofRemoveListener(ofEvents.keyPressed, this, &TextBox::keyPressed);
        }

        void keyPressed(ofKeyEventArgs & key)    {
            if(hasFocus)
                addKey( key.key );
        }



        void mouseReleased(ofMouseEventArgs & mouse)   {
            if(enabled) {
                if(!hasBeenDragged)
                    if(isMouseOn) focus();
                    else        unFocus();
            }
            MouseObject::mouseReleased(mouse);
        }


        void focus(){
            hasFocus = true;
            notify("focus");
        }


        void unFocus(){
            hasFocus = false;
            notify("unfocus");
        }



        shared_ptr<ofTrueTypeFont> font;

        bool hasFocus;

        string str,drawStr;

};


class TextInput: virtual public kRectView, virtual public TextBox {
    public:
    TextInput(shared_ptr<Settings> _settings ):TextBox(_settings) {
        createEvents();
        settings = _settings;
        applySettings(settings);
        setWidgetSettings(settings);
        autoArrange=false;
        height = TEXT_SIZE * 1.5f;
        isDraggable = false;
        int offset = ( height - ( TEXT_SIZE * 1.2f ) ) / 2;

        textBox        =   make_shared<TextBox>( _settings );
        textBox->set(0.0f,0.0f,0.9f,1.0f);
        addWidget(textBox);

        submitBtn      =   make_shared<kButton>();
        submitBtn->set(0.9f,0.0f,0.1f,1.0f);
        submitBtn->notify("press");
        addWidget(submitBtn);

        shouldResetAfterSubmit = true;
        enable();
    }

    void createEvents() {
        saveEvent("submit");
    }

    void set(float _x, float _y, float _w, float _h) {
        x=_x;
        y=_y;
        width=_w;
        height=_h;
        arrangeWidgets();
    }

    void draw(ofEventArgs & args) {
    }

    void enable()   {
//        ofAddListener(*submitBtn->events.lookup("press"),this,&TextInput::submit);
    }
    void disable()   {
//        ofRemoveListener(*submitBtn->events.lookup("press"),this,&TextInput::submit);
    }

    void submit(widgetEvent & _event){
        notify("submit");
        if(shouldResetAfterSubmit) {
            textBox -> reset();
        }
    }

    void addKey ( int key ) {
        if(hasFocus)
            textBox -> addKey( key );
    }

    shared_ptr<TextBox> textBox;
    shared_ptr<kButton> submitBtn;


    bool shouldResetAfterSubmit;

};

//-----



class kDropDown: virtual public kRectView {
    public:
        kDropDown(){ autoArrange = false; createEvents(); }
        ~kDropDown() {
            ofRemoveListener( *text->events.lookup("focus"),this,&kDropDown::displayList);
            ofRemoveListener( *text->events.lookup("unfocus"),this,&kDropDown::hideList);


        }


        void createEvents(){
            saveEvent("dropDownSelect");
        }


        void initialize() {

            displaying = false;

            text = make_shared<TextBox>( widgetSettings );
            text->setText("test01");
            text->set(0,0,1.0f,1.0f);

            ofAddListener( *text->events.lookup("focus"),this,&kDropDown::displayList);
            ofAddListener( *text->events.lookup("unfocus"),this,&kDropDown::hideList);

            list = make_shared<kScrollView>();
            list->set(0,1.0f,1.0f,8.0f);
            list->setCols(1);
            list->setOrientation("vertical");
            list->setPaddingX(10);
            list->setPaddingY(30);
            ofAddListener( *list->events.lookup("btnClicked"),this,&kDropDown::btnClicked);

            list->setSpacingX(50);
//            list->setSpacingY(height*2);

            addWidget( text );
            addWidget( list );


            list->initialize();


            list->hide();

        }

        void displayList(widgetEvent & _event){

            displaying = !displaying;

            if(displaying) {
                list->show();
                list->enable();
                arrangeWidgets();
            }
            else {
                list->hide();
                list->disable();
            }

        }

        void hideList(widgetEvent & _event){
            displaying = false;
            list->hide();
            list->disable();

        }

        void addOptions(vector<string> _options) {

            options = _options;

            shared_ptr<kLabelButton> btn;

            for (int i=0; i<_options.size(); i++)
            {
                btn=make_shared<kLabelButton>();
                btn->set(0,0,width*0.8f,height);
                btn->setLabel( "lbl" + ofToString(options[i]) );
                list->addButton(btn);
            }


            arrangeWidgets();


        }


        void btnClicked(widgetEvent & _event){

            string command = dynamic_pointer_cast<kButtonView>(_event.sender)->getCommand();

            text->setText( command );

            notify("dropDownSelect");

        }

//        addWidget( clip );
//        if(!visible) clip->hide();
//        arrangeWidgets();
        vector<string> options;
        shared_ptr<TextBox> text;
        shared_ptr<kScrollView> list;
        bool displaying;
};



class kNode: virtual public kCircleButton{
    public:
        kNode(){}

        vector <shared_ptr<kNode> > parents;
        vector <shared_ptr<kNode> > silblings;
        vector <shared_ptr<kNode> > children;

};




//--------------------------------------------------------------
/*
class Node: public Button  {
    public:
    Node(int _x, int _y, int _s, string _type, int _id, Object * _target):Button(_x,_y,_s,_type,_id,_target)
    {
        parent          =   NULL;
        isConnecting    =   false;
        isPlaying       =   false;

        isDraggable = true;

        targetScreen    =   0 ;
    }
    virtual ~Node() {
        disable();
        for ( int i = 0; i < connectors.size() ; i++ )
        {
        	delete connectors[i];
        }
        connectors.clear();
        descendants.clear();
        children.clear();

    }


    //--------------------------------------------------------------
    void drawConnections(){
//        if(hasBeenCreated)  {
        if(isConnecting)    {
            ofSetColor(0x444444);
            ofLine(x,y,mouseX,mouseY);
        }
        else
            if(parent!=NULL){
                ofSetColor(0xAAAAAA);
                ofLine(x,y,parent->x,parent->y);
            }
//        }
    }

    //--------------------------------------------------------------
    void draw(){
        ofCircle(x,y,s);
    }

    //--------------------------------------------------------------
    void mouseReleased(ofMouseEventArgs & mouse)   {


        if(!isConnecting)  {
            if(mouseOn) if(!hasBeenDragged) click();
            hasBeenDragged  =   false;
            isBeingDragged  =   false;
            isSelected      =   false;

            mouseX = mouse.x;
            mouseY = mouse.y;

        }


        if(isConnecting)    {

            target->getCall( this, "attemptNodeConnection", id);

            isConnecting=false;

            updateConnectors();

        }

        Object::mouseReleased(mouse);

    }

    //--------------------------------------------------------------
    void mousePressed(ofMouseEventArgs & mouse) {
        Object::mousePressed(mouse);

        recordX=mouse.x;
        recordY=mouse.y;

        hasGotDescendants=false;

    }

    //--------------------------------------------------------------
    void mouseDragged(ofMouseEventArgs & mouse) {

        Object::mouseDragged(mouse);

        if(isBeingDragged)  {

            if(!hasGotDescendants)  {
                getDescendants();
                getDescendantsXY();
            }

            updateConnectors();
            for(int i=0; i<children.size(); i++){
                children[i]->updateConnectors();
            }

            for(int i=0; i<descendants.size(); i++){
                descendants[i]->x = descendantsX[i]+(mouse.x-recordX);
                descendants[i]->y = descendantsY[i]+(mouse.y-recordY);
                descendants[i]->updateConnectors();
            }

        }

    }

    //--------------------------------------------------------------
    void mouseMoved(ofMouseEventArgs & mouse) {

        Object::mouseMoved(mouse);

        if(isConnecting)
            updateConnectors();
    }


    //--------------------------------------------------------------
    void updateConnectors(){

        float angle;

        if(isConnecting)
            angle = getAngle( mouseX, mouseY, x, y ) * ( TWO_PI / 360 );
        else
            if(parent!=NULL)
                angle = getAngle( parent->x, parent->y, x, y ) * ( TWO_PI / 360 );
            else
                angle = getAngle( x, y - ( s * 0.6 ), x, y ) * ( TWO_PI / 360 );

        for(int i =0; i<connectors.size(); i++)    {
            connectors[i]->x=x + ( cos( angle ) * ( s * 0.6 ) );
            connectors[i]->y=y + ( sin( angle ) * ( s * 0.6 ) );
        }

    }


    //--------------------------------------------------------------
    void getCall( Object * source, string message, float param){

        if(allowCalls)  {
            if(message == "connector") {
                isConnecting  =   true;
            }
        }
    }


    //--------------------------------------------------------------
    void getDescendants()    {

        descendants.clear();
        getAllChildren(this);
        hasGotDescendants=true;

    }


    //--------------------------------------------------------------
    void getDescendantsXY()  {
        descendantsX.clear();
        descendantsY.clear();

        for (int i=0; i<descendants.size(); i++ )
        {
        	descendantsX.push_back(descendants[i]->x);
            descendantsY.push_back(descendants[i]->y);
        }

    }


    //--------------------------------------------------------------
    void getAllChildren(Node * parentNode)  {

        // using recursion to find all nodes
        // (based on http://stackoverflow.com/questions/177277/how-to-get-a-list-of-all-child-nodes-in-a-treeview-in-net)
        for(int i = 0 ; i<parentNode->children.size(); i++)  {
            descendants.push_back(parentNode->children[i]);
            getAllChildren(parentNode->children[i]);
        }
    }


    //--------------------------------------------------------------
    int getBranch(Node * descendantNode )    {

        int currentBranch;

            bool foundRoot = false;

            for (int i=0; i<children.size(); i++ )
            {
                if( children[i] == descendantNode ) {
                    currentBranch = i;
                    foundRoot = true;
                    break;
                }
            }

            for (int i=0; i<children.size(); i++ )
            {
                children[i]->getDescendants();
                for (int j = 0; j < children[ i ] -> descendants.size(); j++ )
                {
                    if( children[ i ]->descendants[ j ] == descendantNode )    {
                        currentBranch = i;
                        foundRoot = true;
                        break;
                    }

                    if(foundRoot)   break;
                }
            }

        return currentBranch;

    }



    bool hasBeenCreated;

    bool isConnecting;


    Node * parent;
    vector<Node*> children;

    vector <Node*> descendants;

    vector <int> descendantsX;
    vector <int> descendantsY;

    int targetScreen;

/&/    vector<Button *> demásconnectors;

    int recordX,recordY;

    bool hasGotDescendants;

    bool isPlaying;



};

*/





/*
class kDigit: public kRectButton{
    public:
        kDigit(){}

        int getValue(int amount){
            value += amount;
            value%=10;
        }


        void mousePressed(ofMouseEventArgs & mouse) {

        }
        void mouseDragged(ofMouseEventArgs & mouse) {
        }



};

*/

#endif
