/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "taskcollection.h"
#include "taskcollection_p.h"

#include <QString>

namespace GTasks {

TaskCollection::TaskCollection()
	: d(new TaskCollectionPrivate)
{
}

TaskCollection::TaskCollection(QVariantMap data)
	: d(new TaskCollectionPrivate)
{
	deserialize(data);
}

TaskCollection::~TaskCollection()
{
}

TaskCollection::TaskCollection(const TaskCollection& other)
	: d(other.d)
{
}

TaskCollection& TaskCollection::operator=(const TaskCollection& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

TaskCollectionPrivate::TaskCollectionPrivate()
	: QSharedData(),
	  kind("tasks#tasks"),
	  etag(""),
	  nextPageToken(""),
	  items()
{
}

TaskCollectionPrivate::TaskCollectionPrivate(const TaskCollectionPrivate& other)
	: QSharedData(other),
	  kind(other.kind),
	  etag(other.etag),
	  nextPageToken(other.nextPageToken),
	  items(other.items)
{
}

QVariantMap TaskCollection::serialize() const
{
	QVariantMap result;
	result.insert("kind", d->kind);
	result.insert("etag", d->etag);
	result.insert("nextPageToken", d->nextPageToken);

	// Serialize items
	QVariantList itemsData;
	foreach(const Task& t, d->items) {
		itemsData << t.serialize();
	}
	result.insert("items", itemsData);

	return result;
}

void TaskCollection::deserialize(QVariantMap data)
{
	if (data.value("kind") != "tasks#tasks") {
		return;
	}

	d->etag      = data.value("etag").value<QString>();
	d->nextPageToken     = data.value("nextPageToken").value<QString>();

	// Deserialize items
	foreach(const QVariant& taskData, data.value("items").toList()) {
		d->items << Task(taskData.toMap());
	}
}

// Getters
QString      TaskCollection::kind()      const { return d->kind; }
QString      TaskCollection::etag()      const { return d->etag; }
QString      TaskCollection::nextPageToken()     const { return d->nextPageToken; }
QList<GTasks::Task> TaskCollection::items()   const { return d->items; }

} // namespace GTasks
