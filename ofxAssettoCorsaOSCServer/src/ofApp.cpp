#include "ofApp.h"

bool isServer = false;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetLogLevel(OF_LOG_VERBOSE);        

    // setup an object with different data types
	physicsData = new SPageFilePhysics();
	graphicsData = new SPageFileGraphic();
	staticData = new SPageFileStatic();
    
	physics.setup("Local\\acpmf_physics", sizeof(physics), false);
	graphics.setup("Local\\acpmf_graphics", sizeof(graphics), false);
	fileStatic.setup("Local\\acpmf_static", sizeof(fileStatic), false);
	
	// setup + connect
	//memoryMappedFile.setup(memoryKey, memorySize, isServer);

    isConnected = physics.connect() && graphics.connect() && fileStatic.connect();

	isPhysicsConnected = physics.connect();
	isGraphicsConnected = graphics.connect();
	isStaticConnected = fileStatic.connect();
    
    //ofLog() << "Memory was mapped? " << isConnected;
    /*ofLog() << "Memory key: " << memoryKey;
    ofLog() << "Memory size: " << memorySize;*/

	// oscSender setup
	sender.setup(HOST, PORT);
	lastOscSentTimer = ofGetElapsedTimeMillis();
}



//--------------------------------------------------------------
void ofApp::update() {

	ofSetWindowTitle(ofToString("AC shared memory - connection statud : ") + ofToString(isConnected ? "YES" : "NO") + ", FPS: " + ofToString(ofGetFrameRate(), 0));

	// if not connected, try reconnect every 5 seconds or so
	if (!isPhysicsConnected && ofGetFrameNum() % 300 == 0)		isPhysicsConnected = physics.connect();
	if (!isGraphicsConnected && ofGetFrameNum() % 300 == 0)		isGraphicsConnected = graphics.connect();
	if (!isStaticConnected && ofGetFrameNum() % 300 == 0)		isStaticConnected = fileStatic.connect();

	// server updates data and saves to memory mapped file
	// client loads memory mapped file into object

	//myCustomData = memoryMappedFile.getData();
	if (isPhysicsConnected)		physicsData = physics.getData();
	if (isGraphicsConnected)	graphicsData = graphics.getData();
	if (isStaticConnected)		staticData = fileStatic.getData();
		

	// every 50 ms, send telemetry
	if (ofGetElapsedTimeMillis() - lastOscSentTimer > 50) {
		
		sendGraphicsTelemetryOscMessage();
		//sendFileStaticTelemetryOscMessage();
		sendPhysicsTelemetryOscMessage();	

		lastOscSentTimer = ofGetElapsedTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // server is blue, client is yellow
    (isServer) ? ofBackground(0, 255, 255) : ofBackground(255, 255, 0);

	stringstream physicsOutput, graphicsOutput, fileStaticOutput;
	if (isPhysicsConnected && isGraphicsConnected && isStaticConnected) {
		physicsOutput << "PHYSICS ====================================" << endl
			<< setw(24) << "packetId : " 			<< physicsData->packetId << endl
			<< setw(24) << "gas : " 				<< physicsData->gas << endl
			<< setw(24) << "brake : " 				<< physicsData->brake << endl
			<< setw(24) << "fuel : " 				<< physicsData->fuel << endl
			<< setw(24) << "gear : " 				<< physicsData->gear << endl
			<< setw(24) << "rpms : " 				<< physicsData->rpms << endl
			<< setw(24) << "steerAngle : "			<< physicsData->steerAngle << endl
			<< setw(24) << "speedKmh : "			<< physicsData->speedKmh << endl
			<< setw(24) << "velocity : " 			<< physicsData->velocity << endl
			<< setw(24) << "velocity : "			<< physicsData->velocity[0] << ", " << physicsData->velocity[1] << ", " << physicsData->velocity[2] << endl
			<< setw(24) << "accG : "				<< physicsData->accG[0] << ", " << physicsData->accG[1] << ", " << physicsData->accG[2]<< endl
			<< setw(24) << "wheelSlip : "			<< physicsData->wheelSlip[0] << ", " << physicsData->wheelSlip[1] << ", "<< physicsData->wheelSlip[2] << endl
			<< setw(24) << "wheelLoad : "			<< physicsData->wheelLoad[0] << ", " << physicsData->wheelLoad[1] << ", "<< physicsData->wheelLoad[2] << endl
			<< setw(24) << "wheelsPressure : "		<< physicsData->wheelsPressure[0] << ", " << physicsData->wheelsPressure[1] << ", " << physicsData->wheelsPressure[2] << endl
			<< setw(24) << "wheelAngularSpeed : "	<< physicsData->wheelAngularSpeed[0] << ", " << physicsData->wheelAngularSpeed[1] << ", " << physicsData->wheelAngularSpeed[2] << endl
			<< setw(24) << "tyreWear : "			<< physicsData->tyreWear[0] << ", " << physicsData->tyreWear[1] << ", " << physicsData->tyreWear[2] << ", " << physicsData->tyreWear[2] << endl
			<< setw(24) << "tyreDirtyLevel : "		<< physicsData->tyreDirtyLevel[0] << ", " << physicsData->tyreDirtyLevel[1] << ", "<< physicsData->tyreDirtyLevel[2] << ", "<< physicsData->tyreDirtyLevel[3] << endl
			<< setw(24) << "tyreCoreTemperature : " << physicsData->tyreCoreTemperature[0] << ", " << physicsData->tyreCoreTemperature[1] << ", " << physicsData->tyreCoreTemperature[2] << ", " << physicsData->tyreCoreTemperature[3] << endl
			<< setw(24) << "camberRAD : "			<< physicsData->camberRAD[0] << ", " << physicsData->camberRAD[1] << ", " << physicsData->camberRAD[2] << ", " << physicsData->camberRAD[3] << endl
			<< setw(24) << "suspensionTravel : "	<< physicsData->suspensionTravel[0] << ", " << physicsData->suspensionTravel[1] << ", " << physicsData->suspensionTravel[2] << ", " << physicsData->suspensionTravel[3] << endl
			<< setw(24) << "drs : " 				<< physicsData->drs << endl
			<< setw(24) << "tc : " 					<< physicsData->tc << endl
			<< setw(24) << "heading : " 			<< physicsData->heading << endl
			<< setw(24) << "pitch : " 				<< physicsData->pitch << endl
			<< setw(24) << "roll : " 				<< physicsData->roll << endl
			<< setw(24) << "cgHeight : " 			<< physicsData->cgHeight << endl
			<< setw(24) << "carDamage : " 			<< physicsData->carDamage << endl
			<< setw(24) << "numberOfTyresOut : " 	<< physicsData->numberOfTyresOut << endl
			<< setw(24) << "pitLimiterOn : " 		<< physicsData->pitLimiterOn << endl
			<< setw(24) << "abs : " 				<< physicsData->abs << endl
			<< setw(24) << "kersCharge : " 			<< physicsData->kersCharge << endl
			<< setw(24) << "kersInput : " 			<< physicsData->kersInput << endl
			<< setw(24) << "autoShifterOn : " 		<< physicsData->autoShifterOn << endl
			<< setw(24) << "rideHeight : " 			<< physicsData->rideHeight << endl
			<< setw(24) << "turboBoost : " 			<< physicsData->turboBoost << endl
			<< setw(24) << "ballast : " 			<< physicsData->ballast << endl
			<< setw(24) << "airDensity : " 			<< physicsData->airDensity << endl
			<< setw(24) << "airTemp : " 			<< physicsData->airTemp << endl
			<< setw(24) << "roadTemp : " 			<< physicsData->roadTemp << endl
			<< setw(24) << "localAngularVel : " 	<< physicsData->localAngularVel << endl
			<< setw(24) << "finalFF : " 			<< physicsData->finalFF << endl
			<< setw(24) << "performanceMeter : " 	<< physicsData->performanceMeter << endl
			<< setw(24) << "engineBrake : " 		<< physicsData->engineBrake << endl
			<< setw(24) << "ersRecoveryLevel : " 	<< physicsData->ersRecoveryLevel << endl
			<< setw(24) << "ersPowerLevel : " 		<< physicsData->ersPowerLevel << endl
			<< setw(24) << "ersHeatCharging : " 	<< physicsData->ersHeatCharging << endl
			<< setw(24) << "ersIsCharging : " 		<< physicsData->ersIsCharging << endl
			<< setw(24) << "kersCurrentKJ : " 		<< physicsData->kersCurrentKJ << endl
			<< setw(24) << "drsAvailable : " 		<< physicsData->drsAvailable << endl
			<< setw(24) << "drsEnabled : " 			<< physicsData->drsEnabled << endl;

		// graphics
		graphicsOutput << "GRAPHICS INFO =============================" << endl
			<< setw(28) << "packetID : " 				<< graphicsData->packetId << endl
			<< setw(28) << "STATUS : "					<< graphicsData->status << endl
			<< setw(28) << "session : " 				<< graphicsData->session << endl
			<< setw(28) << "completed laps : " 			<< graphicsData->completedLaps << endl
			<< setw(28) << "position : " 				<< graphicsData->position << endl
			<< setw(28) << "current time s : " 			<< WideCharToMultiByte(CP_ACP, 0, graphicsData->_currentTime, -1, graphicsData->currentTime, 15, &graphicsData->DefChar, NULL) << endl
			<< setw(28) << "lastTime : " 				<< WideCharToMultiByte(CP_ACP, 0, graphicsData->_lastTime, -1, graphicsData->lastTime, 15, &graphicsData->DefChar, NULL) << endl
			<< setw(28) << "bestTime : " 				<< WideCharToMultiByte(CP_ACP, 0, graphicsData->_bestTime, -1, graphicsData->bestTime, 15, &graphicsData->DefChar, NULL) << endl
			<< setw(28) << "split : " 					<< WideCharToMultiByte(CP_ACP, 0, graphicsData->_split, -1, graphicsData->split, 15, &graphicsData->DefChar, NULL) << endl
			<< setw(28) << "current time : " 			<< graphicsData->iCurrentTime << endl
			<< setw(28) << "last time : " 				<< graphicsData->iLastTime << endl
			<< setw(28) << "best time : " 				<< graphicsData->iBestTime << endl
			<< setw(28) << "sessionTimeLeft : " 		<< graphicsData->sessionTimeLeft << endl
			<< setw(28) << "distanceTraveled : " 		<< graphicsData->distanceTraveled << endl
			<< setw(28) << "isInPit : " 				<< graphicsData->isInPit << endl
			<< setw(28) << "currentSectorIndex : " 		<< graphicsData->currentSectorIndex << endl
			<< setw(28) << "lastSectorTime : " 			<< graphicsData->lastSectorTime << endl
			<< setw(28) << "numberOfLaps : " 			<< graphicsData->numberOfLaps << endl
			<< setw(28) << "TYRE COMPOUND : " 			<< WideCharToMultiByte(CP_ACP, 0, graphicsData->_tyreCompound, -1, graphicsData->tyreCompound, 33, &graphicsData->DefChar, NULL) << endl
			<< setw(28) << "replayMult : " 				<< graphicsData->replayTimeMultiplier << endl
			<< setw(28) << "normalizedCarPosition : " 	<< graphicsData->normalizedCarPosition << endl
			<< setw(28) << "carCoordinates : " 			<< graphicsData->carCoordinates << endl;

		// file static 
		fileStaticOutput << "STATIC INFO =============================" << endl
			<< setw(28) << "smVersion : " 				<< WideCharToMultiByte(CP_ACP, 0, staticData->_smVersion, -1, staticData->smVersion, 15, &staticData->DefChar, NULL) << endl
			<< setw(28) << "acVersion : " 				<< WideCharToMultiByte(CP_ACP, 0, staticData->_acVersion, -1, staticData->acVersion, 15, &staticData->DefChar, NULL) << endl
			<< setw(28) << "numberOfSessions : " 		<< staticData->numberOfSessions << endl
			<< setw(28) << "numCars : " 				<< staticData->numCars << endl
			<< setw(28) << "carModel : " 				<< WideCharToMultiByte(CP_ACP, 0, staticData->_carModel, -1, staticData->carModel, 33, &staticData->DefChar, NULL) << endl
			<< setw(28) << "track : " 					<< WideCharToMultiByte(CP_ACP, 0, staticData->_track, -1, staticData->track, 33, &staticData->DefChar, NULL) << endl
			<< setw(28) << "playerName : " 				<< WideCharToMultiByte(CP_ACP, 0, staticData->_playerName, -1, staticData->playerName, 33, &staticData->DefChar, NULL) << endl
			<< setw(28) << "playerSurname : " 			<< WideCharToMultiByte(CP_ACP, 0, staticData->_playerSurname, -1, staticData->playerSurname, 33, &staticData->DefChar, NULL) << endl
			<< setw(28) << "playerNick : " 				<< WideCharToMultiByte(CP_ACP, 0, staticData->_playerNick, 01, staticData->playerName, 33, &staticData->DefChar, NULL) << endl
			<< setw(28) << "sectorCount : " 			<< staticData->sectorCount << endl
			<< setw(28) << "maxTorque : " 				<< staticData->maxTorque << endl
			<< setw(28) << "maxPower : " 				<< staticData->maxPower << endl
			<< setw(28) << "maxRpm : " 					<< staticData->maxRpm << endl
			<< setw(28) << "maxFuel : " 				<< staticData->maxFuel << endl
			<< setw(28) << "suspensionMaxTravel : " 	<< staticData->suspensionMaxTravel << endl
			<< setw(28) << "tyreRadius : " 				<< staticData->tyreRadius << endl
			<< setw(28) << "maxTurboBoost : " 			<< staticData->maxTurboBoost << endl
			<< setw(28) << "deprecated_1 : " 			<< staticData->deprecated_1 << endl
			<< setw(28) << "deprecated_2 : " 			<< staticData->deprecated_2 << endl
			<< setw(28) << "penaltiesEnabled : " 		<< staticData->penaltiesEnabled << endl
			<< setw(28) << "aidFuelRate : " 			<< staticData->aidFuelRate << endl
			<< setw(28) << "aidTireRate : " 			<< staticData->aidTireRate << endl
			<< setw(28) << "aidMechanicalDamage : " 	<< staticData->aidMechanicalDamage << endl
			<< setw(28) << "aidAllowTyreBlankets : " 	<< staticData->aidAllowTyreBlankets << endl
			<< setw(28) << "aidStability : " 			<< staticData->aidStability << endl
			<< setw(28) << "aidAutoClutch : " 			<< staticData->aidAutoClutch << endl
			<< setw(28) << "aidAutoBlip : " 			<< staticData->aidAutoBlip << endl
			<< setw(28) << "hasDRS : " 					<< staticData->hasDRS << endl
			<< setw(28) << "hasERS : " 					<< staticData->hasERS << endl
			<< setw(28) << "hasKERS : " 				<< staticData->hasKERS << endl
			<< setw(28) << "kersMaxJ : " 				<< staticData->kersMaxJ << endl
			<< setw(28) << "engineBrakeSettingsCount : " << staticData->engineBrakeSettingsCount << endl
			<< setw(28) << "ersPowerControllerCount : " << staticData->ersPowerControllerCount << endl
			<< setw(28) << "trackSPlineLength : " 		<< staticData->trackSPlineLength << endl
			<< setw(28) << "trackConfiguration : " 		<< WideCharToMultiByte(CP_ACP, 0, staticData->_trackConfiguration, -1, staticData->trackConfiguration, 33, &staticData->DefChar, NULL) << endl
			<< setw(28) << "ersMaxJ : " 				<< staticData->ersMaxJ << endl
			<< setw(28) << "isTimedRace : " 			<< staticData->isTimedRace << endl
			<< setw(28) << "hasExtraLap : " 			<< staticData->hasExtraLap << endl
			<< setw(28) << "carSkin : " 				<< staticData->carSkin << endl
			<< setw(28) << "reversedGridPosition : " 	<< staticData->reversedGridPositions << endl
			<< setw(28) << "PitWindowStart : " 			<< staticData->PitWindowStart << endl
			<< setw(28) << "PitWindowEnd : " 			<< staticData->PitWindowEnd << endl;


		ofDrawBitmapStringHighlight(physicsOutput.str(), 20, 20);
		ofDrawBitmapStringHighlight(graphicsOutput.str(), 180, 20);
		ofDrawBitmapStringHighlight(fileStaticOutput.str(), 340, 20);
		
	} else {
		ofDrawBitmapStringHighlight("ACS is not running", 20, 20);
	}
}

void ofApp::sendPhysicsTelemetryOscMessage() {
	if (isPhysicsConnected) {
		string physicsOSCAddress = "/telemetry/physics/";

		ofxOscMessage packetID;
		packetID.setAddress(physicsOSCAddress + "packetID");
		packetID.addInt64Arg(physicsData->packetId);
		sender.sendMessage(packetID);

		ofxOscMessage gas;
		gas.setAddress(physicsOSCAddress + "gas");
		gas.addFloatArg(physicsData->gas);
		sender.sendMessage(gas);

		ofxOscMessage brake;
		brake.setAddress(physicsOSCAddress + "brake");
		brake.addFloatArg(physicsData->brake);
		sender.sendMessage(brake);

		ofxOscMessage fuel;
		fuel.setAddress(physicsOSCAddress + "fuel");
		fuel.addFloatArg(physicsData->fuel);
		sender.sendMessage(fuel);

		ofxOscMessage gear;
		gear.setAddress(physicsOSCAddress + "gear");
		gear.addInt64Arg(physicsData->gear);
		sender.sendMessage(gear);

		ofxOscMessage rpms;
		rpms.setAddress(physicsOSCAddress + "rpms");
		rpms.addInt64Arg(physicsData->rpms);
		sender.sendMessage(rpms);

		ofxOscMessage steerAngle;
		steerAngle.setAddress(physicsOSCAddress + "steerAngle");
		steerAngle.addFloatArg(physicsData->steerAngle);
		sender.sendMessage(steerAngle);

		ofxOscMessage speedKmh;
		speedKmh.setAddress(physicsOSCAddress + "speedKmh");
		speedKmh.addFloatArg(physicsData->speedKmh);
		sender.sendMessage(speedKmh);

		ofxOscMessage velocity;
		velocity.setAddress(physicsOSCAddress + "velocity");
		velocity.addFloatArg(physicsData->velocity[0]);
		velocity.addFloatArg(physicsData->velocity[1]);
		velocity.addFloatArg(physicsData->velocity[2]);
		sender.sendMessage(velocity);

		ofxOscMessage accG;
		accG.setAddress(physicsOSCAddress + "accG");
		accG.addFloatArg(physicsData->accG[0]);
		accG.addFloatArg(physicsData->accG[1]);
		accG.addFloatArg(physicsData->accG[2]);
		sender.sendMessage(accG);

		ofxOscMessage wheelSlip;
		wheelSlip.setAddress(physicsOSCAddress + "wheelSlip");
		wheelSlip.addFloatArg(physicsData->wheelSlip[0]);
		wheelSlip.addFloatArg(physicsData->wheelSlip[1]);
		wheelSlip.addFloatArg(physicsData->wheelSlip[2]);
		wheelSlip.addFloatArg(physicsData->wheelSlip[3]);
		sender.sendMessage(wheelSlip);

		ofxOscMessage wheelLoad;
		wheelLoad.setAddress(physicsOSCAddress + "wheelLoad");
		wheelLoad.addFloatArg(physicsData->wheelLoad[0]);
		wheelLoad.addFloatArg(physicsData->wheelLoad[1]);
		wheelLoad.addFloatArg(physicsData->wheelLoad[2]);
		wheelLoad.addFloatArg(physicsData->wheelLoad[3]);
		sender.sendMessage(wheelLoad);

		ofxOscMessage wheelPressure;
		wheelPressure.setAddress(physicsOSCAddress + "wheelPressure");
		wheelPressure.addFloatArg(physicsData->wheelsPressure[0]);
		wheelPressure.addFloatArg(physicsData->wheelsPressure[1]);
		wheelPressure.addFloatArg(physicsData->wheelsPressure[2]);
		wheelPressure.addFloatArg(physicsData->wheelsPressure[3]);
		sender.sendMessage(wheelPressure);

		ofxOscMessage wheelAngularSpeed;
		wheelAngularSpeed.setAddress(physicsOSCAddress + "wheelAngularSpeed");
		wheelAngularSpeed.addFloatArg(physicsData->wheelAngularSpeed[0]);
		wheelAngularSpeed.addFloatArg(physicsData->wheelAngularSpeed[1]);
		wheelAngularSpeed.addFloatArg(physicsData->wheelAngularSpeed[2]);
		wheelAngularSpeed.addFloatArg(physicsData->wheelAngularSpeed[3]);
		sender.sendMessage(wheelAngularSpeed);

		ofxOscMessage tyreWear;
		tyreWear.setAddress(physicsOSCAddress + "tyreWear");
		tyreWear.addFloatArg(physicsData->tyreWear[0]);
		tyreWear.addFloatArg(physicsData->tyreWear[1]);
		tyreWear.addFloatArg(physicsData->tyreWear[2]);
		tyreWear.addFloatArg(physicsData->tyreWear[3]);
		sender.sendMessage(tyreWear);

		ofxOscMessage tyreDirtyLevel;
		tyreDirtyLevel.setAddress(physicsOSCAddress + "tyreDirtyLevel");
		tyreDirtyLevel.addFloatArg(physicsData->tyreDirtyLevel[0]);
		tyreDirtyLevel.addFloatArg(physicsData->tyreDirtyLevel[1]);
		tyreDirtyLevel.addFloatArg(physicsData->tyreDirtyLevel[2]);
		tyreDirtyLevel.addFloatArg(physicsData->tyreDirtyLevel[3]);
		sender.sendMessage(tyreDirtyLevel);

		ofxOscMessage tyreCoreTemperature;
		tyreCoreTemperature.setAddress(physicsOSCAddress + "tyreCoreTemperature");
		tyreCoreTemperature.addFloatArg(physicsData->tyreCoreTemperature[0]);
		tyreCoreTemperature.addFloatArg(physicsData->tyreCoreTemperature[1]);
		tyreCoreTemperature.addFloatArg(physicsData->tyreCoreTemperature[2]);
		tyreCoreTemperature.addFloatArg(physicsData->tyreCoreTemperature[3]);
		sender.sendMessage(tyreCoreTemperature);

		ofxOscMessage camberRAD;
		camberRAD.setAddress(physicsOSCAddress + "camberRAD");
		camberRAD.addFloatArg(physicsData->camberRAD[0]);
		camberRAD.addFloatArg(physicsData->camberRAD[1]);
		camberRAD.addFloatArg(physicsData->camberRAD[2]);
		camberRAD.addFloatArg(physicsData->camberRAD[3]);
		sender.sendMessage(camberRAD);

		ofxOscMessage suspensionTravel;
		suspensionTravel.setAddress(physicsOSCAddress + "suspensionTravel");
		suspensionTravel.addFloatArg(physicsData->suspensionTravel[0]);
		suspensionTravel.addFloatArg(physicsData->suspensionTravel[1]);
		suspensionTravel.addFloatArg(physicsData->suspensionTravel[2]);
		suspensionTravel.addFloatArg(physicsData->suspensionTravel[3]);
		sender.sendMessage(suspensionTravel);

		ofxOscMessage drs;
		drs.setAddress(physicsOSCAddress + "drs");
		drs.addFloatArg(physicsData->drs);
		sender.sendMessage(drs);

		ofxOscMessage tc;
		tc.setAddress(physicsOSCAddress + "tc");
		tc.addFloatArg(physicsData->tc);
		sender.sendMessage(tc);

		ofxOscMessage heading;
		heading.setAddress(physicsOSCAddress + "heading");
		heading.addFloatArg(physicsData->heading);
		sender.sendMessage(heading);

		ofxOscMessage pitch;
		pitch.setAddress(physicsOSCAddress + "pitch");
		pitch.addFloatArg(physicsData->pitch);
		sender.sendMessage(pitch);

		ofxOscMessage roll;
		roll.setAddress(physicsOSCAddress + "roll");
		roll.addFloatArg(physicsData->roll);
		sender.sendMessage(roll);

		ofxOscMessage cgHeight;
		cgHeight.setAddress(physicsOSCAddress + "cgHeight");
		cgHeight.addFloatArg(physicsData->cgHeight);
		sender.sendMessage(cgHeight);

		ofxOscMessage carDamage;
		carDamage.setAddress(physicsOSCAddress + "carDamage");
		carDamage.addFloatArg(physicsData->carDamage[0]);
		carDamage.addFloatArg(physicsData->carDamage[1]);
		carDamage.addFloatArg(physicsData->carDamage[2]);
		carDamage.addFloatArg(physicsData->carDamage[3]);
		carDamage.addFloatArg(physicsData->carDamage[4]);
		sender.sendMessage(carDamage);

		ofxOscMessage numberOfTyresOut;
		numberOfTyresOut.setAddress(physicsOSCAddress + "numberOfTyresOut");
		numberOfTyresOut.addInt64Arg(physicsData->numberOfTyresOut);
		sender.sendMessage(numberOfTyresOut);

		ofxOscMessage pitLimiterOn;
		pitLimiterOn.setAddress(physicsOSCAddress + "pitLimiterOn");
		pitLimiterOn.addInt64Arg(physicsData->pitLimiterOn);
		sender.sendMessage(pitLimiterOn);

		ofxOscMessage abs;
		abs.setAddress(physicsOSCAddress + "abs");
		abs.addFloatArg(physicsData->abs);
		sender.sendMessage(abs);

		ofxOscMessage kersCharge;
		kersCharge.setAddress(physicsOSCAddress + "kersCharge");
		kersCharge.addFloatArg(physicsData->kersCharge);
		sender.sendMessage(kersCharge);

		ofxOscMessage kersInput;
		kersInput.setAddress(physicsOSCAddress + "kersInput");
		kersInput.addFloatArg(physicsData->kersInput);
		sender.sendMessage(kersInput);

		ofxOscMessage autoShifterOn;
		autoShifterOn.setAddress(physicsOSCAddress + "autoShifterOn");
		autoShifterOn.addInt64Arg(physicsData->autoShifterOn);
		sender.sendMessage(autoShifterOn);

		ofxOscMessage rideHeight;
		rideHeight.setAddress(physicsOSCAddress + "rightHeight");
		rideHeight.addFloatArg(physicsData->rideHeight[0]);
		rideHeight.addFloatArg(physicsData->rideHeight[1]);
		sender.sendMessage(rideHeight);

		ofxOscMessage turboBoost;
		turboBoost.setAddress(physicsOSCAddress + "turboBoost");
		turboBoost.addFloatArg(physicsData->turboBoost);
		sender.sendMessage(turboBoost);

		ofxOscMessage ballast;
		ballast.setAddress(physicsOSCAddress + "ballast");
		ballast.addFloatArg(physicsData->ballast);
		sender.sendMessage(ballast);

		ofxOscMessage airDensity;
		airDensity.setAddress(physicsOSCAddress + "airDensity");
		airDensity.addFloatArg(physicsData->airDensity);
		sender.sendMessage(airDensity);

		ofxOscMessage airTemp;
		airTemp.setAddress(physicsOSCAddress + "airTemp");
		airTemp.addFloatArg(physicsData->airTemp);
		sender.sendMessage(airTemp);

		ofxOscMessage roadTemp;
		roadTemp.setAddress(physicsOSCAddress + "roadTemp");
		roadTemp.addFloatArg(physicsData->roadTemp);
		sender.sendMessage(roadTemp);

		ofxOscMessage localAngularVel;
		localAngularVel.setAddress(physicsOSCAddress + "localAngularVel");
		localAngularVel.addFloatArg(physicsData->localAngularVel[0]);
		localAngularVel.addFloatArg(physicsData->localAngularVel[1]);
		localAngularVel.addFloatArg(physicsData->localAngularVel[2]);
		sender.sendMessage(localAngularVel);

		ofxOscMessage finalFF;
		finalFF.setAddress(physicsOSCAddress + "finalFF");
		finalFF.addFloatArg(physicsData->finalFF);
		sender.sendMessage(finalFF);

		ofxOscMessage performanceMeter;
		performanceMeter.setAddress(physicsOSCAddress + "performanceMeter");
		performanceMeter.addFloatArg(physicsData->performanceMeter);
		sender.sendMessage(performanceMeter);

		ofxOscMessage engineBrake;
		engineBrake.setAddress(physicsOSCAddress + "engineBrake");
		engineBrake.addInt64Arg(physicsData->engineBrake);
		sender.sendMessage(engineBrake);

		ofxOscMessage ersRecoveryLevel;
		ersRecoveryLevel.setAddress(physicsOSCAddress + "ersRecoveryLevel");
		ersRecoveryLevel.addInt64Arg(physicsData->ersRecoveryLevel);
		sender.sendMessage(ersRecoveryLevel);

		ofxOscMessage ersPowerLevel;
		ersPowerLevel.setAddress(physicsOSCAddress + "ersPowerLevel");
		ersPowerLevel.addInt64Arg(physicsData->ersPowerLevel);
		sender.sendMessage(ersPowerLevel);

		ofxOscMessage ersHeatCharging;
		ersHeatCharging.setAddress(physicsOSCAddress + "ersHeatCharging");
		ersHeatCharging.addInt64Arg(physicsData->ersHeatCharging);
		sender.sendMessage(ersHeatCharging);

		ofxOscMessage ersIsCharging;
		ersIsCharging.setAddress(physicsOSCAddress + "ersIsCharging");
		ersIsCharging.addInt64Arg(physicsData->ersIsCharging);
		sender.sendMessage(ersIsCharging);

		ofxOscMessage kersCurrentKJ;
		kersCurrentKJ.setAddress(physicsOSCAddress + "kersCurrentKJ");
		kersCurrentKJ.addFloatArg(physicsData->kersCurrentKJ);
		sender.sendMessage(kersCurrentKJ);

		ofxOscMessage drsAvailable;
		drsAvailable.setAddress(physicsOSCAddress + "drsAvailable");
		drsAvailable.addInt64Arg(physicsData->drsAvailable);
		sender.sendMessage(drsAvailable);

		ofxOscMessage drsEnabled;
		drsEnabled.setAddress(physicsOSCAddress + "drsEnabled");
		drsEnabled.addInt64Arg(physicsData->drsEnabled);
		sender.sendMessage(drsEnabled);

		ofxOscMessage brakeTemp;
		brakeTemp.setAddress(physicsOSCAddress + "brakeTemp");
		brakeTemp.addFloatArg(physicsData->brakeTemp[0]);
		brakeTemp.addFloatArg(physicsData->brakeTemp[1]);
		brakeTemp.addFloatArg(physicsData->brakeTemp[2]);
		brakeTemp.addFloatArg(physicsData->brakeTemp[3]);
		sender.sendMessage(brakeTemp);

		ofxOscMessage clutch;
		clutch.setAddress(physicsOSCAddress + "clutch");
		clutch.addFloatArg(physicsData->clutch);
		sender.sendMessage(clutch);

		ofxOscMessage tyreTempI;
		tyreTempI.setAddress(physicsOSCAddress + "tyreTempI");
		tyreTempI.addFloatArg(physicsData->tyreTempI[0]);
		tyreTempI.addFloatArg(physicsData->tyreTempI[1]);
		tyreTempI.addFloatArg(physicsData->tyreTempI[2]);
		tyreTempI.addFloatArg(physicsData->tyreTempI[3]);
		sender.sendMessage(tyreTempI);

		ofxOscMessage tyreTempM;
		tyreTempM.setAddress(physicsOSCAddress + "tyreTempM");
		tyreTempM.addFloatArg(physicsData->tyreTempM[0]);
		tyreTempM.addFloatArg(physicsData->tyreTempM[1]);
		tyreTempM.addFloatArg(physicsData->tyreTempM[2]);
		tyreTempM.addFloatArg(physicsData->tyreTempM[3]);
		sender.sendMessage(tyreTempM);

		ofxOscMessage tyreTempO;
		tyreTempO.setAddress(physicsOSCAddress + "tyreTempO");
		tyreTempO.addFloatArg(physicsData->tyreTempO[0]);
		tyreTempO.addFloatArg(physicsData->tyreTempO[1]);
		tyreTempO.addFloatArg(physicsData->tyreTempO[2]);
		tyreTempO.addFloatArg(physicsData->tyreTempO[3]);
		sender.sendMessage(tyreTempO);

		ofxOscMessage isAIControlled;
		isAIControlled.setAddress(physicsOSCAddress + "isAIControlled");
		isAIControlled.addInt64Arg(physicsData->isAIControlled);
		sender.sendMessage(isAIControlled);

		// tyreContactPoint
		ofxOscMessage tyreContactPointFL;
		tyreContactPointFL.setAddress(physicsOSCAddress + "tyreContactPointFL");
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[0][0]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[0][1]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[0][2]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[0][3]);
		sender.sendMessage(tyreContactPointFL);

		ofxOscMessage tyreContactPointFR;
		tyreContactPointFR.setAddress(physicsOSCAddress + "tyreContactPointFR");
		tyreContactPointFR.addFloatArg(physicsData->tyreContactPoint[1][0]);
		tyreContactPointFR.addFloatArg(physicsData->tyreContactPoint[1][1]);
		tyreContactPointFR.addFloatArg(physicsData->tyreContactPoint[1][2]);
		tyreContactPointFR.addFloatArg(physicsData->tyreContactPoint[1][3]);
		sender.sendMessage(tyreContactPointFR);

		ofxOscMessage tyreContactPointRL;
		tyreContactPointRL.setAddress(physicsOSCAddress + "tyreContactPointRL");
		tyreContactPointRL.addFloatArg(physicsData->tyreContactPoint[2][0]);
		tyreContactPointRL.addFloatArg(physicsData->tyreContactPoint[2][1]);
		tyreContactPointRL.addFloatArg(physicsData->tyreContactPoint[2][2]);
		tyreContactPointRL.addFloatArg(physicsData->tyreContactPoint[2][3]);
		sender.sendMessage(tyreContactPointRL);

		ofxOscMessage tyreContactPointRR;
		tyreContactPointRR.setAddress(physicsOSCAddress + "tyreContactPointRR");
		tyreContactPointRR.addFloatArg(physicsData->tyreContactPoint[3][0]);
		tyreContactPointRR.addFloatArg(physicsData->tyreContactPoint[3][1]);
		tyreContactPointRR.addFloatArg(physicsData->tyreContactPoint[3][2]);
		tyreContactPointRR.addFloatArg(physicsData->tyreContactPoint[3][3]);
		sender.sendMessage(tyreContactPointRR);

		// tyreContactNormal
		ofxOscMessage tyreContactNormalFL;
		tyreContactNormalFL.setAddress(physicsOSCAddress + "tyreContactNormalFL");
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[0][0]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[0][1]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[0][2]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[0][3]);
		sender.sendMessage(tyreContactNormalFL);

		ofxOscMessage tyreContactNormalFR;
		tyreContactNormalFR.setAddress(physicsOSCAddress + "tyreContactNormalFR");
		tyreContactNormalFR.addFloatArg(physicsData->tyreContactNormal[1][0]);
		tyreContactNormalFR.addFloatArg(physicsData->tyreContactNormal[1][1]);
		tyreContactNormalFR.addFloatArg(physicsData->tyreContactNormal[1][2]);
		tyreContactNormalFR.addFloatArg(physicsData->tyreContactNormal[1][3]);
		sender.sendMessage(tyreContactNormalFR);

		ofxOscMessage tyreContactNormalRL;
		tyreContactNormalRL.setAddress(physicsOSCAddress + "tyreContactNormalRL");
		tyreContactNormalRL.addFloatArg(physicsData->tyreContactNormal[2][0]);
		tyreContactNormalRL.addFloatArg(physicsData->tyreContactNormal[2][1]);
		tyreContactNormalRL.addFloatArg(physicsData->tyreContactNormal[2][2]);
		tyreContactNormalRL.addFloatArg(physicsData->tyreContactNormal[2][3]);
		sender.sendMessage(tyreContactNormalRL);

		ofxOscMessage tyreContactNormalRR;
		tyreContactNormalRR.setAddress(physicsOSCAddress + "tyreContactNormalRR");
		tyreContactNormalRR.addFloatArg(physicsData->tyreContactNormal[3][0]);
		tyreContactNormalRR.addFloatArg(physicsData->tyreContactNormal[3][1]);
		tyreContactNormalRR.addFloatArg(physicsData->tyreContactNormal[3][2]);
		tyreContactNormalRR.addFloatArg(physicsData->tyreContactNormal[3][3]);
		sender.sendMessage(tyreContactNormalRR);

		// tyreContactHeading
		ofxOscMessage tyreContactHeadingFL;
		tyreContactHeadingFL.setAddress(physicsOSCAddress + "tyreContactHeadingFL");
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[0][0]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[0][1]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[0][2]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[0][3]);
		sender.sendMessage(tyreContactHeadingFL);

		ofxOscMessage tyreContactHeadingFR;
		tyreContactHeadingFR.setAddress(physicsOSCAddress + "tyreContactHeadingFR");
		tyreContactHeadingFR.addFloatArg(physicsData->tyreContactHeading[1][0]);
		tyreContactHeadingFR.addFloatArg(physicsData->tyreContactHeading[1][1]);
		tyreContactHeadingFR.addFloatArg(physicsData->tyreContactHeading[1][2]);
		tyreContactHeadingFR.addFloatArg(physicsData->tyreContactHeading[1][3]);
		sender.sendMessage(tyreContactHeadingFR);

		ofxOscMessage tyreContactHeadingRL;
		tyreContactHeadingRL.setAddress(physicsOSCAddress + "tyreContactHeadingRL");
		tyreContactHeadingRL.addFloatArg(physicsData->tyreContactHeading[2][0]);
		tyreContactHeadingRL.addFloatArg(physicsData->tyreContactHeading[2][1]);
		tyreContactHeadingRL.addFloatArg(physicsData->tyreContactHeading[2][2]);
		tyreContactHeadingRL.addFloatArg(physicsData->tyreContactHeading[2][3]);
		sender.sendMessage(tyreContactHeadingRL);

		ofxOscMessage tyreContactHeadingRR;
		tyreContactHeadingRR.setAddress(physicsOSCAddress + "tyreContactHeadingRR");
		tyreContactHeadingRR.addFloatArg(physicsData->tyreContactHeading[3][0]);
		tyreContactHeadingRR.addFloatArg(physicsData->tyreContactHeading[3][1]);
		tyreContactHeadingRR.addFloatArg(physicsData->tyreContactHeading[3][2]);
		tyreContactHeadingRR.addFloatArg(physicsData->tyreContactHeading[3][3]);
		sender.sendMessage(tyreContactHeadingRR);

		ofxOscMessage brakeBias;
		brakeBias.setAddress(physicsOSCAddress + "brakeBias");
		brakeBias.addFloatArg(physicsData->brakeBias);
		sender.sendMessage(brakeBias);

		ofxOscMessage localVelocity;
		localVelocity.setAddress(physicsOSCAddress + "localVelocity");
		localVelocity.addFloatArg(physicsData->localVelocity[0]);
		localVelocity.addFloatArg(physicsData->localVelocity[1]);
		localVelocity.addFloatArg(physicsData->localVelocity[2]);
		sender.sendMessage(localVelocity);

	}

}

