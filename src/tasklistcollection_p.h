/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_TASKLISTCOLLECTION_P_H
#define GTASKS_TASKLISTCOLLECTION_P_H

#include <QSharedData>
#include <QString>
#include "tasklist.h"

namespace GTasks {

class TasklistCollectionPrivate : public QSharedData
{
public:
	TasklistCollectionPrivate();
	TasklistCollectionPrivate(const TasklistCollectionPrivate& other);

	QString kind;
	QString etag;
	QString nextPageToken;
	QList<GTasks::Tasklist> items;
};

}
#endif // GTASKS_TASKLISTCOLLECTION_P_H
