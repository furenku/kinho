#pragma once

#include "library.h"
#include "guiVideoObjects.h"

#ifndef editor_h
#define editor_h


class Editor: virtual public kRectView {

    public:
        Editor(){}

        void initialize(){
            autoArrange = false;

            textView = make_shared<kRectView>();
            textView->set(0,0,0.25f,1.0f);
            textView->autoArrange = false;
            addWidget(textView);
            videoView = make_shared <kRectView>();
            videoView->set(0.25f,0,0.75f,0.9f);
            videoView->autoArrange = false;
            addWidget(videoView);

            arrangeWidgets();

            shared_ptr<TextBox> text = make_shared<TextBox>(widgetSettings);
            text->set(0.1f,0.2f+0.1f,0.8f,0.05f);
            text->setText("");
            text->setLabel("nombre:");
            textView->addWidget( text );

            nameText = text;


            textView->arrangeWidgets();


        }

    shared_ptr< kRectView > textView, videoView;
    shared_ptr< TextBox > nameText, descriptionText, tagsText;
    shared_ptr< kScrollView > catsView;
//        void openClip ( shr)



};




#endif
