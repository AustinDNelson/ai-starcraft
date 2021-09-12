#pragma once

#include "Tools.h"

#include <BWAPI.h>

class WorkerManager
{
private:
	BWAPI::Unit m_scout;

public:
	WorkerManager();
	void handleIdleWorkers();
	void buildAdditionalSupply();
	void scout();
	void buildOrder();
};
