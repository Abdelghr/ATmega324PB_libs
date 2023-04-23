# IPSA Space Systems (ISS)

IPSA Space Systems (ISS) is a student rocketry club, located within the aerospace engineering school IPSA (Location: Ivry-sur-Seine, France). The club designs and launches suborbital rockets whose goal is to act as demonstrators for new technologies, such as airbrakes control surfaces, and controlled descent under paragliders. The rockets are launched during the international launch campaign organized by the CNES and Planète Science, as an initiative for young students to get into the space industry.

ISS develops its own avionics in house, from the architecture and design, to the assembly, testing and integration. Most of our designs are purely digital, and require in-depth knowledge of microcontrollers, and familiarity with communication protocols and buses, ADC's, and other popular peripherals that are found on most microcontrollers.

Since the inception of the club in 2014, we have been using microcontrollers from the ATmega line developed by Microchip. An 8-bit family of microcontrollers, powerful enough to carry-out the mission specific tasks required by our projects. The similarities between the different microcontrollers of the ATmega line pushed us to develop low level drivers for several peripherals, that can be used as a reference for developing the low level drivers for other products of the line.


# ATmega324PB Peripherals Low-Level Drivers

This repository contains low-level drivers for the peripherals of the ATmega324PB microcontroller. These drivers should be easily portable to other AVR microcontrollers once a basic understanding is gained of the different peripherals and their functionalities. All the drivers are application specific and are not meant to take into account all the functionalities and modes of operation of the different peripherals.

The making of these drivers took place in the context of developing the embedded systems and control circuitries of multiple student made rockets at the student rocketry club ISS (IPSA Space Systems). The ATmega324PB µC was used in a rocket that was in development from September 2019 to July 2021 called IPER (ISS Parafoil Experimental Rocket), which is part of the CNES's PERSEUS project. The 3 meter rocket performed a nominal flight during the international launch campaign, C'Space, in July 2021. The development resumed on September 2021 in order to optimize and improve on the different aspects of the rocket.
