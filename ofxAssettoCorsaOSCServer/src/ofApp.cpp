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
	fileStaticData = new SPageFileStatic();
    
	physics.setup("Local\\acpmf_physics", sizeof(physics), false);
	graphics.setup("Local\\acpmf_graphics", sizeof(graphics), false);
	fileStatic.setup("Local\\acpmf_static", sizeof(fileStatic), false);
	
	// setup + connect
	//memoryMappedFile.setup(memoryKey, memorySize, isServer);

    isConnected = physics.connect() && graphics.connect() && fileStatic.connect();

	isPhysicsConnected = physics.connect();
	isGraphicsConnected = graphics.connect();
	isFileStaticConnected = fileStatic.connect();
    
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
	if (!isFileStaticConnected && ofGetFrameNum() % 300 == 0)	isFileStaticConnected = fileStatic.connect();

	// server updates data and saves to memory mapped file
	// client loads memory mapped file into object

	//myCustomData = memoryMappedFile.getData();
	if (isPhysicsConnected && isGraphicsConnected && isFileStaticConnected) {
		physicsData = physics.getData();
		graphicsData = graphics.getData();
		fileStaticData = fileStatic.getData();
	}

	// every 100 ms, send telemetry
	if (ofGetElapsedTimeMillis() - lastOscSentTimer > 100) {
		sendPhysicsTelemetryOscMessage();
		sendFileGraphicTelemetryOscMessage();
		sendFileStaticTelemetryOscMessae();
		lastOscSentTimer = ofGetElapsedTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // server is blue, client is yellow
    (isServer) ? ofBackground(0, 255, 255) : ofBackground(255, 255, 0);

	stringstream physicsOutput, graphicsOutput, fileStaticOutput;
	if (isPhysicsConnected && isGraphicsConnected && isFileStaticConnected) {
		physicsOutput << "PHYSICS ====================================" << endl
			<< "packetId" << physicsData->packetId << endl
			<< "gas" << physicsData->gas << endl
			<< "brake" << physicsData->brake << endl
			<< "fuel" << physicsData->fuel << endl
			<< "gear" << physicsData->gear << endl
			<< "rpms" << physicsData->rpms << endl
			<< "steerAngle" << physicsData->steerAngle << endl
			<< "speedKmh" << physicsData->speedKmh << endl
			<< "velocity" << physicsData->velocity << endl
			<< "accG" << physicsData->accG << endl
			<< "wheelSlip" << physicsData->wheelSlip << endl
			<< "wheelLoad" << physicsData->wheelLoad << endl
			<< "wheelsPressure" << physicsData->wheelsPressure << endl
			<< "wheelAngularSpeed" << physicsData->wheelAngularSpeed << endl
			<< "tyreWear" << physicsData->tyreWear << endl
			<< "tyreDirtyLevel" << physicsData->tyreDirtyLevel << endl
			<< "tyreCoreTemperature" << physicsData->tyreCoreTemperature << endl
			<< "camberRAD" << physicsData->camberRAD << endl
			<< "suspensionTravel" << physicsData->suspensionTravel << endl
			<< "drs" << physicsData->drs << endl
			<< "tc" << physicsData->tc << endl
			<< "heading" << physicsData->heading << endl
			<< "pitch" << physicsData->pitch << endl
			<< "roll" << physicsData->roll << endl
			<< "cgHeight" << physicsData->cgHeight << endl
			<< "carDamage" << physicsData->carDamage << endl
			<< "numberOfTyresOut" << physicsData->numberOfTyresOut << endl
			<< "pitLimiterOn" << physicsData->pitLimiterOn << endl
			<< "abs" << physicsData->abs << endl
			<< "kersCharge" << physicsData->kersCharge << endl
			<< "kersInput" << physicsData->kersInput << endl
			<< "autoShifterOn" << physicsData->autoShifterOn << endl
			<< "rideHeight" << physicsData->rideHeight << endl
			<< "turboBoost" << physicsData->turboBoost << endl
			<< "ballast" << physicsData->ballast << endl
			<< "airDensity" << physicsData->airDensity << endl
			<< "airTemp" << physicsData->airTemp << endl
			<< "roadTemp" << physicsData->roadTemp << endl
			<< "localAngularVel" << physicsData->localAngularVel << endl
			<< "finalFF" << physicsData->finalFF << endl
			<< "performanceMeter" << physicsData->performanceMeter << endl
			<< "engineBrake" << physicsData->engineBrake << endl
			<< "ersRecoveryLevel" << physicsData->ersRecoveryLevel << endl
			<< "ersPowerLevel" << physicsData->ersPowerLevel << endl
			<< "ersHeatCharging" << physicsData->ersHeatCharging << endl
			<< "ersIsCharging" << physicsData->ersIsCharging << endl
			<< "kersCurrentKJ" << physicsData->kersCurrentKJ << endl
			<< "drsAvailable" << physicsData->drsAvailable << endl
			<< "drsEnabled" << physicsData->drsEnabled << endl;

		graphicsOutput << "GRAPHICS INFO =============================" << endl
			<< "packetID" << graphicsData->packetId << endl
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
			<< "smVersion" << fileStaticData->smVersion << endl
			<< "acVersion" << fileStaticData->acVersion << endl
			<< "numberOfSessions" << fileStaticData->numberOfSessions << endl
			<< "numCars" << fileStaticData->numCars << endl
			<< "carModel" << fileStaticData->carModel << endl
			<< "track" << fileStaticData->track << endl
			<< "playerName" << fileStaticData->playerName << endl
			<< "playerSurname" << fileStaticData->playerSurname << endl
			<< "playerNick" << fileStaticData->playerNick << endl
			<< "sectorCount" << fileStaticData->sectorCount << endl
			<< "maxTorque" << fileStaticData->maxTorque << endl
			<< "maxPower" << fileStaticData->maxPower << endl
			<< "maxRpm" << fileStaticData->maxRpm << endl
			<< "maxFuel" << fileStaticData->maxFuel << endl
			<< "suspensionMaxTravel" << fileStaticData->suspensionMaxTravel << endl
			<< "tyreRadius" << fileStaticData->tyreRadius << endl
			<< "maxTurboBoost" << fileStaticData->maxTurboBoost << endl
			<< "deprecated_1" << fileStaticData->deprecated_1 << endl
			<< "deprecated_2" << fileStaticData->deprecated_2 << endl
			<< "penaltiesEnabled" << fileStaticData->penaltiesEnabled << endl
			<< "aidFuelRate" << fileStaticData->aidFuelRate << endl
			<< "aidTireRate" << fileStaticData->aidTireRate << endl
			<< "aidMechanicalDamage" << fileStaticData->aidMechanicalDamage << endl
			<< "aidAllowTyreBlankets" << fileStaticData->aidAllowTyreBlankets << endl
			<< "aidStability" << fileStaticData->aidStability << endl
			<< "aidAutoClutch" << fileStaticData->aidAutoClutch << endl
			<< "aidAutoBlip" << fileStaticData->aidAutoBlip << endl
			<< "hasDRS" << fileStaticData->hasDRS << endl
			<< "hasERS" << fileStaticData->hasERS << endl
			<< "hasKERS" << fileStaticData->hasKERS << endl
			<< "kersMaxJ" << fileStaticData->kersMaxJ << endl
			<< "engineBrakeSettingsCount" << fileStaticData->engineBrakeSettingsCount << endl
			<< "ersPowerControllerCount" << fileStaticData->ersPowerControllerCount << endl

			<< "trackSPlineLength" << fileStaticData->trackSPlineLength << endl
			<< "trackConfiguration" << fileStaticData->trackConfiguration << endl;

		ofDrawBitmapStringHighlight(physicsOutput.str(), 20, 20);
		ofDrawBitmapStringHighlight(graphicsOutput.str(), 180, 20);
		ofDrawBitmapStringHighlight(fileStaticOutput.str(), 340, 20);
		
	} else {
		ofDrawBitmapStringHighlight("ACS is not running", 20, 20);
	}
}

