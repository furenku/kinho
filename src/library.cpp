#include "library.h"


void LibraryManager::addMedia(shared_ptr<MediaHolder> _media){
    media.push_back(_media);
}

void LibraryManager::addMedia(shared_ptr<MediaHolder> _media, shared_ptr<Ontology> _ont){
    media.push_back(_media);

    setHierarchy(_ont, _media);

    setOntology(_ont,_media);
}

void LibraryManager::removeMedia(shared_ptr<MediaHolder> _media){
    vector< shared_ptr<StoreObject> > v;
    for (int i=0; i<media.size(); i++)
    	v.push_back(media[i]);
    int index=getIndexByName(v,_media->getName());
    if(index>=0)
        media.erase(media.begin()+index);
    removeObject(_media);
}
        //ontology
void LibraryManager::addOntology(shared_ptr<Ontology> _ont){

    string type = _ont->getType();

    if(type=="tag"){
        vector< shared_ptr<StoreObject> > v;
        for (int i=0; i<tags.size(); i++)
            v.push_back(tags[i]);
        int index=getIndexByName(v,_ont->getName());
        if(index==-1)
            tags.push_back(dynamic_pointer_cast<Tag>(_ont));
        else
            cout << "tag "<<_ont->getName()<<" is already there" << endl;
    }
    if(type=="category"){
        vector< shared_ptr<StoreObject> > v;
        for (int i=0; i<categories.size(); i++)
            v.push_back(categories[i]);
        int index=getIndexByName(v,_ont->getName());
        if(index==-1)
            categories.push_back(dynamic_pointer_cast<Category>(_ont));
        else
            cout << "cat "<<_ont->getName()<<" is already there" << endl;
    }
}
void LibraryManager::removeOntology(shared_ptr<Ontology> _ont){
    if(type=="tag"){
        vector< shared_ptr<StoreObject> > v;
        for (int i=0; i<tags.size(); i++)
            v.push_back(tags[i]);
        int index=getIndexByName(v,_ont->getName());
        if(index!=-1)
            tags.erase(tags.begin()+index);
    }
    if(type=="category"){
        vector< shared_ptr<StoreObject> > v;
        for (int i=0; i<categories.size(); i++)
            v.push_back(categories[i]);
        int index=getIndexByName(v,_ont->getName());
        if(index!=-1)
            categories.erase(categories.begin()+index);
    }
}



void LibraryManager::loadMedia(){}

void LibraryManager::loadOntologies(){}

void LibraryManager::setOntology(shared_ptr<Ontology> _ont, shared_ptr<MediaHolder> _obj){
    string type = _ont->getType();

    if(type=="category"){
        vector<shared_ptr<StoreObject> > & vp = getParents(_obj);
        vp.clear();
    }

    setHierarchy(_ont, _obj);

}

void LibraryManager::setOntology(shared_ptr<Ontology> _ont, vector< shared_ptr<MediaHolder> > _objs){
    string type = _ont->getType();

    for (int i=0; i<_objs.size(); i++)
    {
        if(type=="category"){
            vector<shared_ptr<StoreObject> > & vp = getParents(_objs[i]);
            vp.clear();
        }

        setHierarchy(_ont, _objs[i]);
    }



}
void LibraryManager::desetOntology(shared_ptr<Ontology> _ont, shared_ptr<MediaHolder> _obj){
    removeHierarchy(_ont,_obj);
}
void LibraryManager::desetOntology(shared_ptr<Ontology> _ont, vector< shared_ptr<MediaHolder> > _objs){
    for (int i=0; i<_objs.size(); i++)
        removeHierarchy(_ont, _objs[i]);
}


void LibraryManager::setOntology( string _ontname, shared_ptr<MediaHolder> _obj){


    setHierarchy( getOntology(_ontname), _obj);


}



//get

