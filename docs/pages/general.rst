General
=====================

This page is meant to give an insight in how the control flow for MP-Firm works, and how MP-Firm is operated in general.


Entity-Controller-Boundary
-----------------------------

MP-Firm is built in an object-oriented way using the Entity-Controller-Boundary (ECB) architecture. ECB resembles Model View Controller
for those who worked with it. This means that classes are divided in 3 categories:

- *Entities* are objects meant for storing data. Entities have little to no knowledge of application logic.
- *Boundaries* are objects that interact with the user/environment. In the case of MP-Firm most boundaries are classes that control hardware components.
- *Controllers* are classes where actual application logic takes place. Controllers interact with entities and boundaries to make everything work together.

In MP-firm, a controller is responsible for managing a certain type of action (e.g. movement or configuration). It
uses boundaries to perform the action (e.g. Motor boundary or FlashStorage boundary). When designed correctly,
this means that when swapping components for other components,
only the boundary objects have to be replaced, and not the entire programmed logic of the action.



Control Flow
--------------

MP-Firm works by using an event loop in its main() function. This eventloop should continuously call update() on those controllers
that require continuous updates. This is needed for example, for the movementcontroller, since it drives motors, which may need
to have their step pin driven all the time when moving.





Communication
----------------

When communicating with the robot, the robot should (almost) never have initiative. A "Command" can be sent to the robot, which it responds
to with a "Response", but never the other way around.

Each command has a message id, which the robot also puts in the Response. This way the sender can keep track of which responses
belong to which commands.

A command should usually only yield one response. However, when actions are known to take more time, the robot can
respond with successcode ACTION_STARTED, to indicate that it has started processing the command, and
the actual response will come later.

All commands are received through the CommunicationController. It receives Commands, dispatches them to the corresponding Controller, and sends a response.
For processing, a special type of Controller is used; The CommandController. A CommandController is responsible for processing
a command in one specific command category. When a message in the specified category is received, the CommunicationController calls handle()
on the CommandController. The CommandController should then execute the action using the right controller, and return the Response.

Below is a flowchart for the processing and executing of commands (click to zoom).


.. image:: /_static/FlowDiagram_Communication.png
	:target: ../_static/FlowDiagram_Communication.png



Configuration Values
-----------------------

All parts of the firmware use configuration values to store their settings. Through configuration values, these
settings can be written to flash memory, so that they will be restored at the next reboot. All configuration values are
collected in an array, and passed to the Configuration CommandController. When using configuration values, the value they point
to will be the initial value of it. After this, the value can be changed through the SET_VALUE command, and then stored to flash
using STORE.