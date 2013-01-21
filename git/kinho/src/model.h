//class Tag{
//    public:
//        Tag( string _name ) {
//            name = _name;
//        }
//
//        void addClip(shared_ptr<Clip> _clip) {
//            clips.push_back(_clip);
//        }
//
//        void setName(string _name) {
//            name = _name;
//        }
//
////    protected:
//        string name;
//        vector<shared_ptr<Clip>  > clips;
//
//};
//
//class Category{
//    public:
//        Category( string _name ) {
//            name = _name;
//        }
//
//        void setName(string _name) {
//            name = _name;
//        }
//
//        void addTag(shared_ptr<Tag> _tag) {
//            tags.push_back(_tag);
//        }
//
////    protected:
//        string name;
//        vector<shared_ptr<Tag> > tags;
//
//};
//
//class Model{
//
//    public:
//
//        Model(){
//            loadFile( "xml/archivo01test.xml" );
//
//        }
//        virtual ~Model(){}
//        string getName() { return "caca"; }
//        void loadFile(string _filename) {
//            cout << "cargar archivo: "<<_filename << endl;
//            if( XML.loadFile(_filename) ) {
//                loadCategories();
//            }
//            else{
//                cout << "archivo not found" << endl;
//            }
//        }
//
//        void loadCategories() {
//            int numClips,numTags,numCats;
//
//            numCats = XML.getNumTags("CATEGORY");
//            for (int i=0; i<numCats; i++)
//            {
//                XML.pushTag("CATEGORY", i);
//
//                categories.push_back(make_shared<Category>(XML.getValue("NAME","str")));
//
//                numTags = XML.getNumTags("TAG");
//
//                for (int j=0; j<numTags; j++)
//                {
//                    XML.pushTag("TAG", j);
//                    shared_ptr<Tag> tag = make_shared<Tag>(XML.getValue("NAME","str"));
//
//                    categories.back()->addTag( tag );
//
//                    numClips = XML.getNumTags("CLIP");
//                    for (int k=0; k<numClips; k++)
//                    {
//                        cout << XML.getValue("CLIP","str",k) << endl;
////                        shared_ptr<Clip> clip = make_shared<clip>( );
////                        tag->addClip( clip );
//
//
//                    }
//                    XML.popTag();
//                }
//
//
//                XML.popTag();
//            }
//
//
//
//        }
//
//        void writeFile(string _filename) {
//        }
//
//        void addCategory( shared_ptr<Category> _category) {
//            categories.push_back(_category);
//        }
//
//        int getNoCategories(){
//            return categories.size();
//        };
//
//        vector<string> getCategoryNames() {
//            vector<string> vecstr;
//            for (int i=0; i<categories.size(); i++)
//            	vecstr.push_back( categories[i]->name );
//
//            return vecstr;
//
//        }
//
//        vector<string> getTagNames() {
//            vector<string> vecstr;
//            for (int i=0; i<categories.size(); i++)
//            	for (int j=0; j<categories[i]->tags.size(); j++)
//                    vecstr.push_back( categories[i]->tags[j]->name );
//            return vecstr;
//
//        }
//
//
//        shared_ptr<Category> getCategory(int _i) {
//            return categories[_i];
//        }
//
//
//        vector< shared_ptr<Category> > categories;
//        ofxXmlSettings XML;
//
//
//};
//
//
//
//
//
//
