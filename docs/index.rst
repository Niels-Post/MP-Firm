MP-Firm
================================================

.. toctree::
   :maxdepth: 3
   :caption: Contents:


.. contents:: Table of Contents
    :depth: 3

.. role:: bash(code)
   :language: bash


Introduction
==================
This is the software documentation for the firmware for a moving platform robot built for the Warehouse PMSV project (link here).
This documentation is aimed at developers who want to extend the functionality of MP-Firm or adjust it to their own needs.
For instructions on how to use the firmware as-is, please refer to this instructable (todo).

The base version of MP-firm allows the following:

- **Movement** MP-firm can move the Moving Platform using standard stepper motor drivers (Any driver module using a step and direction pin)
- **Communication** A robot using MP-firm can wirelessly receive commands and transmit measurement through RF, using an NRF24l01.



Entity-Controller-Boundary
""""""""""""""""""""""""""""

MP-Firm is built in an object-oriented way using the Entity-Controller-Boundary (ECB) architecture. This means that classes are divided in 3 categories:

- *Entities* are objects meant for storing data. Entities have little to no knowledge of application logic.
- *Boundaries* are objects that interact with the user/environment. In the case of MP-Firm most boundaries are classes that control hardware components.
- *Controllers* are classes where actual application logic takes place. Controllers interact with entities and boundaries to make everything work together.

Because of this modularity, expanding MP-Firm to add functionality is rather easy. In the following few sections,
some use cases for expansions are explained, along with some short implementation examples.


Installation
================

All the code for MP-Firm is in the same repository. For compiling, uploading and managing dependencies, PlatformIO is used.
This means that the codebase should work cross-platform (not tested), and also makes installation rather straightforward:

1. `Install PlatformIO core <https://docs.platformio.org/en/latest/core/installation.html>`_
2. Clone the MP-Firm repository anywhere you like:

.. code-block:: bash

   git clone https://gitlab.ai.vub.ac.be/multi-agent-benchmarking/warehouse-pmsv-robot

3. Change into the code directory:

.. code-block:: bash

   cd warehouse-pmsv-robot

4. Install dependencies

.. code-block:: bash

   pio install

That's it!
When done modifying the code to your needs:

1. Plug in the robot through it's programming port (the USB port closes to the power jack)
2. Run the following to compile the code and upload it to the robot:

.. code-block:: bash

   pio run -t upload




Adding Custom Commands
========================
All commands in MP-firm are identified by the combination of a category ID (3 bits) and a command ID (5 bits).
The easiest way to add functionality to MP-firm is to create a new command category and add your custom commands to it.



Adding a category ID
""""""""""""""""""""""""

First, find a category ID that is not used yet. Category ID's are stored in ``include/entity/CommandData.hpp`` in the ``CommandCategory`` enum class.
Add your Category ID to the CommandCategory enum. For this example we'll add a command category FOOBAR = 4.

The result might look as follows:

.. code-block:: c++
   :linenos:

   enum class CommandCategory : uint8_t {
       GENERAL     = 0,
       ACTION      = 1,
       MEASUREMENT = 2,
       FOOBAR      = 4
   };

While editing this file, it is recommended to add an enum for the commands in your custom category.
For the example, our category only accepts two commands, so the enum may look like:

.. code-block:: c++
   :linenos:

   enum FooBarCommand {
       FOO = 0,
       BAR = 1,
   };

Creating a command handler
""""""""""""""""""""""""""""


After this, you need a way to handle commands in the category. This can be done by extending CommandCategoryController.
A CommandCategoryController has the following methods:

.. doxygenclass:: CommandCategoryController
   :members:
   :outline:


An example could be:

.. code-block:: c++
   :linenos:

   class FooBarCommandController: public CommandCategoryController {

      RobotMessage handle(const ControllerMessage &cmd) override {
         switch(static_cast<FooBarCommand>(cmd.command_id)) { // The
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

      // Both commands don't take data, but for the purpose of the instruction:
      std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override {
         switch(command_id) {
            case FOO:
               return {0,0};
            case BAR:
               return {0,0};
            default:
               return {255,255};
      }
   }


Adding the command handler to MP-Firm
""""""""""""""""""""""""""""""""""""""


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

All done! When you send a command with the category id 4, and the command id 1, the robot should print "Foo" over its USB interface.

Adding a communication method
==============================

By default, MP-Firm uses RF to communicate through an `NRF24l01 chip <https://www.nordicsemi.com/Products/Low-power-short-range-wireless/nRF24-series/>`_.
To make it easy to use different communication methods, MP-Firm has a boundary class called the MessageBoundary. This boundary is
responsible for all messages that are sent and received. To use a different communication method, you just need to create a MessageBoundary for it,
and make MP-Firm aware of it.

In the following example, we will be creating a MessageBoundary that uses the Arduino UART interface to communicate.
This could be used to receive and send commands over the USB interface.

Creating the MessageBoundary
""""""""""""""""""""""""""""""

The MessageBoundary has the following methods:

.. doxygenclass:: MessageBoundary
   :members:
   :outline:

An example of a USB MessageBoundary could be:


.. code-block:: c++
   :linenos:

   class UartMessageBoundary: public MessageBoundary {
      UARTClass &interface;

   public:
      UartMessageBoundary(UARTClass &anInterface);

   private:

      bool sendMessage(const RobotMessage &command) override{
         // Write all command data
         auto size_written = interface.write((const uint8_t *) (&command), command.size());
         // Check if the bytes written matches the command size to determine success
         return size_written == command.size();
      }

      bool isMessageAvailable() override() {
         // Check if there are enough bytes available for a command header
         return interface.available() >= 2;
      }

      ControllerMessage getNextMessage() override {
         uint8_t data[ControllerMessage::maxMessageSize() + 1];

         // Read the next command
         // Note that in this boundary, we use a ~ to indicate the end of a command,
         // This is because UART itself does not indicate ends of messages
         // We add one to the maximum message size, since the ~ also needs to be read
         size_t length = interface.readBytesUntil('~', data, ControllerMessage::maxMessageSize() + 1);

         // Parse the data.
         // If ill-formatted, parse() will automatically return an INVALID command.
         return ControllerMessage::parse(data, length);
      }
   };


Adding the created MessageBoundary to MP-firm
""""""""""""""""""""""""""""""""""""""""""""""""""

When the MessageBoundary is done, you just need to tell MP-firm to use it when communicating.
This is done in ``main.cpp``.

First, create the boundary object. In this case we also pass Arduino's ``Serial`` Object, to tell the boundary to use the standard Serial interface (USB).
While doing this, you could remove the MessageBoundary used before, since it is no longer needed.

.. code-block:: c++
   :linenos:

   UartMessageBoundary uartBoundary{Serial};

Finally, pass the created boundary to the CommunicationController during its construction.
Look up the following line:

.. code-block:: c++
   :linenos:

    CommunicationController<20, array_size(commandCategoryHandlers)> communicationController{nrfBoundary, commandCategoryHandlers};

Change it to use your boundary instead

.. code-block:: c++
   :linenos:

    CommunicationController<20, array_size(commandCategoryHandlers)> communicationController{uartBoundary, commandCategoryHandlers};


Creating your own documentation
======================================

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

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
