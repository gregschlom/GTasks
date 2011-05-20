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
	//m_baseUrl("https://betterinbox.com")
{
}

ListTasks* Service::listTasks()
{
	return new ListTasks(this);
}

void Service::setApiKey(QString key) { m_apiKey = key; }
void Service::setToken(OAuth::Token token) { m_token = token; }

QString Service::apiKey() const { return m_apiKey; }
QString Service::baseUrl() const { return m_baseUrl; }
OAuth::Token Service::token() const { return m_token; }
QNetworkAccessManager* Service::networkManager() const { return m_networkManager; }

} // namespace GTasks