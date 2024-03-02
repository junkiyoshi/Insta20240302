#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->noise_param += 0.03;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	
	ofColor color;
	for (int deg_start = 0; deg_start < 360; deg_start += 60) {

		for (int deg = deg_start; deg < deg_start + 14; deg += 2) {

			color.setHsb(ofMap(deg, deg_start, deg_start + 14, 0, 255), 255, 255);
			ofSetColor(color, 200);

			ofPushMatrix();
			ofRotate(deg_start);

			auto base_location = glm::vec2(0, -10);
			auto target_location = glm::vec2(0, -620);
			auto distance = target_location - base_location;
			auto len = glm::length(distance);
			auto noise_seed = ofRandom(1000);

			for (int d = 0; d <= len; d++) {

				auto location = base_location + glm::normalize(distance) * d;

				auto gap = abs(len * 0.5 - d);
				auto power = gap < len * 0.35 ? 1 : ofMap(gap, len * 0.35, len * 0.5, 1, 0);

				auto noise_x = ofMap(ofNoise(noise_seed, location.x * 0.005, location.y * 0.005 + this->noise_param), 0, 1,
					ofMap(d, 0, len, -20, -200), ofMap(d, 0, len, 20, 200));
				location += glm::vec2(noise_x * power, 0);

				ofDrawCircle(location, 2
					);
			}

			ofPopMatrix();
		}
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}