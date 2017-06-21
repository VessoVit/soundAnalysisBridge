#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(34);
    ofSetFrameRate(60);
//    ofSetVerticalSync(true);
    //--------------------------------------------------------------
    //    Currenlty not working with this version of OF, to be checked.
    //--------------------------------------------------------------

    //    timeline.setup();
    //    timeline.setLoopType(OF_LOOP_NORMAL);
    ////    timeline.addTrack("Audio", "Soundtrack/01ChichoviteKonye.wav");
    ////    timeline.addAudioTrack("audio", "Soundtrack/01ChichoviteKonye.mp3");
    //    timeline.setDurationInSeconds(60);
    //    
    //    timeline.addCurves("MyCircleRadius", ofRange(0, 200));
    //    ofxTimeline::removeCocoaMenusFromGlut("Audio Track Analysis | OSC");
    //    timeline.addAudioTrac
        
    
    //    Play a song from a local file
    //--------------------------------------------------------------
    soundPlayerExtended.load("Soundtrack/01ChichoviteKonye.mp3");
    soundPlayerExtended.play();
    
    //    Microphone input
    //--------------------------------------------------------------
    //    int channelsOut = 0;    // number of requested output channels (i.e. 2 for stereo).
    //    int channelsIn = 2;  // number of requested input channels.
    //    int sampleRate = 44100; // requested sample rate
    //    int bufferSize = 256; // requested buffer size (256 is typical).
    //    int numOfBuffers = 4;   // number of buffers to queue, less buffers will be more responsive, but less stable.
    //    soundStream.setup(this, channelsOut, channelsIn, sampleRate, bufferSize, numOfBuffers);

    //    samplesChannelL.assign(bufferSize, 0.0);
    //    samplesChannelR.assign(bufferSize, 0.0);
    //      SoundWave (Dep)
    //    phase = 0;
    //    updateWaveform(32);
    //    ofSoundStreamSetup(2, 0);
    
    sampleRate = 44100;
    bufferSize = 512;
    int channels = 2;
    audioAnalyzer.setup(sampleRate, bufferSize, channels);
    soundPlayer.load("Soundtrack/01Chichovite Konye.wav");
    
    //  GUI
    gui.setup();
    gui.setPosition(20, 150);
    gui.add(smoothing.setup("Smoothing", 0.95, 0.0, 1.0));
    //
//    stream.setup(2,2,44100, 512, 2);
//    wave.setup(0, 0, ofGetWidth(), ofGetHeight());
//    stream.setInput(input);
//    stream.setOutput(output);
//    
//    input.connectTo(wave).connectTo(output);
    

    //    OSC
    oscSender.setup("localhost", 9999);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    // create a buffer for the song and hold it

    soundBuffer = soundPlayerExtended.getCurrentSoundBuffer(bufferSize);

    audioAnalyzer.analyze(soundBuffer);
    
    rms = audioAnalyzer.getValue(RMS, 0, smoothing);
    power = audioAnalyzer.getValue(POWER, 0, smoothing);
    
    pitchFreq = audioAnalyzer.getValue(PITCH_FREQ, 0, smoothing);
    pitchConf = audioAnalyzer.getValue(PITCH_CONFIDENCE, 0, smoothing);
    pitchFreqNorm   = audioAnalyzer.getValue(PITCH_FREQ, 0, smoothing, TRUE);
//    pitchFreqNorm = audioAnalyzer.getValue(PITCH_FREQ_OSC_IDX, smoothing);
    specComp  = audioAnalyzer.getValue(SPECTRAL_COMPLEXITY, 0, smoothing);
    strongPeak = audioAnalyzer.getValue(STRONG_PEAK, 0, smoothing);
    strongDecay = audioAnalyzer.getValue(STRONG_DECAY, 0, smoothing);
    inharmonicity = audioAnalyzer.getValue(INHARMONICITY, 0, smoothing);

    strongPeakNorm  = audioAnalyzer.getValue(STRONG_PEAK, 0, smoothing, TRUE);
    strongDecayNorm = audioAnalyzer.getValue(STRONG_DECAY, 0, smoothing, TRUE);
