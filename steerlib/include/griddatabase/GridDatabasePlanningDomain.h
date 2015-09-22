//
// Copyright (c) 2009-2014 Shawn Singh, Glen Berseth, Mubbasir Kapadia, Petros Faloutsos, Glenn Reinman
// See license.txt for complete license.
//

#ifndef __STEERLIB_GRID_DATABASE_PLANNING_DOMAIN_H__
#define __STEERLIB_GRID_DATABASE_PLANNING_DOMAIN_H__

/// @file GridDatabasePlanningDomain.h
/// @brief Defines the state space interface SteerLib::GridDatabasePlanningDomain, used to plan paths in the grid database.

#include "Globals.h"
#include "griddatabase/GridDatabase2D.h"
#include "planning/BestFirstSearchPlanner.h"

namespace SteerLib {


	/**
	 * @brief The internal state space of the grid database that is provided to the BestFirstSearchPlanner.
	 *
	 * This class is implemented directly in the .h file so that most compilers can inline the functions for performance.
	 *
	 * This class should not be used directly.  Instead, use the GridDatabase2D public interface which provides
	 * path-planning functionality.
	 */
	class STEERLIB_API GridDatabasePlanningDomain {
	public:
		GridDatabasePlanningDomain(SteerLib::GridDatabase2D * spatialDatabase) : _spatialDatabase(spatialDatabase) {  }

		inline bool canBeTraversed(unsigned int index) const { return (_spatialDatabase->getTraversalCost(index) < 1000.0f); }

		inline bool isAGoalState( const unsigned int & state, const unsigned int & idealGoalState) {
			return state == idealGoalState;
		}

		inline float estimateTotalCost( const unsigned int & currentState, const unsigned int & idealGoalState, float currentg) {
			return currentg;
		}

		inline void generateTransitions( const unsigned int & currentState, const unsigned int & previousState, const unsigned int & idealGoalState, std::vector<SteerLib::DefaultAction<unsigned int> > & transitions )
		{
			
		}

	protected:

		inline SteerLib::DefaultAction<unsigned int> & initAction(unsigned int newState, float f) {
			_tempAction.cost = f;
			_tempAction.state = newState;
			return _tempAction;
		}


		SteerLib::GridDatabase2D * _spatialDatabase;
		SteerLib::DefaultAction<unsigned int> _tempAction;
	};



} // end namespace SteerLib;


#endif

