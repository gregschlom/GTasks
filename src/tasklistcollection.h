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