void ofApp::sendGraphicsTelemetryOscMessage(){
	if (isGraphicsConnected) {
		string graphicsOSCAddress = "/telemetry/graphics/";
		
		ofxOscMessage packetId;
		packetId.setAddress(graphicsOSCAddress + "packetId");
		packetId.addInt64Arg(graphicsData->packetId);
		sender.sendMessage(packetId);

		ofxOscMessage ac_status;
		ac_status.setAddress(graphicsOSCAddress + "ac_status");
		ac_status.addInt64Arg(graphicsData->status);
		sender.sendMessage(ac_status);

		ofxOscMessage ac_session_type;
		ac_session_type.setAddress(graphicsOSCAddress + "ac_session_type");
		ac_session_type.addInt64Arg(graphicsData->session);
		sender.sendMessage(ac_session_type);

		ofxOscMessage currentTime;
		currentTime.setAddress(graphicsOSCAddress + "currentTime");
		currentTime.addStringArg(ofToString(graphicsData->currentTime));
		sender.sendMessage(currentTime);

		ofxOscMessage lastTime;
		lastTime.setAddress(graphicsOSCAddress + "lastTime");
		lastTime.addStringArg(ofToString(graphicsData->lastTime));
		sender.sendMessage(lastTime);

		ofxOscMessage bestTime;
		bestTime.setAddress(graphicsOSCAddress + "bestTime");
		bestTime.addStringArg(ofToString(graphicsData->bestTime));
		sender.sendMessage(bestTime);

		ofxOscMessage split;
		split.setAddress(graphicsOSCAddress + "split");
		split.addStringArg(ofToString(graphicsData->split));
		sender.sendMessage(split);

		ofxOscMessage completedLaps;
		completedLaps.setAddress(graphicsOSCAddress + "completedLaps");
		completedLaps.addInt64Arg(graphicsData->completedLaps);
		sender.sendMessage(completedLaps);

		ofxOscMessage position;
		position.setAddress(graphicsOSCAddress + "position");
		position.addInt64Arg(graphicsData->position);
		sender.sendMessage(position);

		ofxOscMessage iCurrentTime;
		iCurrentTime.setAddress(graphicsOSCAddress + "iCurrentTime");
		iCurrentTime.addInt64Arg(graphicsData->iCurrentTime);
		sender.sendMessage(iCurrentTime);

		ofxOscMessage iLastTime;
		iLastTime.setAddress(graphicsOSCAddress + "iLastTime");
		iLastTime.addInt64Arg(graphicsData->iLastTime);
		sender.sendMessage(iLastTime);

		ofxOscMessage iBestTime;
		iBestTime.setAddress(graphicsOSCAddress + "iBestTime");
		iBestTime.addInt64Arg(graphicsData->iBestTime);
		sender.sendMessage(iBestTime);

		ofxOscMessage sessionTimeLeft;
		sessionTimeLeft.setAddress(graphicsOSCAddress + "sessionTimeLeft");
		sessionTimeLeft.addFloatArg(graphicsData->sessionTimeLeft);
		sender.sendMessage(sessionTimeLeft);

		ofxOscMessage distanceTraveled;
		distanceTraveled.setAddress(graphicsOSCAddress + "distanceTraveled");
		distanceTraveled.addFloatArg(graphicsData->distanceTraveled);
		sender.sendMessage(distanceTraveled);

		ofxOscMessage isInPit;
		isInPit.setAddress(graphicsOSCAddress + "isInPit");
		isInPit.addInt64Arg(graphicsData->isInPit);
		sender.sendMessage(isInPit);

		ofxOscMessage currentSectorIndex;
		currentSectorIndex.setAddress(graphicsOSCAddress + "currentSectorIndex");
		currentSectorIndex.addInt64Arg(graphicsData->currentSectorIndex);
		sender.sendMessage(currentSectorIndex);

		ofxOscMessage lastSectorTime;
		lastSectorTime.setAddress(graphicsOSCAddress + "lastSectorTime");
		lastSectorTime.addInt64Arg(graphicsData->lastSectorTime);
		sender.sendMessage(lastSectorTime);

		ofxOscMessage numberOfLaps;
		numberOfLaps.setAddress(graphicsOSCAddress + "numberOfLaps");
		numberOfLaps.addInt64Arg(graphicsData->numberOfLaps);
		sender.sendMessage(numberOfLaps);

		ofxOscMessage tyreCompound;
		tyreCompound.setAddress(graphicsOSCAddress + "tyreCompound");
		tyreCompound.addStringArg(ofToString(graphicsData->tyreCompound));
		sender.sendMessage(tyreCompound);

		ofxOscMessage replayTimeMultiplier;
		replayTimeMultiplier.setAddress(graphicsOSCAddress + "replayTimeMultiplier");
		replayTimeMultiplier.addFloatArg(graphicsData->replayTimeMultiplier);
		sender.sendMessage(replayTimeMultiplier);

		ofxOscMessage normalizedCarPosition;
		normalizedCarPosition.setAddress(graphicsOSCAddress + "normalizedCarPosition");
		normalizedCarPosition.addFloatArg(graphicsData->normalizedCarPosition);
		sender.sendMessage(normalizedCarPosition);

		ofxOscMessage carCoordinates;
		carCoordinates.setAddress(graphicsOSCAddress + "carCoordinates");
		carCoordinates.addFloatArg(graphicsData->carCoordinates[0]);
		carCoordinates.addFloatArg(graphicsData->carCoordinates[1]);
		carCoordinates.addFloatArg(graphicsData->carCoordinates[2]);
		sender.sendMessage(carCoordinates);

		ofxOscMessage penaltyTime;
		penaltyTime.setAddress(graphicsOSCAddress + "penaltyTime");
		penaltyTime.addFloatArg(graphicsData->penaltyTime);
		sender.sendMessage(penaltyTime);

		ofxOscMessage ac_flag_type;
		ac_flag_type.setAddress(graphicsOSCAddress + "ac_flag_type");
		ac_flag_type.addInt64Arg(graphicsData->flag);
		sender.sendMessage(ac_flag_type);

		ofxOscMessage idealLineOn;
		idealLineOn.setAddress(graphicsOSCAddress + "idealLineOn");
		idealLineOn.addInt64Arg(graphicsData->idealLineOn);
		sender.sendMessage(idealLineOn);

		ofxOscMessage isInPitLane;
		isInPitLane.setAddress(graphicsOSCAddress + "isInPitLane");
		isInPitLane.addInt64Arg(graphicsData->isInPitLane);
		sender.sendMessage(isInPitLane);

		ofxOscMessage surfaceGrip;
		surfaceGrip.setAddress(graphicsOSCAddress + "surfaceGrip");
		surfaceGrip.addFloatArg(graphicsData->surfaceGrip);
		sender.sendMessage(surfaceGrip);

		ofxOscMessage mandatoryPitDone;
		mandatoryPitDone.setAddress(graphicsOSCAddress + "mandatoryPitDone");
		mandatoryPitDone.addInt64Arg(graphicsData->mandatoryPitDone);
		sender.sendMessage(mandatoryPitDone);

		ofxOscMessage windSpeed;
		windSpeed.setAddress(graphicsOSCAddress + "windSpeed");
		windSpeed.addFloatArg(graphicsData->windSpeed);
		sender.sendMessage(windSpeed);

		ofxOscMessage windDirection;
		windDirection.setAddress(graphicsOSCAddress + "windDirection");
		windDirection.addFloatArg(graphicsData->windDirection);
		sender.sendMessage(windDirection);
	}
}

