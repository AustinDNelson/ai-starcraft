#include "WorkerManager.h"

WorkerManager::WorkerManager()
{
	m_scout = nullptr;
}

void WorkerManager::handleIdleWorkers()
{
	for (auto& unit : BWAPI::Broodwar->self()->getUnits())
	{
		if (unit->getType().isWorker())
		{
			if (unit->isIdle())
			{
				if (unit->isCarryingMinerals() || unit->isCarryingMinerals())
				{
					unit->returnCargo();
				} // closes if is carrying cargo
				else
				{
					// Get the closest mineral to this worker unit
					BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());

					if (!unit->gather(unit->getClosestUnit(BWAPI::Filter::IsMineralField || BWAPI::Filter::IsRefinery)))
					{
						BWAPI::Broodwar << BWAPI::Broodwar->getLastError() << std::endl;
					}
				} // closes if carying cargo else
			} // closes if is idle
		} // closes if is worker
	} // closes unit loop
}

void WorkerManager::scout()
{
	if (BWAPI::Broodwar->self()->getUnits().size() <= 10)
	{
		return;
	}

	if (!m_scout)
	{
		BWAPI::Unit supplyProvider = Tools::getFirstSupplyProvider();
		m_scout = Tools::GetClosestUnitTo(supplyProvider->getPosition(), BWAPI::Broodwar->self()->getUnits());
		std::cerr << "Unit: " << m_scout->getType().getName();
	}

	auto& startLocations = BWAPI::Broodwar->getStartLocations();

	for (BWAPI::TilePosition tp : startLocations)
	{
		BWAPI::Position pos(tp);
		if (BWAPI::Broodwar->isExplored(tp)) { continue; }

		m_scout->move(pos);
		break;
	}
}

// Build more supply if we are going to run out soon
void WorkerManager::buildAdditionalSupply()
{
	// Get the amount of supply supply we currently have unused
	const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

	// If we have a sufficient amount of supply, we don't need to do anything
	if (unusedSupply >= 2) { return; }

	// Otherwise, we are going to build a supply provider
	const BWAPI::UnitType supplyProviderType = BWAPI::Broodwar->self()->getRace().getSupplyProvider();

	const bool startedBuilding = Tools::BuildBuilding(supplyProviderType);
	if (startedBuilding)
	{
		BWAPI::Broodwar->printf("Started Building %s", supplyProviderType.getName().c_str());
	}
}

// Build Order Selector
void WorkerManager::buildOrder()
{
	int supply = BWAPI::Broodwar->self()->supplyUsed();

	BWAPI::UnitType gateway = BWAPI::UnitTypes::Protoss_Gateway;
	BWAPI::UnitType nexus = BWAPI::UnitTypes::Protoss_Nexus;
	BWAPI::UnitType refinery = BWAPI::UnitTypes::Protoss_Assimilator;

	buildAdditionalSupply();

	if (BWAPI::Broodwar->self()->minerals() < 200) { return; }

	if (supply == 11)
	{
		std::cerr << "Hello world!\n";
		const bool startedBuilding = Tools::BuildBuilding(gateway);
		if (startedBuilding)
		{
			BWAPI::Broodwar->printf("Started Building %s", gateway.getName().c_str());
		}
		else
		{
			BWAPI::Broodwar->printf("Couldn't build %s", gateway.getName().c_str());
		}
	}
}
