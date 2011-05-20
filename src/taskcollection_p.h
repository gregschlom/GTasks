/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_TASKCOLLECTION_P_H
#define GTASKS_TASKCOLLECTION_P_H

#include <QSharedData>
#include <QString>
#include "task.h"

namespace GTasks {

class TaskCollectionPrivate : public QSharedData
{
public:
	TaskCollectionPrivate();
	TaskCollectionPrivate(const TaskCollectionPrivate& other);

	QString kind;
	QString etag;
	QString nextPageToken;
	QList<GTasks::Task> items;
};

}
#endif // GTASKS_TASKCOLLECTION_P_H
