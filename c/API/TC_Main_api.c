#include "TC_Main_api.h"

ArrayOfItems (*_tc_allItems)() = 0;
/*! 
 \brief get all visible items
 \ingroup Get items
*/
ArrayOfItems tc_allItems()
{
	if (_tc_allItems)
		return _tc_allItems();
	return newArrayOfItems(0);
}

ArrayOfItems (*_tc_selectedItems)() = 0;
/*! 
 \brief get all selected items
 \ingroup Get items
*/
ArrayOfItems tc_selectedItems()
{
	if (_tc_selectedItems)
		return _tc_selectedItems();
	return newArrayOfItems(0);
}

ArrayOfItems (*_tc_itemsOfFamily)(String family) = 0;
/*!
 \brief get all items of the given family items
 \ingroup Get items
*/
ArrayOfItems tc_itemsOfFamily(String family)
{
	if (_tc_itemsOfFamily)
		return _tc_itemsOfFamily(family);
	return newArrayOfItems(0);
}

ArrayOfItems (*_tc_itemsOfFamilyFrom)(String family, ArrayOfItems itemsToSelectFrom) = 0;
/*! 
 \brief get subset of items that belong to the given family
 \ingroup Get items
*/
ArrayOfItems tc_itemsOfFamilyFrom(String family, ArrayOfItems itemsToSelectFrom)
{
	if (_tc_itemsOfFamilyFrom)
		return _tc_itemsOfFamilyFrom(family,itemsToSelectFrom);
	return newArrayOfItems(0);
}

void * (*_tc_find)(String fullname) = 0;
/*! 
 \brief get the first item with the given name (full name)
 \ingroup Get items
*/
void * tc_find(String fullname)
{
	if (_tc_find)
		return _tc_find(fullname);
	return 0;
}

ArrayOfItems (*_tc_findItems)(ArrayOfStrings names) = 0;
/*! 
 \brief get all items with the given names (full names)
 \ingroup Get items
*/
ArrayOfItems tc_findItems(ArrayOfStrings names)
{
	if (_tc_findItems)
		return _tc_findItems(names);
	return newArrayOfItems(0);
}

void (*_tc_select)(void * item) = 0;
/*! 
 \brief select an item
 \ingroup Get items
*/
void tc_select(void * item)
{
	if (_tc_select && item)
		_tc_select(item);
}

void (*_tc_deselect)() = 0;
/*! 
 \brief deselect all items
 \ingroup Get items
*/
void tc_deselect()
{
	if (_tc_deselect)
		_tc_deselect();
}

String (*_tc_getName)(void * item) = 0;
/*! 
 \brief get the full name of an item
 \ingroup Annotation
*/
String tc_getName(void * item)
{
	if (_tc_getName)
		return _tc_getName(item);
	return 0;
}

void (*_tc_rename)(void * item,String name) = 0;
/*! 
 \brief set the name of an item (not full name)
 \ingroup Annotation
*/
void tc_rename(void * item,String name)
{
	if (_tc_rename)
		_tc_rename(item,name);
}

ArrayOfStrings (*_tc_getNames)(ArrayOfItems items) = 0;
/*! 
 \brief get the full names of several items
 \ingroup Annotation
*/
ArrayOfStrings tc_getNames(ArrayOfItems items)
{
	if (_tc_getNames)
		return _tc_getNames(items);
	return newArrayOfStrings(0);
}

String (*_tc_getFamily)(void * item) = 0;
/*! 
 \brief get the family name of an item
 \ingroup Annotation
*/
String tc_getFamily(void * item)
{
	if (_tc_getFamily)
		return _tc_getFamily(item);
	return 0;
}

int (*_tc_isA)(void * item,String family) = 0;
/*! 
 \brief check is an item belongs in a family (or in a sub-family)
 \ingroup Annotation
*/
int tc_isA(void * item,String family)
{
	if (_tc_isA)
		return _tc_isA(item,family);
	return 0;
}

void (*_tc_print)(String text) = 0;
/*! 
 \brief show text in the output window.
 \ingroup Input and Output
*/
void tc_print(String text)
{
	if (_tc_print && text)
		_tc_print(text);
}

void (*_tc_errorReport)(String text) = 0;
/*! 
 \brief show error text in the output window.
 \ingroup Input and Output
*/
void tc_errorReport(String text)
{
	if (_tc_errorReport && text)
		_tc_errorReport(text);
}

