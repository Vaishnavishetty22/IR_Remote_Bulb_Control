IRrecv irrecv(RECV_PIN);
decode_results results;

// Variables to keep track of bulb state
bool bulbState = false;

// Define your remote button codes (replace with actual values from your remote)
const unsigned long BUTTON_ON_OFF = 0xFFFFFFFF; // Example code for ON/OFF button
const unsigned long BUTTON_ANOTHER = 0x2BD83F32; // Example code for another button

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize IR receiver
  irrecv.enableIRIn();
  
  // Initialize relay pin as an output
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure relay is off initially
}

void loop() {
  // Check if an IR signal is received
  if (irrecv.decode(&results)) {
    // Print the received value in HEX format for debugging
    Serial.println(results.value, HEX);

    // Handle received IR codes
    handleIRCode(results.value);

    // Resume the IR receiver to receive the next value
    irrecv.resume();
  }
}

// Function to handle IR codes
void handleIRCode(unsigned long code) {
  switch (code) {
    case BUTTON_ON_OFF:
      toggleBulb();
      break;
      
    case BUTTON_ANOTHER:
      // Add functionality for another button here
      break;

    // Add more cases for other buttons as needed

    default:
      Serial.println("Unknown IR code received");
      break;
  }
}

// Function to toggle the bulb state
void toggleBulb() {
  bulbState = !bulbState; // Toggle bulb state
  digitalWrite(RELAY_PIN, bulbState ? HIGH : LOW); // Set relay state
  Serial.print("Bulb state: ");
  Serial.println(bulbState ? "ON" : "OFF");