// media
shared_ptr<MediaHolder> LibraryManager::getMedia(string _name){
    vector< shared_ptr<StoreObject> > v;
    for (int i=0; i<media.size(); i++)
        v.push_back(media[i]);
    int index=getIndexByName(v,_name);
    if(index!=-1)
        return media[index];
}

vector< shared_ptr<MediaHolder> > LibraryManager::getMedia(shared_ptr<Ontology> _ont){
    vector< shared_ptr<StoreObject> > & vc = getChildren(_ont);
    vector< shared_ptr<MediaHolder> > c;
    for (int i=0; i<vc.size(); i++)
    {
        if( vc[i]->getType()=="media" ||
            vc[i]->getType()=="clip" ||
            vc[i]->getType()=="sample" ||
            vc[i]->getType()=="text"    )
            c.push_back(dynamic_pointer_cast<MediaHolder>(vc[i]));
    }


    return c;
}

vector< shared_ptr<MediaHolder> > & LibraryManager::getMedia(){
    return media;
}



// clips
shared_ptr<Clip> LibraryManager::getClip(string _name){
    vector< shared_ptr<StoreObject> > v;

    for (int i=0; i<media.size(); i++)
        if(media[i]->getType()=="clip")
            v.push_back(media[i]);

    if(v.size()>0) {
        int index=getIndexByName(v,_name);
        if(index!=-1)
            return dynamic_pointer_cast<Clip>(media[index]);
    }


}

vector< shared_ptr<Clip> > LibraryManager::getClips(shared_ptr<Ontology> _ont){
    vector< shared_ptr<StoreObject> > & vc = getChildren(_ont);
    vector< shared_ptr<Clip> > c;

//    cout << vc.size() << endl;
    for (int i=0; i<vc.size(); i++)
    {
        shared_ptr<Clip> clip = dynamic_pointer_cast<Clip>(vc[i]);
//        cout << "ok" << endl;
        if( clip->getType()=="clip" ){
//            cout << "get ontology clip: "<< clip->getName() << endl;
            c.push_back( clip );
        }
    }
    return c;
}

vector< shared_ptr<Clip> > & LibraryManager::getClips(){
    return clips;
}


// samples
shared_ptr<Sample> LibraryManager::getSample(string _name){
//    vector< shared_ptr<StoreObject> > v;
//    for (int i=0; i<samples.size(); i++)
//        v.push_back(samples[i]);
//    int index=getIndexByName(v,_name);
//    if(index!=-1)
//        return dynamic_pointer_cast<Sample>(media[index]);
}

vector< shared_ptr<Sample> > LibraryManager::getSamples(shared_ptr<Ontology> _ont){
//    vector< shared_ptr<StoreObject> > v;
//
//    for (int i=0; i<media.size(); i++)
//        if(media[i]->getType()=="sample")
//            v.push_back(media[i]);
//
//    if(v.size()>0) {
//        int index=getIndexByName(v,_name);
//        if(index!=-1)
//            return dynamic_pointer_cast<Sample>(media[index]);
//    }
//    else {
//        return 0;
//    }
}

vector< shared_ptr<Sample> > LibraryManager::getSamples(){
    return samples;
}



shared_ptr<Ontology> LibraryManager::getOntology( string _name ){
    vector< shared_ptr<StoreObject> > v;
    for (int i=0; i<tags.size(); i++)
        v.push_back(tags[i]);
    int index=getIndexByName(v,_name);
    if(index!=-1)
        return tags[index];

    v.clear();

    for (int i=0; i<categories.size(); i++)
        v.push_back(categories[i]);
    index=getIndexByName(v,_name);

    if(index!=-1)
        return categories[index];

}
//shared_ptr<Ontology> LibraryManager::getOntology(int id){}

vector< shared_ptr<Ontology> > LibraryManager::getOntologies(shared_ptr<MediaHolder> _media){
    vector< shared_ptr<StoreObject> > vp;
    vector< shared_ptr<Ontology> > vo;

    vp = getParents(_media);

    for (int i=0; i<vp.size(); i++)
    {
    	if(vp[i]->getType()=="tag"||vp[i]->getType()=="category"){
            vo.push_back(dynamic_pointer_cast<Ontology>(vp[i]));
    	}
    }
    return vo;

}


