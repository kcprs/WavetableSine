/*
==============================================================================

This file was auto-generated!

==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
This component lives inside our window, and this is where you should put all
your controls and content.
*/
class MainContentComponent : public AudioAppComponent
{
public:
	//==============================================================================
	MainContentComponent()
	{
		setSize(800, 600);

		// specify the number of input and output channels that we want to open
		setAudioChannels(2, 2);
	}

	~MainContentComponent()
	{
		shutdownAudio();
	}

	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
	{
		amplitude = 0.25;
		frequency = 440;
		phase = phaseAtBufferStart = 0;
		wavetableSize = 1024;
		increment = frequency * wavetableSize / sampleRate;

		for (int i = 0; i < wavetableSize; ++i)
		{
			wavetable.insert(i, sinf(2 * double_Pi * i / wavetableSize));
		}
	}

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
		{
			float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
			phase = phaseAtBufferStart; //This ensures that the phase is the same for each channel

			for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				buffer[sample] = wavetable[(int)phase] * amplitude;
				phase = fmod(phase + increment, wavetableSize);
			}
		}

		phaseAtBufferStart = phase; //This ensures that the phase at the end of this buffer is the same as at the beginning of the next buffer
	}

	void releaseResources() override
	{
		// This will be called when the audio device stops, or when it is being
		// restarted due to a setting change.

		// For more details, see the help for AudioProcessor::releaseResources()
	}

	//==============================================================================
	void paint(Graphics& g) override
	{
		// (Our component is opaque, so we must completely fill the background with a solid colour)
		g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

		// You can add your drawing code here!
	}

	void resized() override
	{
		// This is called when the MainContentComponent is resized.
		// If you add any child components, this is where you should
		// update their positions.
	}


private:
	Array<float> wavetable;
	int wavetableSize;
	float frequency;
	float phase, phaseAtBufferStart;
	float increment;
	float amplitude;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent() { return new MainContentComponent(); }
