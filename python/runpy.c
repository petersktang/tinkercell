#include <Python.h>
#include "TC_api.h"

#ifndef _WIN32
#include "dlfcn.h"
#endif

PyObject* main_dict;
PyObject* dlfl_dict;
PyObject *evalVal;
PyObject *errobj;
PyObject *errdata;
PyObject *errtraceback;

TCAPIEXPORT void initialize()
{
	PyObject *mainmod;
	PyObject *dlfl;
#ifndef _WIN32
	dlopen("@PYTHON_LIBRARIES@", RTLD_LAZY | RTLD_GLOBAL);	
	Py_SetProgramName("Tinkercell");
#endif
	Py_Initialize();
	
	//Py_InitModule("pytc", pytcMethods);
	mainmod = PyImport_AddModule("__main__");
	//dlfl = PyImport_AddModule("pytc");
	main_dict = PyModule_GetDict( mainmod );
	//dlfl_dict = PyModule_GetDict( dlfl );
}

TCAPIEXPORT void exec(const char * code,const char * outfile)
{
	FILE * file;
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
	
	if (errdata != NULL) 
	{ 
		s = PyObject_Str(errdata); 
		errString = PyString_AsString(s);
		tc_errorReport(errString);
		file = fopen(outfile,"w");
		if (file)
		{
			fclose(file);
		}
		Py_DECREF(s); 
	}
	
	Py_XDECREF(errobj); 
	Py_XDECREF(errdata); 
	Py_XDECREF(errtraceback); 
	Py_XDECREF(evalVal);
}

TCAPIEXPORT void finalize()
{
	Py_XDECREF(errobj); 
	Py_XDECREF(errdata); 
	Py_XDECREF(errtraceback); 
	
    Py_Finalize();
}
