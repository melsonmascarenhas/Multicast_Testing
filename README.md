# Multicast Communication

This repository contains example code for multicast communication in C. It includes a sender and receiver program that use multicast groups to send and receive messages.

**Features**
- Customizable Multicast Group IP: The default multicast group IP can be set between 224.0.0.1 and 239.255.255.255.
- Customizable Multicast Port: The default multicast port is 3000, but you can modify it to your desired port.
- Simple Compilation and Execution: Easily compile and run the sender and receiver programs.

**Files in this Repository**
- sender.c: The sender program to broadcast messages to the multicast group.
- recieve.c: The receiver program to listen to messages from the multicast group.

**How to Compile**
To compile the programs, use the gcc compiler as follows:

> gcc sender.c -o sender
> gcc recieve.c -o recieve

**How to Run**
Run the Receiver: Start the receiver program to listen to a specific multicast group and port.

> ./recieve

Run the Sender: Use the sender program to send messages to the multicast group.

> ./sender