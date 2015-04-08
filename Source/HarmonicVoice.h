#include "JuceHeader.h"

class HarmonicSound : public SynthesiserSound
{

public:
	HarmonicSound();

	bool appliesToNote(int midiNoteNumber);
	bool appliesToChannel(int midiChannel);

private:

};

class HarmonicVoice : public SynthesiserVoice
{

public:
	HarmonicVoice();

	bool canPlaySound(SynthesiserSound*) override;
	
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;

	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;

	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

	void setHarmonicGain(double gains[16]);
	

private:
	double currentPhase, phaseDelta, gain;

	double attackTime, decayTime, releaseTime;
	double sustainLevel;

	bool linearEnvelope;

	double harmonicGain[16];

	short envelopeStage;
};