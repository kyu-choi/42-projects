*This project has been created as part of the 42 curriculum by kyu-choi.*

# NetPractice

## Description

NetPractice is a project from the 42 curriculum designed to introduce
the fundamentals of computer networking.

The goal of this project is to understand how network communication
works by configuring and fixing broken network setups. Each exercise
presents a network diagram that does not function correctly. The task is
to modify the configuration so that all devices in the network can
communicate properly.

During this project, we learn how to configure and understand:

* IP addresses
* Subnet masks
* Default gateways
* Routers and switches
* Basic routing concepts

The project consists of 10 levels. Each level requires analyzing the
network topology and correcting the configuration so that the network
becomes functional.

---

## Instructions

### Running the NetPractice Interface

First download the NetPractice project files and extract them.

Run the following command inside the project directory:

```bash
./run.sh
```

This script launches a local web server and opens the NetPractice
interface in your web browser.

If the script does not work, you can start the web server manually:

```bash
python3 -m http.server 49242
```

Then open your browser and go to:

```text
http://localhost:49242
```

Enter your **intra login** to load your personal configuration.

### Solving the Exercises

The training interface provides **10 networking levels**.

For each level:

1. Analyze the network diagram
2. Identify incorrect IP configurations
3. Fix subnet masks if necessary
4. Correct default gateway settings
5. Verify the configuration by clicking **Check again**

If the configuration is correct, the network will become functional.

### Exporting Configuration Files

Once a level is successfully completed, export the configuration file
using the **Get my config** button.

This will download the configuration file for that level.

You must export and keep the configuration file for **each level**.

---

## Submission

To submit the project, you must include **10 exported configuration
files**, one for each level.

All files must be placed at the **root of your Git repository**.

Example repository structure:

```text
.
├── level1.json
├── level2.json
├── level3.json
├── level4.json
├── level5.json
├── level6.json
├── level7.json
├── level8.json
├── level9.json
├── level10.json
└── README.md
```

Only the files present in the repository will be evaluated.

During the defense, you will also be required to solve **three random
levels** within a limited time.

---

## Networking Concepts Learned

This project focuses on several important networking concepts:

* TCP/IP addressing
* Subnet masks
* Default gateways
* Router interfaces
* Network routing
* Communication between different networks
* Basic understanding of the OSI model

Understanding how IP addressing and subnetting work is essential to
successfully complete the exercises.

---

## Resources

The following methods were used to study networking concepts:

* Internet search for networking-related materials
* Using AI question-and-answer tools to support understanding and concept review

These approaches helped reinforce the understanding of IP addressing,
subnet masks, routing, and network communication.

---

## AI Usage

AI tools were used during this project to assist with:

* Summarizing networking concepts
* Understanding subnetting and routing explanations
* Writing and structuring documentation for the README file

All generated content was reviewed and fully understood before being
included in this project.

