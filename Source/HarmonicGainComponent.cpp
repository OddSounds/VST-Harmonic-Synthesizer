/*
  ==============================================================================

    HarmonicGainComponent.cpp
    Created: 4 Mar 2015 2:02:26pm
    Author:  Sam

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "HarmonicGainComponent.h"

//==============================================================================
HarmonicGainComponent::HarmonicGainComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	for(int i = 0; i < 16; i++)
	{
		harmonicComponents.push_back(0);
		drawComponents.push_back(0);
	}
}

HarmonicGainComponent::~HarmonicGainComponent()
{
}

void HarmonicGainComponent::mouseDown(const MouseEvent& event)
{
	mouseDrag(event);
}

void HarmonicGainComponent::mouseDrag(const MouseEvent& event)
{
	drawComponents.at((event.getPosition().getX() - 10)/20) = -1*(event.getPosition().getY() - this->getHeight()/2);

	float sum = 0;

	for(int i = 0; i < 16; i++)
	{
		sum += abs(drawComponents.at(i));
	}

	for(int i = 0; i < 16; i++)
	{
		harmonicComponents.at(i) = drawComponents.at(i)/sum;
	}

	repaint();
}

void HarmonicGainComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);   // clear the background

    g.setColour (Colours::white);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(Colours::white);

	for(int i = 0; i < 16; i++)
	{
		g.drawLine(10 + i*20, this->getHeight()/2, 10 + i*20, this->getHeight()/2 - drawComponents.at(i), 1.5);
		g.drawEllipse(10 + i*20 - 5, this->getHeight()/2 - drawComponents.at(i) - 5, 10, 10, 1.5);
	}
}

void HarmonicGainComponent::setHarmonics(std::vector<float>& h)
{
	this->harmonicComponents.clear();

	this->harmonicComponents = h;
}

std::vector<float>* HarmonicGainComponent::getHarmonics()
{
	return &this->harmonicComponents;
}

void HarmonicGainComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