vector< shared_ptr<Ontology> > LibraryManager::getOntologies(string _type) {
    vector< shared_ptr<Ontology> > v;

    if(_type=="tag"){
        for (int i=0; i<tags.size(); i++)
            v.push_back(tags[i]);
        return v;
    }
    if(_type=="category"){
        for (int i=0; i<categories.size(); i++)
            v.push_back(categories[i]);
        return v;
    }

}

vector< shared_ptr<Ontology> > LibraryManager::getOntologies(){
    vector< shared_ptr<Ontology> > v;
    for (int i=0; i<tags.size(); i++)
        v.push_back(tags[i]);
    for (int i=0; i<categories.size(); i++)
        v.push_back(categories[i]);

    return v;

}



vector< shared_ptr<Ontology> > LibraryManager::getChildOntologies(shared_ptr<Ontology> _ontology){


    vector< shared_ptr < StoreObject > > allChildren;

    vector< shared_ptr < Ontology > > onts;

    allChildren= getChildren(_ontology);

    for (int i=0; i<allChildren.size(); i++)
    {

    string type = allChildren[i]->getType();

    if(type == "tag" || type == "category" || type == "ontologyObject" ||
    type == "place" || type == "action" || type == "web")
        onts.push_back( dynamic_pointer_cast<Ontology>(allChildren[i]));

    }

    return onts;
}









shared_ptr<kBrowseArchive> Library::getView(){ return view; }


void Library::btnClicked(widgetEvent & _event){
    shared_ptr<kBrowseArchive> browse;
    browse = dynamic_pointer_cast<kBrowseArchive>(_event.sender);
//    cout << "row "<<browse->getClickedRow() << endl;
    string ontname = browse->getCommand();
//    cout << ontname << endl;

//    view->clearClips();
    browse->removeAllViews();
    shared_ptr<Ontology> ont = getOntology( ontname );

    vector< shared_ptr < MediaHolder > > media = getMedia( ont );
//

//    cout << getChildOntologies( ont ).size() << endl;

    draggingOntology = ontname;

    vector< shared_ptr < Clip > > clips;
    vector< shared_ptr < Sample > > samples;

    for (int i=0; i<media.size(); i++)
    {
    	if(media[i]->getType()=="clip")
            clips.push_back(dynamic_pointer_cast<Clip>(media[i]));
    	if(media[i]->getType()=="sample")
            samples.push_back(dynamic_pointer_cast<Sample>(media[i]));
    }

    browse->loadMediaViews();

    browse->addMedia( clips, samples );


}


void Library::btnDragged(widgetEvent & _event){

    shared_ptr<kBrowseArchive> browse;
    browse = dynamic_pointer_cast<kBrowseArchive>(_event.sender);
    string ontname = browse->getCommand();

    draggingOntology = ontname;

}


void Library::clipClicked(widgetEvent & _event){

    shared_ptr<kBrowseArchive> browse;
    browse = dynamic_pointer_cast<kBrowseArchive>(_event.sender);
    nextClip = browse->clickedClip;

    draggingOntology = "";
}


void Library::clipDragged(widgetEvent & _event){

    shared_ptr<kBrowseArchive> browse;
    browse = dynamic_pointer_cast<kBrowseArchive>(_event.sender);
    draggingClip = browse->draggingClip;

    draggingOntology = "";
}


void Library::initView(){

    view = make_shared<kBrowseArchive>( );
    view->set(30,50,250,700);
    ofAddListener( *view->events.lookup("buttonClicked"),this,&Library::btnClicked);
    ofAddListener( *view->events.lookup("buttonDragged"),this,&Library::btnDragged);
    ofAddListener( *view->events.lookup("clipClicked"),this,&Library::clipClicked);
    ofAddListener( *view->events.lookup("clipDragged"),this,&Library::clipDragged);
//    ofAddListener( *view->events.lookup("clipClicked"),this,&Library::clipClicked);

};

