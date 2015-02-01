#include <stdio.h>
#include <Python.h>
#include <chibi/eval.h>

static PyObject *PyChibiError;

int execute_scheme(sexp ctx, const char* expression) {

  /* declare and preserve local variables */
  sexp_gc_var2(obj1, obj2);
  sexp_gc_preserve2(ctx, obj1, obj2);

  /* load a file containing Scheme code */
  //obj1 = sexp_c_string(ctx, "hello.scm", -1);
  //sexp_load(ctx, obj1, NULL);

  /* eval a C string as Scheme code */
  obj1 = sexp_eval_string(ctx, expression, -1, NULL);

  /* construct a Scheme expression to eval */
  //obj1 = sexp_intern(ctx, "my-procedure", -1);
  //obj2 = sexp_cons(ctx, obj1, SEXP_NULL);
  //sexp_eval(ctx, obj2, NULL);
  
  int result = 0; 
  if sexp_integerp(obj1) {
      result = sexp_unbox_fixnum(obj1);
  }

  sexp_gc_release2(ctx);
  return result;
}


static PyObject *
pychibi(PyObject *self, PyObject *args)
{
    sexp ctx;
    ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
    sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);
    sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 1);

    const char *expression;
    int result = 0;

    if (!PyArg_ParseTuple(args, "s", &expression))
        return NULL;
    result = execute_scheme(ctx, expression);
    sexp_destroy_context(ctx);
    return Py_BuildValue("i", result);
}


static PyMethodDef PyChibiMethods[] = {
    {"eval",  pychibi, METH_VARARGS,
     "Execute scheme"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


PyMODINIT_FUNC
init_chibi_scheme(void)
{
    PyObject *m;

    m = Py_InitModule("_chibi_scheme", PyChibiMethods);
    if (m == NULL)
        return;

    PyChibiError = PyErr_NewException("pychibi.error", NULL, NULL);
    Py_INCREF(PyChibiError);
    PyModule_AddObject(m, "error", PyChibiError);
}