void ofApp::sendFileStaticTelemetryOscMessage(){
	if (isStaticConnected) {
		string fileStaticOSCAddress = "/telemetry/fileStatic/";

		ofxOscMessage smVersion;
		smVersion.setAddress(fileStaticOSCAddress + "smVersion");
		smVersion.addStringArg(ofToString(staticData->smVersion));
		sender.sendMessage(smVersion);

		ofxOscMessage acVersion;
		acVersion.setAddress(fileStaticOSCAddress + "acVersion");
		acVersion.addStringArg(ofToString(staticData->acVersion));
		sender.sendMessage(acVersion);

		ofxOscMessage numberOfSessions;
		numberOfSessions.setAddress(fileStaticOSCAddress + "numberOfSessions");
		numberOfSessions.addInt64Arg(staticData->numberOfSessions);
		sender.sendMessage(numberOfSessions);

		ofxOscMessage numCars;
		numCars.setAddress(fileStaticOSCAddress + "numCars");
		numCars.addInt64Arg(staticData->numCars);
		sender.sendMessage(numCars);

		ofxOscMessage carModel;
		carModel.setAddress(fileStaticOSCAddress + "carModel");
		carModel.addStringArg(ofToString(staticData->carModel));
		sender.sendMessage(carModel);

		ofxOscMessage track;
		track.setAddress(fileStaticOSCAddress + "track");
		track.addStringArg(ofToString(staticData->track));
		sender.sendMessage(track);

		ofxOscMessage playerName;
		playerName.setAddress(fileStaticOSCAddress + "playerName");
		playerName.addStringArg(ofToString(staticData->playerName));
		sender.sendMessage(playerName);

		ofxOscMessage playerSurname;
		playerSurname.setAddress(fileStaticOSCAddress + "playerSurname");
		playerSurname.addStringArg(ofToString(staticData->playerSurname));
		sender.sendMessage(playerSurname);

		ofxOscMessage playerNick;
		playerNick.setAddress(fileStaticOSCAddress + "playerNick");
		playerNick.addStringArg(ofToString(staticData->playerNick));
		sender.sendMessage(playerNick);

		ofxOscMessage sectorCount;
		sectorCount.setAddress(fileStaticOSCAddress + "sectorCount");
		sectorCount.addInt64Arg(staticData->sectorCount);
		sender.sendMessage(sectorCount);

		ofxOscMessage maxTorque;
		maxTorque.setAddress(fileStaticOSCAddress + "maxTorque");
		maxTorque.addFloatArg(staticData->maxTorque);
		sender.sendMessage(maxTorque);

		ofxOscMessage maxPower;
		maxPower.setAddress(fileStaticOSCAddress + "maxPower");
		maxPower.addFloatArg(staticData->maxPower);
		sender.sendMessage(maxPower);

		ofxOscMessage maxRpm;
		maxRpm.setAddress(fileStaticOSCAddress + "maxRpm");
		maxRpm.addInt64Arg(staticData->maxRpm);
		sender.sendMessage(maxRpm);

		ofxOscMessage maxFuel;
		maxFuel.setAddress(fileStaticOSCAddress + "maxFuel");
		maxFuel.addFloatArg(staticData->maxFuel);
		sender.sendMessage(maxFuel);

		ofxOscMessage suspensionMaxTravel;
		suspensionMaxTravel.setAddress(fileStaticOSCAddress + "suspensionMaxTravel");
		suspensionMaxTravel.addFloatArg(staticData->suspensionMaxTravel[0]);
		suspensionMaxTravel.addFloatArg(staticData->suspensionMaxTravel[1]);
		suspensionMaxTravel.addFloatArg(staticData->suspensionMaxTravel[2]);
		suspensionMaxTravel.addFloatArg(staticData->suspensionMaxTravel[3]);
		sender.sendMessage(suspensionMaxTravel);

		ofxOscMessage tyreRadius;
		tyreRadius.setAddress(fileStaticOSCAddress + "tyreRadius");
		tyreRadius.addFloatArg(staticData->tyreRadius[0]);
		tyreRadius.addFloatArg(staticData->tyreRadius[1]);
		tyreRadius.addFloatArg(staticData->tyreRadius[2]);
		tyreRadius.addFloatArg(staticData->tyreRadius[3]);
		sender.sendMessage(tyreRadius);

		ofxOscMessage maxTurboBoost;
		maxTurboBoost.setAddress(fileStaticOSCAddress + "maxTurboBoost");
		maxTurboBoost.addFloatArg(staticData->maxTurboBoost);
		sender.sendMessage(maxTurboBoost);

		ofxOscMessage penaltiesEnabled;
		penaltiesEnabled.setAddress(fileStaticOSCAddress + "penaltiesEnabled");
		penaltiesEnabled.addInt64Arg(staticData->penaltiesEnabled);
		sender.sendMessage(penaltiesEnabled);

		ofxOscMessage aidTireRate;
		aidTireRate.setAddress(fileStaticOSCAddress + "aidTireRate");
		aidTireRate.addFloatArg(staticData->aidTireRate);
		sender.sendMessage(aidTireRate);

		ofxOscMessage aidMechanicalDamage;
		aidMechanicalDamage.setAddress(fileStaticOSCAddress + "aidMechanicalDamage");
		aidMechanicalDamage.addFloatArg(staticData->aidMechanicalDamage);
		sender.sendMessage(aidMechanicalDamage);

		ofxOscMessage aidAllowTyreBlankets;
		aidAllowTyreBlankets.setAddress(fileStaticOSCAddress + "aidAllowTyreBlankets");
		aidAllowTyreBlankets.addInt64Arg(staticData->aidAllowTyreBlankets);
		sender.sendMessage(aidAllowTyreBlankets);

		ofxOscMessage aidStability;
		aidStability.setAddress(fileStaticOSCAddress + "aidStability");
		aidStability.addFloatArg(staticData->aidStability);
		sender.sendMessage(aidStability);

		ofxOscMessage aidAutoClutch;
		aidAutoClutch.setAddress(fileStaticOSCAddress + "aidAutoClutch");
		aidAutoClutch.addInt64Arg(staticData->aidAutoClutch);
		sender.sendMessage(aidAutoClutch);

		ofxOscMessage aidAutoBlip;
		aidAutoBlip.setAddress(fileStaticOSCAddress + "aidAutoBlip");
		aidAutoBlip.addInt64Arg(staticData->aidAutoBlip);
		sender.sendMessage(aidAutoBlip);

		ofxOscMessage hasDRS;
		hasDRS.setAddress(fileStaticOSCAddress + "hasDRS");
		hasDRS.addInt64Arg(staticData->hasDRS);
		sender.sendMessage(hasDRS);

		ofxOscMessage hasERS;
		hasERS.setAddress(fileStaticOSCAddress + "hadERS");
		hasERS.addInt64Arg(staticData->hasERS);
		sender.sendMessage(hasERS);

		ofxOscMessage hasKERS;
		hasKERS.setAddress(fileStaticOSCAddress + "hasKERS");
		hasKERS.addInt64Arg(staticData->hasKERS);
		sender.sendMessage(hasKERS);

		ofxOscMessage kersMaxJ;
		kersMaxJ.setAddress(fileStaticOSCAddress + "kersMaxJ");
		kersMaxJ.addFloatArg(staticData->kersMaxJ);
		sender.sendMessage(kersMaxJ);

		ofxOscMessage engineBrakeSettingsCount;
		engineBrakeSettingsCount.setAddress(fileStaticOSCAddress + "engineBrakeSettingsCount");
		engineBrakeSettingsCount.addInt64Arg(staticData->engineBrakeSettingsCount);
		sender.sendMessage(engineBrakeSettingsCount);

		ofxOscMessage ersPowerControllerCount;
		ersPowerControllerCount.setAddress(fileStaticOSCAddress + "ersPowerControllerCount");
		ersPowerControllerCount.addInt64Arg(staticData->ersPowerControllerCount);
		sender.sendMessage(ersPowerControllerCount);

		ofxOscMessage trackSPlineLength;
		trackSPlineLength.setAddress(fileStaticOSCAddress + "trackSPlineLength");
		trackSPlineLength.addFloatArg(staticData->trackSPlineLength);
		sender.sendMessage(trackSPlineLength);

		ofxOscMessage trackConfiguration;
		trackConfiguration.setAddress(fileStaticOSCAddress + "trackConfiguration");
		trackConfiguration.addStringArg(ofToString(staticData->trackConfiguration));
		sender.sendMessage(trackConfiguration);

		ofxOscMessage ersMaxJ;
		ersMaxJ.setAddress(fileStaticOSCAddress + "ersMaxJ");
		ersMaxJ.addFloatArg(staticData->ersMaxJ);
		sender.sendMessage(ersMaxJ);

		ofxOscMessage isTimedRace;
		isTimedRace.setAddress(fileStaticOSCAddress + "isTimedRace");
		isTimedRace.addInt64Arg(staticData->isTimedRace);
		sender.sendMessage(isTimedRace);

		ofxOscMessage hasExtraLap;
		hasExtraLap.setAddress(fileStaticOSCAddress + "hasExtraLap");
		hasExtraLap.addInt64Arg(staticData->hasExtraLap);
		sender.sendMessage(hasExtraLap);

		ofxOscMessage carSkin;
		carSkin.setAddress(fileStaticOSCAddress + "carSkin");
		carSkin.addStringArg(ofToString(staticData->carSkin));
		sender.sendMessage(carSkin);

		ofxOscMessage reversedGridPositions;
		reversedGridPositions.setAddress(fileStaticOSCAddress + "reversedGridPositions");
		reversedGridPositions.addInt64Arg(staticData->reversedGridPositions);
		sender.sendMessage(reversedGridPositions);

		ofxOscMessage PitWindowStart;
		PitWindowStart.setAddress(fileStaticOSCAddress + "PitWindowStart");
		PitWindowStart.addInt64Arg(staticData->PitWindowStart);
		sender.sendMessage(PitWindowStart);

		ofxOscMessage PitWindowEnd;
		PitWindowEnd.setAddress(fileStaticOSCAddress + "PitWindowEnd");
		PitWindowEnd.addInt64Arg(staticData->PitWindowEnd);
		sender.sendMessage(PitWindowEnd);
	}
}




			////physicsOutput << "PHYSICS ====================================" << endl
			//<< "packetId" << physicsData->packetId << endl
			//<< "gas" << physicsData->gas << endl
			//<< "brake" << physicsData->brake << endl
			//<< "fuel" << physicsData->fuel << endl
			//<< "gear" << physicsData->gear << endl
			//<< "rpms" << physicsData->rpms << endl
			//<< "steerAngle" << physicsData->steerAngle << endl
			//<< "speedKmh" << physicsData->speedKmh << endl
			//<< "velocity" << physicsData->velocity << endl
			//<< "accG" << physicsData->accG << endl
			//<< "wheelSlip" << physicsData->wheelSlip << endl
			//<< "wheelLoad" << physicsData->wheelLoad << endl
			//<< "wheelsPressure" << physicsData->wheelsPressure << endl
			//<< "wheelAngularSpeed" << physicsData->wheelAngularSpeed << endl
			//<< "tyreWear" << physicsData->tyreWear << endl
			//<< "tyreDirtyLevel" << physicsData->tyreDirtyLevel << endl
			//<< "tyreCoreTemperature" << physicsData->tyreCoreTemperature << endl
			//<< "camberRAD" << physicsData->camberRAD << endl
			//<< "suspensionTravel" << physicsData->suspensionTravel << endl
			//<< "drs" << physicsData->drs << endl
			//<< "tc" << physicsData->tc << endl
			//<< "heading" << physicsData->heading << endl
			//<< "pitch" << physicsData->pitch << endl
			//<< "roll" << physicsData->roll << endl
			//<< "cgHeight" << physicsData->cgHeight << endl
			//<< "carDamage" << physicsData->carDamage << endl
			//<< "numberOfTyresOut" << physicsData->numberOfTyresOut << endl
			//<< "pitLimiterOn" << physicsData->pitLimiterOn << endl
			//<< "abs" << physicsData->abs << endl
			//<< "kersCharge" << physicsData->kersCharge << endl
			//<< "kersInput" << physicsData->kersInput << endl
			//<< "autoShifterOn" << physicsData->autoShifterOn << endl
			//<< "rideHeight" << physicsData->rideHeight << endl
			//<< "turboBoost" << physicsData->turboBoost << endl
			//<< "ballast" << physicsData->ballast << endl
			//<< "airDensity" << physicsData->airDensity << endl
			//<< "airTemp" << physicsData->airTemp << endl
			//<< "roadTemp" << physicsData->roadTemp << endl
			//<< "localAngularVel" << physicsData->localAngularVel << endl
			//<< "finalFF" << physicsData->finalFF << endl
			//<< "performanceMeter" << physicsData->performanceMeter << endl
			//<< "engineBrake" << physicsData->engineBrake << endl
			//<< "ersRecoveryLevel" << physicsData->ersRecoveryLevel << endl
			//<< "ersPowerLevel" << physicsData->ersPowerLevel << endl
			//<< "ersHeatCharging" << physicsData->ersHeatCharging << endl
			//<< "ersIsCharging" << physicsData->ersIsCharging << endl
			//<< "kersCurrentKJ" << physicsData->kersCurrentKJ << endl
			//<< "drsAvailable" << physicsData->drsAvailable << endl
			//<< "drsEnabled" << physicsData->drsEnabled << endl;
			//<< ""
	//&& isGraphicsConnected && isFileStaticConnected)
		//graphicsOutput << "GRAPHICS INFO =============================" << endl
			/*<< "packetID" << graphicsData->packetId << endl
			<< "STATUS " << graphicsData->status << endl
			<< "session" << graphicsData->session << endl
			<< "completed laps" << graphicsData->completedLaps << endl
			<< "position" << graphicsData->position << endl
			<< "current time s" << graphicsData->currentTime << endl
			<< "current time" << graphicsData->iCurrentTime << endl
			<< "last time" << graphicsData->iLastTime << endl
			<< "best time" << graphicsData->iBestTime << endl
			<< "sessionTimeLeft" << graphicsData->sessionTimeLeft << endl
			<< "distanceTraveled" << graphicsData->distanceTraveled << endl
			<< "isInPit" << graphicsData->isInPit << endl
			<< "currentSectorIndex" << graphicsData->currentSectorIndex << endl
			<< "lastSectorTime" << graphicsData->lastSectorTime << endl
			<< "numberOfLaps" << graphicsData->numberOfLaps << endl
			<< "TYRE COMPOUND : " << graphicsData->tyreCompound << endl
			<< "replayMult" << graphicsData->replayTimeMultiplier << endl
			<< "normalizedCarPosition" << graphicsData->normalizedCarPosition << endl
			<< "carCoordinates" << graphicsData->carCoordinates << endl;

		fileStaticOutput << "STATIC INFO =============================" << endl
			<< "smVersion" << staticData->smVersion << endl
			<< "acVersion" << staticData->acVersion << endl
			<< "numberOfSessions" << staticData->numberOfSessions << endl
			<< "numCars" << staticData->numCars << endl
			<< "carModel" << staticData->carModel << endl
			<< "track" << staticData->track << endl
			<< "playerName" << staticData->playerName << endl
			<< "playerSurname" << staticData->playerSurname << endl
			<< "playerNick" << staticData->playerNick << endl
			<< "sectorCount" << staticData->sectorCount << endl
			<< "maxTorque" << staticData->maxTorque << endl
			<< "maxPower" << staticData->maxPower << endl
			<< "maxRpm" << staticData->maxRpm << endl
			<< "maxFuel" << staticData->maxFuel << endl
			<< "suspensionMaxTravel" << staticData->suspensionMaxTravel << endl
			<< "tyreRadius" << staticData->tyreRadius << endl
			<< "maxTurboBoost" << staticData->maxTurboBoost << endl
			<< "deprecated_1" << staticData->deprecated_1 << endl
			<< "deprecated_2" << staticData->deprecated_2 << endl
			<< "penaltiesEnabled" << staticData->penaltiesEnabled << endl
			<< "aidFuelRate" << staticData->aidFuelRate << endl
			<< "aidTireRate" << staticData->aidTireRate << endl
			<< "aidMechanicalDamage" << staticData->aidMechanicalDamage << endl
			<< "aidAllowTyreBlankets" << staticData->aidAllowTyreBlankets << endl
			<< "aidStability" << staticData->aidStability << endl
			<< "aidAutoClutch" << staticData->aidAutoClutch << endl
			<< "aidAutoBlip" << staticData->aidAutoBlip << endl
			<< "hasDRS" << staticData->hasDRS << endl
			<< "hasERS" << staticData->hasERS << endl
			<< "hasKERS" << staticData->hasKERS << endl
			<< "kersMaxJ" << staticData->kersMaxJ << endl
			<< "engineBrakeSettingsCount" << staticData->engineBrakeSettingsCount << endl
			<< "ersPowerControllerCount" << staticData->ersPowerControllerCount << endl

			<< "trackSPlineLength" << staticData->trackSPlineLength << endl
			<< "trackConfiguration" << staticData->trackConfiguration << endl;*/
//}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ }
//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }