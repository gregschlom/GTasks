/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_TASKLIST_P_H
#define GTASKS_TASKLIST_P_H

#include <QSharedData>
#include <QUrl>
#include <QString>

#include "task.h"

namespace GTasks {

class TaskListPrivate : public QSharedData
{
public:
	TaskListPrivate();
	TaskListPrivate(const TaskListPrivate& other);

	QString kind;
	QString id;
	QString etag;
	QString title;
	QUrl selfLink;
};

}
#endif // GTASKS_TASKLIST_P_H
