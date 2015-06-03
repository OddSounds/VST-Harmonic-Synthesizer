#include "JuceHeader.h"
#include "HarmonicGainComponent.h"

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

	void setHarmonicPtr(std::vector<float>* ptr);
	

private:
	ScopedPointer<HarmonicGainComponent> gainsComponent;

	double gain;

	double attackTime, decayTime, releaseTime;
	double sustainLevel;

	bool linearEnvelope;

	std::vector<float>* harmonicPtr;
	std::vector<double> currentPhase, phaseDelta;

	short envelopeStage;
};