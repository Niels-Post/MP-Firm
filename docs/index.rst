MP-Firm
============


Introduction
##############
This is the software documentation for the firmware for a moving platform robot built for the Warehouse PMSV project.
The build process, and installation process for the robot and for the controller software can be found in `this <https://www.instructables.com/Building-a-Moving-Platform-Robot-From-Scratch>`_ instructable.

These documentation pages aim to give a more in-depth view in how MP-Firm works, and what it can do.

The base version of MP-firm curently allows the following:

- **Movement** MP-firm can move the Moving Platform using standard stepper motor drivers (Any driver module using a step and direction pin)
- **Communication** A robot using MP-firm can wirelessly receive commands and transmit measurement through RF, using an NRF24l01.
- **Configuration** Wirelessly setting and retrieving values, and storing them in the flash memory across reboots.




.. toctree::
   :maxdepth: 2
   :caption: Contents:

   ./pages/general
   ./pages/installation
   ./pages/commands
   ./pages/extending_mpfirm
   ./pages/editing_and_building_documentation





.. role:: bash(code)
   :language: bash







Indices and tables
####################

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
