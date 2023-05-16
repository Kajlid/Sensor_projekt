import processing.net.*; 
import processing.serial.*;
Client otherNode;
Serial inoPort; 
boolean firstContact = false;
String val;
String IP_addres ="";

void setup() { 
  //size (300, 100);
  otherNode = new Client(this, IP_addres, 5204);
  
  String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
  
  // println(portName);
  inoPort = new Serial(this, portName, 9600);
  inoPort.bufferUntil('\n');
}




void draw(){


}







void serialEvent( Serial inoPort){
 
val = inoPort.readStringUntil('\n');
//make sure our data isn't empty before continuing
if (val != null) {
  //trim whitespace and formatting characters (like carriage return)
  val = trim(val);
  println(val);

  //look for our 'A' string to start the handshake
  //if it's there, clear the buffer, and send a request for data
  if (firstContact == false) {
    if (val.equals("A")) {
      inoPort.clear();
      firstContact = true;
      inoPort.write("A");
      println("contact");
    }
  }
  else { //if we've already established contact, keep getting and parsing data
    

    //if (mousePressed == true) 
    //{                           //if we clicked in the window
      //myPort.write('1');        //send a 1
      //println("1");
    //}

    // when you've parsed the data you have, ask for more:
    //myPort.write("A");
    }
  }
}

void clientEvent(Client client) {
  
  String from_server = client.readString(); // The argument client is the node that has sent this node a message.
  println("received from " + client.ip() + "'" + val + "'"); // Print the message for debugging
  // TODO use the new received data to do something
  

  //client.write(val_arduino); // Send the other node (client). We assume that the client expects a string.

}
