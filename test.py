#!/usr/bin/env python
import _chibi_scheme

e1 = """
(begin
   (display "Hello, World! --")
   (newline)
   (display "foo")
   (newline))
"""

_chibi_scheme.eval(e1)

