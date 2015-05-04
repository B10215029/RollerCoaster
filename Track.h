#ifndef TRACK_H
#define TRACK_H

#include <QVector>

// make use of other data structures from this project
#include "ControlPoint.h"

// Control Point Vector

class Track {
	public:		
		// Constructor
		Track();

	public:
		// when we want to clear the control points, we really "reset" them 
		// to have 4 default positions (since we should never have fewer
		// than 4 points)
		void resetPoints();

		// read and write to files
		void readPoints(const char* filename);
		void writePoints(const char* filename);

	private:
		// rather than have generic objects, we make a special case for these few
		// objects that we know that all implementations are going to need and that
		// we're going to have to handle specially
		QVector<ControlPoint> CPs;
		//Ogre::SceneManager *mSm;	
		int CPCount;

	public:	
		// add a control point
		int add(ControlPoint tCP);
		// delete a control point
		void remove(const int i);
		// delete all control point
		void removeAll();
		// move a control point
		void move(const int i, const vec3& tPos);
		// rotate a control point
		void rotate(const int i, const vec3& tOri);

		// get control point data through this method
		int findItem(const int tIndex);
		ControlPoint getItem(const int i);

		// return the number of the control point now 
		int getSize(); 

};

#endif // TRACK_H