//    spectrum = audioAnalyzer.getValue(SPECTRUM, 0, smoothing);
    hfcNorm = audioAnalyzer.getValue(HFC, 0, smoothing, TRUE);
    specCompNorm = audioAnalyzer.getValue(SPECTRAL_COMPLEXITY, 0, smoothing, TRUE);

    
    spectrum = audioAnalyzer.getValues(SPECTRUM, 0, smoothing);
    tristimulus = audioAnalyzer.getValues(TRISTIMULUS, 0, smoothing);

    isOnset = audioAnalyzer.getOnsetValue(0);

    //    Logging CSV
//    cout << rms << "," << power << "," << pitchFreq << "," << pitchConf << "," << specComp << "," << strongPeak << "," <<  strongDecay << "," <<  inharmonicity << "," <<  pitchFreqNorm << "," <<  hfcNorm << "," <<  specCompNorm << "," <<  isOnset << "," <<  ofGetElapsedTimef() << "\n" <<endl;

//    ofScopedLock waveformLock(waveformMutex);
//    updateWaveform(ofMap(ofGetMouseX(), 0, ofGetWidth(), 3, 64, true));
//    frequency = ofMap(ofGetMouseY(), 0, ofGetHeight(), 60, 700, true);
    
//    Send OSC Msg
    ofxOscMessage m_rms;
    m_rms.setAddress("/rms");
    m_rms.addFloatArg(rms);
    oscSender.sendMessage(m_rms);

    ofxOscMessage m_power;
    m_power.setAddress("/power");
    m_power.addFloatArg(power);
    oscSender.sendMessage(m_power);
    
    ofxOscMessage m_pitch;
    m_pitch.setAddress("/pitchFreq");
    m_pitch.addFloatArg(pitchFreq);
    oscSender.sendMessage(m_pitch);
    
    ofxOscMessage m_pitch_c;
    m_pitch_c.setAddress("/pitchConf");
    m_pitch_c.addFloatArg(pitchConf);
    oscSender.sendMessage(m_pitch_c);
    
    ofxOscMessage m_spec_c;
    m_spec_c.setAddress("/spectrumComplexity");
    m_spec_c.addFloatArg(specComp);
    oscSender.sendMessage(m_spec_c);
    
    ofxOscMessage s_peak;
    s_peak.setAddress("/stronPeak");
    s_peak.addFloatArg(strongPeak);
    oscSender.sendMessage(s_peak);
    
    ofxOscMessage s_decay;
    s_decay.setAddress("/strongDecay");
    s_decay.addFloatArg(strongDecay);
    oscSender.sendMessage(s_decay);
    
//    ofxOscMessage m_pitch_n;
//    m_pitch_n.setAddress("/pitchFreqNorm");
//    m_pitch_n.addFloatArg();
//    oscSender.sendMessage(m_pitch_n);
    
//    ofxOscMessage m_spectrum;
//    m_spectrum.setAddress("/Spectrum");
//    m_spectrum.addBlobArg(spectrum);
//    oscSender.sendMessage(m_spectrum);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(0, 0, 0);
//    ofSetLineWidth(5);
//    ofSetColor(33, 66, 33);
//    outLine.draw();
//    ofSetColor(99, 10, 30);
//    waveLine.draw();
//}

    
    //----------------------------------------------------------
