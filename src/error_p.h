#ifndef ERROR_P_H
#define ERROR_P_H

#include <QSharedData>
#include <QNetworkReply>
#include <QString>

namespace GTasks {

class ErrorPrivate : public QSharedData
{
public:
	ErrorPrivate();
	ErrorPrivate(const ErrorPrivate& other);

	QNetworkReply::NetworkError code;
	QString message;
	int httpCode;
	QString gtasksMessage;
};

}

#endif // ERROR_P_H
