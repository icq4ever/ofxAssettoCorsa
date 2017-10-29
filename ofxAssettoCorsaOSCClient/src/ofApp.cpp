#include "ofApp.h"
#define PORT 9000

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);

	receiver.setup(PORT);

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
			physicsData->wheelSlip[0] = m.getArgAsFloat(0);
			physicsData->wheelSlip[1] = m.getArgAsFloat(1);
			physicsData->wheelSlip[2] = m.getArgAsFloat(2);
			physicsData->wheelSlip[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "wheelLoad") {
			physicsData->wheelLoad[0] = m.getArgAsFloat(0);
			physicsData->wheelLoad[1] = m.getArgAsFloat(1);
			physicsData->wheelLoad[2] = m.getArgAsFloat(2);
			physicsData->wheelLoad[1] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "wheelPressure") {
			physicsData->wheelsPressure[0] = m.getArgAsFloat(0);
			physicsData->wheelsPressure[1] = m.getArgAsFloat(1);
			physicsData->wheelsPressure[2] = m.getArgAsFloat(2);
			physicsData->wheelsPressure[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "wheelAngularSpeed") {
			physicsData->wheelAngularSpeed[0] = m.getArgAsFloat(0);
			physicsData->wheelAngularSpeed[1] = m.getArgAsFloat(1);
			physicsData->wheelAngularSpeed[2] = m.getArgAsFloat(2);
			physicsData->wheelAngularSpeed[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreWear") {
			physicsData->tyreWear[0] = m.getArgAsFloat(0);
			physicsData->tyreWear[1] = m.getArgAsFloat(1);
			physicsData->tyreWear[2] = m.getArgAsFloat(2);
			physicsData->tyreWear[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreDirtyLevel") {
			physicsData->tyreDirtyLevel[0] = m.getArgAsFloat(0);
			physicsData->tyreDirtyLevel[1] = m.getArgAsFloat(1);
			physicsData->tyreDirtyLevel[2] = m.getArgAsFloat(2);
			physicsData->tyreDirtyLevel[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "tyreCoreTemprature") {
			physicsData->tyreCoreTemperature[0] = m.getArgAsFloat(0);
			physicsData->tyreCoreTemperature[1] = m.getArgAsFloat(1);
			physicsData->tyreCoreTemperature[2] = m.getArgAsFloat(2);
			physicsData->tyreCoreTemperature[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "camberRAD") {
			physicsData->camberRAD[0] = m.getArgAsFloat(0);
			physicsData->camberRAD[1] = m.getArgAsFloat(1);
			physicsData->camberRAD[2] = m.getArgAsFloat(2);
			physicsData->camberRAD[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == physicsOSCAddress + "suspensionTravel") {
			physicsData->suspensionTravel[0] = m.getArgAsFloat(0);
			physicsData->suspensionTravel[1] = m.getArgAsFloat(1);
			physicsData->suspensionTravel[2] = m.getArgAsFloat(2);
			physicsData->suspensionTravel[3] = m.getArgAsFloat(3);
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
			physicsData->brakeTemp[0] = m.getArgAsFloat(0);
			physicsData->brakeTemp[1] = m.getArgAsFloat(1);
			physicsData->brakeTemp[2] = m.getArgAsFloat(2);
			physicsData->brakeTemp[3] = m.getArgAsFloat(3);
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


		// file static OSC message
		if (m.getAddress() == fileStaticOSCAddress + "smVersion")			fileStaticData->smVersion = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "acVersion")			fileStaticData->acVersion = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "numberOfSessions")	fileStaticData->numberOfSessions = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "numCars")				fileStaticData->numCars = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "carModel")			fileStaticData->carModel = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "track")				fileStaticData->track = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "playerName")			fileStaticData->playerName = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "playerSurname")		fileStaticData->playerSurname = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "playerNick")			fileStaticData->playerNick = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "sectorCount")			fileStaticData->sectorCount = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "maxTorque")			fileStaticData->maxTorque = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "maxPower")			fileStaticData->maxPower = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "maxRpm")				fileStaticData->maxRpm = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "maxFuel")				fileStaticData->maxFuel = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "suspensionMaxTravel") {
			fileStaticData->suspensionMaxTravel[0] = m.getArgAsFloat(0);
			fileStaticData->suspensionMaxTravel[1] = m.getArgAsFloat(1);
			fileStaticData->suspensionMaxTravel[2] = m.getArgAsFloat(2);
			fileStaticData->suspensionMaxTravel[3] = m.getArgAsFloat(3);
		}
		if (m.getAddress() == fileStaticOSCAddress + "tyreRadius") {
			fileStaticData->tyreRadius[0] = m.getArgAsFloat(0);
			fileStaticData->tyreRadius[1] = m.getArgAsFloat(1);
			fileStaticData->tyreRadius[2] = m.getArgAsFloat(2);
			fileStaticData->tyreRadius[3] = m.getArgAsFloat(3);
		}

		if (m.getAddress() == fileStaticOSCAddress + "maxTurboBoost")		fileStaticData->maxTurboBoost = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "penaltiesEnabled")	fileStaticData->penaltiesEnabled = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "aidTireRate")			fileStaticData->aidTireRate = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "aidMechanicalDamage")	fileStaticData->aidMechanicalDamage = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "aidAllowTyreBlankets")	fileStaticData->aidAllowTyreBlankets = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "aidStability")		fileStaticData->aidStability = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "aidAutoClutch")		fileStaticData->aidAutoClutch = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "aidAutoBlip")			fileStaticData->aidAutoBlip = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "hasDRS")				fileStaticData->hasDRS = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "hasERS")				fileStaticData->hasERS = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "hasKERS")				fileStaticData->hasKERS = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "kersMaxJ")			fileStaticData->kersMaxJ = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "engineBrakeSettingsCount")	fileStaticData->engineBrakeSettingsCount = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "ersPowercontrollerCount")		fileStaticData->ersPowerControllerCount = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "trackSPlineLength")			fileStaticData->trackSPlineLength = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "trackConfiguration")			fileStaticData->trackConfiguration = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "ersMaxJ")						fileStaticData->ersMaxJ = m.getArgAsFloat(0);
		if (m.getAddress() == fileStaticOSCAddress + "isTimedRace")					fileStaticData->isTimedRace = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "hasExtraLap")					fileStaticData->hasExtraLap = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "carSkin")						fileStaticData->carSkin = m.getArgAsString(0);
		if (m.getAddress() == fileStaticOSCAddress + "reversedGridPositions")		fileStaticData->reversedGridPositions = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "PitWindowStart")				fileStaticData->PitWindowStart = m.getArgAsInt64(0);
		if (m.getAddress() == fileStaticOSCAddress + "PitWindowEnd")				fileStaticData->PitWindowEnd = m.getArgAsInt64(0);


		//graphics OSC message
		if (m.getAddress() == graphicsOSCAddress + "packetId")				graphicsData->packetId = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "ac_status")				graphicsData->status = (AC_STATUS)m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "ac_session_type")		graphicsData->session = (AC_SESSION_TYPE)m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "currentTime")			graphicsData->currentTime = m.getArgAsString(0);
		if (m.getAddress() == graphicsOSCAddress + "lastTime")				graphicsData->lastTime = m.getArgAsString(0);
		if (m.getAddress() == graphicsOSCAddress + "bestTime")				graphicsData->bestTime = m.getArgAsString(0);
		if (m.getAddress() == graphicsOSCAddress + "split")					graphicsData->split = m.getArgAsString(0);
		if (m.getAddress() == graphicsOSCAddress + "completedLaps")			graphicsData->completedLaps = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "position")				graphicsData->position = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "iCurrentTime")			graphicsData->iCurrentTime = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "iLastTime")				graphicsData->iLastTime = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "iBestTime")				graphicsData->iBestTime = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "sessionTimeLeft")		graphicsData->sessionTimeLeft = m.getArgAsFloat(0);
		if (m.getAddress() == graphicsOSCAddress + "distanceTraveled")		graphicsData->distanceTraveled = m.getArgAsFloat(0);
		if (m.getAddress() == graphicsOSCAddress + "isInPit")				graphicsData->isInPit = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "currentSectorIndex")	graphicsData->currentSectorIndex = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "lastSectorTime")		graphicsData->lastSectorTime = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "numberOfLaps")			graphicsData->numberOfLaps = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "tyreCompound")			graphicsData->tyreCompound = m.getArgAsString(0);
		if (m.getAddress() == graphicsOSCAddress + "replayTimeMultiplier")	graphicsData->replayTimeMultiplier = m.getArgAsFloat(0);
		if (m.getAddress() == graphicsOSCAddress + "normalizedCarPosition")	graphicsData->normalizedCarPosition = m.getArgAsFloat(0);
		if (m.getAddress() == graphicsOSCAddress + "carCoordinages") {
			graphicsData->carCoordinates[0] = m.getArgAsFloat(0);
			graphicsData->carCoordinates[1] = m.getArgAsFloat(1);
			graphicsData->carCoordinates[2] = m.getArgAsFloat(2);
		}

		if (m.getAddress() == graphicsOSCAddress + "penaltyTime")			graphicsData->penaltyTime = m.getArgAsFloat(0);
		if (m.getAddress() == graphicsOSCAddress + "ac_flag_type")			graphicsData->flag = (AC_FLAG_TYPE)m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "idealLineOn")			graphicsData->idealLineOn = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "isInPitLane")			graphicsData->isInPitLane = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "surfaceGrip")			graphicsData->surfaceGrip = m.getArgAsFloat(0);
		if (m.getAddress() == graphicsOSCAddress + "mandatoryPitDone")		graphicsData->mandatoryPitDone = m.getArgAsInt64(0);
		if (m.getAddress() == graphicsOSCAddress + "windSpeed")				graphicsData->windSpeed = m.getArgAsFloat(0);
		if (m.getAddress() == graphicsOSCAddress + "windDirection")			graphicsData->windDirection = m.getArgAsFloat(0);

	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	stringstream physicsOutut;
	physicsOutput << "PHYSICS =================================================================" << endl << endl
		<< setw(24) << "packetID : "			<< physicsData->packetId << endl
		<< setw(24) << "gas : "					<< physicsData->gas << endl
		<< setw(24) << "brake : "				<< physicsData->brake << endl
		<< setw(24) << "fuel : "				<< physicsData->fuel << endl
		<< setw(24) << "gear : "				<< physicsData->gear << endl
		<< setw(24) << "rpms : "				<< physicsData->rpms << endl
		<< setw(24) << "steerAngle : "			<< physicsData->steerAngle << endl
		<< setw(24) << "speedKmh : "			<< physicsData->speedKmh << endl
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
		<< setw(24) << "drs : "					<< physicsData->drs << endl
		<< setw(24) << "tc : "					<< physicsData->tc << endl
		<< setw(24) << "heading : "				<< physicsData->heading << endl
		<< setw(24) << "pitch : "				<< physicsData->pitch << endl
		<< setw(24) << "roll : "				<< physicsData->roll << endl
		<< setw(24) << "cgHeight : "			<< physicsData->cgHeight << endl
		<< setw(24) << "carDamage : "			<< physicsData->carDamage[0] << ", " << physicsData->carDamage[1] << ", " << physicsData->carDamage[2] << ", " << physicsData->carDamage[3] << ", " << physicsData->carDamage[4] << endl
		<< setw(24) << "numberOfTyresOut : "	<< physicsData->numberOfTyresOut << endl
		<< setw(24) << "pitLimiterOn : "		<< physicsData->pitLimiterOn << endl
		<< setw(24) << "abs : "					<< physicsData->abs << endl
		<< setw(24) << "kersCharge : "			<< physicsData->kersCharge << endl
		<< setw(24) << "kersInput : "			<< physicsData->kersInput << endl
		<< setw(24) << "autoShifterOn : "		<< physicsData->autoShifterOn << endl
		<< setw(24) << "rideHeight : "			<< physicsData->rideHeight[0] << ", " << physicsData->rideHeight[1] << endl
		<< setw(24) << "turboBoost : "			<< physicsData->turboBoost << endl
		<< setw(24) << "ballast : "				<< physicsData->ballast << endl
		<< setw(24) << "airDensity : "			<< physicsData->airDensity << endl
		<< setw(24) << "airTemp : "				<< physicsData->airTemp << endl
		<< setw(24) << "roadTemp : "			<< physicsData->roadTemp << endl
		<< setw(24) << "localAngularVel : "		<< physicsData->localAngularVel[0] << ", " << physicsData->localAngularVel[1] << ", " << physicsData->localAngularVel[2] << endl
		<< setw(24) << "finalFF : "				<< physicsData->finalFF << endl
		<< setw(24) << "performanceMeter : "	<< physicsData->performanceMeter << endl
		<< setw(24) << "engineBrake : "			<< physicsData->engineBrake << endl
		<< setw(24) << "ersRecoveryLevel : "	<< physicsData->ersRecoveryLevel << endl
		<< setw(24) << "ersPowerLevel : "		<< physicsData->ersPowerLevel << endl
		<< setw(24) << "ersHeatCharging : "		<< physicsData->ersHeatCharging << endl
		<< setw(24) << "ersIsCharging : "		<< physicsData->ersIsCharging << endl
		<< setw(24) << "kersCurrentKJ : "		<< physicsData->kersCurrentKJ << endl
		<< setw(24) << "drsAvailable : "		<< physicsData->drsAvailable << endl
		<< setw(24) << "drsEnabled : "			<< physicsData->drsEnabled << endl;


	stringstream graphicsOutput;
	graphicsOutput << "GRAPHICS INFO =============================" << endl << endl
		<< setw(24) << "packetID : "				<< graphicsData->packetId << endl
		<< setw(24) << "STATUS : " 					<< graphicsData->status << endl
		<< setw(24) << "session : " 				<< graphicsData->session << endl
		<< setw(24) << "completed laps : " 			<< graphicsData->completedLaps << endl
		<< setw(24) << "position : " 				<< graphicsData->position << endl
		<< setw(24) << "current time s : " 			<< graphicsData->currentTime << endl
		<< setw(24) << "current time : " 			<< graphicsData->iCurrentTime << endl
		<< setw(24) << "last time : " 				<< graphicsData->iLastTime << endl
		<< setw(24) << "best time : " 				<< graphicsData->iBestTime << endl
		<< setw(24) << "sessionTimeLeft : " 		<< graphicsData->sessionTimeLeft << endl
		<< setw(24) << "distanceTraveled : " 		<< graphicsData->distanceTraveled << endl
		<< setw(24) << "isInPit : " 				<< graphicsData->isInPit << endl
		<< setw(24) << "currentSectorIndex : " 		<< graphicsData->currentSectorIndex << endl
		<< setw(24) << "lastSectorTime : " 			<< graphicsData->lastSectorTime << endl
		<< setw(24) << "numberOfLaps : " 			<< graphicsData->numberOfLaps << endl
		<< setw(24) << "TYRE COMPOUND : " 			<< graphicsData->tyreCompound << endl
		<< setw(24) << "replayMult : " 				<< graphicsData->replayTimeMultiplier << endl
		<< setw(24) << "normalizedCarPosition : " 	<< graphicsData->normalizedCarPosition << endl
		<< setw(24) << "carCoordinates : " 			<< graphicsData->carCoordinates[0] << ", " << graphicsData->carCoordinates[1] << ", " << graphicsData->carCoordinates[2] << endl;

	stringstream fileStaticOutput;
	fileStaticOutput << "STATIC INFO =============================" << endl << endl
		<< setw(28) << "smVersion : " 				<< fileStaticData->smVersion << endl
		<< setw(28) << "acVersion : " 				<< fileStaticData->acVersion << endl
		<< setw(28) << "numberOfSessions : " 		<< fileStaticData->numberOfSessions << endl
		<< setw(28) << "numCars : " 				<< fileStaticData->numCars << endl
		<< setw(28) << "carModel : " 				<< fileStaticData->carModel << endl
		<< setw(28) << "track : " 					<< fileStaticData->track << endl
		<< setw(28) << "playerName : " 				<< fileStaticData->playerName << endl
		<< setw(28) << "playerSurname : " 			<< fileStaticData->playerSurname << endl
		<< setw(28) << "playerNick : " 				<< fileStaticData->playerNick << endl
		<< setw(28) << "sectorCount : " 			<< fileStaticData->sectorCount << endl
		<< setw(28) << "maxTorque : " 				<< fileStaticData->maxTorque << endl
		<< setw(28) << "maxPower : " 				<< fileStaticData->maxPower << endl
		<< setw(28) << "maxRpm : " 					<< fileStaticData->maxRpm << endl
		<< setw(28) << "maxFuel : " 				<< fileStaticData->maxFuel << endl
		<< setw(28) << "suspensionMaxTravel : " 	<< fileStaticData->suspensionMaxTravel[0] << ", " << fileStaticData->suspensionMaxTravel[1] << ", " << fileStaticData->suspensionMaxTravel[2] << ", " << fileStaticData->suspensionMaxTravel[3] << endl
		<< setw(28) << "tyreRadius : " 				<< fileStaticData->tyreRadius[0] << ", " << fileStaticData->tyreRadius[1] << ", " << fileStaticData->tyreRadius[2] << ", " << fileStaticData->tyreRadius[3] << endl
		<< setw(28) << "maxTurboBoost : " 			<< fileStaticData->maxTurboBoost << endl
		//<<  set2824) << "deprecated_1 : " << fileStaticData->deprecated_1 << endl
		//<<  set2824) << "deprecated_2 : " << fileStaticData->deprecated_2 << endl
		<< setw(28) << "penaltiesEnabled : " 		<< fileStaticData->penaltiesEnabled << endl
		<< setw(28) << "aidFuelRate : " 			<< fileStaticData->aidFuelRate << endl
		<< setw(28) << "aidTireRate : " 			<< fileStaticData->aidTireRate << endl
		<< setw(28) << "aidMechanicalDamage : " 	<< fileStaticData->aidMechanicalDamage << endl
		<< setw(28) << "aidAllowTyreBlankets : " 	<< fileStaticData->aidAllowTyreBlankets << endl
		<< setw(28) << "aidStability : " 			<< fileStaticData->aidStability << endl
		<< setw(28) << "aidAutoClutch : " 			<< fileStaticData->aidAutoClutch << endl
		<< setw(28) << "aidAutoBlip : "				<< fileStaticData->aidAutoBlip << endl
		<< setw(28) << "hasDRS : " 					<< fileStaticData->hasDRS << endl
		<< setw(28) << "hasERS : " 					<< fileStaticData->hasERS << endl
		<< setw(28) << "hasKERS : " 				<< fileStaticData->hasKERS << endl
		<< setw(28) << "kersMaxJ : "				<< fileStaticData->kersMaxJ << endl
		<< setw(28) << "engineBrakeSettingsCount : " << fileStaticData->engineBrakeSettingsCount << endl
		<< setw(28) << "ersPowerControllerCount : " << fileStaticData->ersPowerControllerCount << endl
		<< setw(28) << "trackSPlineLength : " 		<< fileStaticData->trackSPlineLength << endl
		<< setw(28) << "trackConfiguration : " 		<< fileStaticData->trackConfiguration << endl;
		<< setw(28) << "ersMaxJ : " 				<< staticData->ersMaxJ << endl
		<< setw(28) << "isTimedRace : " 			<< staticData->isTimedRace << endl
		<< setw(28) << "hasExtraLap : " 			<< staticData->hasExtraLap << endl
		<< setw(28) << "carSkin : " 				<< staticData->carSkin << endl
		<< setw(28) << "reversedGridPosition : " 	<< staticData->reversedGridPositions << endl
		<< setw(28) << "PitWindowStart : " 			<< staticData->PitWindowStart << endl
		<< setw(28) << "PitWindowEnd : " 			<< staticData->PitWindowEnd << endl;


	ofDrawBitmapStringHighlight(physicsOutput.str(), 20, 20);
	ofDrawBitmapStringHighlight(graphicsOutput.str(), 620, 20);
	ofDrawBitmapStringHighlight(fileStaticOutput.str(), 1020, 20);
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