//    ofPushMatrix();
//    ofTranslate(0, ofGetHeight() * 0.25);
//    drawSamples(samplesChannelL);
//    ofPopMatrix();
//    
//    ofPushMatrix();
//    ofTranslate(0, ofGetHeight() * 0.75);
//    drawSamples(samplesChannelR);
//    ofPopMatrix();
    //----------------------------------------------------------
    
    ofPushMatrix();
    ofTranslate(350, 0);
    int mw = 250;
    int xpos = 0;
    int ypos = 30;
    
    float value, valueNorm;
    
    ofSetColor(255);
    value = rms;
    string strValue = "RMS: " + ofToString(value, 2);
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, value * mw, 10);

    ypos += 50;
    ofSetColor(255);
    value = power;
    strValue = "Power: " + ofToString(value, 2);
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, value*mw, 10);

    ypos += 50;
    ofSetColor(255);
    value = pitchFreq;
    valueNorm = pitchFreqNorm;
    strValue = "Pitch Frequency: " + ofToString(value, 2) + " hz.";
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, valueNorm*mw, 10);

    ypos += 50;
    ofSetColor(255);
    value = pitchConf;
    strValue = "pitchConf: " + ofToString(value, 2);
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, value*mw, 10);
    
    ypos += 50;
    ofSetColor(255);
    value = specComp;
    valueNorm = specCompNorm;
    strValue = "specComp: " + ofToString(value, 2);
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, valueNorm*mw, 10);
    
    ypos += 50;
    ofSetColor(255);
    value = strongPeak;
    valueNorm = strongPeakNorm;
    strValue = "strongPeak: " + ofToString(value, 2);
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, valueNorm*mw, 10);
    
    ypos += 50;
    ofSetColor(255);
    valueNorm = strongDecayNorm;
    value = strongDecay;
    strValue = "strongDecay: " + ofToString(value, 2);
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, valueNorm*mw, 10);
    
    ypos += 50;
    ofSetColor(255);
    value = inharmonicity;
    strValue = "Inharmonicity: " + ofToString(value, 2);
    ofDrawBitmapString(strValue, xpos, ypos);
    ofSetColor(ofColor::cyan);
    ofDrawRectangle(xpos, ypos+5, value * mw, 10);
    
    
    ofPopMatrix();
//    Vector Values Algorithms:
    
    ofPushMatrix();
    ofTranslate(700, 0);
    
    int graphH = 75;
    int yoffset = graphH + 50;
    ypos = 30;
    
    ofSetColor(255);
    ofDrawBitmapString("Spectrum: ", 0, ypos);
    ofPushMatrix();
    ofTranslate(0, ypos);
    ofSetColor(ofColor::cyan);
    float bin_w = (float) mw / spectrum.size();
    for(int i = 0; i < spectrum.size(); i++){
        float scaledValue = ofMap(spectrum[i], DB_MIN, DB_MAX, 0.0, 1.0, true);
        float bin_h = -1 * (scaledValue * graphH);
        ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
    }
    ofPopMatrix();
    
    ypos += yoffset;
    ofSetColor(255);
    ofDrawBitmapString("Tristimulus: ", 0, ypos);
    ofPushMatrix();
    ofTranslate(0, ypos);
    ofSetColor(ofColor::cyan);
    bin_w = (float) mw / tristimulus.size();
    for(int i = 0; i < tristimulus.size(); i++){
        float scaledValue = tristimulus[i];
        float bin_h = -1*(scaledValue*graphH);
        ofDrawRectangle(i*bin_w, graphH, bin_w, bin_h);
    }
    ofPopMatrix();

//
//  Channels [TODO]
//


    
    ofPopMatrix();

    //    drawKiloscope();
    
    //
    //    GUI
    gui.draw();
    ofSetColor(255);
    ofDrawBitmapString("ofxAudioAnalyzer", 10, 32);
    ofSetColor(ofColor::hotPink);
    ofDrawBitmapString("vvSoundAnalysis - Sketches", 10, 100);
    ofSetColor(255);
    ofDrawBitmapString(ofToString(soundPlayerExtended.getDuration()) + " | " + ofToString(soundPlayerExtended.getPositionMS()*0.001) + " sec | ", 30, 250);
