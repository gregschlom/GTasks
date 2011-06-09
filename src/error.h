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

#ifndef ERROR_H
#define ERROR_H

#include <QSharedData>
#include <QNetworkReply>

class QString;

namespace GTasks {

class ErrorPrivate;

class Error
{
public:
	Error();
	Error(const Error& other);
	Error &operator=(const Error&);
	~Error();

	QNetworkReply::NetworkError code() const;
	QString message() const;
	int httpCode() const;
	QString gtasksMessage() const;

	void setCode(QNetworkReply::NetworkError code);
	void setMessage(const QString& message);
	void setHttpCode(int httpCode);
	void setGtasksMessage(const QString& gtasksMessage);

private:
	friend class ErrorPrivate;
	QSharedDataPointer<ErrorPrivate> d;
};

}

#endif // ERROR_H
