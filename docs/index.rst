.. PMSV Warehouse Robot documentation master file, created by
   sphinx-quickstart on Tue Oct 27 13:49:22 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to PMSV Warehouse Robot's documentation!
================================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

Communication
==================

.. doxygenclass:: CommunicationController
   :members:
   :protected-members:

Commands
-------------------

.. doxygenstruct:: Command
   :members:

.. doxygenstruct:: ReturnCommand
   :members:

Handlers
-------------------

.. doxygenclass:: CommandHandler
   :members:

.. doxygenclass:: GeneralCommandHandler
   :members:

.. doxygenclass:: ActionCommandHandler
   :members:

.. doxygenclass:: MeasurementCommandHandler
   :members:

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
