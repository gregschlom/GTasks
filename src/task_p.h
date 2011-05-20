/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef TASK_P_H
#define TASK_P_H

#include <QSharedData>
#include <QUrl>
#include <QString>
#include <QDateTime>

#include "task.h"

namespace GTasks {

class TaskPrivate : public QSharedData
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

	// helper methods for serialization / deserialization
	void statusFromString(const QString& s);
	QString statusAsString() const;
};

}
#endif // TASK_P_H
