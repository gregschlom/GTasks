/*
 *  GTasks - A C++/Qt API client for Google Tasks
 *
 *  Copyright (C) 2011 Gregory Schlomoff <gregory.schlomoff@gmail.com>
 *                     http://gregschlom.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
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
