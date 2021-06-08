# DAMBIEngine
<div align="center">
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/Dmabi.png"><br><br>
</div>

-----------------

Introduction
-----------------
  **Dambi Engine** is an Open Source SW Project for Game server architecture. **Dambi Engine** provides architecture to help users to make fast-working server through some techniques. **Dambi Engine** uses standard C++ libraries and Window APIs to make sure of stable environment.
  
* There are Several techniques we used.
  
  * Multi-Threading - Divided functions by their features. It helps program works more faster.
 
  * IOCP - Windows I/O model with great performance.
 
  * Lock-free Queue - C++ template libraries for multi-core processor.
 
 What can I do with Dambi?
-----------------
**Dambi Engine** provides basic game server architecture with several threads and objects. Users can build server with adding additional features everything they need and accept their clients through their customized server environment.
 
-----------------
If You want to check out more details about our project, Please read our [Proposal Report](CONTRIBUTING.md)

-----------------

Installation
-----------------
Dmabi engine is a framework working on **Window OS** and **Standard C++** in visual studio IDE.

Plaese download the project and build through IDE.

* Check all the header and source files are in the right folder
<div align="left">
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/files.PNG"><br><br>
</div>

* To use Lock-free queue provided by intel open source, Please download the [tbb](https://github.com/oneapi-src/oneTBB) and add to external libraries.
<div align="left">
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install1.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install2.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install3.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install4.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install5.png"><br><br>
</div>

* Build a project to make .exe file
<img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install6.png"><br><br>


Support
-----------------

License
-----------------
Dmabi Endine is licensed under [Apache License, Version 2.0.](https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/LICENSE). By its terms, contributions submitted to the project are also done under that license.
