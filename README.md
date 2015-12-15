###########################################
# UnixViz
# Author: Kevin Clark - kac8dd@virginia.edu
###########################################

	UnixViz is a Qt based GUI application that was developed
	as part of a University of Virginia capstone project for
	the Bon Secours Enterprise Data Center team. It is released
	with a GPL license. 

	Build Steps
		
		-Linux
			A linux executable compiled for x86_64 is included in this repo,
			but it's not guaranteed to work for your particular setup. 
			To build the project yourself, first make sure you have the Qt 5 framework installed.
			See http://www.qt.io/download/ and your local package manager's website to
			ensure you've done this correctly. Next, pull the project from this repo, cd
			into its directory, and then issue the following commands

			~$ qmake
			~$ make
	
			An executable named UnixViz will now be in the current directory

		-Windows
			Building Qt projects from a Windows host is always finicky. You could do the Windows equivalent of
			the Linux steps above, but the easiest way to build UnixViz is to download the 
			Qt Creator IDE, import the project and then ask the framework to build it for you.

			See http://doc.qt.io/qt-5/windows-building.html for help installing Qt Creator on Windows

			See http://doc.qt.io/qt-5/windows-deployment.html for help compiling for Windows

	Unix_Master_Spreadsheet.xlsx
  
			UnixViz reads its data from a file named Unix_Master_Spreadsheet.xlsx. The excel file must
			reside in the same directory as the executable, but using hardlinks should remove any 
			inconvenience of this. The three resource types understood by UnixViz are HMCs, physical servers, 
			and LPARs. The required format is easily deduced from examining the spreadsheet.  

Public comments and development are encouraged
