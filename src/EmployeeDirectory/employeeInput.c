#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "directoryCRUD.c"

void modyifyDirectoryMenu () {

  /* Give these options: Add, Edit, Delete, Change Password */
  int choice = getIntInput("\n\n----- Modify Employee Directory -----\n1. Add\n2. Edit\n3. Delete\n4. Change Password\n5. Cancel\n\nChoose an option: ");

  switch (choice)
  {
    case 1:;
      addEmployee ();
      break;

    case 2:;
      editEmployee ();
      break;

    case 3:;
      deleteEmployee ();
      break;

    case 4:;
      changePassword ();
      break;

    case 5:
      return;

    default:
      printf ("Invalid Option. Choose a number shown.\n");
      break;
  }
}

void employeeDirectoryStart () {

  /* TODO: change permissions to be admin only read write */

  int choice = 0;

  do {
    choice = getIntInput("\n\n----- Employee Directory -----\n1. Read\n2. Modify\n3. Main Menu\n\nChoose an option: ");

    switch (choice)
    {
    /* Read */
    case 1:;
      displayEmployees ();
      break;

    /* Modify - Requires Password for Admin Access */
    case 2:;
      if (isPasswordValid ())
        modyifyDirectoryMenu ();
      break;

    case 3:
      return;

    default:
      printf ("Invalid Option. Choose a number shown.\n");
      break;
    }

  } while (choice != 3);

}

/*
//  Ask user if they want to modify or view an employee directory
// - If modify, then they need to give the password
// - Modifying includes adding editing or deleting
// - Viewing the directory just output the directory to a screen
// - Also ask the user if they want to modify the password

// The directyory is stopred in a file called directory.txt
// - permissions set to 644
// - Set the owner as root

// If the directory does not exist, then create it
// - CSV file one record per line
// - Cols: last_name, first_name, position, employee_id_number,
telephone_number

// Program does not exit unless specified

// Compile as user and then change group (chgrp root) then change
permissions to 4555
*/