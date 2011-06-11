GTasks - A C++/Qt API client for Google Tasks
=============================================

GTasks is a C++/library that allows you to interact with the Google Tasks API. 
Before using GTasks, please make sure that you are familiar with the Google Tasks API.

Read the documentation of the Google Tasks API:
http://code.google.com/apis/tasks/overview.html

Enable the API:
https://code.google.com/apis/console

Dependencies
============

GTasks depends on the following libraries:

  * SimpleOAuth - A OAuth library for Qt:
    https://github.com/gregschlom/SimpleOAuth

  * QJson - A library for reading and writing JSON:
    http://qjson.sourceforge.net/

  * And of course, Qt:
    http://qt.nokia.com/

Architecture
============

GTasks is structured into jobs. There is a job for each operation that you can do (list tasks, list tasklists, delete task, etc...), and each job has a result signal that is emitted when the job finishes.

You create a new job instances by using the appropriate method in the GTasks::Service, for example, to delete a task:

	QString taskId = "ABCDEFGH1234";
	// Assume service is a pointer to a Gtasks::Service instance
	gtasksService->deleteTask(taskId).startAndCallback(this, SLOT(onTaskDeleted(GTasks::Error)));

startAndCallback will connect the slot that you provide with the job's result signal, and will start the job. If you're not interested in receiving the job's result signal, you could just call start() instead.

Memory management
=================

GTasks use the copy-on-write idiom for the model classes, and Qt's deleteLater() for the jobs, meaning that you don't have to manually delete any object, except the GTasks::Service instance.

Authentication
==============

You must use the SimpleOAuth library to authenticate your user.
Once you have a valid OAuth::Token, just pass it to the GTasks::Service.

See SimpleOauth documentation: https://github.com/gregschlom/SimpleOAuth

Usage
=====

	MyClass::setupGTasks()
	{		
		m_gtasks = new GTasks::Service(new QNetworkAccessManager(this), this);
		m_gtasks->setApiKey("[YOUR API KEY HERE]");

		// Creates a oauth token from the SimpleOAuth library
		OAuth::Token token;
		token.setType(OAuth::Token::AccessToken);
		token.setConsumerKey("[YOUR OAUTH CONSUMER KEY]");
		token.setConsumerSecret("[YOUR OAUTH CONSUMER SECRET]");
		token.setTokenString("[VALID OAUTH TOKEN STRING]");  // Assuming you have previously
		token.setTokenSecret("[VALID OAUTH TOKEN SECRET]");	 // authenticated the user

		// m_gtasks is ready to process request now
		m_gtasks->setToken(token);
	}

	/*!
	  Retrieves a list of all Tasklists
	 */
	MyClass::getAllTaskslists
	{
		m_gtasks->listTasklists().startAndCallback(this, 
			SLOT(onTasklistsReceived(GTasks::TasklistCollection, GTasks::Error)));
	}
	
	/*!
	  This slot will be called by GTasks when the tasklists have been retrieved
	*/
	MyClass::onTasklistsReceived(GTasks::TasklistCollection tasklists, GTasks::Error error))
	{
		if (error.code() != QNetworkReply::NoError) {
			// Do some error handling here
			qDebug() << "Error:" << error.code() << error.message();
			return;
		}
	
		// Display the title and id of each tasklist
		foreach (const GTasks::Tasklist& tasklist, tasklists.items()) {
			qDebug() << "Tasklist:" << tasklist.title() << "id:" << tasklist.id();
		}
	}

Contact
=======
GTasks is released under the terms of the MIT license.

For any information, feel free to contact me:
Gregory Schlomoff - gregory.schlomoff@gmail.com