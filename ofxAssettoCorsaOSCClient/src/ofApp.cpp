#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);

	physicsData = new SPageFilePhysics();
	graphicsData = new SPageFileGraphic();
	fileStaticData = new SPageFileStatic();
}

//--------------------------------------------------------------
void ofApp::update() {
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);

		if (m.getAddress() == physicsOSCAddress + "packetID")	physicsData->packetId = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "gas")		physicsData->gas = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "brake")		physicsData->brake = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "fuel")		physicsData->fuel = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "gear")		physicsData->gear = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "rpms")		physicsData->rpms = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "steerAngle")	physicsData->steerAngle = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "speedKmh")	physicsData->speedKmh = m.getArgAsFloat(0);

		if (m.getAddress() == physicsOSCAddress + "velocity") {
			physicsData->velocity[0] = m.getArgAsFloat(0);
			physicsData->velocity[1] = m.getArgAsFloat(1);
			physicsData->velocity[2] = m.getArgAsFloat(2);
		}

		if (m.getAddress() == physicsOSCAddress + "accG") {
			physicsData->accG[0] = m.getArgAsFloat(0);
			physicsData->accG[1] = m.getArgAsFloat(1);
			physicsData->accG[2] = m.getArgAsFloat(2);
		}

		if (m.getAddress() == physicsOSCAddress + "wheelSlip") {
			physicsData->wheelSlip[0] = m.getArgAsFloat[0];
			physicsData->wheelSlip[1] = m.getArgAsFloat[1];
			physicsData->wheelSlip[2] = m.getArgAsFloat[2];
			physicsData->wheelSlip[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "wheelLoad") {
			physicsData->wheelLoad[0] = m.getArgAsFloat[0];
			physicsData->wheelLoad[1] = m.getArgAsFloat[1];
			physicsData->wheelLoad[2] = m.getArgAsFloat[2];
			physicsData->wheelLoad[1] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "wheelPressure") {
			physicsData->wheelsPressure[0] = m.getArgAsFloat[0];
			physicsData->wheelsPressure[1] = m.getArgAsFloat[1];
			physicsData->wheelsPressure[2] = m.getArgAsFloat[2];
			physicsData->wheelsPressure[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "wheelAngularSpeed") {
			physicsData->wheelAngularSpeed[0] = m.getArgAsFloat[0];
			physicsData->wheelAngularSpeed[1] = m.getArgAsFloat[1];
			physicsData->wheelAngularSpeed[2] = m.getArgAsFloat[2];
			physicsData->wheelAngularSpeed[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "tyreWear") {
			physicsData->tyreWear[0] = m.getArgAsFloat[0];
			physicsData->tyreWear[1] = m.getArgAsFloat[1];
			physicsData->tyreWear[2] = m.getArgAsFloat[2];
			physicsData->tyreWear[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "tyreDirtyLevel") {
			physicsData->tyreDirtyLevel[0] = m.getArgAsFloat[0];
			physicsData->tyreDirtyLevel[1] = m.getArgAsFloat[1];
			physicsData->tyreDirtyLevel[2] = m.getArgAsFloat[2];
			physicsData->tyreDirtyLevel[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "tyreCoreTemprature") {
			physicsData->tyreCoreTemperature[0] = m.getArgAsFloat[0];
			physicsData->tyreCoreTemperature[1] = m.getArgAsFloat[1];
			physicsData->tyreCoreTemperature[2] = m.getArgAsFloat[2];
			physicsData->tyreCoreTemperature[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "camberRAD") {
			physicsData->camberRAD[0] = m.getArgAsFloat[0];
			physicsData->camberRAD[1] = m.getArgAsFloat[1];
			physicsData->camberRAD[2] = m.getArgAsFloat[2];
			physicsData->camberRAD[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "suspensionTravel") {
			physicsData->suspensionTravel[0] = m.getArgAsFloat[0];
			physicsData->suspensionTravel[1] = m.getArgAsFloat[1];
			physicsData->suspensionTravel[2] = m.getArgAsFloat[2];
			physicsData->suspensionTravel[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "drs")		physicsData->drs = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "tc")			physicsData->tc = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "heading")	physicsData->heading = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "pitch")		physicsData->pitch = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "roll")		physicsData->roll = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "cgHeight")	physicsData->cgHeight = m.getArgAsFloat(0);

		if (m.getAddress() == physicsOSCAddress + "carDamage") {
			physicsData->carDamage[0] = m.getArgAsFloat(0);
			physicsData->carDamage[1] = m.getArgAsFloat(1);
			physicsData->carDamage[2] = m.getArgAsFloat(2);
			physicsData->carDamage[3] = m.getArgAsFloat(3);
			physicsData->carDamage[4] = m.getArgAsFloat(4);
		}

		if (m.getAddress() == physicsOSCAddress + "numberOfTyresOut")		physicsData->numberOfTyresOut = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "pitLimitOn")				physicsData->pitLimiterOn = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "abs")					physicsData->abs = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "kersCharge")				physicsData->kersCharge = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "kersInput")				physicsData->kersInput = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "autoShifterOn")			physicsData->autoShifterOn = m.getArgAsInt64(0);

		if (m.getAddress() == physicsOSCAddress + "rideHeight") {
			physicsData->rideHeight[0] = m.getArgAsFloat(0);
			physicsData->rideHeight[1] = m.getArgAsFloat(1);
		}

		if (m.getAddress() == physicsOSCAddress + "turboBoost")		physicsData->turboBoost = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "ballast")		physicsData->ballast = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "airDensity")		physicsData->airDensity = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "airTemp")		physicsData->airTemp = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "roadTemp")		physicsData->roadTemp = m.getArgAsFloat(0);

		if (m.getAddress() == physicsOSCAddress + "localAngularVel") {
			physicsData->localAngularVel[0] = m.getArgAsFloat(0);
			physicsData->localAngularVel[1] = m.getArgAsFloat(1);
			physicsData->localAngularVel[2] = m.getArgAsFloat(2);
		}

		if (m.getAddress() == physicsOSCAddress + "finalFF")			physicsData->finalFF = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "performanceMeter")	physicsData->performanceMeter = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "engineBrake")		physicsData->engineBrake = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "ersRecoveryLevel")	physicsData->ersRecoveryLevel = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "ersPowerLevel")		physicsData->ersPowerLevel = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "ersHeatCharging")	physicsData->ersHeatCharging = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "ersIsCharing")		physicsData->ersIsCharging = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "kersCurrentKJ")		physicsData->kersCurrentKJ = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "drsAvailable")		physicsData->drsAvailable = m.getArgAsInt64(0);
		if (m.getAddress() == physicsOSCAddress + "drsEnabled")			physicsData->drsEnabled = m.getArgAsInt64(0);

		if (m.getAddress() == physicsOSCAddress + "brakeTemp") {
			physicsData->brakeTemp[0] = m.getArgAsFloat[0];
			physicsData->brakeTemp[1] = m.getArgAsFloat[1];
			physicsData->brakeTemp[2] = m.getArgAsFloat[2];
			physicsData->brakeTemp[3] = m.getArgAsFloat[3];
		}

		if (m.getAddress() == physicsOSCAddress + "clutch")				physicsData->clutch = m.getArgAsFloat(0);

		if (m.getAddress() == physicsOSCAddress + "tyreTempI") {
			physicsData->tyreTempI[0] = m.getArgAsFloat(0);
			physicsData->tyreTempI[1] = m.getArgAsFloat(1);
			physicsData->tyreTempI[2] = m.getArgAsFloat(2);
			physicsData->tyreTempI[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreTempM") {
			physicsData->tyreTempM[0] = m.getArgAsFloat(0);
			physicsData->tyreTempM[1] = m.getArgAsFloat(1);
			physicsData->tyreTempM[2] = m.getArgAsFloat(2);
			physicsData->tyreTempM[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreTempO") {
			physicsData->tyreTempO[0] = m.getArgAsFloat(0);
			physicsData->tyreTempO[1] = m.getArgAsFloat(1);
			physicsData->tyreTempO[2] = m.getArgAsFloat(2);
			physicsData->tyreTempO[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "isAIControlled")		physicsData->isAIControlled = m.getArgAsInt64(0);

		if (m.getAddress() == physicsOSCAddress + "tyreContactPointFL") {
			physicsData->tyreContactPoint[0][0] = m.getArgAsFloat(0);
			physicsData->tyreContactPoint[0][1] = m.getArgAsFloat(1);
			physicsData->tyreContactPoint[0][2] = m.getArgAsFloat(2);
			physicsData->tyreContactPoint[0][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreContactPointFR") {
			physicsData->tyreContactPoint[1][0] = m.getArgAsFloat(0);
			physicsData->tyreContactPoint[1][1] = m.getArgAsFloat(1);
			physicsData->tyreContactPoint[1][2] = m.getArgAsFloat(2);
			physicsData->tyreContactPoint[1][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreContactPointRL") {
			physicsData->tyreContactPoint[2][0] = m.getArgAsFloat(0);
			physicsData->tyreContactPoint[2][1] = m.getArgAsFloat(1);
			physicsData->tyreContactPoint[2][2] = m.getArgAsFloat(2);
			physicsData->tyreContactPoint[2][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreContactPointRR") {
			physicsData->tyreContactPoint[3][0] = m.getArgAsFloat(0);
			physicsData->tyreContactPoint[3][1] = m.getArgAsFloat(1);
			physicsData->tyreContactPoint[3][2] = m.getArgAsFloat(2);
			physicsData->tyreContactPoint[3][3] = m.getArgAsFloat(3);
		}

		// tyreContactNormal
		if (m.getAddress() == physicsOSCAddress + "tyreContactNormalFL") {
			physicsData->tyreContactNormal[0][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[0][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[0][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[0][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreContactNormalFR") {
			physicsData->tyreContactNormal[1][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[1][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[1][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[1][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreContactNormalRL") {
			physicsData->tyreContactNormal[2][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[2][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[2][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[2][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreContactNormalRR") {
			physicsData->tyreContactNormal[3][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[3][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[3][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[3][3] = m.getArgAsFloat(3);
		}

		// tyreContactHeading
		if (m.getAddress() == physicsOSCAddress + "tyreContactHeadingFL") {
			physicsData->tyreContactNormal[0][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[0][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[0][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[0][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreContactHeadingFR") {
			physicsData->tyreContactNormal[1][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[1][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[1][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[1][3] = m.getArgAsFloat(3);
		}
		if (m.getAddress() == physicsOSCAddress + "tyreContactHeadingRL") {
			physicsData->tyreContactNormal[2][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[2][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[2][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[2][3] = m.getArgAsFloat(3);
		}
		if (m.getAddress() == physicsOSCAddress + "tyreContactHeadingRR") {
			physicsData->tyreContactNormal[3][0] = m.getArgAsFloat(0);
			physicsData->tyreContactNormal[3][1] = m.getArgAsFloat(1);
			physicsData->tyreContactNormal[3][2] = m.getArgAsFloat(2);
			physicsData->tyreContactNormal[3][3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "brakeBias")			physicsData->brakeBias = m.getArgAsFloat(0);
		if (m.getAddress() == physicsOSCAddress + "localVelocity") {
			physicsData->localVelocity[0] = m.getArgAsFloat(0);
			physicsData->localVelocity[1] = m.getArgAsFloat(1);
			physicsData->localVelocity[2] = m.getArgAsFloat(2);
		}
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	stringstream physicsOutput;
	physicsOutput « "PHYSICS ====================================" « endl << endl
		« "packetId" « physicsData->packetId « endl
		« "gas" « physicsData->gas « endl
		« "brake" « physicsData->brake « endl
		« "fuel" « physicsData->fuel « endl
		« "gear" « physicsData->gear « endl
		« "rpms" « physicsData->rpms « endl
		« "steerAngle" « physicsData->steerAngle « endl
		« "speedKmh" « physicsData->speedKmh « endl
		« "velocity" « physicsData->velocity « endl
		« "accG" « physicsData->accG « endl
		« "wheelSlip" « physicsData->wheelSlip « endl
		« "wheelLoad" « physicsData->wheelLoad « endl
		« "wheelsPressure" « physicsData->wheelsPressure « endl
		« "wheelAngularSpeed" « physicsData->wheelAngularSpeed « endl
		« "tyreWear" « physicsData->tyreWear « endl
		« "tyreDirtyLevel" « physicsData->tyreDirtyLevel « endl
		« "tyreCoreTemperature" « physicsData->tyreCoreTemperature « endl
		« "camberRAD" « physicsData->camberRAD « endl
		« "suspensionTravel" « physicsData->suspensionTravel « endl
		« "drs" « physicsData->drs « endl
		« "tc" « physicsData->tc « endl
		« "heading" « physicsData->heading « endl
		« "pitch" « physicsData->pitch « endl
		« "roll" « physicsData->roll « endl
		« "cgHeight" « physicsData->cgHeight « endl
		« "carDamage" « physicsData->carDamage « endl
		« "numberOfTyresOut" « physicsData->numberOfTyresOut « endl
		« "pitLimiterOn" « physicsData->pitLimiterOn « endl
		« "abs" « physicsData->abs « endl
		« "kersCharge" « physicsData->kersCharge « endl
		« "kersInput" « physicsData->kersInput « endl
		« "autoShifterOn" « physicsData->autoShifterOn « endl
		« "rideHeight" « physicsData->rideHeight « endl
		« "turboBoost" « physicsData->turboBoost « endl
		« "ballast" « physicsData->ballast « endl
		« "airDensity" « physicsData->airDensity « endl
		« "airTemp" « physicsData->airTemp « endl
		« "roadTemp" « physicsData->roadTemp « endl
		« "localAngularVel" « physicsData->localAngularVel « endl
		« "finalFF" « physicsData->finalFF « endl
		« "performanceMeter" « physicsData->performanceMeter « endl
		« "engineBrake" « physicsData->engineBrake « endl
		« "ersRecoveryLevel" « physicsData->ersRecoveryLevel « endl
		« "ersPowerLevel" « physicsData->ersPowerLevel « endl
		« "ersHeatCharging" « physicsData->ersHeatCharging « endl
		« "ersIsCharging" « physicsData->ersIsCharging « endl
		« "kersCurrentKJ" « physicsData->kersCurrentKJ « endl
		« "drsAvailable" « physicsData->drsAvailable « endl
		« "drsEnabled" « physicsData->drsEnabled « endl;

	ofDrawBitmapStringHighlight(physicsOutput.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
