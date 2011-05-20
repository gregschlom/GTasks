/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef TASK_P_H
#define TASK_P_H

#include "model.h"
#include "task.h"

#include <QUrl>
#include <QString>
#include <QDateTime>

namespace GTasks {

class TaskPrivate : public Model
{
public:
	TaskPrivate();
	TaskPrivate(const TaskPrivate& other);

	QString kind;
	QString id;
	QString etag;
	QString title;
	QDateTime updated;
	QUrl selfLink;
	QString parent;
	QString position;
	QString notes;
	Task::Status status;
	QDateTime due;
	bool completed;
	bool deleted;
	bool hidden;
};

}
#endif // TASK_P_H
