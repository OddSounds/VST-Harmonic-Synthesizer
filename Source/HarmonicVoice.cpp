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
	linearEnvelope = true;
	gain = 1;
}

bool HarmonicVoice::canPlaySound(SynthesiserSound* sound) override
{
	return dynamic_cast<HarmonicSound*>(sound) != nullptr;
}

void HarmonicVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
{
	currentPhase = 0;

	double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
	double cyclesPerSample = cyclesPerSecond / getSampleRate();

	phaseDelta = cyclesPerSample * 2.0 * double_Pi;
}

void HarmonicVoice::stopNote(float velocity, bool allowTailOff) override
{
	clearCurrentNote();
	phaseDelta = 0;
}

void HarmonicVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
{
	if(phaseDelta != 0)
	{
		while(--numSamples >= 0)
		{
			float sample = 0;

			for(int i = 0; i < 16; i++)
			{
				sample += (float)sin(currentPhase*(i+1))*gain*harmonicGain[i];
			}

			for(int i = 0; i < outputBuffer.getNumChannels(); i++)
				outputBuffer.addSample(i, startSample, sample);

			currentPhase += phaseDelta;
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

void HarmonicVoice::setHarmonicGain(double gains[16])
{
	memcpy(harmonicGain, gains, 16*sizeof(double));
}