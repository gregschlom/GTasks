/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_TASK_H
#define GTASKS_TASK_H

#include <QSharedData>

class QString;
class QUrl;
class QDateTime;

namespace GTasks {

class TaskPrivate;

class Task
{
public:
	enum Status {
		NeedsAction,
		Completed
	};

	Task();
	Task(const Task& other);
	Task &operator=(const Task&);
	~Task();

	QString kind() const;
	QString id() const;
	QString etag() const;
	QString title() const;
	QDateTime updated() const;
	QUrl selfLink() const;
	QString parent() const;
	QString position() const;
	QString notes() const;
	Status status() const;
	QDateTime due() const;
	bool completed() const;
	bool deleted() const;
	bool hidden() const;

	void setTitle(const QString& title);
	void setNotes(const QString& notes);
	void setStatus(Status status);
	void setDue(const QDateTime& due);
	void setCompleted(bool completed);

private:
    friend class TaskPrivate;
	QSharedDataPointer<TaskPrivate> d;
};

}
#endif // GTASKS_TASK_H
