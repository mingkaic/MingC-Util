#include <Python/Python.h>
#include <vector>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include "prodcons.cpp"
static const char* directory = "tests";
static const char* readDirPython = "readdir";
static const char* readDirFunc = "readdir";
static PCBuffer buffer;
static std::mutex sleep_mu;

std::vector<std::string>* readDirectory(const char* directory) {
	PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    int i;
    std::vector<std::string>* out = NULL;

    Py_Initialize();
    pName = PyString_FromString(readDirPython);

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, readDirFunc);

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            pValue = PyString_FromString(directory);
            PyTuple_SetItem(pArgs, i, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
            	size_t nfiles = PyList_Size(pValue);
            	out = new std::vector<std::string>();
            	for (size_t i = 0; i < nfiles; i++) {
            		char buffer[256];
            		char* pystr = PyString_AsString(PyList_GetItem(pValue, i));
            		if (pystr) {
	            		strcpy(buffer, pystr);
	            		out->push_back(std::string(buffer));
            		}
            	}
                Py_DECREF(pValue);
            } else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", readDirFunc);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", readDirPython);
    }
    Py_Finalize();

    return out;
}

static void* testIn(void* not_used) {
	std::vector<std::string>* files = readDirectory(directory);
	if (NULL == files) {
	} else {
		std::ifstream file;
		double d;
		for (std::vector<std::string>::iterator it = files->begin(); it != files->end(); it++) {
			file.open("tests/"+*it, std::ifstream::in);
			if (file.good()) {
				while (!file.eof()) {
					file >> d;
					buffer.add(d);
                    sleep_mu.lock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    sleep_mu.unlock();
				}
				buffer.add(-1);
                sleep_mu.lock();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                sleep_mu.unlock();
			}
			file.close();
		}
	}
	delete files;
	return 0;
}

void readdir() {
	static pthread_t thread;
	int i;
	int rc = pthread_create(&thread, NULL, testIn, NULL);
	if (rc) {
        std::cout << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
	}
}

double getTestData() {
    double data = buffer.remove();
    sleep_mu.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    sleep_mu.unlock();
    return data;
}