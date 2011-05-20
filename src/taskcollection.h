/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_TASKCOLLECTION_H
#define GTASKS_TASKCOLLECTION_H

#include <QSharedData>
#include <QVariant>

namespace GTasks {

class Task;
class TaskCollectionPrivate;

class TaskCollection
{
public:
	TaskCollection();
	TaskCollection(QVariantMap data);
	TaskCollection(const TaskCollection& other);
	TaskCollection &operator=(const TaskCollection&);
	~TaskCollection();

	QVariantMap serialize() const;
	void deserialize(QVariantMap data);

	QString kind() const;
	QString etag() const;
	QString nextPageToken() const;
	QList<GTasks::Task> items() const;

private:
    friend class TaskCollectionPrivate;
	QSharedDataPointer<TaskCollectionPrivate> d;
};

}
#endif // GTASKS_TASKCOLLECTION_H
