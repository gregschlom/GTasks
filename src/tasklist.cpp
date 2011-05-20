/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "tasklist.h"
#include "tasklist_p.h"

#include <QString>

namespace GTasks {

TaskList::TaskList()
	: d(new TaskListPrivate)
{
}

/*!
  Convenience constructor to create a TaskList and initialize it with serialized data
*/
TaskList::TaskList(QVariantMap data)
	: d(new TaskListPrivate)
{
	deserialize(data);
}

TaskList::~TaskList()
{
}

TaskList::TaskList(const TaskList& other)
	: d(other.d)
{
}

TaskList& TaskList::operator=(const TaskList& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

TaskListPrivate::TaskListPrivate()
	: QSharedData(),
	  kind("tasks#taskList"),
	  id(""),
	  etag(""),
	  title(""),
	  selfLink(QUrl())
{
}

TaskListPrivate::TaskListPrivate(const TaskListPrivate& other)
	: QSharedData(other),
	  kind(other.kind),
	  id(other.id),
	  etag(other.etag),
	  title(other.title),
	  selfLink(other.selfLink)
{
}

QVariantMap TaskList::serialize() const
{
	QVariantMap result;
	result.insert("kind", d->kind);
	result.insert("id", d->id);
	result.insert("etag", d->etag);
	result.insert("title", d->title);
	result.insert("selfLink", d->selfLink);
	return result;
}

void TaskList::deserialize(QVariantMap data)
{
	Q_ASSERT(data.value("kind") == "tasks#taskList");

	d->kind      = data.value("kind").value<QString>();
	d->id        = data.value("id").value<QString>();
	d->etag      = data.value("etag").value<QString>();
	d->title     = data.value("title").value<QString>();
	d->selfLink  = data.value("selfLink").value<QUrl>();
}

// Getters
QString      TaskList::kind()      const { return d->kind; }
QString      TaskList::id()        const { return d->id; }
QString      TaskList::etag()      const { return d->etag; }
QString      TaskList::title()     const { return d->title; }
QUrl         TaskList::selfLink()  const { return d->selfLink; }

// Setters
void TaskList::setTitle(const QString& title) { d->title = title; }

} // namespace GTasks