//   improvised 'Timeline' for the song
    float trackWidth = ofMap(soundPlayerExtended.getPositionMS(), 0, 309000, 0, ofGetWidth()/3.5);
    std::cout<< trackWidth<<std::endl;
    
    ofFill();
    ofDrawRectangle(40, 270, ofGetWidth()/3.5, 25);
    
    ofSetColor(ofColor::red);
    ofDrawRectangle(40, 270, trackWidth, 25);

    ofSetColor(ofColor::white);

    ofDrawBitmapString("OSC active on: localhost:9999 ", 30, 400);
    ofDrawBitmapString(" /strongDecay \n /stronPeak \n /spectrumComplexity \n /pitchConf \n /pitchFreq \n /power \n /rms ", 40, 430);
    ofDrawBitmapString(" forward : '>'; back: '<' (3 sec) ", 40, 530);
    
    // GUI.Timeline
//    float changeRadius = timeline.getValue("MyCircleRadius");
//    ofCircle(mouseX, mouseY, changeRadius);
//    timeline.draw();
//    wave.draw();


}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case '1':
            soundPlayerExtended.load("Soundtrack/01ChichoviteKonye.mp3");
            break;
        case 's':
            soundPlayerExtended.stop();
            break;
        case 'p':
            soundPlayerExtended.play();
            break;
        case 'c':
            soundPlayerExtended.setPaused(true);
            break;
            
        case ' ':
            soundPlayerExtended.setPaused(false);
            
        case '<':
            soundPlayerExtended.setPositionMS(soundPlayerExtended.getPositionMS()-3000);
            break;
            
        case '>':
            soundPlayerExtended.setPositionMS(soundPlayerExtended.getPositionMS()+3000);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------

void ofApp::drawSamples(vector<float> samples) {
    
    int sampleWidth = ofGetWidth() / samples.size();
    int sampleHeight = ofGetHeight() / 4;
    int numOfSamples = samples.size();
    
    for(int i=0; i<numOfSamples; i++) {
        int x = ofMap(i, 0, numOfSamples-1, 0, ofGetWidth()-sampleWidth);
        int y = 0;
        int w = sampleWidth;
        int h = samples[i] * sampleHeight;
        
        ofRectangle(x, y, w, h);
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
    
    for(int i = 0; i<bufferSize; i++) {
        samplesChannelL[i] = input[i * 2 + 0];
        samplesChannelR[i] = input[i * 2 + 1];
    }
}
//--------------------------------------------------------------

//void ofApp::audioOut(ofSoundBuffer &outBuffer){
//    for (int i = 0; i < outBuffer.size(); i *= 2) {
//        float sample = sin(phase);
//        outBuffer[i] = sample;
//        outBuffer[i+1] = sample;
//        phase += 0.05;
//    }
//}

void ofApp::updateWaveform(int waveformResolution){
    waveform.resize(waveformResolution);
    waveLine.clear();
    // "waveformStep" maps a full oscillation of sin() to the size
    // of the waveform lookup table
    float waveFormStep = (M_PI * 2.) / (float) waveform.size();
    for(int i = 0; i < waveform.size(); i++){
        waveform[i] = sin(i * waveFormStep);
        waveLine.addVertex(ofMap(i, 0, waveform.size() - 1, 0, ofGetWidth()), ofMap(waveform[i], -1, 1, 0, ofGetHeight()));
    }
}

//void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
//    ofScopedLock waveformLock(waveformMutex);
//    
//    float sampleRate = 44100;
//    float phaseSteps = frequency / sampleRate;
//    
//    outLine.clear();
//    
//    for (int i = 0; i < bufferSize * nChannels; i += nChannels) {
//        phase += phaseSteps;
//        int waveformIndex = (int)(phase * waveform.size()) % waveform.size();
//        output[i] = waveform[waveformIndex];
//        
//        outLine.addVertex(ofMap(i, 0, bufferSize - 1, 0, ofGetWidth()), ofMap(output[i], -1, 1, 0, ofGetHeight()));
//    }
//}


void ofApp::exit(){
    
    audioAnalyzer.exit();
    soundPlayerExtended.stop();
}
