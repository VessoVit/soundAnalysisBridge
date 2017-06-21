#pragma once

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"
#include "ofSoundPlayerExtended.h"
#include "ofxGui.h"
#include "ofxOsc.h"
//#include "ofxTimeline.h"
//#include "ofxTLAudioTrack.h"


using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofSoundPlayer soundPlayer;
        ofSoundBuffer soundBuffer;
        //    Kiloscope [TO-DO]
        void setupKiloscope();
        void drawKiloscope();
        //    Audio
        //        void audioOut(ofSoundBuffer &outBuffer);
        //        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
        ofSoundStream soundStream;
        vector<float> samplesChannelL;
        vector<float> samplesChannelR;
        void drawSamples(vector<float> samples);
    
        //    Sound Analysis
        ofxAudioAnalyzer audioAnalyzer;
        ofSoundPlayerExtended soundPlayerExtended;
        //    Sound Analysis input parameters
        int sampleRate, bufferSize;
        // SoundAnalysis Variables/outpus
        float rms, power;
        float pitchFreq, pitchFreqNorm, pitchConf;
        float specComp, specCompNorm;
        float strongPeak, strongPeakNorm;
        float strongDecay, strongDecayNorm;
        float inharmonicity, hfcNorm;
        //   SoundAnalysis Data Sctructures
        vector<float> spectrum;
        vector<float> tristimulus;
        bool isOnset;

        // GUI
        ofxPanel gui;
        ofxFloatSlider smoothing;
    
        // Waveform
        void updateWaveform(int waveformResolution);
        double phase;
        // ofSoundBuffer outBuffer;
        float frequency;
        
        std::vector<float> waveform;
        ofMutex waveformMutex;
        ofPolyline waveLine;
        ofPolyline outLine;
    
        // Keliscope Visuals
        ofImage img;
        ofPlanePrimitive plane;
        ofShader shader_kelido;
        ofShader shader;
    
        ofTexture texture;
        // Some issues with current version of OF (0.9) [Not working]
//        ofxTimeline timeline;
//        ofxTLTrack track;
    
    
        // OSC
        ofxOscSender oscSender;

    
    
};
