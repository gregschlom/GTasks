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

#ifndef GTASKS_TASK_P_H
#define GTASKS_TASK_P_H

#include <QSharedData>
#include <QUrl>
#include <QString>
#include <QDateTime>

#include "task.h"

namespace GTasks {

class TaskPrivate : public QSharedData
{
public:
	TaskPrivate();
	TaskPrivate(const TaskPrivate& other);

	QString kind;
	QString id;
	QString etag;
	QString title;
	QDateTime updated;
	QUrl selfLink;
	QString parent;
	QString position;
	QString notes;
	Task::Status status;
	QDateTime due;
	QDateTime completed;
	bool deleted;
	bool hidden;

	// helper methods for serialization / deserialization
	void statusFromString(const QString& s);
	QString statusAsString() const;
};

}
#endif // GTASKS_TASK_P_H
