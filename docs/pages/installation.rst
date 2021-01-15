Installation
===============

All code for MP-Firm is in the same repository. For compiling, uploading and managing dependencies, PlatformIO is used.
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

1. Plug in the robot through it's programming port (the USB port closest to the power jack)
2. Run the following to compile the code and upload it to the robot:

.. code-block:: bash

   pio run -t upload




..
	Bitbang_I2C
    ##############
	At the time of writing, the builds will likely fail. A small adjustment needs to be made in a library dependency.
	To do this, open the following file:
	`.pio/libdeps/due/Bitbang_I2C/src/BitBang_I2C.cpp`
	Adjust the following line (linenr 559 for me)
	.. code-block:: cpp
		#if defined(TEENSYDUINO) || defined( __AVR__ ) || defined( NRF52 ) || defined ( ARDUINO_ARCH_NRF52840 )
	Add the following to the end of it (including the ||):
	.. code-block:: cpp
		|| defined(ARDUINO_ARCH_SAM)
	After this, building should succeed.

