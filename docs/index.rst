.. MP-Firm documentation master file, created by
   sphinx-quickstart on Tue Oct 27 13:49:22 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

MP-Firm
================================================

.. toctree::
   :maxdepth: 3
   :caption: Contents:

Introduction
==================
This is the software documentation for the firmware for a moving platform robot built for the Warehouse PMSV project (link here).
This page is aimed at developers who want to extend the functionality of MP-Firm or adjust it to their own needs. For instructions on how to use the firmware as-is, please refer to this instructable (todo).

MP-Firm is built in an object-oriented way using the Entity-Controller-Boundary (ECB) architecture. This means that classes are divided in 3 categories:

- *Entities* are objects meant for storing data. Entities have little to no knowledge of application logic.
- *Boundaries* are objects that interact with the user/environment. In the case of MP-Firm most boundaries are classes that control hardware components.
- *Controllers* are classes where actual application logic takes place. Controllers interact with entities and boundaries to make everything work together.

Because of this modularity, expanding MP-Firm to add functionality is rather easy. In the following few sections,
some use cases for expansions are explained, along with some short implementation examples.

Extending MP-Firm
====================

Adding Custom Commands
------------------------

All commands in MP-firm consist of a category ID (3 bits) and a command ID (5 bits).
When adding commands, it is easiest to define a custom category for it.

Adding a category ID
^^^^^^^^^^^^^^^^^^^^^^

First, find a category ID that is not used yet. Category ID's are stored in ``include/entity/CommandData.hpp``.
Add your Category ID to the CommandCategory enum. For this example we'll add a command category FOOBAR = 4.

Creating a command handler
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After this, you need a way to handle commands in the category. This can be done by extending CommandCategoryController.
An example could be:

.. code-block:: c++
   :linenos:

   class FooBarCommandController: public CommandCategoryController {

      RobotMessage handle(const ControllerMessage &cmd) override {
         switch(cmd.command_id) {
            case 1: // Print Foo when command 1 was issued
               Serial.println("Foo");
               break;
            case 2: // Print Bar when command 1 was issued
               Serial.println("Bar");
               break;
            default: // Unknown command; Return an error code
               return RobotMessage(cmd.message_id, SuccessCode::UNKNOWN_COMMAND);
         }
         return RobotMessage(cmd.message_id, SuccessCode::SUCCESS);
      }

      uint8_t getCategoryID() override {
         return static_cast<uint8_t>(CommandCategory::FOOBAR);
      }
   }


Adding the command handler to MP-Firm
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When the CommandCategoryController is implemented, you just need to make MP-firm aware of it.
This can be done in main.cpp, using the following steps:

Construct the freshly built Controller in setup:

.. code-block:: c++
   :linenos:

   FooBarCommandController foobarCommandController{};


Add it to the CommandCategoryHandlers array:

.. code-block:: c++
   :linenos:

   CommandCategoryController *commandCategoryHandlers[] = {
            &generalCommandHandler,
            &actionCommandHandler,
            &measurementCommandHandler,
            &foobarCommandController
    };

All done! When you send a command with the category id 4, and the command id 1, the robot should send "Foo" over its USB interface.





Communication
==================

.. doxygenclass:: CommunicationController
   :members:
   :protected-members:

Commands
-------------------

.. doxygenstruct:: ControllerMessage
   :members:

.. doxygenstruct:: RobotMessage
   :members:

Handlers
-------------------

.. doxygenclass:: CommandCategoryController
   :members:

.. doxygenclass:: GeneralCommandController
   :members:

.. doxygenclass:: ActionCommandController
   :members:

.. doxygenclass:: MeasurementCommandController
   :members:

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
