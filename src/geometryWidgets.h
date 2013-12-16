//
//#ifndef geometrywidgets_h
//#define geometrywidgets_h
//
//class kVectorHolder: virtual public kDragObject {
//    public:
//        kVectorHolder(){ setupVars(); }
//
//        void setupVars() {
//            size=100;
//            zoom=1.0f;
//            collapsing = false;
//        }
//
//        void initialize(){
//
//
//
//            center = ofVec2f(x,y);
//    //            vecs.push_back( shared_ptr<ofVec2f> ( &_widget->pt ));
//            viewMode="collapsed";
//
//
//            shared_ptr<kCircleButton> btn;
//
//
//            for (int i=0; i<10; i++)
//            {
//                btn = make_shared<kCircleButton>();
//                btn->set( x-50+(ofRandomuf()*100),y-50+(ofRandomuf()*100),20,20);
//                btn->setLabel("vec_"+ofToString(i));
//                addWidget(btn);
//            }
//            arrangeWidgets();
//
//        }
//
//        void collapse(){
//            collapsing = true;
//            zoom = 1.0f;
//        }
//
//        virtual void addWidget( shared_ptr<kWidget> _widget ) {
//
//
//            float newX = ( getInRange(_widget->x,x-size,x+size) * 2 ) -1;
//            float newY = ( getInRange(_widget->y,y-size,y+size) * 2 ) -1;
//            vecs.push_back( ofVec2f(newX, newY) );
////            vecs.push_back( ofVec2f(_widget->x, _widget->y) );
//            kWidget::addWidget(_widget);
//        }//                cout << i<<"   "<<vecs[i] << endl;
//
//
//        void scale(float _factor){
//            for (int i=0; i<vecs.size(); i++)
//            {
//            	cout << vecs[i].x << endl;
//            }
//        }
//
///*
//        vector <float> getWidgetAngles() {
//            vector <float> angles;
//            for (int i=0; i<widgets.size(); i++)
//            	angles.push_back(
//                    getAngle(
//                        x,
//                        y
//                        widgets[i]->x,
//                        widgets[i]->y
//                    ));
//            return angles;
//        }
//        vector <float> gfloat angle = v1.angleRad(v2);etWidgetDistances() {
//            vector <float> distances;
//            for (int i=0; i<widgets.size(); i++)
//            	distances.push_back(
//                    getDistance(
//                        x,
//                        y
//                        widgets[i]->x,
//                        widgets[i]->y
//                    ));
//
//            return distances;
//        }
//*/
//
//        void draw(ofEventArgs &args){
//            for (int i=0; i<widgets.size(); i++)
//            {
//            	ofLine(widgets[i]->x,widgets[i]->y,center.x,center.y);
//                ofVec2f pt(1,0);
////                cout << i<<"   "<<vecs[i] << endl;
//            	float angle = getAngle(vecs[i].x,vecs[i].y,0,0) * ( TWO_PI / 360 );
////                ofFill();
//            	ofCircle(center.x+(cos(angle)*45),center.y+(sin(angle)*45),10);
//            }
//            ofNoFill();
//            ofCircle(center.x,center.y,width);
//            ofCircle(center.x,center.y,45);
//
//        }
//
//        void update(ofEventArgs & args){
//            if(collapsing) {
//                zoom-=0.05f;
//                scale(zoom);
//                if(zoom<=0)
//                    collapsing = false;
//            }
//        }
//
//        void arrangeWidgets() {
//            for (int i=0; i<widgets.size(); i++)
//            {
//                widgets[i]->set(
//                    x+(vecs[i].x*zoom*size),
//                    y+(vecs[i].y*zoom*size),
//                    30,30);
//                widgets[i]->arrangeWidgets();
//            }
//
//
//        }
//
//
//        void mouseDragged(ofMouseEventArgs & mouse) {
//            kDragObject::mouseDragged(mouse);
//        }
//
//    string viewMode;
//    float zoom,size;
//    bool collapsing;
//    ofVec2f center;
//    vector<ofVec2f>  vecs;
//
//};
//
//
//
//
//
//#endif geometrywidgets_h
//
