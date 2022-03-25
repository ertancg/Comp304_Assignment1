##How to run Problem 4:  
	1. Open terminal and swith your current directory to this one.  
	2. First run the make file by typing 'make' or 'make install' to the terminal.  
	3. The the compiled kernel module should be installed to the kernel. You have to have root permission to install or remove a kernel module.  
	4. Type 'sudo insmod my_module.ko' to terminal to install.  
	5. Check the kernel debug console by typing 'sudo dmesg' and find the 'Major= %d, Minor=%d' line to verify the module install.  
	6. Compile the test program by entering 'gcc test_app.c -o test_app' to the terminal.  
	7. Run the test program by entering './test_app' to the terminal and follow the instructions in the program.  
	8. After all the testing is done, module can be removed from the kernel by typing 'sudo rmmod my_module.ko'.  
	
