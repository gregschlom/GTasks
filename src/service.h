/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_SERVICE_H
#define GTASKS_SERVICE_H

#include <QObject>
#include <QUrl>

#include "simpleoauth/oauth_token.h"

class QNetworkAccessManager;

namespace GTasks {

class Tasklist;
class ListTasksJob;
class ListTasklistsJob;
class InsertTasklistJob;
class DeleteTasklistJob;

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QNetworkAccessManager* networkManager, QObject* parent = 0);

	void setApiKey(const QString& key);
	void setToken(const OAuth::Token& token);

	QNetworkAccessManager* networkManager() const;
	QUrl baseUrl() const;
	const QString apiKey() const;
	const OAuth::Token token() const;

	ListTasksJob& listTasks(const QString& tasklistId);
	ListTasklistsJob& listTasklists();
	InsertTasklistJob& insertTasklist(const Tasklist& tasklist);
	DeleteTasklistJob& deleteTasklist(const Tasklist& tasklist);
	DeleteTasklistJob& deleteTasklist(const QString& tasklistId);

private:
	QNetworkAccessManager* m_networkManager;
	QString m_apiKey;
	OAuth::Token m_token;
	const QUrl m_baseUrl;
};

}

#endif // GTASKS_SERVICE_H
