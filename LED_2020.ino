
int led_pins[] = {3, 5, 6};
int led_vals[] = {0, 0, 0};
String incoming = "";

int r, g, b;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps
  // configure led pins
  for(int i = 0; i < sizeof(led_pins) ; i++){
    pinMode(led_pins[i], OUTPUT);
  }
}

// filler method for rainbow mode
void do_rainbow(){
  Serial.println("Rainbowing");
}

// parses hex string into rgb values, stores those values in led_vals
void parse_str(String str){  
  String r_str = str.substring(0, 2);
  String g_str = str.substring(2, 4);
  String b_str = str.substring(4, 6);
  
  sscanf(r_str.c_str(), "%02x", &r);
  sscanf(g_str.c_str(), "%02x", &g);
  sscanf(b_str.c_str(), "%02x", &b);
  
  led_vals[0] = r;
  led_vals[1] = g;
  led_vals[2] = b;

}

// use parsed rgb-values as analog signals for MOSFETs
void set_led_vals(){
  for(int i = 0; i < sizeof(led_pins); i++){
    analogWrite(led_pins[i], led_vals[i]);
  }
}
void Main(){
  if(Serial.available() > 0){
    Serial.write("OK");
    incoming = Serial.readString();    
    if(incoming.length() == 8){ // "RAINBOW" str is also null terminated, so it will have length of 7 plus one for the null-term. character/
      do_rainbow();
    } else if(incoming.length() == 7){ // Hex string is length 6, plus one since it is null-terminated.
      parse_str(incoming);
      set_led_vals();
    } else {
      Serial.println("Gibberish");
    }
  }
  
}

void loop() {
  Main();
}
