/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_TASKLISTCOLLECTION_H
#define GTASKS_TASKLISTCOLLECTION_H

#include <QSharedData>
#include <QVariant>

namespace GTasks {

class TaskList;
class TaskListCollectionPrivate;

class TaskListCollection
{
public:
	TaskListCollection();
	TaskListCollection(QVariantMap data);
	TaskListCollection(const TaskListCollection& other);
	TaskListCollection &operator=(const TaskListCollection&);
	~TaskListCollection();

	QVariantMap serialize() const;
	void deserialize(QVariantMap data);

	QString kind() const;
	QString etag() const;
	QString nextPageToken() const;
	QList<GTasks::TaskList> items() const;

private:
    friend class TaskListCollectionPrivate;
	QSharedDataPointer<TaskListCollectionPrivate> d;
};

}
#endif // GTASKS_TASKLISTCOLLECTION_H
