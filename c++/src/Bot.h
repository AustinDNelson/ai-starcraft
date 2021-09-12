#pragma once

#include "MapTools.h"
#include "WorkerManager.h"

#include <BWAPI.h>

class Bot
{
    MapTools m_mapTools;
	WorkerManager m_workerManager;

	// helper functions to get you started with bot programming and learn the API
	void trainAdditionalWorkers();
	void drawDebugInformation();

public:

    Bot();

    // functions that are triggered by various BWAPI events from main.cpp
	void onStart();
	void onFrame();
	void onEnd(bool isWinner);
	void onUnitDestroy(BWAPI::Unit unit);
	void onUnitMorph(BWAPI::Unit unit);
	void onSendText(std::string text);
	void onUnitCreate(BWAPI::Unit unit);
	void onUnitComplete(BWAPI::Unit unit);
	void onUnitShow(BWAPI::Unit unit);
	void onUnitHide(BWAPI::Unit unit);
	void onUnitRenegade(BWAPI::Unit unit);
};