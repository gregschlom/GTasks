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

#ifndef GTASKS_TASKLIST_H
#define GTASKS_TASKLIST_H

#include <QSharedData>
#include <QVariant>

class QString;
class QUrl;
class QDateTime;

namespace GTasks {

class TasklistPrivate;

class Tasklist
{
public:
	enum Status {
		NeedsAction,
		Completed
	};

	Tasklist();
	Tasklist(QVariantMap data);
	Tasklist(const Tasklist& other);
	Tasklist &operator=(const Tasklist&);
	~Tasklist();

	QVariantMap serialize() const;
	void deserialize(QVariantMap data);
	static QUrl generateSelfLink(const QString& tasklistId);

	QString kind() const;
	QString id() const;
	QString etag() const;
	QString title() const;
	QUrl selfLink() const;

	void setTitle(const QString& title);

private:
    friend class TasklistPrivate;
	QSharedDataPointer<TasklistPrivate> d;
};

}
#endif // GTASKS_TASKLIST_H
