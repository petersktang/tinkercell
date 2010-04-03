#include <Python.h>
#include "TC_api.h"

#cmakedefine CMAKE_WIN32

#ifndef CMAKE_WIN32
#include "dlfcn.h"
#endif

FILE * pyout;

PyObject* main_dict;
PyObject* dlfl_dict;
PyObject * s;
PyObject *evalVal;
PyObject *errobj;
PyObject *errdata;
PyObject *errtraceback;

FILE * pyout;

void initialize()
{
	PyObject *mainmod;
	PyObject *dlfl;
#ifndef CMAKE_WIN32
	dlopen("@PYTHON_LIBRARIES@", RTLD_LAZY | RTLD_GLOBAL);	
	Py_SetProgramName("Tinkercell");
#endif
	Py_Initialize();
	
	//Py_InitModule("pytc", pytcMethods);
	mainmod = PyImport_AddModule("__main__");
	//dlfl = PyImport_AddModule("pytc");
	main_dict = PyModule_GetDict( mainmod );
	//dlfl_dict = PyModule_GetDict( dlfl );
	
	pyout = fopen("py.out","a");
}

void exec(const char * code,const char * outfile)
{
	char *retString, 
	 	   *errString;
	PyObject * s,
			 *evalVal,
			 *errobj, 
			 *errdata, 
			 *errtraceback;
			 
	//PyRun_SimpleString( code );
	evalVal = PyRun_String( code, Py_file_input, main_dict, dlfl_dict );
	//evalVal = PyDict_GetItemString( main_dict, "_" );
	
	PyErr_Fetch (&errobj, &errdata, &errtraceback);
	
	/*if (evalVal != NULL)
	{
		s = PyObject_Str(evalVal); 
		retString = PyString_AsString(s);
		tc_print(retString);
		Py_DECREF(s); 
		Py_DECREF(evalVal);
	}*/

	tc_printFile(outfile);
	
	if (errdata != NULL) 
	{ 
		s = PyObject_Str(errdata); 
		errString = PyString_AsString(s);
		tc_errorReport(errString);
		Py_DECREF(s); 
	}
	
	Py_XDECREF(errobj); 
	Py_XDECREF(errdata); 
	Py_XDECREF(errtraceback); 
	Py_XDECREF(evalVal);
}

void finalize()
{
	Py_XDECREF(errobj); 
	Py_XDECREF(errdata); 
	Py_XDECREF(errtraceback); 
	
    Py_Finalize();
	
	fclose(pyout);
}