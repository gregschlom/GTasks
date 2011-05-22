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

class ListTasksJob;
class InsertTasklistJob;
class Tasklist;

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
	InsertTasklistJob& insertTasklist(const Tasklist& tasklist);

private:
	QNetworkAccessManager* m_networkManager;
	QString m_apiKey;
	OAuth::Token m_token;
	const QUrl m_baseUrl;
};

}

#endif // GTASKS_SERVICE_H
