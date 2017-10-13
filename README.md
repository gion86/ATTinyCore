# ATTinyCore

Atmel ATTiny core taken from <https://github.com/SpenceKonde/ATTinyCore/>: **all credits to the author**.

------------------------------------------------------------

Changes:

*   added core_build_options.h to compile for different Atmel MCU; 
*   modified pins_aurdino.h to include ATTinyX4 an ATTinyX5 configuration;
*   the #define \_\_AVR\_ATtinyX4\_\_ and \_\_AVR\_ATtinyX5\_\_ come from Eclipse AVR plugin configuration;
*   added Link-time optimization options in Eclispe progect configuration.
*   added new() operator. 
*   removed unused source files;