void (*_tc_printTable)(Matrix data) = 0;
/*! 
 \brief show table in the output window.
 \ingroup Input and Output
*/
void tc_printTable(Matrix data)
{
	if (_tc_printTable)
		_tc_printTable(data);
}

void (*_tc_printFile)(String filename) = 0;
/*! 
 \brief show file contents in the output window. 
 \ingroup Input and Output
*/
void tc_printFile(String filename)
{
	if (_tc_printFile)
		_tc_printFile(filename);
}

void (*_tc_clear)() = 0;
/*! 
 \brief cleat the contents in the output window. 
 \ingroup Input and Output
*/
void tc_clear()
{
	if (_tc_clear)
		_tc_clear();
}

void (*_tc_remove)(void * item) = 0;
/*! 
 \brief delete an item
 \ingroup Insert and remove
*/
void tc_remove(void * item)
{
	if (_tc_remove)
		_tc_remove(item);
}

double (*_tc_getY)(void * item) = 0;

/*! 
 \brief get the x location of an item
 \ingroup Appearance
*/
double tc_getY(void * item)
{
	if (_tc_getY && item)
		return _tc_getY(item);
	return 0.0;
}

double (*_tc_getX)(void * item) = 0;
/*! 
 \brief get the y location of an item
 \ingroup Appearance
*/
double tc_getX(void * item)
{
	if (_tc_getX)
		return _tc_getX(item);
	return 0.0;
}

Matrix (*_tc_getPos)(ArrayOfItems items) = 0;
/*! 
 \brief get the y location of a list item. Output is a N x 2 matrix
 \ingroup Appearance
*/
Matrix tc_getPos(ArrayOfItems items)
{
	if (_tc_getPos)
		return _tc_getPos(items);
	return newMatrix(0,0);
}

void (*_tc_setPos)(void * item,double x,double y) = 0;
/*! 
 \brief set the x and y location of an item
 \ingroup Appearance
*/
void tc_setPos(void * item,double x,double y)
{
	if (_tc_setPos && item)
		_tc_setPos(item,x,y);
}

void (*_tc_setPosMulti)(ArrayOfItems items, Matrix positions) = 0;
/*! 
 \brief set the x and y location of a list of N items. Input a matrix of positions, with N rows and 2 columns (x,y)
 \ingroup Appearance
*/
void tc_setPosMulti(ArrayOfItems items, Matrix positions)
{
	if (_tc_setPosMulti && items.length > 0 && items.items && positions.rows == items.length)
		_tc_setPosMulti(items,positions);
}

void (*_tc_moveSelected)(double dx,double dy) = 0;
/*! 
 \brief move all the selected items by a given amount
 \ingroup Appearance
*/
void tc_moveSelected(double dx,double dy)
{
	if (_tc_moveSelected)
		_tc_moveSelected(dx,dy);
}

int (*_tc_isWindows)() = 0;
/*! 
 \brief is this running in MS windows?
 \ingroup System information
*/
int tc_isWindows()
{
	if (_tc_isWindows)
		return _tc_isWindows();
	return 0;
}

int (*_tc_isMac)() = 0;
/*! 
 \brief is this running in a Mac?
 \ingroup System information
*/
int tc_isMac()
{
	if (_tc_isMac)
		return _tc_isMac();
	return 0;
}

int (*_tc_isLinux)() = 0;
/*! 
 \brief is this running in Linux?
 \ingroup System information
*/
int tc_isLinux()
{
	if (_tc_isLinux)
		return _tc_isLinux();
	return 0;
}

String (*_tc_appDir)() = 0;
/*! 
 \brief TinkerCell application folder
 \ingroup System information
*/
String tc_appDir()
{
	if (_tc_appDir)
		return _tc_appDir();
	return 0;
}

void (*_tc_createInputWindowFromFile)(Matrix input, String filename,String functionname, String title) = 0;
/*! 
 \brief create an input window that can call a dynamic library
 \ingroup Input and Output
*/
void tc_createInputWindowFromFile(Matrix input, String filename,String functionname, String title)
{
	if (_tc_createInputWindowFromFile)
		_tc_createInputWindowFromFile(input,filename,functionname,title);
}

