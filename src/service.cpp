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
    m_networkManager(networkManager),
    m_baseUrl("https://www.googleapis.com/tasks/v1")
{
}

ListTasksJob& Service::listTasks(const QString& tasklistId)
{
	return *new ListTasksJob(this, tasklistId);
}

InsertTasklistJob& Service::insertTasklist(const Tasklist& tasklist)
{
	return *new InsertTasklistJob(this, tasklist);
}

// Setters
void Service::setApiKey(const QString& key)       { m_apiKey = key; }
void Service::setToken(const OAuth::Token& token) { m_token = token; }

// Getters
QUrl                   Service::baseUrl()        const { return m_baseUrl; }
const QString          Service::apiKey()         const { return m_apiKey; }
const OAuth::Token     Service::token()          const { return m_token; }
QNetworkAccessManager* Service::networkManager() const { return m_networkManager; }

} // namespace GTasks