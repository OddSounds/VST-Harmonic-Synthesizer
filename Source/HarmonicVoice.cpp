#include "JuceHeader.h"
#include "HarmonicVoice.h"

#define ENV_ATTACK	0
#define ENV_DECAY	1
#define ENV_SUSTAIN	2
#define ENV_RELEASE	3
#define ENV_POST	4


bool HarmonicSound::appliesToNote(int midiNoteNumber) override
{
	return true;
}

bool HarmonicSound::appliesToChannel(int midiChannel) override
{
	return true;
}

HarmonicVoice::HarmonicVoice()
{
	for(int i = 0; i < 16; i++)
	{
		currentPhase.push_back(0);
		phaseDelta.push_back(0);
	}

	linearEnvelope = true;
	gain = 1;
}

bool HarmonicVoice::canPlaySound(SynthesiserSound* sound) override
{
	return dynamic_cast<HarmonicSound*>(sound) != nullptr;
}

void HarmonicVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
{
	double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
	double cyclesPerSample = cyclesPerSecond / getSampleRate();

	for(int i = 0; i < 16; i++)
	{
		currentPhase.at(i) = 0;
		phaseDelta.at(i) = cyclesPerSample*(i+1) * 2.0 * double_Pi;
	}
}

void HarmonicVoice::stopNote(float velocity, bool allowTailOff) override
{
	clearCurrentNote();

	for(int i = 0; i < 16; i++)
		phaseDelta.at(i) = 0;
}

void HarmonicVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
{
	if(phaseDelta.at(0) != 0)
	{
		while(--numSamples >= 0)
		{
			float sample = 0;

			for(int i = 0; i < 16; i++)
			{
				sample += (float)sin(currentPhase.at(i))*harmonicPtr->at(i);

				currentPhase.at(i) += phaseDelta.at(i);
			}

			for(int i = 0; i < outputBuffer.getNumChannels(); i++)
				outputBuffer.addSample(i, startSample, sample);

			++startSample;
		}
	}
}

void HarmonicVoice::pitchWheelMoved(int newPitchWheelValue) override
{
	return;
}

void HarmonicVoice::controllerMoved(int controllerNumber, int newControllerValue) override
{
	return;
}

void HarmonicVoice::setHarmonicPtr(std::vector<float>* ptr)
{
	this->harmonicPtr = ptr;
}

HarmonicSound::HarmonicSound()
{}

/*bool HarmonicSound::appliesToChannel(int midiChannel) override
{
	return true;
}

bool HarmonicSound::appliesToChannel(int midiChannel) override
{
	return true;
}*/