void (*_tc_createInputWindow)(Matrix, String title, void (*f)(Matrix)) = 0;
/*!
 \brief create an input window that can call a dynamic library
 \ingroup Input and Output
*/
void tc_createInputWindow(Matrix input, String title, void (*f)(Matrix))
{
	if (_tc_createInputWindow)
		_tc_createInputWindow(input,title,f);
}

void (*_tc_addInputWindowOptions)(String, int i, int j, ArrayOfStrings) = 0;
/*! 
 \brief add options to an existing input window at the i,j-th cell. Options will appear in a list
 \ingroup Input and Output
*/
void tc_addInputWindowOptions(String title, int i, int j, ArrayOfStrings options)
{
	if (_tc_addInputWindowOptions)
		_tc_addInputWindowOptions(title,i,j,options);
}

void (*_tc_addInputWindowCheckbox)(String, int i, int j) = 0;
/*! 
 \brief add a yes or no type of option to an existing input window at the i,j-th cell
 \ingroup Input and Output
*/
void tc_addInputWindowCheckbox(const char * title, int i, int j)
{
	if (_tc_addInputWindowCheckbox)
		_tc_addInputWindowCheckbox(title,i,j);
}

void (*_tc_openNewWindow)(const char * title) = 0;
/*! 
 \brief open a new graphics window
 \ingroup Input and Output
*/
void tc_openNewWindow(const char * title)
{
	if (_tc_openNewWindow)
		_tc_openNewWindow(title);
}

ArrayOfItems (*_tc_getChildren)(void *) = 0;
/*! 
 \brief get child items of the given item
 \ingroup Get items
*/
ArrayOfItems tc_getChildren(void * o)
{
	if (_tc_getChildren)
		return _tc_getChildren(o);
	return newArrayOfItems(0);
}

void * (*_tc_getParent)(void *) = 0;
/*! 
 \brief get parent item of the given item
 \ingroup Get items
*/
void * tc_getParent(void * o)
{
	if (_tc_getParent)
		return _tc_getParent(o);
	return 0;
}

Matrix (*_tc_getNumericalData)(void * item,String data) = 0;
/*! 
 \brief get the entire data matrix for the given numerical data table of the given item
 \ingroup Data
*/
Matrix tc_getNumericalData(void * item,String data)
{
	if (_tc_getNumericalData)
		return _tc_getNumericalData(item,data);
	return newMatrix(0,0);
}

void (*_tc_setNumericalData)(void *,String,Matrix) = 0;
/*! 
 \brief set a new data matrix for an item. Use 0 for the global model item.
 \ingroup Data
*/
void tc_setNumericalData(void * o,String title,Matrix data)
{
	if (_tc_setNumericalData)
		_tc_setNumericalData(o, title, data);
}

TableOfStrings (*_tc_getTextData)(void * item,String data) = 0;
/*! 
 \brief get the entire data matrix for the given strings data table of the given item
 \ingroup Data
*/
TableOfStrings tc_getTextData(void * item,String data)
{
	if (_tc_getTextData)
		return _tc_getTextData(item,data);
	return newTableOfStrings(0,0);
}

void (*_tc_setTextData)(void *,String,TableOfStrings) = 0;
/*! 
 \brief set the entire data matrix for the given strings data table of the given item
 \ingroup Data
*/
void tc_setTextData(void * o,String title,TableOfStrings data)
{
	if (_tc_setTextData)
		_tc_setTextData(o, title, data);
}


ArrayOfStrings (*_tc_getNumericalDataNames)(void *) = 0;
/*! 
 \brief get all the numeric data table names for the given item. Use 0 for the global tables.
 \ingroup Data
*/
ArrayOfStrings tc_getNumericalDataNames(void * o)
{
	if (_tc_getNumericalDataNames)
		return _tc_getNumericalDataNames(o);
	return newArrayOfStrings(0);
}

ArrayOfStrings (*_tc_getTextDataNames)(void *) = 0;
/*! 
 \brief get all the text data table names for the given item. Use 0 for the global tables.
 \ingroup Data
*/
ArrayOfStrings tc_getTextDataNames(void * o)
{
	if (_tc_getTextDataNames)
		return _tc_getTextDataNames(o);
	return newArrayOfStrings(0);
}

void (*_tc_zoom)(double factor) = 0;
/*! 
 \brief zoom by the given factor (0 - 1)
 \ingroup Input and Output
*/
void tc_zoom(double factor)
{
	if (_tc_zoom)
		_tc_zoom(factor);
}

