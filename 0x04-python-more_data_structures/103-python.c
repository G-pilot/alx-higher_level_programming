#include <stdio.h>
#include <stdlib.h>

void print_python_list(PyObject *p)
{
	if (!PyList_Check(p))
	{
		printf("Invalid PyListObject\n");
		return;
	}
	Py_ssize_t size = PyList_Size(p);

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %zd\n", size);
	printf("[*] Allocated = %zd\n", ((PyListObject *)p)->allocated);

	for (Py_ssize_t i = 0; i < size; ++i)
	{
		PyObject *item = PyList_GetItem(p, i);

		printf("Element %zd: %s\n", i, Py_TYPE(item)->tp_name);
	}
}

void print_python_bytes(PyObject *p)
{
	if (!PyBytes_Check(p))
	{
		printf("Invalid PyBytesObject\n");
		return;
	}
	Py_ssize_t size = PyBytes_Size(p);

	printf("[.] bytes object info\n");
	printf("  size: %zd\n", size);
	printf("  trying string: %s\n", PyBytes_AsString(p));
	printf("  first 10 bytes: ");
	for (Py_ssize_t i = 0; i < size && i < 10; ++i)
	{
		printf("%02x ", (unsigned char)PyBytes_AsString(p)[i]);
	}
	printf("\n");
}
int main(void)
{
	Py_Initialize();
	PyObject *pythonList = PyList_New(3);

	PyList_SetItem(pythonList, 0, PyLong_FromLong(42));
	PyList_SetItem(pythonList, 1, PyUnicode_FromString("Hello"));
	PyList_SetItem(pythonList, 2, PyFloat_FromDouble(3.14));
	print_python_list(pythonList);
	const char *byteData = "PythonBytes";
	PyObject *pythonBytes = PyBytes_FromStringAndSize
		(byteData, strlen(byteData));
	print_python_bytes(pythonBytes);
	Py_XDECREF(pythonList);
	Py_XDECREF(pythonBytes);
	Py_Finalize();
return (0);
}
