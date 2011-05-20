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

TasklistCollection::TasklistCollection()
	: d(new TasklistCollectionPrivate)
{
}

TasklistCollection::TasklistCollection(QVariantMap data)
	: d(new TasklistCollectionPrivate)
{
	deserialize(data);
}

TasklistCollection::~TasklistCollection()
{
}

TasklistCollection::TasklistCollection(const TasklistCollection& other)
	: d(other.d)
{
}

TasklistCollection& TasklistCollection::operator=(const TasklistCollection& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

TasklistCollectionPrivate::TasklistCollectionPrivate()
	: QSharedData(),
	  kind("tasks#taskLists"),
	  etag(""),
	  nextPageToken(""),
	  items()
{
}

TasklistCollectionPrivate::TasklistCollectionPrivate(const TasklistCollectionPrivate& other)
	: QSharedData(other),
	  kind(other.kind),
	  etag(other.etag),
	  nextPageToken(other.nextPageToken),
	  items(other.items)
{
}

QVariantMap TasklistCollection::serialize() const
{
	QVariantMap result;
	result.insert("kind", d->kind);
	result.insert("etag", d->etag);
	result.insert("nextPageToken", d->nextPageToken);

	// Serialize items
	QVariantList itemsData;
	foreach(const Tasklist& t, d->items) {
		itemsData << t.serialize();
	}
	result.insert("items", itemsData);

	return result;
}

void TasklistCollection::deserialize(QVariantMap data)
{
	Q_ASSERT(data.value("kind") == "tasks#taskLists");

	d->kind      = data.value("kind").value<QString>();
	d->etag      = data.value("etag").value<QString>();
	d->nextPageToken     = data.value("nextPageToken").value<QString>();

	// Deserialize items
	foreach(const QVariant& tasklistData, data.value("items").toList()) {
		d->items << Tasklist(tasklistData.toMap());
	}
}

// Getters
QString      TasklistCollection::kind()      const { return d->kind; }
QString      TasklistCollection::etag()      const { return d->etag; }
QString      TasklistCollection::nextPageToken()     const { return d->nextPageToken; }
QList<GTasks::Tasklist> TasklistCollection::items()   const { return d->items; }

} // namespace GTasks