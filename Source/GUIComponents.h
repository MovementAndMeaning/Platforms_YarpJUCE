/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_BC4899FDB6184DA2__
#define __JUCE_HEADER_BC4899FDB6184DA2__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "YarpInterface.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GUIComponents  : public Component,
                       public ChangeListener,
                       public ButtonListener
{
public:
    //==============================================================================
    GUIComponents ();
    ~GUIComponents();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback(ChangeBroadcaster* changeSource);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	YarpInterface* myYarpInterface;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> textEditorNameserver;
    ScopedPointer<TextButton> textButton;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> textEditorPort;
    ScopedPointer<TextEditor> textEditorOutput;
    ScopedPointer<TextButton> textButtonDisconnect;
    ScopedPointer<Label> label3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIComponents)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_BC4899FDB6184DA2__
