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
	if (data.value("kind") != "tasks#taskLists") {
		return;
	}

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
