# cli_linux_phonebook
This is a CLI Phonebook for linux
This program only works on Linux PCs

Installation:
1. Download ph_012.c file
2. Compile it with cc ph_012.c -o phonebook
3. Copy phonebook file to /bin directory with cp phonebook /bin/phonebook
4. Create /home/phonebook directory with mkdir /home/phonebook

Usage:
phonebook add <name> <number> - add person with name <name> and number <number>
phonebook name <name> - print number of person with name <name>
phonebook number <number> - print a name list of peuples with number <number>
phonebook delate <name> - delate person with name <name>
phonebook changenum <name> <number> - change number to <number> for person with name <name>
