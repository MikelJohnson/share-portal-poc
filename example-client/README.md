Example client
------
### Build instructions
1. cd into the qmake folder
2. qmake && make

### "Installation"
1. Change "/path/to/client" in .desktop to point to compile executable (you need to do this in five places).
2. Copy .desktop file to /usr/share/applications/

### Running the program
1. Run example-client. You will be presented an interface displaying contacts from "Contacts.json". feel free to fiddle with that file and change uuid/images/names.
2. At the bottom there are two buttons "Register dynamic targets" and "Clear dynamic targets" which will use the contacts to populate dynamic targets which will be send to the server.
3. The fun part comes when you actually share stuff to the client. use share-sender to try out sharing stuff to change your profile pic to a specific person or view the actual data as it was sent.
