/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_TASKLIST_H
#define GTASKS_TASKLIST_H

#include <QSharedData>
#include <QVariant>

class QString;
class QUrl;
class QDateTime;

namespace GTasks {

class TaskListPrivate;

class TaskList
{
public:
	enum Status {
		NeedsAction,
		Completed
	};

	TaskList();
	TaskList(QVariantMap data);
	TaskList(const TaskList& other);
	TaskList &operator=(const TaskList&);
	~TaskList();

	QVariantMap serialize() const;
	void deserialize(QVariantMap data);

	QString kind() const;
	QString id() const;
	QString etag() const;
	QString title() const;
	QUrl selfLink() const;

	void setTitle(const QString& title);

private:
    friend class TaskListPrivate;
	QSharedDataPointer<TaskListPrivate> d;
};

}
#endif // GTASKS_TASKLIST_H
