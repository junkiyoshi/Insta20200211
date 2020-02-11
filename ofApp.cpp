#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetLineWidth(3);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto radius_min = 50;
	auto radius_max = 200;
	auto radius_span = 10;
	auto len = 360;

	for (auto radius = radius_min; radius < radius_max; radius += radius_span) {

		auto start_deg = ofGetFrameNum() * ofRandom(3, 5) + ofRandom(720);
		int start_index = this->face.getNumVertices();
		vector<glm::vec3> vertices;
		for (int deg = start_deg; deg < start_deg + len; deg += 1) {

			auto param = deg % 720;
			auto z = 0;
			if (param < 360) {

				z = param < 180 ? ofMap(param, 0, 180, -30, -20) : ofMap(param, 180, 360, -20, 30);

				vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z) + glm::vec3((radius_min + radius_max) * -0.5, 0, 0));
				vertices.push_back(glm::vec3((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD), z) + glm::vec3((radius_min + radius_max) * -0.5, 0, 0));
			}
			else {

				z = param < 540 ? ofMap(param, 360, 540, 30, 20) : ofMap(param, 540, 720, 20, -30);

				int tmp_radius = ofMap(radius, radius_min, radius_max, radius_max, radius_min);
				vertices.push_back(glm::vec3(-1 * tmp_radius * cos(deg * DEG_TO_RAD), tmp_radius * sin(deg * DEG_TO_RAD), z) + glm::vec3((radius_min + radius_max) * 0.5, 0, 0));
				vertices.push_back(glm::vec3(-1 * (tmp_radius - radius_span) * cos(deg * DEG_TO_RAD), (tmp_radius - radius_span) * sin(deg * DEG_TO_RAD), z) + glm::vec3((radius_min + radius_max) * 0.5, 0, 0));
			}
		}

		this->face.addVertices(vertices);
		this->frame.addVertices(vertices);

		for (int i = start_index; i < this->face.getNumVertices() - 4; i += 2) {

			this->face.addIndex(i + 0); this->face.addIndex(i + 2); this->face.addIndex(i + 3);
			this->face.addIndex(i + 0); this->face.addIndex(i + 3); this->face.addIndex(i + 1);

			this->frame.addIndex(i + 0); this->frame.addIndex(i + 2);
			this->frame.addIndex(i + 1); this->frame.addIndex(i + 3);
		}

		this->face.addIndex(this->frame.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 1);
		this->face.addIndex(this->frame.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3);

		this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 2);
		this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 1);

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 1);
		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(239);
	this->face.draw();

	ofSetColor(39);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}