#include <Python/Python.h>
#include <vector>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include "prodcons.cpp"
static const std::string numdirectory = "tests/number/";
static const std::string strdirectory = "tests/string/";
static const char* readDirPython = "readdir";
static const char* readDirFunc = "readdir";
static PCBuffer<double> numbuffer;
static PCBuffer<std::string> strbuffer;
static std::mutex sleep_mu;

std::vector<std::string>* readDirectory(const char* directory) 
    {
	PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    int i;
    std::vector<std::string>* out = NULL;

    Py_Initialize();
    pName = PyString_FromString(readDirPython);

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) 
        {
        pFunc = PyObject_GetAttrString(pModule, readDirFunc);

        if (pFunc && PyCallable_Check(pFunc)) 
            {
            pArgs = PyTuple_New(1);
            pValue = PyString_FromString(directory);
            PyTuple_SetItem(pArgs, i, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) 
                {
            	size_t nfiles = PyList_Size(pValue);
            	out = new std::vector<std::string>();
            	for (size_t i = 0; i < nfiles; i++) 
                    {
            		char buffer[256];
            		char* pystr = PyString_AsString(PyList_GetItem(pValue, i));
            		if (pystr) 
                        {
	            		strcpy(buffer, pystr);
	            		out->push_back(std::string(buffer));
            		  }
            	   }
                Py_DECREF(pValue);
                } 
            else 
                {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                }
            } 
        else 
            {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", readDirFunc);
            }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
        } 
    else 
        {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", readDirPython);
        }
    Py_Finalize();

    return out;
}

template <typename T>
void bufferPopulate(std::string directory, 
                    std::vector<std::string>* fileset, 
                    PCBuffer<T>& buff,
                    T delimiter)
    {
    if (NULL == fileset) {} 
    else 
        {
        std::ifstream file;
        T data;
        for (std::vector<std::string>::iterator it = fileset->begin(); 
            it != fileset->end();
            it++) 
            {
            file.open(directory+*it, std::ifstream::in);
            if (file.good()) 
                {
                while (!file.eof()) 
                    {
                    file >> data;
                    buff.add(data);
                    }
                buff.add(delimiter);
                }
            file.close();
            }
        }
    }

static void* testNumIn(void* not_used) 
    {
    sleep_mu.lock();
    std::vector<std::string>* nfiles = readDirectory(numdirectory.c_str());
    sleep_mu.unlock();
	bufferPopulate<double>(numdirectory, nfiles, numbuffer, -1);
    delete nfiles;
	return 0;
    }

static void* testStrIn(void* not_used) 
    {
    sleep_mu.lock();
    std::vector<std::string>* sfiles = readDirectory(strdirectory.c_str());
    sleep_mu.unlock();
    bufferPopulate<std::string>(strdirectory, sfiles, strbuffer, "");
    delete sfiles;
    return 0;
    }

void readdir(pthread_t& thread, pthread_t& thread2) 
    {
	int i;
	int rc = pthread_create(&thread, NULL, testNumIn, NULL);
	if (rc) 
        {
        std::cout << "Error:unable to create number thread," << rc << std::endl;
        exit(-1);
        }

    rc = pthread_create(&thread2, NULL, testStrIn, NULL);
    if (rc) 
        {
        std::cout << "Error:unable to create string thread," << rc << std::endl;
        exit(-1);
        }
    }

std::string getStrData() 
    {
    std::string data = strbuffer.remove();
    return data;
    }

double getNumData() 
    {
    double data = numbuffer.remove();
    return data;
    }