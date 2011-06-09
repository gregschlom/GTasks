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

#ifndef GTASKS_JOB_H
#define GTASKS_JOB_H

#include <QObject>
#include <QVariant>
#include <QUrl>

class QNetworkReply;
class QNetworkRequest;

namespace GTasks {

class Service;
class Error;

class Job : public QObject {
	Q_OBJECT

public:
	enum HttpMethod { Get, Post, Put, Delete, Head };

	explicit Job(Service* service, HttpMethod method, const QUrl& url, const char* result);
	void start();
	void startAndCallback(QObject* object, const char* callbackSlot);

protected:
	void addRequestParam(const QString& param, const QVariant& value);
	void setRequestData(const QVariantMap& data);
	virtual void parseReply(const QVariantMap& response, const GTasks::Error& error) = 0;

private slots:
	void parseReply();

private:
	Service* m_service;
	HttpMethod m_method;
	QUrl m_url;
	QMap<QString, QString> m_parameters;
	QVariantMap m_data;
	QNetworkReply* m_reply;
	const char* m_resultSignal;
};

}
#endif // GTASKS_JOB_H
