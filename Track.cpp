#include "Track.h"
//#include "ObjectControl.h"
#include <QFile>
#include <QTextStream>

// * Constructor
Track::Track() : CPCount(0)
{
	resetPoints();
}

// * provide a default set of points
void Track::resetPoints()
{
	removeAll();
	add(ControlPoint(vec3(  50,	 10,	  0)));
	add(ControlPoint(vec3(   0,	 10,	 50)));
	add(ControlPoint(vec3( -50,	 10,	  0)));
	add(ControlPoint(vec3(   0,	 10,	-50)));
}

// * The file format is simple
//   first line: an integer with the number of control points
//	  other lines: one line per control point
//   either 3 (X,Y,Z) numbers on the line, or 6 numbers (X,Y,Z, orientation)
void Track::readPoints(const char* filename)
{
	removeAll();
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) {
			printf("Can't Open File!\n");
	}
	else {
		QTextStream data(&file);
		file.close();
		int npts;
		data >> npts;
		if( (npts<4) || (npts>65535)) {
				printf("Illegal Number of Points Specified in File");
		}
		else {
			CPs.clear();
			// get lines until EOF or we have enough points
			while( (CPs.size() < npts) && !data.atEnd() ) {
				vec3 pos,orient;
				QStringList words = data.readLine().split(' ');
				if(words[0][0]=='#')
					continue;
				if (words.size() >= 3) {
					pos.x() = words[0].toDouble();
					pos.y() = words[1].toDouble();
					pos.z() = words[2].toDouble();
				} else {
					pos.x() = 0;
					pos.y() = 0;
					pos.z() = 0;
				}
				if (words.size() >= 6) {
					orient.x() = words[3].toDouble();
					orient.y() = words[4].toDouble();
					orient.z() = words[5].toDouble();
				} else {
					orient.x() = 0;
					orient.y() = 1;
					orient.z() = 0;
				}
				orient.normalize();
				add(ControlPoint(pos,orient));
			}
		}
	}
}

// * write the control points to our simple format
void Track::writePoints(const char* filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly)) {
		printf("Can't open file for writing");
	}
	else {
		QTextStream data(&file);
		data << CPs.size() << "\n";
		for(int i=0; i<CPs.size(); ++i)
			data << CPs[i].pos.x() << CPs[i].pos.y() << CPs[i].pos.z()
				 << CPs[i].orient.x() << CPs[i].orient.y() << CPs[i].orient.z() <<"\n";
		file.close();
	}
}

// add a control point
int Track::add(ControlPoint tCP)
{
//	Ogre::Entity *ent;
//	char name[16];
//	sprintf(name, "ControlPoint%d", mCount++);
//	ent = mSm->createEntity(name, "point.mesh");
//	ent->setQueryFlags(ObjectControl::CONTROL_POINT);

//	Ogre::SceneNode *mCurrentObject = mSm->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", tCP.pos);
//	mCurrentObject->attachObject(ent);
//	mCurrentObject->setScale(0.05f, 0.05f, 0.05f);

	tCP.index = CPCount++;
	CPs.push_back(tCP);
	return tCP.index;
}

// delete a control point
void Track::remove(const int i)
{
	if (i < CPs.size() && i >= 0)
		CPs.remove(i);
//	for (int i = 0; i < CPs.size(); ++i) {
//		if (CPs[i].index == i) {
//			CPs.remove(i);
//			break;
//		}
//	}
}

// delete all control point
void Track::removeAll()
{
//	for (int i =0; i<CPs.size(); i++)
//	{
//		mSm->destroySceneNode(mSm->getSceneNode(CPs[i].name));
//		mSm->destroyEntity(CPs[i].name);
//	}

	CPs.clear();
}

// move a control point
void Track::move(const int i, const vec3& tPos)
{
	if (i < CPs.size() && i >= 0)
		CPs[i].pos = tPos;
//	for (int i = 0; i < CPs.size(); ++i) {
//		if (CPs[i].index == tIndex) {
//			CPs[i].pos = tPos;
//			break;
//		}
//	}
//	for (CPV::iterator ii = CPs.begin(); ii != CPs.end(); ii++)
//	{
//		ControlPoint a = *ii;
//		if (a.name == tName)
//		{
//			ii->pos = tPos;
//			break;
//		}
//	}
}

// rotate a control point
void Track::rotate(const int i, const vec3 &tOri)
{
	if (i < CPs.size() && i >= 0)
		CPs[i].orient = tOri;
//	for (int i = 0; i < CPs.size(); ++i) {
//		if (CPs[i].index == tIndex) {
//			CPs[i].orient = tOri;
//			break;
//		}
//	}
//	for (CPV::iterator ii = CPs.begin(); ii != CPs.end(); ii++)
//	{
//		ControlPoint a = *ii;
//		if (a.name == tName)
//		{
//			ii->orient = tOri;
//			break;
//		}
//	}
}

// get control point data through this method
//ControlPoint Track::findItem(const int tIndex)
int Track::findItem(const int tIndex)
{
	for (int i = 0; i < CPs.size(); ++i) {
		if (CPs[i].index == tIndex) {
			return i;
		}
	}
//	for (CPV::iterator ii = CPs.begin(); ii != CPs.end(); ii++)
//	{
//		ControlPoint a = *ii;
//		if (a.name == tName)
//		{
//			return a;
//		}
//	}
	return -1;
}

ControlPoint Track::getItem(const int i)
{
	if (i < CPs.size() && i >= 0)
		return CPs[i];
	return ControlPoint(-1);
}

// return the number of the control point now
int Track::getSize()
{
	return CPs.size();
}
