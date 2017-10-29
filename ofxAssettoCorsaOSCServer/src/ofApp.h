#pragma once

#include "ofMain.h"
#include "ofxSharedMemory.h"
#include "ofxOSC.h"

#define HOST	"192.168.100.255"
#define PORT	9000

typedef int AC_STATUS;

#define AC_OFF 0
#define AC_REPLAY 1
#define AC_LIVE 2
#define AC_PAUSE 3

typedef int AC_SESSION_TYPE;

#define AC_UNKNOWN -1
#define AC_PRACTICE 0
#define AC_QUALIFY 1
#define AC_RACE 2
#define AC_HOTLAP 3
#define AC_TIME_ATTACK 4
#define AC_DRIFT 5
#define AC_DRAG 6

typedef int AC_FLAG_TYPE;

#define AC_NO_FLAG 0
#define AC_BLUE_FLAG 1
#define AC_YELLOW_FLAG 2
#define AC_BLACK_FLAG 3
#define AC_WHITE_FLAG 4
#define AC_CHECKERED_FLAG 5
#define AC_PENALTY_FLAG 6

class SPageFilePhysics {
public:

	int packetId = 0;
	float gas = 0;
	float brake = 0;
	float fuel = 0;
	int gear = 0;
	int rpms = 0;
	float steerAngle = 0;
	float speedKmh = 0;
	float velocity[3];
	float accG[3];
	float wheelSlip[4];
	float wheelLoad[4];
	float wheelsPressure[4];
	float wheelAngularSpeed[4];
	float tyreWear[4];
	float tyreDirtyLevel[4];
	float tyreCoreTemperature[4];
	float camberRAD[4];
	float suspensionTravel[4];
	float drs = 0;
	float tc = 0;
	float heading = 0;
	float pitch = 0;
	float roll = 0;
	float cgHeight;
	float carDamage[5];
	int numberOfTyresOut = 0;
	int pitLimiterOn = 0;
	float abs = 0;
	float kersCharge = 0;
	float kersInput = 0;
	int autoShifterOn = 0;
	float rideHeight[2];
	float turboBoost = 0;
	float ballast = 0;
	float airDensity = 0;
	float airTemp = 0;
	float roadTemp = 0;
	float localAngularVel[3];
	float finalFF = 0;
	float performanceMeter = 0;

	int engineBrake = 0;
	int ersRecoveryLevel = 0;
	int ersPowerLevel = 0;
	int ersHeatCharging = 0;
	int ersIsCharging = 0;
	float kersCurrentKJ = 0;

	int drsAvailable = 0;
	int drsEnabled = 0;

	float brakeTemp[4];
	float clutch = 0;

	float tyreTempI[4];
	float tyreTempM[4];
	float tyreTempO[4];

	int isAIControlled;

	float tyreContactPoint[4][3];
	float tyreContactNormal[4][3];
	float tyreContactHeading[4][3];

	float brakeBias = 0;
	float localVelocity[3];
};

class SPageFileGraphic {
public:
	char DefChar = ' ';
	int packetId = 0;
	AC_STATUS status = AC_OFF;
	AC_SESSION_TYPE session = AC_PRACTICE;
	wchar_t _currentTime[15];
	wchar_t _lastTime[15];
	wchar_t _bestTime[15];
	wchar_t _split[15];

	char currentTime[15];
	char lastTime[15];
	char bestTime[15];
	char split[15];

	int completedLaps = 0;
	int position = 0;
	int iCurrentTime = 0;
	int iLastTime = 0;
	int iBestTime = 0;
	float sessionTimeLeft = 0;
	float distanceTraveled = 0;
	int isInPit = 0;
	int currentSectorIndex = 0;
	int lastSectorTime = 0;
	int numberOfLaps = 0;
	wchar_t _tyreCompound[33];
	char tyreCompound[33];

	float replayTimeMultiplier = 0;
	float normalizedCarPosition = 0;
	float carCoordinates[3];
	float penaltyTime = 0;
	AC_FLAG_TYPE flag = AC_NO_FLAG;
	int idealLineOn = 0;
	int isInPitLane = 0;

	float surfaceGrip = 0;
	int mandatoryPitDone = 0;
	float windSpeed = 0;
	float windDirection = 0;
};

class SPageFileStatic {
public:
	wchar_t _smVersion[15];
	wchar_t _acVersion[15];
	char smVersion[15];
	char acVersion[15];
	char DefChar = ' ';

	// session static info
	int numberOfSessions = 0;
	int numCars = 0;

	wchar_t _carModel[33];
	wchar_t _track[33];
	wchar_t _playerName[33];
	wchar_t _playerSurname[33];
	wchar_t _playerNick[33];

	char carModel[33];
	char track[33];
	char playerName[33];
	char playerSurname[33];
	char playerNick[33];

	int sectorCount = 0;

	// car static info
	float maxTorque = 0;
	float maxPower = 0;
	int	maxRpm = 0;
	float maxFuel = 0;
	float suspensionMaxTravel[4];
	float tyreRadius[4];
	float maxTurboBoost = 0;

	float deprecated_1 = -273;
	float deprecated_2 = -273;

	int penaltiesEnabled = 0;

	float aidFuelRate = 0;
	float aidTireRate = 0;
	float aidMechanicalDamage = 0;
	int aidAllowTyreBlankets = 0;
	float aidStability = 0;
	int aidAutoClutch = 0;
	int aidAutoBlip = 0;

	int hasDRS = 0;
	int hasERS = 0;
	int hasKERS = 0;
	float kersMaxJ = 0;
	int engineBrakeSettingsCount = 0;
	int ersPowerControllerCount = 0;
	float trackSPlineLength = 0;

	wchar_t _trackConfiguration[33];
	char trackConfiguration[33];
	float ersMaxJ = 0;
	int isTimedRace = 0;
	int hasExtraLap = 0;
	wchar_t _carSkin[33];
	char carSkin[33];
	int reversedGridPositions;
	int PitWindowStart;
	int PitWindowEnd;
};

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// when creating an ofxSharedMemory, use the <> to assign a data type
	ofxSharedMemory<SPageFilePhysics*> physics;
	SPageFilePhysics* physicsData;

	ofxSharedMemory<SPageFileGraphic*> graphics;
	SPageFileGraphic* graphicsData;

	ofxSharedMemory<SPageFileStatic*> fileStatic;
	SPageFileStatic* staticData;

	bool isConnected;
	bool isPhysicsConnected;
	bool isGraphicsConnected;
	bool isStaticConnected;

	// OSC setup
	ofxOscSender sender;
	uint64_t lastOscSentTimer;

	void sendPhysicsTelemetryOscMessage();
	void sendGraphicsTelemetryOscMessage();
	void sendFileStaticTelemetryOscMessage();
};
