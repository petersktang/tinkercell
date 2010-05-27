/****************************************************************************
 Copyright (c) 2008 Deepak Chandran
 Contact: Deepak Chandran (dchandran1@gmail.com)

 see COPYRIGHT.TXT

 The python interpreter that runs as a separate thread and can accept strings to parse and execute
 
****************************************************************************/
#ifndef TINKERCELL_PYTHONINTERPRETERTHREAD_H
#define TINKERCELL_PYTHONINTERPRETERTHREAD_H

#include "InterpreterThread.h"

namespace Tinkercell
{

    class PythonInterpreterThread : public InterpreterThread
	{
		Q_OBJECT
		
		typedef void (*initFunc)();
		typedef void (*execFunc)(const char*,const char*);
		typedef void (*finalFunc)();
		
	public:
		PythonInterpreterThread(const QString&, MainWindow* main);

	public slots:
		virtual void initialize();
		virtual void finalize();

	protected:
		virtual void run();
		execFunc f;
	};
}

#endif