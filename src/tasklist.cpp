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

Tasklist::Tasklist()
	: d(new TasklistPrivate)
{
}

/*!
  Convenience constructor to create a Tasklist and initialize it with serialized data
*/
Tasklist::Tasklist(QVariantMap data)
	: d(new TasklistPrivate)
{
	deserialize(data);
}

Tasklist::~Tasklist()
{
}

Tasklist::Tasklist(const Tasklist& other)
	: d(other.d)
{
}

Tasklist& Tasklist::operator=(const Tasklist& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

TasklistPrivate::TasklistPrivate()
	: QSharedData(),
	  kind("tasks#taskList"),
	  id(""),
	  etag(""),
	  title(""),
	  selfLink(QUrl())
{
}

TasklistPrivate::TasklistPrivate(const TasklistPrivate& other)
	: QSharedData(other),
	  kind(other.kind),
	  id(other.id),
	  etag(other.etag),
	  title(other.title),
	  selfLink(other.selfLink)
{
}

QVariantMap Tasklist::serialize() const
{
	QVariantMap result;
	result.insert("kind", d->kind);
	result.insert("id", d->id);
	result.insert("etag", d->etag);
	result.insert("title", d->title);
	result.insert("selfLink", d->selfLink);
	return result;
}

void Tasklist::deserialize(QVariantMap data)
{
	if (data.value("kind") != "tasks#taskList") {
		return;
	}

	d->id        = data.value("id").value<QString>();
	d->etag      = data.value("etag").value<QString>();
	d->title     = data.value("title").value<QString>();
	d->selfLink  = data.value("selfLink").value<QUrl>();
}

QUrl Tasklist::generateSelfLink(const QString& tasklistId)
{
	QUrl url("https://www.googleapis.com/tasks/v1/users/@me/lists");
	if (!tasklistId.isEmpty()) {
		url.setPath(url.path() + "/" + tasklistId);
	}
	return url;
}

// Getters
QString      Tasklist::kind()      const { return d->kind; }
QString      Tasklist::id()        const { return d->id; }
QString      Tasklist::etag()      const { return d->etag; }
QString      Tasklist::title()     const { return d->title; }
QUrl         Tasklist::selfLink()  const { return d->selfLink; }

// Setters
void Tasklist::setTitle(const QString& title) { d->title = title; }

} // namespace GTasks