String (*_tc_getString)(String title) = 0;
/*! 
 \brief get a text from the user (dialog)
 \ingroup Input and Output
*/
String tc_getString(String title)
{
	if (_tc_getString)
		return _tc_getString(title);
	return 0;
}

String (*_tc_getFilename)() = 0;
/*! 
 \brief get a file from the user (dialog)
 \ingroup Input and Output
*/
String tc_getFilename()
{
	if (_tc_getFilename)
		return _tc_getFilename();
	return 0;
}

int (*_tc_getFromList)(String title, ArrayOfStrings list,String selectedString, int comboBox) = 0;
/*! 
 \brief get a text from the user (dialog) from a list of selections
 \ingroup Input and Output
*/
int tc_getFromList(String title, ArrayOfStrings list,String selectedString, int comboBox)
{
	if (_tc_getFromList)
		return _tc_getFromList(title,list,selectedString,comboBox);
	return 0;
}

double (*_tc_getNumber)(String title) = 0;
/*! 
 \brief get a number from the user (dialog)
 \ingroup Input and Output
*/
double tc_getNumber(String title)
{
	if (_tc_getNumber)
		return _tc_getNumber(title);
	return 0.0;
}

void (*_tc_getNumbers)(ArrayOfStrings labels, double* result) = 0;
/*! 
 \brief get a list of numbers from the user (dialog) into the argument array
 \ingroup Input and Output
*/
void tc_getNumbers(ArrayOfStrings labels, double* result)
{
	if (_tc_getNumbers && result)
		_tc_getNumbers(labels,result);
}

int (*_tc_askQuestion)(String) = 0;
/*! 
 \brief display a dialog with a text and a yes and no button
 \param char* displayed message or question
 \ingroup Input and Output
*/
int tc_askQuestion(String message)
{
	if (_tc_askQuestion && message)
		return _tc_askQuestion(message);
	return 0;
}

void (*_tc_messageDialog)(String) = 0;
/*! 
 \brief display a dialog with a text message and a close button
 \param char* displayed message
 \ingroup Input and Output
*/
void tc_messageDialog(String message)
{
	if (_tc_messageDialog && message)
		_tc_messageDialog(message);
}

static void * _cthread_ptr = 0;

/*!
 \brief get pointer to the current thread
 \ingroup Programming interface
*/
void * tc_thisThread()
{
	return _cthread_ptr;
}


void (*_tc_createSliders)(void*, Matrix, void (*f)(Matrix)) = 0;
/*!
 \brief create a window with several sliders. when the sliders change, the given function will be called with the values in the sliders
 \ingroup Input and Output
*/
void tc_createSliders(Matrix input, void (*f)(Matrix))
{
	if (_tc_createSliders && _cthread_ptr)
		_tc_createSliders(_cthread_ptr, input,f);
}

void (*_tc_setSize)(void*,double,double,int) = 0;
/*!
 \brief Change the size of an item
 \ingroup Appearance
*/
void tc_setSize(void * item,double width,double height,int permanent)
{
	if (_tc_setSize)
		_tc_setSize(item,width,height,permanent);
}

double (*_tc_getWidth)(void*) = 0;
/*!
 \brief get the width of an item
 \ingroup Appearance
*/
double tc_getWidth(void * item)
{
	if (_tc_getWidth)
		_tc_getWidth(item);
	return 1.0;
}

double (*_tc_getHeight)(void*) = 0;
/*!
 \brief get the width of an item
 \ingroup Appearance
*/
double tc_getHeight(void * item)
{
	if (_tc_getHeight)
		_tc_getHeight(item);
	return 1.0;
}

void (*_tc_setAngle)(void*,double,int) = 0;
/*!
 \brief get the width of an item
 \ingroup Appearance
*/
void tc_setAngle(void * item, double t,int permanent)
{
	if (_tc_setAngle)
		_tc_setAngle(item,t,permanent);
}

double (*_tc_getAngle)(void*) = 0;
/*!
 \brief get the angle of an item
 \ingroup Appearance
*/
double tc_getAngle(void* item)
{
	if (_tc_getAngle)
		_tc_getAngle(item);
	return 1.0;
}

int (*_tc_getColorR)(void* item) = 0;
/*! 
 \brief get the red color of the item
 \ingroup Appearance
*/
int tc_getColorR(void* item)
{
	if (_tc_getColorR)
		return _tc_getColorR(item);
	return 0;
}

