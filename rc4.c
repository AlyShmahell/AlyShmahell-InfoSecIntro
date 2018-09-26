#include <Python.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>


int64_t* ksa(char* key)
{
    static int64_t S[256];
    for(int64_t i = 0; i < 256; i++)
    {
        S[i] = i;
    }

    int64_t j = 0;
    int64_t key_length = strlen(key);
    int64_t temp;
    for(int64_t i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % key_length]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    return S;
}



char* _rc4(char* key, char* message)
{
    int64_t *S = ksa(key);
    int64_t i = 0;
    int64_t j = 1;
    int64_t temp;
    int64_t k;
    char* cipher = malloc(strlen(message));
    for(int64_t counter = 0; counter < strlen(message); counter++)
    {
        i = (i+1) % 256;
        j = (j+S[i]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        k = S[((S[i]+S[j])%256)];

        cipher[counter] = message[counter] ^ k;
    }
    return cipher;
}

static PyObject*
rc4(PyObject* self, PyObject* args)
{
    char* key;
    char* message;


    if (!PyArg_ParseTuple(args, "ss", &key, &message))
        return NULL;

    char* cipher = _rc4(key, message);
    PyObject * return_value;
    return_value = PyString_FromString(cipher);
    free(cipher);
    return return_value;
}

static PyMethodDef RC4Methods[] =
{
    {"rc4", rc4, METH_VARARGS, "Calculate the Fibonacci numbers."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initrc4(void)
{
    (void) Py_InitModule("rc4", RC4Methods);
}
