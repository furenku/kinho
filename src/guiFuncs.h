

class SeekVideo: public Functor {

    public:
        SeekVideo( float* _pos, shared_ptr<ofVideoPlayer> _trgt){
            pos = _pos;
            trgt = _trgt;
        }

        void execute() {
            trgt->setPosition(*pos);
        }

        float* pos;
        shared_ptr<ofVideoPlayer> trgt;

};

class CreateRange: public Functor {

    public:
        CreateRange( shared_ptr<Clip> _target, shared_ptr<kRangeHolder> _range, ofColor _color ) {
            target = _target;   start = shared_ptr<float>(&_range->start); end = shared_ptr<float>(&_range->end); color = _color;
        }

        void execute() {
            shared_ptr<Range> range = make_shared<Range>();
            range->start = *start; range->end=*end; range->color=color;
//            target  -> addRange( range );
        }

        shared_ptr<Clip> target;
        ofColor color;
        shared_ptr<float>start; shared_ptr<float> end;

};


class ViewClip: public Functor {
    public:
        ViewClip( shared_ptr<kView> _srcView, shared_ptr<kView> _trgtView ) {
            srcView = dynamic_pointer_cast<kArchiveView>(_srcView);
            trgtView = dynamic_pointer_cast<kEditorView>(_trgtView);
        }


        void execute() {
            trgtView->viewClip(srcView->currentClip);
        }

        shared_ptr<kArchiveView> srcView;
        shared_ptr<kEditorView>  trgtView;

};

class AddClip: public Functor {
    public:
        AddClip( shared_ptr<kView> _src, shared_ptr<kView> _trgt ) {
            src= dynamic_pointer_cast<kClipView>(_src);
            trgt = dynamic_pointer_cast<kClipView>(_trgt);
        }

        void execute() {
            if(src->currentClip){
                bool clipFound = false;

                for (int i=0; i<trgt->widgets.size(); i++)
                {
                    shared_ptr<Clip> clip2 = dynamic_pointer_cast<kClip>(trgt->widgets[i])->clip;
                    if(src->currentClip == clip2)
                        clipFound = true;
                }
                if(!clipFound)
                    trgt->addClip(src->currentClip);

            }
        }

        shared_ptr<kClipView> src;
        shared_ptr<kClipView> trgt;

};


class DropFunc: public Functor {
    public:
        DropFunc( shared_ptr<kWidget> _src, shared_ptr<kWidget> _trgt ) {
            src = _src; trgt = _trgt;
        }


        void execute() {
            if(src->draggingWidget)   {
                trgt -> dropped ( src->draggingWidget );
                src->draggingWidget.reset();
            }
        }

        shared_ptr<kWidget> src,trgt;
};




class SwapViews: public Functor {
    public:
        SwapViews( shared_ptr<kWidget> _src, shared_ptr<kWidget> _trgt ) {
            src = _src; trgt = _trgt;
        }
//        SwapViews( vector<shared_ptr<kWidget> > _srcs, shared_ptr<kWidget> _trgt ) {
//            srcs = _srcs; trgt = _trgt;
//        }
//        SwapViews( shared_ptr<kWidget> _src, vector<shared_ptr<kWidget> > _trgts ) {
//            src = _src; trgts = _trgts;
//        }
//        SwapViews( vector<shared_ptr<kWidget> > _srcs, vector<shared_ptr<kWidget> > _trgts ) {
//            srcs = _srcs; trgts = _trgts;
//        }
//


        void execute() {

                if(trgt)
                    trgt  -> show();
//                if(trgts.size()>0)
//                    for (int i=0; i<trgts.size(); i++)
//                    	trgts[i]->show();

                if(src)
                    src  -> hide();
//                if(srcs.size()>0)
//                    for (int i=0; i<srcs.size(); i++)
//                    	srcs[i]->hide();

        }

        shared_ptr<kWidget> src,trgt;
        vector<shared_ptr<kWidget> > srcs,trgts;
};
