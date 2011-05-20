/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "task.h"
#include "task_p.h"

#include <QString>
#include <QStringList>

namespace GTasks {

TaskPrivate::TaskPrivate()
	: Model()
{
	/*
	REGISTER_PROPERTY(Task, kind, "tasks#task")
	REGISTER_PROPERTY(Task, id, "")
	REGISTER_PROPERTY(Task, etag, "")
	REGISTER_PROPERTY(Task, title, "")
	REGISTER_PROPERTY(Task, updated, QDateTime())
	REGISTER_PROPERTY(Task, selfLink, QUrl())
	REGISTER_PROPERTY(Task, parent, "")
	REGISTER_PROPERTY(Task, position, "")
	REGISTER_PROPERTY(Task, notes, "")
	REGISTER_PROPERTY(Task, status)
	REGISTER_PROPERTY(Task, due, QDateTime())
	REGISTER_PROPERTY(Task, completed, false)
	REGISTER_PROPERTY(Task, deleted, false)
	REGISTER_PROPERTY(Task, hidden, false)
	*/
}

TaskPrivate::TaskPrivate(const TaskPrivate& other)
	: Model(other) /*,
	m_title(other.m_title),
	m_subtitle(other.m_subtitle),
	m_inInbox(other.m_inInbox),
	m_status(other.m_status),
	m_deleted(other.m_deleted),
	m_archived(other.m_archived),
	m_created(other.m_created),
	m_modified(other.m_modified),
	m_rating(other.m_rating),
	m_dueDate(other.m_dueDate),
	m_hasData(other.m_hasData),
	m_completed(other.m_completed),
	m_projectId(other.m_projectId),
	m_oldProjectId(other.m_oldProjectId),
	m_order(other.m_order),
	m_predictedLabel(other.m_predictedLabel),
	m_mailCount(other.m_mailCount),
	m_people(other.m_people),
	m_unseenCount(other.m_unseenCount),
	m_notes(other.m_notes)*/
{
}

Task::Task()
	: d(new TaskPrivate)
{
}

Task::~Task()
{
}

Task::Task(const Task& other)
	: d(other.d)
{
}

Task& Task::operator=(const Task& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

// Getters
QString      Task::kind()      const { return d->kind; }
QString      Task::id()        const { return d->id; }
QString      Task::etag()      const { return d->etag; }
QString      Task::title()     const { return d->title; }
QDateTime    Task::updated()   const { return d->updated; }
QUrl         Task::selfLink()  const { return d->selfLink; }
QString      Task::parent()    const { return d->parent; }
QString      Task::position()  const { return d->position; }
QString      Task::notes()     const { return d->notes; }
Task::Status Task::status()    const { return d->status; }
QDateTime    Task::due()       const { return d->due; }
bool         Task::completed() const { return d->completed; }
bool         Task::deleted()   const { return d->deleted; }
bool         Task::hidden()    const { return d->hidden; }

// Setters
void Task::setTitle(const QString& title) { d->title = title; }
void Task::setNotes(const QString& notes) { d->notes = notes; }
void Task::setStatus(Status status)       { d->status = status; }
void Task::setDue(const QDateTime& due)   { d->due = due; }
void Task::setCompleted(bool completed)   { d->completed = completed; }

} // namespace GTasks