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

//[Headers] You can add your own extra header files here...
#include <yarp/os/all.h>
//[/Headers]

#include "GUIComponents.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void GUIComponents::changeListenerCallback(ChangeBroadcaster* changeSource) {
	textEditorOutput->setCaretPosition((textEditorOutput->getText().length()-1));
	this->repaint();
}


//[/MiscUserDefs]

//==============================================================================
GUIComponents::GUIComponents ()
{
    addAndMakeVisible (textEditorNameserver = new TextEditor ("new text editor"));
    textEditorNameserver->setMultiLine (false);
    textEditorNameserver->setReturnKeyStartsNewLine (false);
    textEditorNameserver->setReadOnly (false);
    textEditorNameserver->setScrollbarsShown (true);
    textEditorNameserver->setCaretVisible (true);
    textEditorNameserver->setPopupMenuEnabled (true);
    textEditorNameserver->setText (String::empty);

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->setButtonText (TRANS("connect"));
    textButton->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("local port name:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("yarp nameserver:")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textEditorPort = new TextEditor ("new text editor"));
    textEditorPort->setMultiLine (false);
    textEditorPort->setReturnKeyStartsNewLine (false);
    textEditorPort->setReadOnly (false);
    textEditorPort->setScrollbarsShown (true);
    textEditorPort->setCaretVisible (true);
    textEditorPort->setPopupMenuEnabled (true);
    textEditorPort->setText (String::empty);

    addAndMakeVisible (textEditorOutput = new TextEditor ("new text editor"));
    textEditorOutput->setMultiLine (true);
    textEditorOutput->setReturnKeyStartsNewLine (true);
    textEditorOutput->setReadOnly (true);
    textEditorOutput->setScrollbarsShown (true);
    textEditorOutput->setCaretVisible (true);
    textEditorOutput->setPopupMenuEnabled (true);
    textEditorOutput->setText (String::empty);

    addAndMakeVisible (textButtonDisconnect = new TextButton ("new button"));
    textButtonDisconnect->setButtonText (TRANS("disconnect"));
    textButtonDisconnect->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("read output:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
	textEditorNameserver->setText("127.0.0.1");
	textEditorPort->setText("/YarpJUCE");
    //[/UserPreSize]

    setSize (800, 600);


    //[Constructor] You can add your own custom stuff here..
	myYarpInterface = NULL;
    //[/Constructor]
}

GUIComponents::~GUIComponents()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textEditorNameserver = nullptr;
    textButton = nullptr;
    label = nullptr;
    label2 = nullptr;
    textEditorPort = nullptr;
    textEditorOutput = nullptr;
    textButtonDisconnect = nullptr;
    label3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	if (myYarpInterface != NULL)
		delete myYarpInterface;
    //[/Destructor]
}

//==============================================================================
void GUIComponents::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);
    //[UserPaint] Add your own custom painting code here..
	String output;
	DBG("paint");
	if (myYarpInterface!= NULL) {
		myYarpInterface->lock.enter();
		output = myYarpInterface->getOutputText();
		myYarpInterface->lock.exit();
		textEditorOutput->setText(output);
	}
    //[/UserPaint]
}

void GUIComponents::resized()
{
    textEditorNameserver->setBounds (168, 200, 150, 24);
    textButton->setBounds (336, 200, 96, 24);
    label->setBounds (24, 240, 128, 24);
    label2->setBounds (24, 200, 150, 24);
    textEditorPort->setBounds (168, 240, 150, 24);
    textEditorOutput->setBounds (168, 288, 280, 112);
    textButtonDisconnect->setBounds (336, 240, 96, 24);
    label3->setBounds (24, 288, 128, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GUIComponents::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]
    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
		DBG("connect btn\n");
		if (myYarpInterface != NULL)
			delete myYarpInterface;
		myYarpInterface = new YarpInterface();
		yarp::os::ConstString nsIP = textEditorNameserver->getText().toRawUTF8();
		myYarpInterface->setNSAddress(nsIP);
		yarp::os::ConstString portstr = textEditorPort->getText().toRawUTF8();
		if (myYarpInterface->setPortName(portstr)) {
			myYarpInterface->addChangeListener(this);
			myYarpInterface->startThread();
		}
		else {
			textEditorOutput->setText("Invalid port name! must start with '/'");
		}
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == textButtonDisconnect)
    {
        //[UserButtonCode_textButtonDisconnect] -- add your button handler code here..
		DBG("disconnect btn\n");
		myYarpInterface->stopThread(2000);

        //[/UserButtonCode_textButtonDisconnect]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GUIComponents" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="new text editor" id="b264509ac6d8f3c9" memberName="textEditorNameserver"
              virtualName="" explicitFocusOrder="0" pos="168 200 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="5f342e7982e34039" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="336 200 96 24" buttonText="connect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="7886a28ed6a28e5b" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="24 240 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="local port name:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b949d49e021ce9df" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="24 200 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="yarp nameserver:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="2921870cfbe547c3" memberName="textEditorPort"
              virtualName="" explicitFocusOrder="0" pos="168 240 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="2d5482ce1491c10f" memberName="textEditorOutput"
              virtualName="" explicitFocusOrder="0" pos="168 288 280 112" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="84cae9a3ed16fc8d" memberName="textButtonDisconnect"
              virtualName="" explicitFocusOrder="0" pos="336 240 96 24" buttonText="disconnect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="605ff976507302cc" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="24 288 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="read output:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
