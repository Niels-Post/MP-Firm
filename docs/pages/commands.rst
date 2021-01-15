Implemented Commands
======================

Below are the commands currently implemented in MP-firm as of January 2021.

--------------------

General Commands
-------------------

--------------------

REBOOT
^^^^^^^^^^^^
Performs a software reset on the robot.

**Parameters**

None

**Return Data**

None

------------------------

SET_ID
^^^^^^^^^^^^

Used to assign ID's to robots. The command is meant to be sent to all robots at once.
Robots will only respond in the following two cases:

- The robot has no id (ID 0) assigned. The robot responds with SUCCESS, and changes its ID to the one provided.
- The robot already has the requested ID. The robot responds with ID_ALREADY_SET, so the controller can connect mark the id as in use



**Parameters**

.. image:: /_static/SET_ID.png

**Return Data**

None



------------------

Action Commands
------------------

---------------

CANCEL_MOVEMENT
^^^^^^^^^^^^^^^^^^^

Stop all movement currently being processed by the robot.
Avoid this command as much as possible, since it also cancels any movement easing that would usually be performed.

**Parameters**

None

**Return Data**

None

-------------------

START_MOVE_MM
^^^^^^^^^^^^^^^^

Start a movement of a specified amount of millimeters forward or backward.


**Parameters**

.. image:: /_static/START_MOVE_MM.png

**Return Data**

None

-----------------------

START_ROTATE_DEGREES
^^^^^^^^^^^^^^^^^^^^^^

Start rotating a specified amount of degrees left (direction 0) or right (direction 1)

**Parameters**

.. image:: /_static/START_ROTATE_DEGREES.png

**Return Data**

None


Measurement Commands
--------------------------

-------------------------

GET_MEASUREMENT_RAW (unimplemented)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

-------------------------

GET_DISTANCE_SENSOR (unimplemented)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

--------------------------------

Configuration Commands
-------------------------

-------------------------------

SET_VALUE
^^^^^^^^^^^^^^

Set a configuration to a new value.
Note that depending on the type of the value, data may consist of more than one byte (see GET_INFO).

**Parameters**

.. image:: /_static/START_ROTATE_DEGREES.png

**Return Data**

None

-----------------


GET_VALUE
^^^^^^^^^^^^

Get the current value of a configuration.
Depending on the type of the value, return data length may vary (See GET_INFO).

**Parameters**

.. image:: /_static/GET_VALUE.png

**Return Data**


-------------------------

LOAD
^^^^^^^^^^^^

Reload all configuration values from the flash memory of the robot. The robot automatically does this at startup.

**Parameters**

None

**Return Data**

None

---------------------

STORE
^^^^^^^^^^

Store the current configuration values to the flash memory.

**Parameters**

None

**Return Data**

None

------------------------

PRINT_ALL
^^^^^^^^^^^^^^^^

Print the names of all configuration values. Note that printing happens on the robot, through its serial interface.

**Parameters**

None

**Return Data**

None

------------------------

GET_INFO
^^^^^^^^^^^^^^^^

Get the type and name of a configurationvalue.

Available Types:

- 'f': 4 byte floating point
- 'c': 1 byte unsigned integer
- 'i': 4 byte signed integer
- 'b': 1 byte boolean (only looks at the lsb)

**Parameters**

.. image:: /_static/GET_INFO.png

**Return Data**

.. image:: /_static/GET_INFO_RETURN.png

---------------------

GET_CONFIGURATION_COUNT
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the amount of configurationvalues that are used by the robot. It can be assumed that when the robot
has N configuration values, all configuration ids are between 1 and N.

**Parameters**

None

**Return Data**

.. image:: /_static/GET_CONFIGCOUNT_RETURN.png

