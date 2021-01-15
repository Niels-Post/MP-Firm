.. toctree::
   :maxdepth: 2
   :caption: Contents:

Extending MP-Firm
========================



Introduction
##################

This page gives information on how to get started extending the functionality of MP-Firm.

Adding a communication method
################################


By default, MP-Firm uses RF to communicate through an `NRF24l01 chip <https://www.nordicsemi.com/Products/Low-power-short-range-wireless/nRF24-series/>`_.
To make it easy to use different communication methods, MP-Firm has a boundary class called the CommunicationBoundary. This boundary is
responsible for all messages that are sent and received. To use a different communication method, you just need to create a CommunicationBoundary for it,
and make MP-Firm aware of it.

In the following example, we will be creating a CommunicationBoundary that uses the Arduino UART interface to communicate.
This could be used to receive and send commands over the USB interface.

Creating the MessageBoundary
""""""""""""""""""""""""""""""

A CommunicationBoundary has the following methods:

.. doxygenclass:: BaseCommunicationBoundary
   :members:
   :outline:

An example of a USB CommunicationBoundary could be:


.. code-block:: c++
   :linenos:

   class UartCommunicationBoundary: public MessageBoundary {
      UARTClass &interface;

   public:
      UartCommunicationBoundary(UARTClass &anInterface);

   private:

      bool sendMessage(const Response &command) override{
         // Write all command data
         auto size_written = interface.write((const uint8_t *) (&command), command.size());
         // Check if the bytes written matches the command size to determine success
         return size_written == command.size();
      }

      bool isMessageAvailable() override() {
         // Check if there are enough bytes available for a command header
         return interface.available() >= 2;
      }

      Command getNextMessage() override {
         uint8_t data[ControllerMessage::maxMessageSize() + 1];

         // Read the next command
         // Note that in this boundary, we use a ~ to indicate the end of a command,
         // This is because UART itself does not indicate ends of messages
         // We add one to the maximum message size, since the ~ also needs to be read
         size_t length = interface.readBytesUntil('~', data, ControllerMessage::maxMessageSize() + 1);

         // Parse the data.
         // If ill-formatted, parse() will automatically return an INVALID command.
         return Command::parse(data, length);
      }
   };


Adding the created CommunicationBoundary to MP-firm
""""""""""""""""""""""""""""""""""""""""""""""""""""""""

When the CommunicationBoundary is done, you just need to tell MP-firm to use it when communicating.
This is done in ``main.cpp``.

First, create the boundary object. In this case we also pass Arduino's ``Serial`` Object, to tell the boundary to use the standard Serial interface (USB).
While doing this, you could remove the CommunicationBoundary used before, since it is no longer needed.

.. code-block:: c++
   :linenos:

   UartCommunicationBoundary uartBoundary{Serial};

Finally, pass the created boundary to the CommunicationController during its construction.
Look up the following line:

.. code-block:: c++
   :linenos:

	CommunicationController communicationController{nrfBoundary, commandControllers, lengthof(commandControllers)};

Change it to use your boundary instead

.. code-block:: c++
   :linenos:

    CommunicationController communicationController{uartBoundary, commandControllers, lengthof(commandControllers)};





---------------------

Adding New Commands
################################

All commands in MP-firm are identified by the combination of a category ID (3 bits) and a command ID (5 bits).
The easiest way to add functionality to MP-firm is to create a new command category and add your custom commands to it.
This chapter describes the process for this.



Adding a category ID
""""""""""""""""""""""""

First, find a category ID that is not used yet. Category ID's are stored in ``include/communication/CommandRegistry.hpp`` in the ``CommandCategory`` enum class.
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
This enum can later be used to easily check which command was sent.

For the example, our category only accepts two commands, so the enum may look like:

.. code-block:: c++
   :linenos:

   enum FooBarCommand {
       FOO = 0,
       BAR = 1,
   };

Creating a command controller
""""""""""""""""""""""""""""""""


After this, you need a way to handle commands in the category. This can be done by extending BaseCommandController.
A CommandController has the following methods:

.. doxygenclass:: BaseCommandController
   :members:
   :outline:


An example could be:

.. code-block:: c++
   :linenos:

   class CommandController_FooBar: public BaseCommandController {

      RobotMessage handle(const Command &cmd) override {
         switch(static_cast<FooBarCommand>(cmd.command_id)) { // The
            case 1: // Print Foo when command 1 was issued
               Serial.println("Foo");
               break;
            case 2: // Print Bar when command 1 was issued
               Serial.println("Bar");
               break;
            default: // Unknown command; Return an error code
               return Response(cmd.message_id, SuccessCode::UNKNOWN_COMMAND);
         }
         return Response(cmd.message_id, SuccessCode::SUCCESS);
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


When the CommandController is implemented, you just need to make MP-firm aware of it.
This can be done in main.cpp, using the following steps:

Construct the freshly built Controller in setup:

.. code-block:: c++
   :linenos:

   CommandController_FooBar foobarCommandController{};


Add it to the CommandCategoryHandlers array:

.. code-block:: c++
   :linenos:

   std::reference_wrapper<BaseCommandController> commandControllers[] = {
               generalCommandHandler,
               actionCommandHandler,
               measurementCommandHandler,
               configurationCommandController,
               foobarCommandController
       };

All done! When you send a command with the category id 4, and the command id 1, the robot should print "Foo" over its USB interface.


---------------------

Adding Configuration Values
################################

When adding new functionality, you should consider using a configuration struct to store its settings. When using
a configuration struct, and defining it in the main, it can easily be changed wirelessly through Configuration Commands.

To add a setting as value configuration, add it to the main. In this example we will be adding configuration values for
a hypothetical distance sensor. The Configuration struct is as follows:

.. code-block:: c++
	:linenos:

	struct DistanceSensorConfiguration {
		uint8_t pin_out;
		uint8_t pin_in;
		float some_multiplication_factor;
	}


To add all values as configuration values, first initialize a single instance in main.cpp:

.. code-block:: c++
	:linenos:

	DistanceSensorConfiguration mainDistanceSensorConfiguration { 14, 15, 0.85 };


Next, we need to register all values as configuration values. By calling registerConfig, we give each value a name,
and allocate enough flash memory for it. registerConfig also generates a config_id for it. Make sure that each name
you choose is unique within the project.

.. code-block:: c++
	:linenos:

	auto c_mainDistanceSensor_pOut = registerConfig("MAIN_DISTANCESENSOR_PIN_OUT", mainDistanceSensorConfiguration.pin_out);
	auto c_mainDistanceSensor_pIn  = registerConfig("MAIN_DISTANCESENSOR_PIN_IN", mainDistanceSensorConfiguration.pin_in);
	auto c_mainDistanceSensor_mult = registerConfig("MAIN_DISTANCESENSOR_MULT", mainDistanceSensorConfiguration.some_multiplication_factor);


The last thing we need to do is add the ConfigurationValues to the ConfigurationController. We can do this by adding the values
to the configurationValues array, also in main.cpp:

.. code-block:: c++
	:linenos:

	std::reference_wrapper<BaseConfigurationValue> configurationValues[]{
	        .......,
	        c_mainDistanceSensor_pOut,
	        c_mainDistanceSensor_pIn,
	        c_mainDistanceSensor_mult,
	};