int (*_tc_getColorG)(void* item) = 0;
/*! 
 \brief get the green color of the item
 \ingroup Appearance
*/
int tc_getColorG(void* item)
{
	if (_tc_getColorG)
		return _tc_getColorG(item);
	return 0;
}

int (*_tc_getColorB)(void* item) = 0;
/*! 
 \brief get the blue color of the item
 \ingroup Appearance
*/
int tc_getColorB(void* item)
{
	if (_tc_getColorB)
		return _tc_getColorB(item);
	return 0;
}

void (*_tc_setColor)(void* item,int R,int G,int B, int permanent) = 0;
/*! 
 \brief set the rgb color  of the item and indicate whether or not the color is permanenet
 \ingroup Appearance
*/
void tc_setColor(void* item,int R,int G,int B, int permanent)
{
	if (_tc_setColor)
		_tc_setColor(item,R,G,B,permanent);
}

void (*_tc_changeNodeImage)(void*,const char*) = 0;
/*! 
 \brief change the graphics file for drawing one of the nodes
 \ingroup Appearance
*/
void tc_changeNodeImage(void* item,const char* filename)
{
	if (_tc_changeNodeImage)
		_tc_changeNodeImage(item,filename);
}

void (*_tc_changeArrowHead)(void*,const char*) = 0;
/*! 
 \brief change the graphics file for drawing the arrowheads for the given connection
 \ingroup Appearance
*/
void tc_changeArrowHead(void* connection,const char* filename)
{
	if (_tc_changeArrowHead)
		_tc_changeArrowHead(connection,filename);
}