void ofApp::sendPhysicsTelemetryOscMessage() {
	//stringstream physicsOutput, graphicsOutput, fileStaticOutput;
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
		tyreTempI.setAddress(physicsOSCAddress + "tyreTempM");
		tyreTempI.addFloatArg(physicsData->tyreTempM[0]);
		tyreTempI.addFloatArg(physicsData->tyreTempM[1]);
		tyreTempI.addFloatArg(physicsData->tyreTempM[2]);
		tyreTempI.addFloatArg(physicsData->tyreTempM[3]);
		sender.sendMessage(tyreTempM);

		ofxOscMessage tyreTempO;
		tyreTempI.setAddress(physicsOSCAddress + "tyreTempO");
		tyreTempI.addFloatArg(physicsData->tyreTempO[0]);
		tyreTempI.addFloatArg(physicsData->tyreTempO[1]);
		tyreTempI.addFloatArg(physicsData->tyreTempO[2]);
		tyreTempI.addFloatArg(physicsData->tyreTempO[3]);
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
		tyreContactPointFL.setAddress(physicsOSCAddress + "tyreContactPointFR");
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[1][0]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[1][1]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[1][2]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[1][3]);
		sender.sendMessage(tyreContactPointFR);

		ofxOscMessage tyreContactPointRL;
		tyreContactPointFL.setAddress(physicsOSCAddress + "tyreContactPointRL");
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[2][0]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[2][1]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[2][2]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[2][3]);
		sender.sendMessage(tyreContactPointRL);

		ofxOscMessage tyreContactPointRR;
		tyreContactPointFL.setAddress(physicsOSCAddress + "tyreContactPointRR");
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[3][0]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[3][1]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[3][2]);
		tyreContactPointFL.addFloatArg(physicsData->tyreContactPoint[3][3]);
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
		tyreContactNormalFL.setAddress(physicsOSCAddress + "tyreContactNormalFR");
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[1][0]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[1][1]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[1][2]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[1][3]);
		sender.sendMessage(tyreContactNormalFR);

		ofxOscMessage tyreContactNormalRL;
		tyreContactNormalFL.setAddress(physicsOSCAddress + "tyreContactNormalRL");
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[2][0]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[2][1]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[2][2]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[2][3]);
		sender.sendMessage(tyreContactNormalRL);

		ofxOscMessage tyreContactNormalRR;
		tyreContactNormalFL.setAddress(physicsOSCAddress + "tyreContactNormalRR");
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[3][0]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[3][1]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[3][2]);
		tyreContactNormalFL.addFloatArg(physicsData->tyreContactNormal[3][3]);
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
		tyreContactHeadingFL.setAddress(physicsOSCAddress + "tyreContactHeadingFR");
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[1][0]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[1][1]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[1][2]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[1][3]);
		sender.sendMessage(tyreContactHeadingFR);

		ofxOscMessage tyreContactHeadingRL;
		tyreContactHeadingFL.setAddress(physicsOSCAddress + "tyreContactHeadingRL");
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[2][0]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[2][1]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[2][2]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[2][3]);
		sender.sendMessage(tyreContactHeadingRL);

		ofxOscMessage tyreContactHeadingRR;
		tyreContactHeadingFL.setAddress(physicsOSCAddress + "tyreContactHeadingRR");
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[3][0]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[3][1]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[3][2]);
		tyreContactHeadingFL.addFloatArg(physicsData->tyreContactHeading[3][3]);
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