void Library::loadView(){

//    shared_ptr<Category> cat = make_shared<Category>( );
//    cat->setName("uncat");
//    addOntology(cat);

    shared_ptr<Tag> tag = make_shared<Tag>( );
    tag->setName("tag1");
    addOntology(tag);

    tag = make_shared<Tag>( );
    tag->setName("tag2");
    addOntology(tag);

    vector <string> strs;    view->applySettings ( settings );
    view->setWidgetSettings( widgetSettings );

    vector< shared_ptr < Ontology > > onts = getOntologies("category");
    for (int i=0; i<onts.size(); i++)
        strs.push_back( onts[i]->getName() );

    view->addCol( strs );

    strs.clear();

    vector< shared_ptr < Ontology > > onts2 = getOntologies("tag");
    for (int i=0; i<onts2.size(); i++)
        strs.push_back( onts2[i]->getName() );

    view->addCol( strs );
//    view->createClipView();
//    setClips();

//    view->clearWidgets();


    view->initMediaViews();

}


void Library::setClips(){
//    vector< shared_ptr < Clip > > media = getMedia();
//    view->addClips( media );
}



shared_ptr<MediaHolder> Library::getDraggingMedia() { if(draggingMedia) return draggingMedia; }
shared_ptr<Clip> Library::getDraggingClip() { if(draggingClip) return draggingClip; }
string Library::getDraggingOntology() { if(draggingOntology!="") return draggingOntology; }


void Library::mouseReleased(ofMouseEventArgs & mouse) {
//            kView::mouseReleased(mouse);
//            draggingOntology="";
//            draggingClip.reset();
//            draggingMedia.reset();

    if(view->inside(mouse.x, mouse.y)) {
        draggingOntology="";
        cout << "ins" << endl;
    }
}








WordSelect::WordSelect(){ orientation="vertical"; autoArrange="true"; spacingX=100; spacingY=30; }
WordSelect::~WordSelect(){
    for (int i=0; i<widgets.size(); i++)
    {
        ofRemoveListener(*widgets[i]->events.lookup("press"),this,&WordSelect::btnClicked);
    }

}

void WordSelect::initialize(){
    saveEvent("selectedWords");
    kScrollView::initialize();
    setSpacingY(50);
    setPaddingX(10);
    setPaddingY(50);
}

void WordSelect::btnClicked(widgetEvent & _event){
//    cout << "click" << endl;
    selectedStrings.clear();
    for (int i=0; i<widgets.size(); i++)
    {

        if (dynamic_pointer_cast<kLabelButton>(widgets[i])->getToggle() ) {
            selectedStrings.push_back( widgets[i]->getLabel() );
        }


    }
    notify("selectedWords");

}

void WordSelect::clear(){
    for (int i=0; i<widgets.size(); i++)
    {
        addDelete( widgets[i] ); //->events.lookup("press"),this,&WordSelect::btnClicked);
    }
}


void WordSelect::makeButton(string _str){
    btn = make_shared<kLabelButton>( );
    btn->setLabel(_str);
    btn->set(0,0,100,80);
    btn->setMode(TOGGLE_ON);
    addWidget(btn);
    ofAddListener(*btn->events.lookup("press"),this,&WordSelect::btnClicked);
    arrangeWidgets();
}



//void WordSelect::draw(ofEventArgs & args){
//    kRectView::draw(args);
//    drawString(label,x,y-20);
//}


vector<string> & WordSelect::getSelected(){
    return selectedStrings;
}





void GraphBrowser::browse( vector<string> & _selectedStrings ){
    for (int i=0; i<_selectedStrings.size(); i++)
    {
        cout << "browser:" << _selectedStrings[i] << endl;
    }
}