/*! 
 \brief initialize main
 \ingroup init
*/
void tc_Main_api_initialize(
	    ArrayOfItems (*tc_allItems0)(),
		ArrayOfItems (*tc_selectedItems0)(),
		ArrayOfItems (*tc_itemsOfFamily0)(String),
		ArrayOfItems (*tc_itemsOfFamily1)(String, ArrayOfItems),
		void * (*tc_find0)(String),
		ArrayOfItems (*tc_findItems0)(ArrayOfStrings),
		void (*tc_select0)(void *),
		void (*tc_deselect0)(),
		String (*tc_getName0)(void *),
		void (*tc_setName0)(void * item,String name),
		ArrayOfStrings (*tc_getNames0)(ArrayOfItems),
		String (*tc_getFamily0)(void *),
		int (*tc_isA0)(void *,String),

		void (*tc_clearText)(),
		void (*tc_outputText0)(String),
		void (*tc_errorReport0)(String),
		void (*tc_outputTable0)(Matrix),
		void (*tc_printFile0)(String),

		void (*tc_removeItem0)(void *),

		double (*tc_getY0)(void *),
		double (*tc_getX0)(void *),
		Matrix (*tc_getPos0)(ArrayOfItems),
		void (*tc_setPos0)(void *,double,double),
		void (*tc_setPos1)(ArrayOfItems,Matrix),
		void (*tc_moveSelected0)(double,double),

		int (*tc_isWindows0)(),
		int (*tc_isMac0)(),
		int (*tc_isLinux0)(),
		String (*tc_appDir0)(),
		
		void (*tc_createInputWindow0)(Matrix,String,String, String),
        void (*tc_createInputWindow1)(Matrix, String, void (*f)(Matrix)),
		void (*createSliders0)(void*, Matrix, void (*f)(Matrix)),
		
		void (*tc_addInputWindowOptions0)(String, int i, int j, ArrayOfStrings),
		void (*tc_addInputWindowCheckbox0)(String, int i, int j),
		void (*tc_openNewWindow0)(const char * title),
		
		ArrayOfItems (*tc_getChildren0)(void *),
		void * (*tc_getParent0)(void *),
		
		Matrix (*tc_getNumericalData0)(void *,String),
		void (*tc_setNumericalData0)(void *,String,Matrix),
		TableOfStrings (*tc_getTextData0)(void *,String),
		void (*tc_setTextData0)(void *,String, TableOfStrings),
				
		ArrayOfStrings (*tc_getNumericalDataNames0)(void *),
		ArrayOfStrings (*tc_getTextDataNames0)(void *),
		
		void (*tc_zoom0)(double factor),
		
		String (*getString0)(String),
		int (*getSelectedString0)(String, ArrayOfStrings, String, int),
		double (*getNumber0)(String),
		void (*getNumbers0)( ArrayOfStrings, double * ),
		String (*getFilename0)(),
		
		int (*askQuestion0)(String),
		void (*messageDialog0)(String),
		
		void (*setSize0)(void*,double,double,int),
		double (*getWidth0)(void*),
		double (*getHeight0)(void*),
		void (*setAngle0)(void*,double,int),
		double (*getAngle0)(void*),
		int (*getColorR0)(void*),
		int (*getColorG0)(void*),
		int (*getColorB0)(void*),
		void (*setColor0)(void*,int,int,int,int),
		
		void (*changeGraphics0)(void*,const char*),
		void (*changeArrowHead0)(void*,const char*)
	)
{
	_tc_allItems = tc_allItems0;
	_tc_selectedItems = tc_selectedItems0; 
	_tc_itemsOfFamily = tc_itemsOfFamily0;
	_tc_itemsOfFamilyFrom = tc_itemsOfFamily1;
	_tc_find = tc_find0;
	_tc_findItems = tc_findItems0;
	_tc_select = tc_select0;
	_tc_deselect = tc_deselect0;
	_tc_getName = tc_getName0;
	_tc_rename = tc_setName0;
	
	_tc_getNames = tc_getNames0;
	_tc_getFamily = tc_getFamily0;
	_tc_isA = tc_isA0;

	_tc_clear = tc_clearText;
	_tc_print = tc_outputText0;
	_tc_errorReport = tc_errorReport0;
	_tc_printTable = tc_outputTable0;
	_tc_printFile = tc_printFile0;

	_tc_remove = tc_removeItem0;

	_tc_getY = tc_getY0;
	_tc_getX = tc_getX0;
	_tc_getPos = tc_getPos0;
	_tc_setPos = tc_setPos0;
	_tc_setPosMulti = tc_setPos1;
	_tc_moveSelected = tc_moveSelected0;

	_tc_isWindows = tc_isWindows0;
	_tc_isMac = tc_isMac0;
	_tc_isLinux = tc_isLinux0;
	_tc_appDir = tc_appDir0;
    _tc_createInputWindow = tc_createInputWindow1;
    _tc_createInputWindowFromFile = tc_createInputWindow0;
	_tc_addInputWindowOptions = tc_addInputWindowOptions0;
	_tc_addInputWindowCheckbox = tc_addInputWindowCheckbox0;
	
	_tc_openNewWindow = tc_openNewWindow0;
	
	_tc_getNumericalData = tc_getNumericalData0;
	_tc_getTextData = tc_getTextData0;
	_tc_setNumericalData = tc_setNumericalData0;
	_tc_setTextData = tc_setTextData0;
	_tc_getChildren = tc_getChildren0;
	_tc_getParent = tc_getParent0;

	_tc_getNumericalDataNames = tc_getNumericalDataNames0;
	_tc_getTextDataNames = tc_getTextDataNames0;
	
	_tc_zoom = tc_zoom0;
	
	_tc_getString = getString0;
	_tc_getFromList = getSelectedString0;
	_tc_getNumber = getNumber0;
	_tc_getNumbers = getNumbers0;
	_tc_getFilename = getFilename0;
	
	_tc_askQuestion = askQuestion0;
	_tc_messageDialog = messageDialog0;
	
	_tc_createSliders = createSliders0;
	
	_tc_setSize = _tc_setSize0;
	_tc_getWidth = getWidth0;
	_tc_getHeight = getHeight0;
	_tc_setAngle = setAngle0;
	_tc_getAngle = getAngle0;
	_tc_getColorR = getColorR0;
	_tc_getColorG = getColorG0;
	_tc_getColorB = getColorB0;
	_tc_setColor = setColor0;
	
	_tc_changeGraphics = changeGraphics0;
	_tc_changeArrowHead = changeArrowHead0;
}

void (*_tc_showProgress)(void * thread, int progress);
/*! 
 \brief show progress of current operation
 \ingroup Input and Output
*/
void tc_showProgress(int progress)
{
	if (_tc_showProgress && _cthread_ptr)
		_tc_showProgress(_cthread_ptr,progress);
}

/*! 
 \brief initialize main
 \ingroup init
*/
void tc_CThread_api_initialize( 
	void * cthread,
	void (*showProgress)(void*, int)	)
{
	_tc_showProgress = showProgress;
	_cthread_ptr = cthread;
}

