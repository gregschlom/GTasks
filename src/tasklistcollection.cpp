/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "tasklistcollection.h"
#include "tasklistcollection_p.h"

#include <QString>

namespace GTasks {

TaskListCollection::TaskListCollection()
	: d(new TaskListCollectionPrivate)
{
}

TaskListCollection::TaskListCollection(QVariantMap data)
	: d(new TaskListCollectionPrivate)
{
	deserialize(data);
}

TaskListCollection::~TaskListCollection()
{
}

TaskListCollection::TaskListCollection(const TaskListCollection& other)
	: d(other.d)
{
}

TaskListCollection& TaskListCollection::operator=(const TaskListCollection& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

TaskListCollectionPrivate::TaskListCollectionPrivate()
	: QSharedData(),
	  kind("tasks#taskLists"),
	  etag(""),
	  nextPageToken(""),
	  items()
{
}

TaskListCollectionPrivate::TaskListCollectionPrivate(const TaskListCollectionPrivate& other)
	: QSharedData(other),
	  kind(other.kind),
	  etag(other.etag),
	  nextPageToken(other.nextPageToken),
	  items(other.items)
{
}

QVariantMap TaskListCollection::serialize() const
{
	QVariantMap result;
	result.insert("kind", d->kind);
	result.insert("etag", d->etag);
	result.insert("nextPageToken", d->nextPageToken);

	// Serialize items
	QVariantList itemsData;
	foreach(const TaskList& t, d->items) {
		itemsData << t.serialize();
	}
	result.insert("items", itemsData);

	return result;
}

void TaskListCollection::deserialize(QVariantMap data)
{
	Q_ASSERT(data.value("kind") == "tasks#taskLists");

	d->kind      = data.value("kind").value<QString>();
	d->etag      = data.value("etag").value<QString>();
	d->nextPageToken     = data.value("nextPageToken").value<QString>();

	// Deserialize items
	foreach(const QVariant& tasklistData, data.value("items").toList()) {
		d->items << TaskList(tasklistData.toMap());
	}
}

// Getters
QString      TaskListCollection::kind()      const { return d->kind; }
QString      TaskListCollection::etag()      const { return d->etag; }
QString      TaskListCollection::nextPageToken()     const { return d->nextPageToken; }
QList<GTasks::TaskList> TaskListCollection::items()   const { return d->items; }

} // namespace GTasks