void ofApp::sendFileGraphicTelemetryOscMessage(){
	if (isGraphicsConnected) {

	}
}

void ofApp::sendFileStaticTelemetryOscMessae(){
	if (isFileStaticConnected) {

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
			<< "smVersion" << fileStaticData->smVersion << endl
			<< "acVersion" << fileStaticData->acVersion << endl
			<< "numberOfSessions" << fileStaticData->numberOfSessions << endl
			<< "numCars" << fileStaticData->numCars << endl
			<< "carModel" << fileStaticData->carModel << endl
			<< "track" << fileStaticData->track << endl
			<< "playerName" << fileStaticData->playerName << endl
			<< "playerSurname" << fileStaticData->playerSurname << endl
			<< "playerNick" << fileStaticData->playerNick << endl
			<< "sectorCount" << fileStaticData->sectorCount << endl
			<< "maxTorque" << fileStaticData->maxTorque << endl
			<< "maxPower" << fileStaticData->maxPower << endl
			<< "maxRpm" << fileStaticData->maxRpm << endl
			<< "maxFuel" << fileStaticData->maxFuel << endl
			<< "suspensionMaxTravel" << fileStaticData->suspensionMaxTravel << endl
			<< "tyreRadius" << fileStaticData->tyreRadius << endl
			<< "maxTurboBoost" << fileStaticData->maxTurboBoost << endl
			<< "deprecated_1" << fileStaticData->deprecated_1 << endl
			<< "deprecated_2" << fileStaticData->deprecated_2 << endl
			<< "penaltiesEnabled" << fileStaticData->penaltiesEnabled << endl
			<< "aidFuelRate" << fileStaticData->aidFuelRate << endl
			<< "aidTireRate" << fileStaticData->aidTireRate << endl
			<< "aidMechanicalDamage" << fileStaticData->aidMechanicalDamage << endl
			<< "aidAllowTyreBlankets" << fileStaticData->aidAllowTyreBlankets << endl
			<< "aidStability" << fileStaticData->aidStability << endl
			<< "aidAutoClutch" << fileStaticData->aidAutoClutch << endl
			<< "aidAutoBlip" << fileStaticData->aidAutoBlip << endl
			<< "hasDRS" << fileStaticData->hasDRS << endl
			<< "hasERS" << fileStaticData->hasERS << endl
			<< "hasKERS" << fileStaticData->hasKERS << endl
			<< "kersMaxJ" << fileStaticData->kersMaxJ << endl
			<< "engineBrakeSettingsCount" << fileStaticData->engineBrakeSettingsCount << endl
			<< "ersPowerControllerCount" << fileStaticData->ersPowerControllerCount << endl

			<< "trackSPlineLength" << fileStaticData->trackSPlineLength << endl
			<< "trackConfiguration" << fileStaticData->trackConfiguration << endl;*/
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