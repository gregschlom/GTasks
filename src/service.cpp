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

#include "service.h"
#include "jobs.h"

namespace GTasks {

Service::Service(QNetworkAccessManager* networkManager, QObject* parent) :
    QObject(parent),
    m_networkManager(networkManager)
{
}

ListTasklistsJob& Service::listTasklists() { return *new ListTasklistsJob(this); }
GetTasklistJob& Service::getTasklist(const QUrl& selfLink) { return *new GetTasklistJob(this, selfLink); }
GetTasklistJob& Service::getTasklist(const QString& tasklistId) { return *new GetTasklistJob(this, Tasklist::generateSelfLink(tasklistId)); }
InsertTasklistJob& Service::insertTasklist(const Tasklist& tasklist) { return *new InsertTasklistJob(this, tasklist); }
UpdateTasklistJob& Service::updateTasklist(const Tasklist& tasklist) { return *new UpdateTasklistJob(this, tasklist); }
DeleteTasklistJob& Service::deleteTasklist(const Tasklist& tasklist) { return *new DeleteTasklistJob(this, tasklist.selfLink()); }
DeleteTasklistJob& Service::deleteTasklist(const QString& tasklistId) { return *new DeleteTasklistJob(this, Tasklist::generateSelfLink(tasklistId)); }
DeleteTasklistJob& Service::deleteTasklist(const QUrl& selfLink) { return *new DeleteTasklistJob(this, selfLink); }
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
