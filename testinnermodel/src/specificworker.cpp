/*
 *    Copyright (C) 2016 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
	RoboCompCommonBehavior::Parameter par;
	try
	{
		par = params.at("InnerModel");
		if( QFile::exists(QString::fromStdString(par.value)) )
			innerModel = new InnerModel(par.value);
		else
		{
			std::cout << "Innermodel path " << par.value << " not found. "; 
			qFatal("Abort");
		}
	}
	catch(std::exception e)
	{
		qFatal("Error reading config params %s", par.value.c_str());
	}
	
	
  
	qDebug() << "------------------------------";
	
	
	innerModel->getNode<InnerModelLaser>("laser")->print(true);
	qDebug() << innerModel->getNode<InnerModelLaser>("laser")->port;
	qDebug() << dynamic_cast<InnerModelLaser*>(innerModel->getNode("laser"))->port;
	
	qDebug() << dynamic_cast<InnerModelTransform*>(innerModel->getNode("monitor_pose"))->id;
	
	qDebug() << dynamic_cast<InnerModelCamera*>(innerModel->getNode("camera"))->focal;
	
	
// 	InnerModelOmniRobot *robot = innerModel->getNode<InnerModelOmniRobot>("robot");
// 	qDebug() << __FUNCTION__ << "Robot:"  << robot->id << robot->port << robot->tx << robot->ty << robot->tz;
// 	
// 	InnerModelRGBD *rgbd = innerModel->getNode<InnerModelRGBD>("rgbd");
// 	qDebug() << __FUNCTION__ << "RGBD:"  << rgbd->id << rgbd->port << rgbd->getFocal();
// 	
	InnerModelLaser *laser = innerModel->getNode<InnerModelLaser>("laser");
	qDebug() << __FUNCTION__ << "LASER:"  << laser->id << laser->port << laser->measures << laser->min;
	qDebug() << __FUNCTION__ << "LASER2:" <<  dynamic_cast<InnerModelLaser*>(innerModel->getNode("laser"))->port;
	
	innerModel->getNode<InnerModelCamera>("camera")->project("rgbd", QVec::vec3(30, 450, 100), "camera").print("project");
	
	
	timer.start(Period);
	return true;
}

void SpecificWorker::compute()
{
	//qDebug() << __FUNCTION__ << "hola";
	qFatal("Job done");
}







