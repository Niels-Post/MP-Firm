Changing and building the documentation
=========================================

Generating this documentation page is done using Doxygen and Sphinx, using Breathe to combine the two.
Should you want to make your own version of this page, this chapter explains how.

Requirements
""""""""""""""""

Before starting, you need the following.

- `Python 3 and Pip <https://www.python.org/downloads/>`_
- `Doxygen <https://www.doxygen.nl/download.html>`_

When both are installed, run the following to install the python packages required:

.. code-block:: bash

   cd docs
   pip install -r requirements.txt

After this, you should be ready to go

Changing the documentation
""""""""""""""""""""""""""""""

The main structure of the documentation is defined in ``docs/index.rst``. In here, multiple sections are included from ``docs/pages``.
All documentation is written in RestructuredText, with some extensions of it being added by sphinx and breathe.
While writing documentation, you can reference the following manuals:

- `Sphinx RST cheatsheet <https://thomas-cokelaer.info/tutorials/sphinx/rest_syntax.html>`_.
- `Breathe RST directives <https://breathe.readthedocs.io/en/latest/directives.html>`_.

Building the documentation
""""""""""""""""""""""""""""

To build the documentation, you need to execute two steps. Both of these steps need to be executed in the ``docs/`` folder.
These steps are automatically executed by ``docs/documentation.bat``

1. First, use doxygen to create the XML files Breathe uses to document code:

.. code-block:: bash

   doxygen Doxyfile

2. Next, generate the HTML pages using sphinx:

.. code-block:: bash

   sphinx-build -b html -Dbreathe_projects.MPFirm=xml "." "_build"

The documentation should now be generated in ``docs/_build``. To view the documentation, just open ``docs/_build/index.html``