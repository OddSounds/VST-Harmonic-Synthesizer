/*
  ==============================================================================

    HarmonicGainComponent.h
    Created: 4 Mar 2015 2:02:26pm
    Author:  Sam

  ==============================================================================
*/

#ifndef HARMONICGAINCOMPONENT_H_INCLUDED
#define HARMONICGAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class HarmonicGainComponent    : public Component
{
public:
    HarmonicGainComponent();
    ~HarmonicGainComponent();

    void paint (Graphics&);
    void resized();

	void mouseDown(const MouseEvent& event);
	void mouseDrag(const MouseEvent& event);

	void setHarmonics(std::vector<float>&);
	std::vector<float>* getHarmonics();

private:
	std::vector<float> harmonicComponents;
	std::vector<float> drawComponents;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonicGainComponent)
};


#endif  // HARMONICGAINCOMPONENT_H_INCLUDED
