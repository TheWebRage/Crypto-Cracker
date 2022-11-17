-------------------- Ecryption - David Weber - Version 2.0.1 -------------------- 


This new addition now has a setUID portion with a employee directory.
- The previous assignment is also in the main menu, but all new logic is found in the new menu item

In this database, you are able to view all records, but to modify you need the password. 
- The current password is "Toe" and can be changed in the modify menu.
- In the modify menu, you are able to add, edit, and delete records

These records are saved in a directory.txt file with 0644 permissions
- This means that anyone can view, but only root can modify

The password is saved in a password.txt file, but only root can read and modify. 
- Noone else has any permissions.

The root priviliges are only used for those two files. Nothing else is used by them.


-------------------- How to Compile -------------------- 

1. Create a "build" folder if it doesn't exist.
2. Change directory to the "build" folder.
3. Run "cmake .."
4. Run "make"
5. Finally, to execute the program, run "./Ecryption" to start and use. 


--------------------------------------------------------

NOTE: To make sure ownership stays after extracting, use the following command to extract:
- "sudo tar --same-owner -xvf ./SetUID.tar"

