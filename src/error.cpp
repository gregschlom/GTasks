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

#include "error.h"
#include "error_p.h"

#include <QString>

namespace GTasks {

Error::Error()
	: d(new ErrorPrivate)
{
}

Error::~Error()
{
}

Error::Error(const Error& other)
	: d(other.d)
{
}

Error& Error::operator=(const Error& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

ErrorPrivate::ErrorPrivate()
	: QSharedData(),
	  code(QNetworkReply::NoError),
	  message(""),
	  httpCode(0),
	  gtasksMessage("")
{
}

ErrorPrivate::ErrorPrivate(const ErrorPrivate& other)
	: QSharedData(other),
	  code(other.code),
	  message(other.message),
	  httpCode(other.httpCode),
	  gtasksMessage(other.gtasksMessage)
{
}

// Getters
QNetworkReply::NetworkError Error::code()          const { return d->code; }
QString                     Error::message()       const { return d->message; }
int                         Error::httpCode()      const { return d->httpCode; }
QString                     Error::gtasksMessage() const { return d->gtasksMessage; }

// Setters
void Error::setCode(QNetworkReply::NetworkError code) { d->code = code; }
void Error::setMessage(const QString& message) { d->message = message; }
void Error::setHttpCode(int httpCode) { d->httpCode = httpCode; }
void Error::setGtasksMessage(const QString& gtasksMessage) { d->gtasksMessage = gtasksMessage; }

} // namespace GTasks
