/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "service.h"
#include "jobs.h"

namespace GTasks {

Service::Service(QNetworkAccessManager* networkManager, QObject* parent) :
    QObject(parent),
    m_networkManager(networkManager)
{
}

ListTasklistsJob& Service::listTasklists() { return *new ListTasklistsJob(this); }
//GetTasklistJob& Service::getTasklist(const QUrl& selfLink);
GetTasklistJob& Service::getTasklist(const QString& tasklistId) { return *new GetTasklistJob(this, tasklistId); }
InsertTasklistJob& Service::insertTasklist(const Tasklist& tasklist) { return *new InsertTasklistJob(this, tasklist); }
UpdateTasklistJob& Service::updateTasklist(const Tasklist& tasklist) { return *new UpdateTasklistJob(this, tasklist); }
DeleteTasklistJob& Service::deleteTasklist(const Tasklist& tasklist) { return *new DeleteTasklistJob(this, tasklist.id()); }
DeleteTasklistJob& Service::deleteTasklist(const QString& tasklistId) { return *new DeleteTasklistJob(this, tasklistId); }
//DeleteTasklistJob& Service::deleteTasklist(const QUrl& selfLink);
ListTasksJob& Service::listTasks(const Tasklist& tasklist) { return *new ListTasksJob(this, tasklist.id()); }
ListTasksJob& Service::listTasks(const QString& tasklistId) { return *new ListTasksJob(this, tasklistId); }
GetTaskJob& Service::getTask(const QUrl& selfLink) { return *new GetTaskJob(this, selfLink); }
GetTaskJob& Service::getTask(const QString& tasklistId, const QString& taskId) { return *new GetTaskJob(this, Task::generateSelfLink(tasklistId, taskId)); }
InsertTaskJob& Service::insertTask(const QString& tasklistId, const Task& task) { return *new InsertTaskJob(this, tasklistId, task); }
UpdateTaskJob& Service::updateTask(const Task& task) { return *new UpdateTaskJob(this, task); }
DeleteTaskJob& Service::deleteTask(const Task& task) { return *new DeleteTaskJob(this, task.selfLink()); }
DeleteTaskJob& Service::deleteTask(const QUrl& selfLink) { return *new DeleteTaskJob(this, selfLink); }
DeleteTaskJob& Service::deleteTask(const QString& tasklistId, const QString& taskId) { return *new DeleteTaskJob(this, Task::generateSelfLink(tasklistId, taskId)); }
MoveTaskJob& Service::moveTask(const Task& task) { return *new MoveTaskJob(this, task.selfLink()); }
MoveTaskJob& Service::moveTask(const QUrl& selfLink) { return *new MoveTaskJob(this, selfLink); }
MoveTaskJob& Service::moveTask(const QString& tasklistId, const QString& taskId)  { return *new MoveTaskJob(this, Task::generateSelfLink(tasklistId, taskId)); }
ClearTasksJob& Service::clearTasks(const Tasklist& tasklist) { return *new ClearTasksJob(this, tasklist.id()); }
ClearTasksJob& Service::clearTasks(const QString& tasklistId) { return *new ClearTasksJob(this, tasklistId); }


// Setters
void Service::setApiKey(const QString& key)       { m_apiKey = key; }
void Service::setToken(const OAuth::Token& token) { m_token = token; }

// Getters
const QString          Service::apiKey()         const { return m_apiKey; }
const OAuth::Token     Service::token()          const { return m_token; }
QNetworkAccessManager* Service::networkManager() const { return m_networkManager; }

} // namespace GTasks