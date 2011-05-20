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

class Tasklist;
class TasklistCollectionPrivate;

class TasklistCollection
{
public:
	TasklistCollection();
	TasklistCollection(QVariantMap data);
	TasklistCollection(const TasklistCollection& other);
	TasklistCollection &operator=(const TasklistCollection&);
	~TasklistCollection();

	QVariantMap serialize() const;
	void deserialize(QVariantMap data);

	QString kind() const;
	QString etag() const;
	QString nextPageToken() const;
	QList<GTasks::Tasklist> items() const;

private:
    friend class TasklistCollectionPrivate;
	QSharedDataPointer<TasklistCollectionPrivate> d;
};

}
#endif // GTASKS_TASKLISTCOLLECTION_H
