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
